#include"stdafx.h"
/*
m_ID.GetWindowText(m_id);
	m_NAME.GetWindowText(m_name);
	m_AGE.GetWindowText(m_age);
	m_MATH.GetWindowText(m_math);
	m_CPULSPULS.GetWindowText(m_cpulspuls);
	m_ADDRESS.GetWindowText(m_address);
	UpdateData(TRUE);
	//微小异常处理


	if (m_id == "")
	{
		MessageBox(_T("学号不能为空!"));
		return;
	}
	if (m_name == "")
	{
		MessageBox(_T("姓名不能为空!"));
		return;
	}
	if (m_age == "")
	{
		MessageBox(_T("年龄不能为空!"));
		return;
	}
	if (m_math == "")
	{
		MessageBox(_T("数学成绩不能为空!"));
		return;
	}
	if (m_cpulspuls == "")
	{
		MessageBox(_T("程序成绩不能为空!"));
		return;
	}
	if (m_address == "")
	{
		MessageBox(_T("地址不能为空!"));
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

	UpdateData(TRUE);   //控件内容置空
	m_id = "";
	m_name = "";
	m_Sex = -1;
	m_age = "";
	m_address = "";
	m_math = "";
	m_cpulspuls = "";
	UpdateData(FALSE);
	num++;
*/