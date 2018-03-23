// PlayGame.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "PlayGame.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"


// CPlayGame 对话框

IMPLEMENT_DYNAMIC(CPlayGame, CDialogEx)

CPlayGame::CPlayGame(CWnd* pParent /*=NULL*/)
	: CDialogEx(CPlayGame::IDD, pParent)
{

}

CPlayGame::~CPlayGame()
{
}

void CPlayGame::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, flashshow);
}


BEGIN_MESSAGE_MAP(CPlayGame, CDialogEx)
//	ON_BN_CLICKED(IDOK, &CPlayGame::OnBnClickedOk)
	ON_WM_CLOSE()
END_MESSAGE_MAP()


// CPlayGame 消息处理程序


BOOL CPlayGame::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	RECT rc;
	this->GetClientRect(&rc);//获得客户区的坐标

	//调整flash的位置

	rc.left = 0;

	rc.right = rc.right;

	rc.top += 0;

	rc.bottom = rc.bottom;

	flashshow.MoveWindow(&rc, true);



	TCHAR strCurDrt[5000];

	int nLen = ::GetCurrentDirectory(5000, strCurDrt);

	if (strCurDrt[nLen] != '\\')

	{

		strCurDrt[nLen++] = '\\';

		strCurDrt[nLen] = '\0';

	}



	CString strFileName = strCurDrt;

	strFileName += _T("3.swf");//clock.swf是flash文件的名字，该flash文件放在工程目录下。

	flashshow.LoadMovie(0, strFileName);

	flashshow.Play();
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//void CPlayGame::OnBnClickedOk()
//{
//	// TODO:  在此添加控件通知处理程序代码
//	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
//	//flashshow.MoveWindow(0, 0, 0, 0);
//	
//	//flashshow.Stop();
//	CDialogEx::OnClose();
//	//(CQQClientDlg*)cdlg = (CQQClientDlg*)AfxGetMainWnd();
//	
//}


void CPlayGame::OnCancel()
{
	// TODO:  在此添加专用代码和/或调用基类
	//DestroyWindow();
	flashshow.StopPlay();
	CDialogEx::OnCancel();
}


void CPlayGame::PostNcDestroy()
{
	// TODO:  在此添加专用代码和/或调用基类

	CDialogEx::PostNcDestroy();
	//delete this;
}


void CPlayGame::OnClose()
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	DestroyWindow();
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	dlg->m_game = NULL;
	CDialogEx::OnClose();
}
