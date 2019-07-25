
// StudentInfoDlg.h: 头文件
//
#include"Student.h"
#pragma once


// CStudentInfoDlg 对话框
class CStudentInfoDlg : public CDialogEx
{
// 构造
public:
	CStudentInfoDlg(CWnd* pParent = nullptr);	// 标准构造函数

	DWORD m_dwPos;
// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_STUDENTINFO_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnLvnItemchangedList1(NMHDR *pNMHDR, LRESULT *pResult);
	CListCtrl m_ListControl;
	afx_msg void OnBnClickedOk();
	CEdit m_ID;
	CString m_id;

	CEdit m_NAME;
	CString m_name;
	CEdit m_AGE;
	CString m_age;
	CEdit m_ADDRESS;
	CString m_address;
	CEdit m_MATH;
	CString m_math;
	CEdit m_CPULSPULS;
	CString m_cpulspuls;

	afx_msg void OnEnChangeEditId();
	int m_Sex;
	afx_msg void OnBnClickedButtonAdd();
	afx_msg void OnBnClickedButtonSave();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonChange();
	afx_msg void OnBnClickedButtonSortByMath();
	afx_msg void OnBnClickedButtoSortByCpp();
	
	afx_msg void OnBnClickedButtoSortById();
	int m_StuNum;
};
