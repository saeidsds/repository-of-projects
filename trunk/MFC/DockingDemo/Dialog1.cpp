// Dialog1.cpp : 实现文件
//

#include "stdafx.h"
#include "DockingDemo.h"
#include "Dialog1.h"


/*
BEGIN_MESSAGE_MAP(TabDialog, CDialog)
END_MESSAGE_MAP()
/////////////////////////////////////////////////////////////////////////////
// 
// 
void TabDialog::OnCancel()
{	//CDialog::OnCancel();
}
// 
void TabDialog::OnOK()
{	//CDialog::OnOK();
}*/

// CDialog1 对话框

IMPLEMENT_DYNAMIC(CDialog1, CDialog)

CDialog1::CDialog1(CWnd* pParent)
	: CDialog(CDialog1::IDD, pParent)
{

}

CDialog1::~CDialog1()
{
}

void CDialog1::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDialog1, CDialog)
END_MESSAGE_MAP()


// CDialog1 消息处理程序
