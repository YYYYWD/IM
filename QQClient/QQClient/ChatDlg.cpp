// ChatDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "ChatDlg.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"
#include<atlconv.h>
#include "afxdialogex.h"
// CChatDlg 对话框

IMPLEMENT_DYNAMIC(CChatDlg, CDialogEx)

CChatDlg::CChatDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CChatDlg::IDD, pParent)
	, m_input(_T(""))
{

}

CChatDlg::~CChatDlg()
{
}

void CChatDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_input);
	DDX_Control(pDX, IDC_RICHEDIT21, m_hist);
	DDX_Control(pDX, IDC_PROGRESS_SHOW, m_progress_Info);
	DDX_Control(pDX, IDC_SHOCKWAVEFLASH1, m_flash);
}


BEGIN_MESSAGE_MAP(CChatDlg, CDialogEx)
	ON_BN_CLICKED(IDOK, &CChatDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BTN_SELECTION, &CChatDlg::OnBnClickedBtnSelection)
	ON_BN_CLICKED(IDC_BTN_START, &CChatDlg::OnBnClickedBtnStart)
	ON_BN_CLICKED(IDCANCEL, &CChatDlg::OnBnClickedCancel)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BTN_HIST, &CChatDlg::OnBnClickedBtnHist)
	ON_BN_CLICKED(IDC_BTN_PICTURE, &CChatDlg::OnBnClickedBtnPicture)
END_MESSAGE_MAP()


// CChatDlg 消息处理程序


BOOL CChatDlg::OnInitDialog()
{
	m_hist.SubclassDlgItem(IDC_RICHEDIT21, this);
	CString str = _T("正在和 ");
	str += info.sIP;
	str += _T("的");
	str += info.Username;
	str += _T(" 聊天中...");
	SetWindowText(str);
	CDialogEx::OnInitDialog();
	RECT rc;
	this->GetClientRect(&rc);//获得客户区的坐标

	//调整flash的位置

	rc.left = 0;

	rc.right = rc.right;



	rc.bottom = rc.bottom;

	m_flash.MoveWindow(&rc, true);



	TCHAR strCurDrt[5000];

	int nLen = ::GetCurrentDirectory(5000, strCurDrt);

	if (strCurDrt[nLen] != '\\')

	{

		strCurDrt[nLen++] = '\\';

		strCurDrt[nLen] = '\0';

	}



	CString strFileName = strCurDrt;

	strFileName += _T("high.swf");//clock.swf是flash文件的名字，该flash文件放在工程目录下。

	m_flash.LoadMovie(0, strFileName);

	m_flash.Play();
	// TODO:  在此添加额外的初始化
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


void CChatDlg::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
//	CDialogEx::OnOK();
	
	USES_CONVERSION;
	UpdateData(TRUE);
	int nCmd = 0;
	nCmd = INFO_TEXT;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	COleDateTime time = COleDateTime::GetCurrentTime();
	CString str;
	CString str1(m_input);//获取发送编辑框的值
	str.Format(_T("%d年%d月%d日 %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
	str += str1;
	str += _T("\r\n\r\n");
	//CRichEditCtrl* richEdit = (CRichEditCtrl*)GetDlgItem(IDC_RICHEDIT21);
	PARAFORMAT pf;
	pf.dwMask = PFM_ALIGNMENT;
	pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//设置成左对齐
	m_hist.SetParaFormat(pf);
	m_hist.SetSel(-1, -1);
	m_hist.ReplaceSel(str);
	PlaySound((LPCTSTR)IDR_WAVE2, AfxGetInstanceHandle(), SND_RESOURCE | SND_ASYNC);

	UserInfo Send_Info;
	strcpy(Send_Info.Text, T2A(m_input));
	strcpy(Send_Info.Username, info.Username);
	strcpy(Send_Info.From_Username, (dlg->m_info.Username));
	strcpy(Send_Info.sIP, info.sIP);
	
	CFile HistFile;

	dlg->m_sock.Send(&nCmd, sizeof(nCmd));
	dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));
	m_input.Format(_T(""));
	UpdateData(FALSE);

	CStringA name(dlg->m_info.Username);
	name += _T("说\r\n");

	CString string1(dlg->m_info.Username), str2;
	string1+=_T("和");
	str2.Format(_T("的聊天记录.txt"));
	string1 += Send_Info.Username;
	string1 += str2;
	HistFile.Open(string1, CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
	HistFile.SeekToEnd();
	//str += Send_Info.From_Username;
	
	CStringA str3;
	str3 = str;
	str3 += _T("\r\n");
	name += str3;
	HistFile.Write(name,name.GetLength());
	HistFile.Close();
	

}


void CChatDlg::OnBnClickedBtnSelection()
{
	USES_CONVERSION;
	CQQClientDlg* dlg = (CQQClientDlg*)AfxGetMainWnd();
	UserInfo Send_info;
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("请选择你要发送的文件");
	fileDlg.m_ofn.lpstrFilter = _T("All Files(*.*)\0*.*\0\0");
	if (IDOK == fileDlg.DoModal())
	{
		GetDlgItem(IDC_PROGRESS_SHOW)->ShowWindow(TRUE);
		CFile file;
		file.Open(fileDlg.GetPathName(), CFile::modeRead);

		long fileOffset = 0;
		ULONGLONG fileLen = file.GetLength();
		Send_info.fileLen = fileLen;
		strcpy(Send_info.Username, info.Username);
		strcpy(Send_info.From_Username, info.From_Username);
		strcpy(Send_info.From_Path, T2A(file.GetFilePath()));
		strcpy(Send_info.fileName, T2A(file.GetFileName()));

		int nCmd = 0;
		nCmd = INFO_FILE;
		dlg->m_sock.Send(&nCmd, sizeof(nCmd));
		int nCount = fileLen / MAX_FILE_SIZE;

		if (fileLen % MAX_FILE_SIZE != 0)//如果不能整除，次数就加1
		{
			nCount++;
		}
		m_progress_Info.SetRange(0, nCount - 1);

		dlg->m_sock.Send(&nCount, sizeof(nCount));
		char* buff = new char[MAX_FILE_SIZE];
		int i = 0;
		for (i = 0; i < nCount; i++)
		{

			int nOther = MAX_FILE_SIZE;
			if (i == nCount - 1) //如果是最后一次
			{
				nOther = fileLen % MAX_FILE_SIZE;//设定读和写的大小
			}
			file.Read(buff, nOther);
			//UserInfo Send_info;
			//Send_info.fileLen = fileLen;
			//strcpy(Send_info.Username, info.Username);
			//strcpy(Send_info.From_Username, info.From_Username);
			//strcpy(Send_info.From_Path, T2A(fileDlg.GetPathName()));
			//strcpy(Send_info.fileName, T2A(file.GetFileName()));

			//ZeroMemory(Send_info.sendFile, nOther);
			//file.Seek(fileOffset, CFile::begin);

			//file.Read(Send_info.sendFile, nOther);


			//fileOffset += nOther;
			//g->m_sock.Send(&Send_info, sizeof(Send_info));

			m_progress_Info.SetPos(i);

		}
		
		file.Close();
		dlg->m_sock.Send(&Send_info, sizeof(Send_info));
		Sleep(2000);
		if (i == nCount)
		{
			MessageBox(_T("文件发送已成功！"));
		}
		m_progress_Info.SetPos(0);
	}
}


void CChatDlg::OnBnClickedBtnStart()
{
	// TODO:  在此添加控件通知处理程序代码
}


void CChatDlg::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	//CDialogEx::OnOK();
	this->ShowWindow(SW_HIDE);
}


void CChatDlg::OnPaint()
{
	CPaintDC dc(this); // device context for painting
	// TODO:  在此处添加消息处理程序代码
	// 不为绘图消息调用 CDialogEx::OnPaint()
	
}


void CChatDlg::OnBnClickedBtnHist()
{
	// TODO:  在此添加控件通知处理程序代码
	strcpy(m_Hist_Dlg.m_info.From_Username, info.Username);
	m_Hist_Dlg.DoModal();
}


void CChatDlg::InsertBitmap(CString pBmpFile)
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


void CChatDlg::OnBnClickedBtnPicture()
{
	USES_CONVERSION;
	int nCmd = 0;
	nCmd = INFO_PICTRUE;
	// TODO:  在此添加控件通知处理程序代码
	CQQClientDlg*dlg = (CQQClientDlg*)AfxGetMainWnd();
	CFileDialog fileDlg(TRUE);
	fileDlg.m_ofn.lpstrTitle = _T("请选择你要发送的表情");
	fileDlg.m_ofn.lpstrFilter = _T("All Files(*.*)\0*.*\0\0");
	if (IDOK == fileDlg.DoModal())
	{
		
		CString str(fileDlg.GetPathName());
		COleDateTime time = COleDateTime::GetCurrentTime();
		CString str1;
		str1.Format(_T("%d年%d月%d日 %02d:%02d:%02d\r\n\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
		PARAFORMAT pf;
		pf.dwMask = PFM_ALIGNMENT;
		pf.wAlignment = PFA_RIGHT; //PFA_CENTER or PFA_LEFT//设置成左对齐
		m_hist.SetParaFormat(pf);
		m_hist.SetSel(-1, -1);
		str1 += _T("\r\n");
		m_hist.ReplaceSel(str1);
		InsertBitmap(str);
		m_hist.ReplaceSel(_T("\r\n"));
		UserInfo Send_Info;
		strcpy(Send_Info.Username, info.Username);
		strcpy(Send_Info.From_Username, (dlg->m_info.Username));
		strcpy(Send_Info.sIP, info.sIP);
		strcpy(Send_Info.From_Path, T2A(str));
		dlg->m_sock.Send(&nCmd, sizeof(nCmd));
		dlg->m_sock.Send(&Send_Info, sizeof(Send_Info));
	}

}
