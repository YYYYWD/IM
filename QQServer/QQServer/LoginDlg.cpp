// LoginDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQServer.h"
#include "LoginDlg.h"
#include "afxdialogex.h"
#include"QQServerDlg.h"
#include<atlconv.h>
// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)

CLoginDlg::CLoginDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLoginDlg::IDD, pParent)
	, m_rootname(_T(""))
	, m_rootpassword(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_ROOT_NAME, m_rootname);
	DDX_Text(pDX, IDC_ROOT_PASSWORD, m_rootpassword);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH, flashshow);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDCANCEL, &CLoginDlg::OnBnClickedCancel)
	ON_WM_NCHITTEST()
	ON_WM_LBUTTONDOWN()
//	ON_EN_CHANGE(IDC_EDIT2, &CLoginDlg::OnEnChangeEdit2)
END_MESSAGE_MAP()


// CLoginDlg 消息处理程序


void CLoginDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	USES_CONVERSION;
	UpdateData(TRUE);
	if (!strcmp(T2A(m_rootname), "root"))
	{
		if (!strcmp(T2A(m_rootpassword), "123456"))
		{
			OnOK();
		}
		else
		{
			MessageBox(_T("密码错误！！！"), _T("警告！"));
			return;
		}
	}
	else
	{
		MessageBox(_T("登陆失败！！！"), _T("警告！"));
		exit(0);
	}

}


void CLoginDlg::OnPaint()
{
	CPaintDC dc(this);


	RECT rc;
	this->GetClientRect(&rc);//获得客户区的坐标

	//调整flash的位置

	rc.left = 0;

	rc.right = rc.right;



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

	strFileName += _T("high.swf");//clock.swf是flash文件的名字，该flash文件放在工程目录下。

	flashshow.LoadMovie(0, strFileName);

	flashshow.Play();


	//return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CLoginDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	exit(0);
}


LRESULT CLoginDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
	{
		nHitTest = HTCAPTION;
	}
	return nHitTest;
}


void CLoginDlg::OnLButtonDown(UINT nFlags, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	SendMessage(WM_SYSCOMMAND, SC_MOVE | HTCAPTION, 0);
	PostMessage(WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(point.x, point.y));
	CDialogEx::OnLButtonDown(nFlags, point);
}


BOOL CLoginDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * f;
	f = new CFont;
	f->CreateFont(30, // nHeight   
		0, // nWidth   
		0, // nEscapement   
		0, // nOrientation   
		FW_BOLD, // nWeight   
		FALSE, // bItalic   
		FALSE, // bUnderline   
		0, // cStrikeOut   
		ANSI_CHARSET, // nCharSet   
		OUT_DEFAULT_PRECIS, // nOutPrecision   
		CLIP_DEFAULT_PRECIS, // nClipPrecision   
		DEFAULT_QUALITY, // nQuality   
		DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily   
		_T("微软雅黑")); // lpszFac   
	GetDlgItem(IDC_ROOT_NAME)->SetFont(f);
	GetDlgItem(IDC_ROOT_PASSWORD)->SetFont(f);


	//CString m_sRootPath;
	//GetModuleFileName(NULL, m_sRootPath.GetBufferSetLength(MAX_PATH + 1), MAX_PATH);
	//m_sRootPath.ReleaseBuffer();
	//int nPos;
	//nPos = m_sRootPath.ReverseFind('\\');
	//m_sRootPath = m_sRootPath.Left(nPos);
	//CString strMovieUrl = m_sRootPath + "\\6789.swf"; //flash文件“start.swf”应放在Debug目录下  
	//flashshow.LoadMovie(0, strMovieUrl);	  ////加载并播放动画 
	//flashshow.Play();



	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
	// TODO:  在此添加额外的初始化

	//return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


//void CLoginDlg::OnEnChangeEdit2()
//{
//	// TODO:  如果该控件是 RICHEDIT 控件，它将不
//	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
//	// 函数并调用 CRichEditCtrl().SetEventMask()，
//	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。
//
//	// TODO:  在此添加控件通知处理程序代码
//}
