// AllChat.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "AllChat.h"
#include "afxdialogex.h"
#include<atlconv.h>
#include"QQClientDlg.h"
#include<string.h>

// CAllChat 对话框

IMPLEMENT_DYNAMIC(CAllChat, CDialogEx)

CAllChat::CAllChat(CWnd* pParent /*=NULL*/)
	: CDialogEx(CAllChat::IDD, pParent)
	, m_input(_T(""))
{

}

CAllChat::~CAllChat()
{
}

void CAllChat::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_RICHEDIT21, m_hist);
	DDX_Text(pDX, IDC_EDIT1, m_input);
}


BEGIN_MESSAGE_MAP(CAllChat, CDialogEx)
	ON_BN_CLICKED(IDOK, &CAllChat::OnBnClickedOk)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_PICTURE, &CAllChat::OnBnClickedBtnPicture)
	ON_BN_CLICKED(IDC_BTN_HIST, &CAllChat::OnBnClickedBtnHist)
END_MESSAGE_MAP()


// CAllChat 消息处理程序


void CAllChat::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	CFile WriteFile;
	USES_CONVERSION;
	UpdateData(TRUE);
	int nCmd = 0;
	nCmd = INFO_ALLTEXT;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString str;
	CString str1(m_input);//获取发送编辑框的值
	CString name;
	CString name1;
	str.Format(_T("%d年%d月%d日 %02d:%02d:%02d "), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	name.Format(_T(" %s说"), CStringW(dlg->m_info.Username));
	name1.Format(_T("%s的聊天室.txt"), CStringW(dlg->m_info.Username));
	str += name;
	str += _T("\r\n");
	str += str1;
	str += _T("\r\n");
	//CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);
	PARAFORMAT pf;
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//设置成左对齐
	m_hist.SetParaFormat(pf);
	m_hist.SetSel(-1, -1);
	m_hist.ReplaceSel(str);
	
	
	CStringA str2(str);
	WriteFile.Open(name1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	WriteFile.SeekToEnd();
	WriteFile.Write(str2, str2.GetLength());
	WriteFile.Close();
	
	UserInfo Send_Info;
	strcpy_s(Send_Info.Text, T2A(m_input));
	strcpy_s(Send_Info.From_Username, (dlg->m_info.Username));
	strcpy_s(Send_Info.From_sIP, dlg->m_info.sIP);
	PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);
	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));

	
	m_input.Format(_T(""));
	UpdateData(FALSE);



}


void CAllChat::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	//CFont * f;
	//f = new CFont;
	//f->CreateFont(20, // nHeight   
	//	0, // nWidth   
	//	0, // nEscapement   
	//	0, // nOrientation   
	//	FW_BOLD, // nWeight   
	//	TRUE, // bItalic   
	//	FALSE, // bUnderline   
	//	0, // cStrikeOut   
	//	ANSI_CHARSET, // nCharSet   
	//	OUT_DEFAULT_PRECIS, // nOutPrecision   
	//	CLIP_DEFAULT_PRECIS, // nClipPrecision   
	//	DEFAULT_QUALITY, // nQuality   
	//	DEFAULT_PITCH | FF_SWISS, // nPitchAndFamily   
	//	_T("微软雅黑")); // lpszFac   
	//GetDlgItem(IDC_RICHEDIT21)->SetFont(f);
	//GetDlgItem(IDC_EDIT1)->SetFont(f);
}


BOOL CAllChat::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	SetWindowText(_T("聊天室"));
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
	GetDlgItem(IDC_RICHEDIT21)->SetFont(f);
	GetDlgItem(IDC_EDIT1)->SetFont(f);
	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CAllChat::OnBnClickedBtnPicture()
{
	// TODO:  在此添加控件通知处理程序代码
	int nCmd;
	nCmd = INFO_ALLPICTURE;
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("请选择你要发送的表情");
	fileDlg.m_ofn.lpstrFilter = _T("All Files(*.*)\0*.*\0\0");
	if (IDOK == fileDlg.DoModal())
	{
		USES_CONVERSION;
		CString str(fileDlg.GetPathName());
		CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
		COleDateTime time = COleDateTime::GetCurrentTime();
		CString str1;
		str1.Format(_T("%d年%d月%d日 %02d:%02d:%02d "), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		CString name;
		name.Format(_T(" %s说\r\n"), CStringW(dlg->m_info.Username));
		str1 += name;
		PARAFORMAT pf;
		pf.dwMask = PFM_ALIGNMENT;
		pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//设置成左对齐
		m_hist.SetParaFormat(pf);
		m_hist.SetSel(-1, -1);
		m_hist.ReplaceSel(str1);
		InsertBitmap(str);
		m_hist.ReplaceSel(_T("\r\n"));
		UserInfo Send_Info;
		strcpy(Send_Info.From_Username, (dlg->m_info.Username));
		strcpy(Send_Info.From_sIP, dlg->m_info.sIP);
		strcpy(Send_Info.From_Path, T2A(str));
		dlg->m_sock.Send(&nCmd, sizeof(nCmd));
		dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));
	}
}


void CAllChat::InsertBitmap(CString pBmpFile)
{
	HBITMAP hBmp;
	hBmp = (HBITMAP)::LoadImage(NULL, pBmpFile, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE | LR_DEFAULTCOLOR | LR_DEFAULTSIZE);


	STGMEDIUM stgm;
	stgm.tymed = TYMED_GDI;
	stgm.hBitmap = hBmp;
	stgm.pUnkForRelease = NULL;


	FORMATETC fm;
	fm.cfFormat = CF_BITMAP;
	fm.ptd = NULL;
	fm.dwAspect = DVASPECT_CONTENT;
	fm.lindex = -1;
	fm.tymed = TYMED_GDI;


	//创建输入数据源  
	IStorage* pStorage;


	//分配内存  
	LPLOCKBYTES lpLockBytes = NULL;
	SCODE sc = CreateILockBytesOnHGlobal(NULL, TRUE, &lpLockBytes);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}
	ASSERT(lpLockBytes != NULL);


	sc = StgCreateDocfileOnILockBytes(lpLockBytes, STGM_SHARE_EXCLUSIVE | STGM_CREATE | STGM_READWRITE, 0, &pStorage);
	if (sc != S_OK)
	{
		VERIFY(lpLockBytes->Release() == 0);
		lpLockBytes = NULL;
		AfxThrowOleException(sc);
	}
	ASSERT(pStorage != NULL);


	COleDataSource* pDataSource = new COleDataSource;
	pDataSource->CacheData(CF_BITMAP, &stgm);
	LPDATAOBJECT lpDataObject = (LPDATAOBJECT)pDataSource->GetInterface(&IID_IDataObject);


	//获取RichEdit的OLEClientSite  
	LPOLECLIENTSITE lpClientSite;
	m_hist.GetIRichEditOle()->GetClientSite(&lpClientSite);


	//创建OLE对象  
	IOleObject* pOleObject;
	sc = OleCreateStaticFromData(lpDataObject, IID_IOleObject, OLERENDER_FORMAT, &fm, lpClientSite, pStorage, (void**)&pOleObject);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}


	//插入ole对象  
	REOBJECT reObject;
	ZeroMemory(&reObject, sizeof(reObject));
	reObject.cbStruct = sizeof(REOBJECT);


	CLSID clsid;
	sc = pOleObject->GetUserClassID(&clsid);
	if (sc != S_OK)
	{
		AfxThrowOleException(sc);
	}


	reObject.clsid = clsid;
	reObject.cp = REO_CP_SELECTION;
	reObject.dvaspect = DVASPECT_CONTENT;
	reObject.poleobj = pOleObject;
	reObject.polesite = lpClientSite;
	reObject.pstg = pStorage;


	HRESULT hr = m_hist.GetIRichEditOle()->InsertObject(&reObject);


	delete pDataSource;
}


void CAllChat::OnBnClickedBtnHist()
{
	// TODO:  在此添加控件通知处理程序代码
	USES_CONVERSION;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	strcpy(m_hist_dlg.m_info.Username,T2A(dlg->m_MyselfName));
	m_hist_dlg.DoModal();
	//if (m_hist_dlg == NULL)//没创建
	//{
	//	m_hist_dlg = new CAllHist;
	//	m_hist_dlg->Create(IDD_DLG_ALL_HIST);
	//}

	//m_hist_dlg->ShowWindow(SW_SHOW);
	
}