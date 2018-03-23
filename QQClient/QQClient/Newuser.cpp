// Newuser.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "Newuser.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"
#include<atlconv.h>
// CNewuser 对话框

IMPLEMENT_DYNAMIC(CNewuser, CDialogEx)

CNewuser::CNewuser(CWnd* pParent /*=NULL*/)
	: CDialogEx(CNewuser::IDD, pParent)
	, m_newusername(_T(""))
	, m_newpassword1(_T(""))
	, m_newpassword2(_T(""))
{

}

CNewuser::~CNewuser()
{
}

void CNewuser::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_newusername);
	DDX_Text(pDX, IDC_EDIT2, m_newpassword1);
	DDX_Text(pDX, IDC_EDIT3, m_newpassword2);
	DDX_Control(pDX, IDC_EDIT4, m_edt1);
	DDX_Control(pDX, IDC_EDIT5, m_edt2);
	DDX_Control(pDX, IDC_EDIT6, m_edt3);
}


BEGIN_MESSAGE_MAP(CNewuser, CDialogEx)
	ON_BN_CLICKED(IDOK, &CNewuser::OnBnClickedOk)
	ON_WM_PAINT()
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CNewuser 消息处理程序


void CNewuser::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	/*if (!dlg->m_sock.Connect(_T("192.168.187.1"), 8888))
	AfxMessageBox(_T("连接服务器失败！"));*/
	USES_CONVERSION;
	UpdateData(TRUE);
	
	if (strcmp(T2A(m_newpassword1), T2A(m_newpassword2)))
	{
		AfxMessageBox(_T("     两次输入的密码不相同,\n             请重新输入！"));
		return;
	}
	//CQQClientDlg *dlg = (CQQClientDlg*)AfxGetMainWnd();
	int nCmd = INFO_ADD;
	UserInfo info;
	strcpy_s(info.Username, T2A(m_newusername));
	strcpy_s(info.Password, T2A(m_newpassword2));
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&info, sizeof(info));

}


void CNewuser::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP8);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(HALFTONE);             //*添加于此
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}


HBRUSH CNewuser::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT4)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(0, 0, 0));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
		//pDC->SetBkMode(TRANSPARENT); //透明

	}
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT5)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(0, 0, 0));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
		//pDC->SetBkMode(TRANSPARENT); //透明

	}
	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT6)
	{
		pDC->SetBkColor(RGB(0, 0, 0));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(0, 0, 0));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
		//pDC->SetBkMode(TRANSPARENT); //透明

	}
	return hbr;
}


BOOL CNewuser::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	CFont * f1;
	f1 = new CFont;
	f1->CreateFont(20, // nHeight   
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
	m_edt1.SetFont(f1);
	m_edt2.SetFont(f1);
	m_edt3.SetFont(f1);
	// TODO:  在此添加额外的初始化
	SetDlgItemText(IDC_EDIT4,_T("新的用户"));
	SetDlgItemText(IDC_EDIT5, _T("密码"));
	SetDlgItemText(IDC_EDIT6, _T("确认密码"));
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
	GetDlgItem(IDC_EDIT1)->SetFont(f);
	GetDlgItem(IDC_EDIT2)->SetFont(f);
	GetDlgItem(IDC_EDIT3)->SetFont(f);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}
