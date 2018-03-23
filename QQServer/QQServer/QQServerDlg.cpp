
// QQServerDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQServer.h"
#include "QQServerDlg.h"
#include "afxdialogex.h"
#include<atlconv.h>
#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// 用于应用程序“关于”菜单项的 CAboutDlg 对话框

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg LRESULT OnNcHitTest(CPoint point);
};

CAboutDlg::CAboutDlg() : CDialogEx(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	ON_WM_NCHITTEST()
END_MESSAGE_MAP()


// CQQServerDlg 对话框



CQQServerDlg::CQQServerDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CQQServerDlg::IDD, pParent)
	, m_user_number(0)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CQQServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HIST, m_hist);
	DDX_Control(pDX, IDC_LIST_USER, m_ListCtrl_UserInfo);
	DDX_Text(pDX, IDC_EDT_USERNUMBER, m_user_number);
	DDX_Control(pDX, IDC_STATIC1, m_static);
	DDX_Control(pDX, IDC_EDIT3, m_now);
}

BEGIN_MESSAGE_MAP(CQQServerDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_WM_NCHITTEST()
	ON_WM_NCLBUTTONDOWN()
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_USER, &CQQServerDlg::OnDblclkListUser)
	ON_EN_CHANGE(IDC_EDT_USERNUMBER, &CQQServerDlg::OnEnChangeEdtUsernumber)
	ON_WM_CTLCOLOR()
END_MESSAGE_MAP()


// CQQServerDlg 消息处理程序

BOOL CQQServerDlg::OnInitDialog()
{
	if ((m_dlg).DoModal() != IDOK)
	{
		OnOK();
	}
	CDialogEx::OnInitDialog();
	if (!m_sock.Create(8888))
	{
		int nError = GetLastError();
		AfxMessageBox(_T("创建网络失败"));
	}
	m_sock.Listen();
	// 将“关于...”菜单项添加到系统菜单中。

	CFont * f;
	f = new CFont;
	f->CreateFont(25, // nHeight   
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

	GetDlgItem(IDC_HIST)->SetFont(f);
	

	// IDM_ABOUTBOX 必须在系统命令范围内。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
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

	// TODO:  在此添加额外的初始化代码
	try
	{
		HRESULT hr;
		_bstr_t strConn = _T("Driver=MySQL ODBC 5.3 Unicode Driver;SERVER=127.0.0.1;UID=root;DATABASE=user;PORT=3306");
		hr = m_pConn.CreateInstance(_T("ADODB.Connection"));
		if (SUCCEEDED(hr))
		{
			hr = m_pConn->Open(strConn, _T("root"), _T(""), adModeUnknown);
		}

	}
	catch (_com_error e)
	{
		CString errorMsg = _T("");
		errorMsg.Format(_T("连接数据库失败！\r\n错误信息：%s"), e.ErrorMessage());
		AfxMessageBox(errorMsg);

	}

	m_ListCtrl_UserInfo.InsertColumn(0, _T("用户名"), 0, 120);
	m_ListCtrl_UserInfo.InsertColumn(1, _T("IP地址"), 0, 120);
	m_ListCtrl_UserInfo.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);
	//CFont * f;
	//f = new CFont;
	//f->CreateFont(200,            // nHeight
	//	0,           // nWidth
	//	0,           // nEscapement
	//	0,           // nOrientation
	//	FW_BOLD,     // nWeight
	//	TRUE,        // bItalic
	//	FALSE,       // bUnderline
	//	0,           // cStrikeOut
	//	ANSI_CHARSET,              // nCharSet
	//	OUT_DEFAULT_PRECIS,        // nOutPrecision
	//	CLIP_DEFAULT_PRECIS,       // nClipPrecision
	//	DEFAULT_QUALITY,           // nQuality
	//	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily
	//	_T("Arial"));              // lpszFac
	m_static.SetFont(f);
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
	m_now.SetFont(f1);
	SetDlgItemText(IDC_EDIT3, _T("在线人数："));
	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CQQServerDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CQQServerDlg::OnPaint()
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
		CPaintDC dc(this);
		CRect rect;
		GetClientRect(&rect);
		CDC dcMem;
		dcMem.CreateCompatibleDC(&dc);	
		CBitmap bmpBackground;
		bmpBackground.LoadBitmap(IDB_BITMAP7);
		BITMAP bitmap;
		bmpBackground.GetBitmap(&bitmap);
		CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
		dc.SetStretchBltMode(HALFTONE);             //*添加于此
		dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
			bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);

	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CQQServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



int CQQServerDlg::OnAdd(UserInfo info)
{
	USES_CONVERSION;
	_CommandPtr m_pCommand;
	m_pCommand.CreateInstance(_T("ADODB.Command"));
	CString strSQL = _T("insert into user(Username,Password)value('");
	strSQL = strSQL + A2T(info.Username) + _T("','");
	strSQL = strSQL + A2T(info.Password) + _T("')");
	try
	{
		m_pCommand->CommandText = (LPCTSTR)strSQL;
		m_pCommand->ActiveConnection = m_pConn;
		m_pCommand->Execute(NULL, NULL, adCmdText);
		//MessageBox(_T("恭喜你！"), _T("注册成功"));
		//OnOK();
		int a = INFO_ADD;
		//m_sock.Send(&a, sizeof(a));
		return a;

	}
	catch (_com_error e)
	{

		int a = INFO_FAILADD;
		
		return a;
	}
	
}


int CQQServerDlg::OnLogin(UserInfo info)
{
	USES_CONVERSION;
	//return 0;
	_RecordsetPtr    m_pRecordset; //声明一个记录指针
	m_pRecordset.CreateInstance(_T("ADODB.Recordset"));

	try
	{
		//构造SQL语句
		CString strSQL = _T("select * from user");
		m_pRecordset->Open((LPCTSTR)strSQL, (IDispatch*)m_pConn, adOpenStatic, adLockReadOnly, adCmdText);

		//定义两个_variant_t变量，用来接收查询数据库，查询到的值
		_variant_t vUserName, vPassword;


		while (!(m_pRecordset->lkEOF))
		{
			//通过GetCollect函数，得到值
			vUserName = m_pRecordset->GetCollect(_T("Username"));//参数为数据库的列名
			vPassword = m_pRecordset->GetCollect(_T("Password"));

			//将得到的值与编辑框中的值进行比较，这里涉及到了字符编码的问题
			if (!::wcscmp(A2T(info.Username), (LPCWSTR)(_bstr_t)vUserName) && !::wcscmp(A2T(info.Password), (LPCWSTR)(_bstr_t)vPassword.bstrVal))
			{
				//m_pRecordset->Close();//如果相匹配，关闭这个记录指针
				//int a = 5;
				//AfxMessageBox(_T("hhh"));
				//m_sock.Send(&a, sizeof(a));
				//return a;
				break;

			}
			else
			{
				m_pRecordset->MoveNext();//如果没有查询到，就移动这个记录指针到下一行
			}

		}
		if (m_pRecordset->lkEOF)
		{
			int a = INFO_FAILLOFIN;
			//m_sock.Send(&a, sizeof(a));
			//AfxMessageBox(_T("hh"));
			return a;
		}
		m_pRecordset->Close(); //并在最后，关闭这个记录指针
		int a = INFO_LOGIN;
		return a;
	}
	catch (_com_error e)
	{
		int a = INFO_FAILLOFIN;
		m_pRecordset->Close();
		//m_sock.Send(&a, sizeof(a));
		//AfxMessageBox(_T("h"));
		return a;
	}
}


void CQQServerDlg::OnReceive(UserInfo info)
{
	USES_CONVERSION;
	CString str;
	CString str1;
	COleDateTime time = COleDateTime::GetCurrentTime();
	str1.Format(_T("%d年%d月%d日 %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	
	
	//将CSocketC的OnReceive函数发送过来的IP,端口,消息处理成一条语句
	str.Format(_T("%s- %d:\r\n %s\r成功登陆！\n"),A2T(info.sIP),info.nPort,A2T(info.Username));
	str1 += str;
	int nLen = m_hist.GetWindowTextLength();
	m_hist.SetSel(nLen, -1);//m_szText是编辑框添加的控件变量
	m_hist.ReplaceSel(str1);

	CFile Write_File;
	CStringA str2(str1);
	Write_File.Open(_T("服务器日志.txt"), CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	Write_File.SeekToEnd();
	Write_File.Write(str2, str2.GetLength());
	Write_File.Close();

	CString MSG1;
	MSG1.Format(_T("%s"), CStringW(info.Username));
	CString MSG2;
	MSG2.Format(_T("%s"), CStringW(info.sIP));

	m_ListCtrl_UserInfo.InsertItem(i, MSG1);
	m_ListCtrl_UserInfo.SetItemText(i, 1, MSG2);
	i++;
	
	m_user_number = i;
	
	UpdateData(FALSE);
}


void CQQServerDlg::OnUpdata()
{
	POSITION pos = theApp.m_list.GetHeadPosition();
	int nCount = theApp.m_list.GetCount();
	int j = 0;
	m_ListCtrl_UserInfo.DeleteAllItems();
	while (j < nCount)
	{
		CString str = _T(" ");
		UserInfo info(theApp.m_list.GetAt(pos));
	
		str += info.Username;
		m_ListCtrl_UserInfo.InsertItem(i, str);
		CString MSG;
		MSG.Format(_T("%s"), CStringW(info.sIP));
		m_ListCtrl_UserInfo.SetItemText(i, 1, MSG);
		++j;
	}
}


LRESULT CQQServerDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	CRect rect;
	GetWindowRect(&rect);
	CRect rect1 = rect;
	rect1.DeflateRect(10, 10, -10, -10);
	rect1.NormalizeRect();
	if (point.x <= rect.left + 3)
		return HTLEFT;
	else if (point.x >= rect.right - 3)
		return HTRIGHT;
	else if (point.y <= rect.top + 3)
		return HTTOP;
	else if (point.y >= rect.bottom - 3)
		return HTBOTTOM;
	else if (point.x <= rect.left + 10 && point.y <= rect.top + 10)
		return HTTOPLEFT;
	else if (point.x >= rect.right - 10 && point.y <= rect.top + 10)
		return HTTOPRIGHT;
	else if (point.x <= rect.left + 10 && point.y >= rect.bottom - 10)
		return HTBOTTOMLEFT;
	else if (point.x >= rect.right - 10 && point.y >= rect.bottom - 10)
		return HTBOTTOMRIGHT;
	else if (!rect.IsRectEmpty())
	{
		LRESULT uRet = CWnd::OnNcHitTest(point);
		uRet = (uRet == HTCLIENT) ? HTCAPTION : uRet;
		return uRet;
	}
	else
	{
		return CWnd::OnNcHitTest(point);
	}
	return 0;
	return CDialogEx::OnNcHitTest(point);
	return CDialogEx::OnNcHitTest(point);
}


void CQQServerDlg::OnNcLButtonDown(UINT nHitTest, CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值
	// TODO: 在此添加消息处理程序代码和/或调用默认值  
	if (nHitTest == HTTOP)
	{
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOP, MAKELPARAM(point.x, point.y));
	}
	else if (nHitTest == HTBOTTOM)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOM, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTLEFT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_LEFT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTRIGHT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_RIGHT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTTOPLEFT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPLEFT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTTOPRIGHT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_TOPRIGHT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTBOTTOMLEFT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMLEFT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTBOTTOMRIGHT)
		SendMessage(WM_SYSCOMMAND, SC_SIZE | WMSZ_BOTTOMRIGHT, MAKELPARAM(point.x, point.y));
	else if (nHitTest == HTCAPTION)
		SendMessage(WM_SYSCOMMAND, SC_MOVE | 4, MAKELPARAM(point.x, point.y));
	CDialogEx::OnNcLButtonDown(nHitTest, point);
}


void CQQServerDlg::OnDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult)
{
	//LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	USES_CONVERSION;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	CString Username;
	CString szIP;
	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
	int nSel = p->iItem;

	if (nSel < 0)
		return;
	Username = m_ListCtrl_UserInfo.GetItemText(p->iItem, 0);
	szIP = m_ListCtrl_UserInfo.GetItemText(p->iItem, 1);
	dlg.m_Username.Format(_T(""));
	dlg.m_Password.Format(_T(""));
	dlg.m_Username += (Username);
	dlg.m_Password += szIP;
	dlg.DoModal();
	/*Username = m_ListCtrl_UserInfo.GetItemText(p->iItem, 0);
	szIP = m_ListCtrl_UserInfo.GetItemText(p->iItem, 1);
	dlg.m_Username+=(Username);
	dlg.m_Password+=szIP;*/
	UpdateData(FALSE);
	*pResult = 0;
}


void CQQServerDlg::OnEnChangeEdtUsernumber()
{
	// TODO:  如果该控件是 RICHEDIT 控件，它将不
	// 发送此通知，除非重写 CDialogEx::OnInitDialog()
	// 函数并调用 CRichEditCtrl().SetEventMask()，
	// 同时将 ENM_CHANGE 标志“或”运算到掩码中。

	// TODO:  在此添加控件通知处理程序代码
}


LRESULT CAboutDlg::OnNcHitTest(CPoint point)
{
	// TODO:  在此添加消息处理程序代码和/或调用默认值

	LRESULT nHitTest = CDialog::OnNcHitTest(point);
	if (nHitTest == HTCLIENT)
	{
		nHitTest = HTCAPTION;
	}
	return nHitTest;
}


HBRUSH CQQServerDlg::OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor)
{
	HBRUSH hbr = CDialogEx::OnCtlColor(pDC, pWnd, nCtlColor);

	// TODO:  在此更改 DC 的任何特性

	// TODO:  如果默认的不是所需画笔，则返回另一个画笔

	if (CTLCOLOR_STATIC == nCtlColor&&pWnd->GetDlgCtrlID() == IDC_EDIT3)
	{
		pDC->SetBkColor(RGB(255, 255, 255));  //需要指定背景色的时候用 
		pDC->SetTextColor(RGB(255, 255, 255));    //文字前景色
		pDC->SetBkMode(TRANSPARENT);    //设置透明
		hbr = (HBRUSH)GetStockObject(NULL_BRUSH);  //获取画笔颜色混合后的画笔，完成透明 
		//pDC->SetBkMode(TRANSPARENT); //透明

	}

	return hbr;
}
