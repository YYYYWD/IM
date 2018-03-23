// User.cpp : 实现文件
//

#include "stdafx.h"
#include "QQServer.h"
#include "User.h"
#include "afxdialogex.h"
#include<atlconv.h>
#include"SocketC.h"

// CUser 对话框

IMPLEMENT_DYNAMIC(CUser, CDialogEx)

CUser::CUser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CUser::IDD, pParent)
	, m_Username(_T(""))
	, m_Password(_T(""))
{

}

CUser::~CUser()
{
}

void CUser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Username);
	DDX_Text(pDX, IDC_EDIT2, m_Password);
}


BEGIN_MESSAGE_MAP(CUser, CDialogEx)
	ON_BN_CLICKED(IDOK, &CUser::OnBnClickedOk)
END_MESSAGE_MAP()


// CUser 消息处理程序


void CUser::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	USES_CONVERSION;
	int nCmd = 0;
	nCmd = INFO_BYE;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (!strcmp(theApp.m_list.GetAt(pos2).Username, T2A(m_Username)))
		{
			CSocketC::OnExit(theApp.m_list.GetAt(pos2));
			//theApp.m_list.GetAt(pos2).pSock->Send(&nCmd, sizeof(nCmd));
			break;
		}
		theApp.m_list.GetNext(pos2);
	}
	OnOK();



}
