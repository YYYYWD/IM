// Login.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "Login.h"
#include "afxdialogex.h"
#include"Newuser.h"
#include<atlconv.h>
#include"QQClientDlg.h"


// CLogin 对话框

IMPLEMENT_DYNAMIC(CLogin, CDialogEx)

CLogin::CLogin(CWnd* pParent /*=NULL*/)
	: CDialogEx(CLogin::IDD, pParent)
	, m_username(_T(""))
	, m_password(_T(""))
	, m_vir_Username(_T(""))
{

}

CLogin::~CLogin()
{
}

void CLogin::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_username);
	DDX_Text(pDX, IDC_EDIT2, m_password);
	//  DDX_Control(pDX, IDB_BITMAP1, m_Btn);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, flashshow);
	DDX_CBString(pDX, IDC_COMBO1, m_vir_Username);
}


BEGIN_MESSAGE_MAP(CLogin, CDialogEx)
	ON_BN_CLICKED(IDC_BTN_NEWUSER, &CLogin::OnBnClickedBtnNewuser)
	ON_BN_CLICKED(IDOK, &CLogin::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CLogin::OnBnClickedCancel)
	ON_WM_PAINT()
//	ON_WM_NCHITTEST()
//	ON_WM_NCLBUTTONDOWN()
ON_WM_NCHITTEST()
ON_BN_CLICKED(IDC_BUTTON1, &CLogin::OnBnClickedButton1)
END_MESSAGE_MAP()


// CLogin 消息处理程序


void CLogin::OnBnClickedBtnNewuser()
{
	// TODO:  在此添加控件通知处理程序代码
	CNewuser dlg;
	dlg.DoModal();
}


void CLogin::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CQQClientDlg * dlg = (CQQClientDlg*)AfxGetMainWnd();
	//if (dlg->m_sock == NULL)
	//{
	//	if (!dlg->m_sock.Connect(_T("192.168.187.1"), 8888))
	//		AfxMessageBox(_T("连接服务1器失败！"));
	//}
	//else
	//{
	//	if (!dlg->m_sock.Connect(_T("192.168.187.1"), 8888))
	//		;//AfxMessageBox(_T("连接服务器失败1！"));
	//}
	USES_CONVERSION;
	//CQQClientDlg * dlg = (CQQClientDlg*)AfxGetMainWnd();
	UpdateData(TRUE);
	int nCmd = 0;
	nCmd = INFO_LOGIN;
	UserInfo info;
	gethostname(info.sIP, sizeof(info.sIP));//获取主机名称
	hostent*pHost = gethostbyname(info.sIP);//通过主机名称获取主机IP
	in_addr * ad = (in_addr*)pHost->h_addr;//IP转化
	m_username=m_vir_Username;
	strcpy_s(info.sIP, inet_ntoa(*ad));
	strcpy_s(info.Username, T2A(m_username));
	strcpy_s(info.Password, T2A(m_password));
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&info, sizeof(info));
	strcpy_s(dlg->m_info.Username, T2A(m_username));
	
	OnOK();

	UpdateData(FALSE);
}


void CLogin::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
	exit(0);
}


void CLogin::OnPaint()
{
	//CPaintDC dc(this); // device context for painting
	//// TODO:  在此处添加消息处理程序代码
	//// 不为绘图消息调用 CDialogEx::OnPaint()
	//CRect rc;
	//GetClientRect(&rc);
	//CDC dcMem;
	//dcMem.CreateCompatibleDC(&dc);
	//CBitmap bmpBackground;
	//bmpBackground.LoadBitmap(IDB_BITMAP4);

	//BITMAP bitmap;
	//bmpBackground.GetBitmap(&bitmap);
	//CBitmap* pbmpPri = dcMem.SelectObject(&bmpBackground);
	//dc.StretchBlt(0, 0, rc.Width(), rc.Height(), &dcMem, 0, 0, bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	//HBITMAP hBmp = ::LoadBitmap(AfxGetInstanceHandle(), MAKEINTRESOURCE(IDB_BITMAP3));
	//m_Btn.SetBitmap(hBmp);
	
	CPaintDC dc(this);

	//CRect rect;
	//GetClientRect(&rect);
	//CDC dcMem;
	//dcMem.CreateCompatibleDC(&dc);
	//CBitmap bmpBackground;
	//bmpBackground.LoadBitmap(IDB_BITMAP4);
	//BITMAP bitmap;
	//bmpBackground.GetBitmap(&bitmap);
	//CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
	//dc.SetStretchBltMode(HALFTONE);             //*添加于此
	//dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
	//	bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	
}


//LRESULT CLogin::OnNcHitTest(CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	CRect rect;
//	GetWindowRect(&rect);
//	CRect rect1 = rect;
//	rect1.DeflateRect(10, 10, -10, -10);
//	rect1.NormalizeRect();
//	if (point.x <= rect.left + 3)
//		return HTLEFT;
//	else if (point.x >= rect.right - 3)
//		return HTRIGHT;
//	else if (point.y <= rect.top + 3)
//		return HTTOP;
//	else if (point.y >= rect.bottom - 3)
//		return HTBOTTOM;
//	else if (point.x <= rect.left + 10 && point.y <= rect.top + 10)
//		return HTTOPLEFT;
//	else if (point.x >= rect.right - 10 && point.y <= rect.top + 10)
//		return HTTOPRIGHT;
//	else if (point.x <= rect.left + 10 && point.y >= rect.bottom - 10)
//		return HTBOTTOMLEFT;
//	else if (point.x >= rect.right - 10 && point.y >= rect.bottom - 10)
//		return HTBOTTOMRIGHT;
//	else if (!rect.IsRectEmpty())
//	{
//		LRESULT uRet = CWnd::OnNcHitTest(point);
//		uRet = (uRet == HTCLIENT) ? HTCAPTION : uRet;
//		return uRet;
//	}
//	else
//	{
//		return CWnd::OnNcHitTest(point);
//	}
//	return 0;
//}


//void CLogin::OnNcLButtonDown(UINT nHitTest, CPoint point)
//{
//	// TODO:  在此添加消息处理程序代码和/或调用默认值
//
//	if (nHitTest == HTTOP)
//	{
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
//	}
//	else if (nHitTest == HTBOTTOM)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTTOPLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTTOPRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTBOTTOMLEFT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTBOTTOMRIGHT)
//		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
//	else if (nHitTest == HTCAPTION)
//		SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
//}


LRESULT CLogin::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
	{
		nHitTest = HTCAPTION;
	}
	return nHitTest;
	
}


BOOL CLogin::OnInitDialog()
{
	CDialogEx::OnInitDialog();

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

	strFileName += _T("14.swf");//clock.swf是flash文件的名字，该flash文件放在工程目录下。

	flashshow.LoadMovie(0, strFileName);

	flashshow.Play();
	CFont * f;
	f = new CFont;
	f->CreateFont(20, // nHeight   
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
	GetDlgItem(IDC_COMBO1)->SetFont(f);
	GetDlgItem(IDC_EDIT2)->SetFont(f);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}


void CLogin::OnBnClickedButton1()
{
	// TODO:  在此添加控件通知处理程序代码
	ABdlg.DoModal();
}
