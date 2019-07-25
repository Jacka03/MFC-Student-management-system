
// StudentInfoDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "StudentInfo.h"
#include "StudentInfoDlg.h"
#include "afxdialogex.h"
#include"Student.h"
#include"Management.h"
#include"cstring"
#include"iostream"
#include"ostream"
#include <algorithm>

using namespace std;

int num = 0;


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CStudentInfoDlg 对话框



CStudentInfoDlg::CStudentInfoDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_STUDENTINFO_DIALOG, pParent)
	, m_id(_T(""))
	, m_name(_T(""))
	, m_age(_T(""))
	, m_address(_T(""))
	, m_math(_T(""))
	, m_cpulspuls(_T(""))
	, m_Sex(-1)
	, m_StuNum(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
	m_dwPos = 0;
}

void CStudentInfoDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST1, m_ListControl);
	DDX_Control(pDX, IDC_EDIT_ID, m_ID);
	DDX_Text(pDX, IDC_EDIT_ID, m_id);
	DDX_Control(pDX, IDC_EDIT_NAME, m_NAME);
	DDX_Text(pDX, IDC_EDIT_NAME, m_name);
	DDX_Control(pDX, IDC_EDIT_AGE, m_AGE);
	DDX_Text(pDX, IDC_EDIT_AGE, m_age);
	DDX_Control(pDX, IDC_EDIT_ADDRESS, m_ADDRESS);
	DDX_Text(pDX, IDC_EDIT_ADDRESS, m_address);
	DDX_Control(pDX, IDC_EDIT_MATH, m_MATH);
	DDX_Text(pDX, IDC_EDIT_MATH, m_math);
	DDX_Control(pDX, IDC_EDIT_CPULS_PULS, m_CPULSPULS);
	DDX_Text(pDX, IDC_EDIT_CPULS_PULS, m_cpulspuls);
	DDX_Radio(pDX, IDC_RADIO1, m_Sex);
	//  DDX_Text(pDX, IDC_EDIT1, stuNum);
	DDX_Text(pDX, IDC_EDIT1, m_StuNum);
}

BEGIN_MESSAGE_MAP(CStudentInfoDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_NOTIFY(LVN_ITEMCHANGED, IDC_LIST1, &CStudentInfoDlg::OnLvnItemchangedList1)
	ON_BN_CLICKED(IDOK, &CStudentInfoDlg::OnBnClickedOk)
	ON_EN_CHANGE(IDC_EDIT_ID, &CStudentInfoDlg::OnEnChangeEditId)
	ON_BN_CLICKED(IDC_BUTTON_ADD, &CStudentInfoDlg::OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_SAVE, &CStudentInfoDlg::OnBnClickedButtonSave)
	ON_BN_CLICKED(IDC_BUTTON_DELETE, &CStudentInfoDlg::OnBnClickedButtonDelete)
	ON_BN_CLICKED(IDC_BUTTON_CHANGE, &CStudentInfoDlg::OnBnClickedButtonChange)
	ON_BN_CLICKED(IDC_BUTTON_SORT_BY_MATH, &CStudentInfoDlg::OnBnClickedButtonSortByMath)
	ON_BN_CLICKED(IDC_BUTTO_SORT_BY_CPP, &CStudentInfoDlg::OnBnClickedButtoSortByCpp)
	ON_BN_CLICKED(IDC_BUTTO_SORT_BY_ID, &CStudentInfoDlg::OnBnClickedButtoSortById)
END_MESSAGE_MAP()


// CStudentInfoDlg 消息处理程序

BOOL CStudentInfoDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	CListCtrl* pmyListCtrl = (CListCtrl*)GetDlgItem(IDC_LIST1); //获取列表控件
	DWORD dwStyle = GetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE);  //获取当前风格
	SetWindowLong(pmyListCtrl->m_hWnd, GWL_STYLE, dwStyle | LVS_REPORT);  //设计风格
	DWORD styles = pmyListCtrl->GetExtendedStyle();
	pmyListCtrl->SetExtendedStyle(styles | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES);//设置选择listctrl整行高亮和网格条纹
	CRect rect;
	pmyListCtrl->GetWindowRect(&rect);  //该函数返回指定窗口的边框矩形的尺寸

	m_ListControl.InsertColumn(0, _T("保留"), LVCFMT_CENTER);   //初始化List Control
	m_ListControl.InsertColumn(1, _T("学号"), LVCFMT_CENTER, 100);  //将List control划分，中间对齐
	m_ListControl.InsertColumn(2, _T("姓名"), LVCFMT_CENTER, 90);
	m_ListControl.InsertColumn(3, _T("性别"), LVCFMT_CENTER, 42);
	m_ListControl.InsertColumn(4, _T("年龄"), LVCFMT_CENTER, 42);
	m_ListControl.InsertColumn(5, _T("高数成绩"), LVCFMT_CENTER, 72);
	m_ListControl.InsertColumn(6, _T("C++成绩"), LVCFMT_CENTER, 74);
	m_ListControl.InsertColumn(7, _T("地址"), LVCFMT_CENTER, 220);
	m_ListControl.DeleteColumn(0);                    //删除第0列，确保第一列为居中（
	UpdateData(TRUE);

	GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
	GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);

	CFile file;
	file.Open(_T("C:\\student.dat"), CFile::modeRead | CFile::shareDenyNone);//);
	student stu;
	int i = 0;
	while (file.Read(&stu, sizeof(stu)) == sizeof(stu))
	{
		m_ListControl.InsertItem(i, (LPCTSTR)stu.id);
		m_ListControl.SetItemText(i, 1, (LPCTSTR)stu.name);
		m_ListControl.SetItemText(i, 2, (LPCTSTR)stu.age);
		m_ListControl.SetItemText(i, 3, (LPCTSTR)stu.sex);
		m_ListControl.SetItemText(i, 4, (LPCTSTR)stu.math);
		m_ListControl.SetItemText(i, 5, (LPCTSTR)stu.cpp);
		m_ListControl.SetItemText(i, 6, (LPCTSTR)stu.address);
		i++;
	}
	UpdateData(TRUE);
	file.Close();
	m_StuNum = m_ListControl.GetItemCount();   //
	UpdateData(FALSE);
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CStudentInfoDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CStudentInfoDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文
		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);
		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;
		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CStudentInfoDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CStudentInfoDlg::OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMLISTVIEW pNMLV = reinterpret_cast<LPNMLISTVIEW>(pNMHDR);
	// TODO: 在此添加控件通知处理程序代码
	DWORD dwPos = GetMessagePos();
	CPoint point(LOWORD(dwPos), HIWORD(dwPos));
	//查看点击位置
	m_ListControl.ScreenToClient(&point);
	LVHITTESTINFO lvinfo;
	lvinfo.pt = point;
	lvinfo.flags = LVHT_ABOVE;
	int nItem = m_ListControl.SubItemHitTest(&lvinfo);

	if (nItem != LB_ERR)
	{
		GetDlgItem(IDC_BUTTON_ADD)->EnableWindow(TRUE);
		for (int i = 0; i < m_ListControl.GetItemCount(); i++)
		{
			if (m_ListControl.GetItemState(i, LVIS_SELECTED) == LVIS_SELECTED)
			{
				m_id = m_ListControl.GetItemText(i, 0);
				m_name = m_ListControl.GetItemText(i, 1);
				char *c = "男";
				if (m_ListControl.GetItemText(i, 2) == c)
					m_Sex = 0;
				else
					m_Sex = 1;
				m_age = m_ListControl.GetItemText(i, 3);
				m_math = m_ListControl.GetItemText(i, 4);
				m_cpulspuls = m_ListControl.GetItemText(i, 5);
				m_address = m_ListControl.GetItemText(i, 6);
				UpdateData(FALSE);
			}
		}
		GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(TRUE);
		GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(TRUE);
	}
	else
	{
		GetDlgItem(IDC_BUTTON_CHANGE)->EnableWindow(FALSE);
		GetDlgItem(IDC_BUTTON_DELETE)->EnableWindow(FALSE);
		m_id = "";
		m_name = "";
		m_Sex = -1;
		m_age = "";
		m_address = "";
		m_math = "";
		m_cpulspuls = "";
		UpdateData(FALSE);
	}
	*pResult = 0;
}

void CStudentInfoDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}

void CStudentInfoDlg::OnEnChangeEditId()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}

void CStudentInfoDlg::OnBnClickedButtonSave()
{
	// TODO: 在此添加控件通知处理程序代码
	CFile file;
	if (!file.Open(_T("C:\\student.dat"), CFile::modeCreate | CFile::modeWrite))
	{
		MessageBox(_T("保存文件时失败！"));
		return;
	}
	int i = 0;
	int nCount = m_ListControl.GetItemCount();
	student u;
	while (i < nCount)
	{
		m_ListControl.GetItemText(i, 0, (LPTSTR)u.id, sizeof(u.id));
		m_ListControl.GetItemText(i, 1, (LPTSTR)u.name, sizeof(u.name));
		m_ListControl.GetItemText(i, 2, (LPTSTR)u.age, sizeof(u.age));
		m_ListControl.GetItemText(i, 3, (LPTSTR)u.sex, sizeof(u.sex));
		m_ListControl.GetItemText(i, 4, (LPTSTR)u.math, sizeof(u.math));
		m_ListControl.GetItemText(i, 5, (LPTSTR)u.cpp, sizeof(u.cpp));
		m_ListControl.GetItemText(i, 6, (LPTSTR)u.address, sizeof(u.address));
		file.Write(&u, sizeof(u));
		i++;
	}
	file.Close();
	MessageBox(_T("保存文件成功！"));
}

void CStudentInfoDlg::OnBnClickedButtonAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	     //将控件内容赋给变量
	m_ID.GetWindowText(m_id);
	m_NAME.GetWindowText(m_name);
	m_AGE.GetWindowText(m_age);
	m_MATH.GetWindowText(m_math);
	m_CPULSPULS.GetWindowText(m_cpulspuls);
	m_ADDRESS.GetWindowText(m_address);
	UpdateData(TRUE);
	//微小异常处理

	m_id.Trim();
	CString string = m_id.SpanIncluding(_T("0123456789"));  //
	if (string.GetLength() != m_id.GetLength()|| m_id.GetLength()!=10)
	{
		MessageBox(_T("学号不正确，请重新输入！"));
		return;
	}
	else 
	{
		CString str1;
		int i = 0;
		int nCount = m_ListControl.GetItemCount();
		while (i < nCount)
		{
			str1 = m_ListControl.GetItemText(i, 0);
			if (str1 == m_id)
			{
				MessageBox(_T("改学生已经存在！"));
				return;
			}
			i++;
		}
	}
	if (m_name.IsEmpty())
	{
		MessageBox(_T("姓名不能为空!"));
		return;
	}
	m_age.Trim();
	string = m_age.SpanIncluding(_T("0123456789"));
	int x = _ttoi(m_age);
	if (m_age.IsEmpty()|| x <= 0|| x >= 120)
	{
		MessageBox(_T("年龄不正确，请重新输入！"));
		return;
	}
	if (m_address.IsEmpty())
	{
		MessageBox(_T("地址不能为空!"));
		return;
	}
	m_math.Trim();
	string = m_math.SpanIncluding(_T(".0123456789"));
	x = _ttoi(m_math);
	if (string.GetLength() != m_math.GetLength() || x <= 0 || x >= 100)
	{
		MessageBox(_T("高数成绩不正确，请重新输入！"));
		return;
	}
	m_cpulspuls.Trim();
	string = m_cpulspuls.SpanIncluding(_T(".0123456789"));
	x = _ttoi(m_cpulspuls);
	if (string.GetLength() != m_cpulspuls.GetLength() || x <= 0 || x >= 100)
	{
		MessageBox(_T("程序成绩不正确，请重新输入！"));
		return;
	}
	if (m_Sex == -1)
	{
		MessageBox(_T("请选择性别"));
		return;
	}
	m_ListControl.InsertItem(0, m_id);  //将控件内容赋给List Control相应位置
	m_ListControl.SetItemText(0, 1, m_name);
	UpdateData(TRUE);
	if (m_Sex == 1)
		m_ListControl.SetItemText(0, 2, _T("女"));
	else if (m_Sex == 0)
		m_ListControl.SetItemText(0, 2, _T("男"));
	m_ListControl.SetItemText(0, 3, m_age);
	m_ListControl.SetItemText(0, 4, m_math);
	m_ListControl.SetItemText(0, 5, m_cpulspuls);
	m_ListControl.SetItemText(0, 6, m_address);
	UpdateData(TRUE);
	m_StuNum = m_ListControl.GetItemCount();   //
	UpdateData(FALSE);
	
	m_id = "";   //控件内容置空
	m_name = "";
	m_Sex = -1;
	m_age = "";
	m_address = "";
	m_math = "";
	m_cpulspuls = "";
	UpdateData(FALSE);
	num++;
}

void CStudentInfoDlg::OnBnClickedButtonDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	int i = 0, num = 0;
	while (m_ListControl.GetItemText(i, 0) != "")
	{
		i++;
		num++;
	}
	m_ID.GetWindowText(m_id);
	if (m_id == "")
	{
		CString str = _T("学号为空，无法删除!");
		MessageBox(str);
		return;
	}

	for (i = 0; i < num; i++)
	{
		if (m_id == m_ListControl.GetItemText(i, 0))
		{
			m_ListControl.DeleteItem(i);
			break;
		}
	}
	UpdateData(TRUE);
	m_StuNum = m_ListControl.GetItemCount();   //
	UpdateData(FALSE);
	m_id = "";
	m_name = "";
	m_Sex = -1;
	m_age = "";
	m_address = "";
	m_math = "";
	m_cpulspuls = "";
	UpdateData(FALSE);
}

void CStudentInfoDlg::OnBnClickedButtonChange()
{
	// TODO: 在此添加控件通知处理程序代码
	int  nItem = m_ListControl.GetSelectionMark();   //获取选中行
	//将控件内容赋给变量
	m_ID.GetWindowText(m_id);
	m_NAME.GetWindowText(m_name);
	m_AGE.GetWindowText(m_age);
	m_MATH.GetWindowText(m_math);
	m_CPULSPULS.GetWindowText(m_cpulspuls);
	m_ADDRESS.GetWindowText(m_address);
	UpdateData(TRUE);
	

	m_id.Trim();
	CString string = m_id.SpanIncluding(_T("0123456789"));  //
	if (string.GetLength() != m_id.GetLength() || m_id.GetLength() != 10)
	{
		MessageBox(_T("学号不正确，请重新输入！"));
		return;
	}
	
	if (m_name.IsEmpty())
	{
		MessageBox(_T("姓名不能为空!"));
		return;
	}
	m_age.Trim();
	string = m_age.SpanIncluding(_T("0123456789"));
	int x = _ttoi(m_age);
	if (m_age.IsEmpty() || x <= 0 || x >= 120)
	{
		MessageBox(_T("年龄不正确，请重新输入！"));
		return;
	}
	if (m_address.IsEmpty())
	{
		MessageBox(_T("地址不能为空!"));
		return;
	}
	m_math.Trim();
	string = m_math.SpanIncluding(_T(".0123456789"));
	x = _ttoi(m_math);
	if (string.GetLength() != m_math.GetLength() || x <= 0 || x >= 100)
	{
		MessageBox(_T("高数成绩不正确，请重新输入！"));
		return;
	}
	m_cpulspuls.Trim();
	string = m_cpulspuls.SpanIncluding(_T(".0123456789"));
	x = _ttoi(m_cpulspuls);
	if (string.GetLength() != m_cpulspuls.GetLength() || x <= 0 || x >= 100)
	{
		MessageBox(_T("程序成绩不正确，请重新输入！"));
		return;
	}
	if (m_Sex == -1)
	{
		MessageBox(_T("请选择性别"));
		return;
	}
	m_ListControl.InsertItem(nItem, m_id);    //将控件内容赋给List Control相应位置
	m_ListControl.SetItemText(nItem, 1, m_name);
	if (m_Sex == 1)
		m_ListControl.SetItemText(nItem, 2, _T("女"));
	else if (m_Sex == 0)
		m_ListControl.SetItemText(nItem, 2, _T("男"));
	m_ListControl.SetItemText(nItem, 3, m_age);
	m_ListControl.SetItemText(nItem, 4, m_math);
	m_ListControl.SetItemText(nItem, 5, m_cpulspuls);
	m_ListControl.SetItemText(nItem, 6, m_address);
	UpdateData(FALSE);
	m_ListControl.DeleteItem(nItem + 1);  //删除修改的行
	UpdateData(TRUE);   //控件内容置空
	m_id = "";
	m_name = "";
	m_Sex = -1;
	m_age = "";
	m_address = "";
	m_math = "";
	m_cpulspuls = "";
	UpdateData(FALSE);
}

bool sortMath(student a, student b)
{
	return _ttoi((LPTSTR)a.math) > _ttoi((LPTSTR)b.math);   //高数（m_math）大小比较函数
}

bool sortCpp(student a, student b)
{
	return _ttoi((LPTSTR)a.cpp) > _ttoi((LPTSTR)b.cpp);   //高数（m_math）大小比较函数
}

bool sortId(student a, student b)
{
	return _ttoi((LPTSTR)a.id) < _ttoi((LPTSTR)b.id);   //高数（m_math）大小比较函数
}

void CStudentInfoDlg::OnBnClickedButtonSortByMath()
{
	// TODO: 在此添加控件通知处理程序代码
	student stu[100];
	int i = 0;
	int nCount = m_ListControl.GetItemCount();
	while (i < nCount)
	{
		m_ListControl.GetItemText(i, 0, (LPTSTR)stu[i].id, sizeof(stu[i].id));
		m_ListControl.GetItemText(i, 1, (LPTSTR)stu[i].name, sizeof(stu[i].name));
		m_ListControl.GetItemText(i, 2, (LPTSTR)stu[i].age, sizeof(stu[i].age));
		m_ListControl.GetItemText(i, 3, (LPTSTR)stu[i].sex, sizeof(stu[i].sex));
		m_ListControl.GetItemText(i, 4, (LPTSTR)stu[i].math, sizeof(stu[i].math));
		m_ListControl.GetItemText(i, 5, (LPTSTR)stu[i].cpp, sizeof(stu[i].cpp));
		m_ListControl.GetItemText(i, 6, (LPTSTR)stu[i].address, sizeof(stu[i].address));
		UpdateData(FALSE);
		i++;
	}
	std::sort(stu, stu + i, sortMath);
	m_ListControl.DeleteAllItems();
	int t = 0;
	while (i)  
	{
		m_ListControl.InsertItem(t, (LPTSTR)stu[t].id);
		m_ListControl.SetItemText(t, 1, (LPTSTR)stu[t].name);
		m_ListControl.SetItemText(t, 2, (LPTSTR)stu[t].age);
		m_ListControl.SetItemText(t, 3, (LPTSTR)stu[t].sex);
		m_ListControl.SetItemText(t, 4, (LPTSTR)stu[t].math);
		m_ListControl.SetItemText(t, 5, (LPTSTR)stu[t].cpp);
		m_ListControl.SetItemText(t, 6, (LPTSTR)stu[t].address);
		UpdateData(TRUE);
		t++;
		i--;
	}
}

void CStudentInfoDlg::OnBnClickedButtoSortByCpp()
{
	// TODO: 在此添加控件通知处理程序代码
	student stu[100];
	int i = 0;
	int nCount = m_ListControl.GetItemCount();
	while (i < nCount)
	{
		m_ListControl.GetItemText(i, 0, (LPTSTR)stu[i].id, sizeof(stu[i].id));
		m_ListControl.GetItemText(i, 1, (LPTSTR)stu[i].name, sizeof(stu[i].name));
		m_ListControl.GetItemText(i, 2, (LPTSTR)stu[i].age, sizeof(stu[i].age));
		m_ListControl.GetItemText(i, 3, (LPTSTR)stu[i].sex, sizeof(stu[i].sex));
		m_ListControl.GetItemText(i, 4, (LPTSTR)stu[i].math, sizeof(stu[i].math));
		m_ListControl.GetItemText(i, 5, (LPTSTR)stu[i].cpp, sizeof(stu[i].cpp));
		m_ListControl.GetItemText(i, 6, (LPTSTR)stu[i].address, sizeof(stu[i].address));
		UpdateData(FALSE);
		i++;
		
	}
	std::sort(stu, stu + i, sortCpp);
	m_ListControl.DeleteAllItems();
	int t = 0;
	while (i)
	{
		m_ListControl.InsertItem(t, (LPTSTR)stu[t].id);
		m_ListControl.SetItemText(t, 1, (LPTSTR)stu[t].name);
		m_ListControl.SetItemText(t, 2, (LPTSTR)stu[t].age);
		m_ListControl.SetItemText(t, 3, (LPTSTR)stu[t].sex);
		m_ListControl.SetItemText(t, 4, (LPTSTR)stu[t].math);
		m_ListControl.SetItemText(t, 5, (LPTSTR)stu[t].cpp);
		m_ListControl.SetItemText(t, 6, (LPTSTR)stu[t].address);
		UpdateData(TRUE);
		t++;
		i--;
	}
}

void CStudentInfoDlg::OnBnClickedButtoSortById()
{
	// TODO: 在此添加控件通知处理程序代码
	student stu[100];
	int i = 0;
	int nCount = m_ListControl.GetItemCount();
	while (i < nCount)
	{
		m_ListControl.GetItemText(i, 0, (LPTSTR)stu[i].id, sizeof(stu[i].id));
		m_ListControl.GetItemText(i, 1, (LPTSTR)stu[i].name, sizeof(stu[i].name));
		m_ListControl.GetItemText(i, 2, (LPTSTR)stu[i].age, sizeof(stu[i].age));
		m_ListControl.GetItemText(i, 3, (LPTSTR)stu[i].sex, sizeof(stu[i].sex));
		m_ListControl.GetItemText(i, 4, (LPTSTR)stu[i].math, sizeof(stu[i].math));
		m_ListControl.GetItemText(i, 5, (LPTSTR)stu[i].cpp, sizeof(stu[i].cpp));
		m_ListControl.GetItemText(i, 6, (LPTSTR)stu[i].address, sizeof(stu[i].address));
		UpdateData(FALSE);
		i++;
	}
	std::sort(stu, stu + i, sortId);
	m_ListControl.DeleteAllItems();
	int t = 0;
	while (i)
	{
		m_ListControl.InsertItem(t, (LPTSTR)stu[t].id);
		m_ListControl.SetItemText(t, 1, (LPTSTR)stu[t].name);
		m_ListControl.SetItemText(t, 2, (LPTSTR)stu[t].age);
		m_ListControl.SetItemText(t, 3, (LPTSTR)stu[t].sex);
		m_ListControl.SetItemText(t, 4, (LPTSTR)stu[t].math);
		m_ListControl.SetItemText(t, 5, (LPTSTR)stu[t].cpp);
		m_ListControl.SetItemText(t, 6, (LPTSTR)stu[t].address);
		UpdateData(TRUE);
		t++;
		i--;
	}
}
