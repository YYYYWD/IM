// MusicDlg.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "MusicDlg.h"
#include "afxdialogex.h"
#include"QQClientDlg.h"

// CMusicDlg 对话框
#include <MMSystem.h>  
#include <Digitalv.h>  

#pragma comment(lib, "Winmm.lib")  

HWND m_hWnd;
DWORD DeviceId;
MCI_OPEN_PARMS mciopenparms;

void Load(HWND hWnd, CString strFilepath)
{
	m_hWnd = hWnd;
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0); //在加载文件前先清空上一次播放的设备  
	mciopenparms.lpstrElementName = strFilepath; //将音乐文件路径传给设备  
	DWORD dwReturn;
	if (dwReturn = mciSendCommand(NULL, MCI_OPEN, MCI_OPEN_ELEMENT | MCI_WAIT, (DWORD)(LPVOID)&mciopenparms))
	{
		//如果打开玩家失败,将出错信息储存在buffer,并显示出错警告  
		char buffer[256];
		mciGetErrorString(dwReturn, (LPWSTR)buffer, 256); //获取错误码对应的错误信息  
		MessageBox(hWnd, (LPWSTR)buffer, _T("出错警告！"), MB_ICONHAND | MB_ICONERROR | MB_ICONSTOP); //弹出错误信息提示对话框  
	}
	DeviceId = mciopenparms.wDeviceID;
	//打开文件成功就关联文件到设备  
}

void play()
{
	MCI_PLAY_PARMS mciplayparms;
	mciplayparms.dwCallback = (DWORD)m_hWnd;
	mciplayparms.dwFrom = 0; //每次播放都是从0开始播放  
	mciSendCommand(DeviceId, MCI_PLAY, MCI_FROM | MCI_NOTIFY, (DWORD)(LPVOID)&mciplayparms);
}


void pause()
{
	mciSendCommand(DeviceId, MCI_PAUSE, 0, 0);
}


void resume()
{
	mciSendCommand(DeviceId, MCI_RESUME, 0, 0);
}

void stop()
{
	mciSendCommand(DeviceId, MCI_STOP, 0, 0);
	mciSendCommand(DeviceId, MCI_CLOSE, 0, 0);
	//当点击停止按钮时,将所有的信息都清除掉  
}


DWORD setVolume(DWORD vol)
{
	MCI_DGV_SETAUDIO_PARMS setvolume; //设置音量的参数结构体  
	setvolume.dwCallback = NULL; //  
	setvolume.dwItem = MCI_DGV_SETAUDIO_VOLUME; //动作是设置音量  
	setvolume.dwValue = vol; //音量值是vol  
	mciSendCommand(DeviceId, MCI_SETAUDIO, MCI_DGV_SETAUDIO_ITEM | MCI_DGV_SETAUDIO_VALUE, (DWORD)(LPVOID)&setvolume);
	return 0;
}







IMPLEMENT_DYNAMIC(CMusicDlg, CDialogEx)

CMusicDlg::CMusicDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CMusicDlg::IDD, pParent)
	, m_path(_T(""))
{

}

CMusicDlg::~CMusicDlg()
{
}

void CMusicDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_MUSIC_LIST, m_music_list);
	DDX_Text(pDX, IDC_filename, m_path);
}


BEGIN_MESSAGE_MAP(CMusicDlg, CDialogEx)
	ON_BN_CLICKED(IDC_exitbtn, &CMusicDlg::OnBnClickedexitbtn)
	ON_BN_CLICKED(IDC_filechoice, &CMusicDlg::OnBnClickedfilechoice)
	ON_BN_CLICKED(IDC_play, &CMusicDlg::OnBnClickedplay)
	ON_BN_CLICKED(IDC_pause, &CMusicDlg::OnBnClickedpause)
	ON_BN_CLICKED(IDC_stop, &CMusicDlg::OnBnClickedstop)
	ON_NOTIFY(NM_DBLCLK, IDC_MUSIC_LIST, &CMusicDlg::OnDblclkMusicList)
	ON_WM_PAINT()
END_MESSAGE_MAP()


// CMusicDlg 消息处理程序


void CMusicDlg::OnBnClickedexitbtn()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialog::OnCancel(); //退出  
}

void GetFileFromDir(CString csDirPath)
{
	csDirPath += _T("\\*.mp3");
	HANDLE file;
	WIN32_FIND_DATA fileData;
	char line[1024];
	char fn[1000];
	//mbstowcs(fn,csDirPath.GetBuffer(),999);  
	file = FindFirstFile(csDirPath.GetBuffer(), &fileData);
	theApp.m_musiclist.AddTail(fileData.cFileName);
	bool bState = false;
	bState = FindNextFile(file, &fileData);
	while (bState){
		//wcstombs(line,(const char*)fileData.cFileName,259);  
		theApp.m_musiclist.AddTail(fileData.cFileName);
		bState = FindNextFile(file, &fileData);
	}
}
















void CMusicDlg::OnBnClickedfilechoice()
{
	// TODO:  在此添加控件通知处理程序代码
	UpdateData(TRUE);
	CFileDialog dlg(TRUE);///TRUE为OPEN对话框，FALSE为SAVE AS对话框  
	CString csDirParth;
	CString m_csFileName;
	if (dlg.DoModal() == IDOK)
		m_csFileName = dlg.GetPathName();
	else
		m_csFileName.Empty();

	int iEndPos = 0;
	iEndPos = m_csFileName.ReverseFind('\\');
	csDirParth = m_csFileName.Left(iEndPos);
	CString musicpath = m_csFileName.Right(iEndPos);

	theApp.m_musiclist.RemoveAll();
	GetFileFromDir(csDirParth);

	POSITION pos = theApp.m_musiclist.GetHeadPosition();
	
	int i = 0;
	int nCount=theApp.m_musiclist.GetCount();
	m_music_list.DeleteAllItems();
	while (i<nCount&&pos)
	{
		m_music_list.InsertItem(i, theApp.m_musiclist.GetAt(pos)); 
		theApp.m_musiclist.GetNext(pos);
		
	}
	POSITION pos2 = theApp.m_musiclist.GetHeadPosition();
	m_path = csDirParth;
	while (pos2)
	{
		theApp.m_pathlist.AddTail(csDirParth +_T("\\") +theApp.m_musiclist.GetAt(pos2));
		theApp.m_musiclist.GetNext(pos2);
	}


	
	//Load(this->m_hWnd, strFilepath);

	//TCHAR szFileFilter[] = _T("mp3文件(*.mp3)|*.mp3|wma文件(*.wma)|*.wma|wav文件(*.wav)|*.wav|所有文件(*.*)|*.*||");
	////TCHAR szFilter[] = _T("mp3文件(*.mp3)|*.txt|图片文件(*.png)|*.png|图片文件(*.jpg)|*.jpg|所有文件(*.*)|*.*||");
	////CQQClientDlg Dlg1 = (CQQClientDlg*)AfxGetMainWnd();
	//CFileDialog dlg(TRUE, _T("mp3"), NULL, 0, szFileFilter);
	//if (dlg.DoModal() == IDOK)
	//{
	//	CString strFilepath = dlg.GetPathName();
	//	CString strFilename = dlg.GetFileName();
	//	SetDlgItemText(IDC_filename, strFilename);
	//	Load(this->m_hWnd, strFilepath);
	//}
	GetDlgItem(IDC_play)->EnableWindow(true); //文件读取成功时所有按钮变成可选  
	GetDlgItem(IDC_pause)->EnableWindow(true);
	GetDlgItem(IDC_stop)->EnableWindow(true);
	UpdateData(FALSE);
}


void CMusicDlg::OnBnClickedplay()
{
	// TODO:  在此添加控件通知处理程序代码
	play();
	SetDlgItemText(IDC_pause, _T("暂停"));
}


void CMusicDlg::OnBnClickedpause()
{
	// TODO:  在此添加控件通知处理程序代码
	CString strTemp;
	GetDlgItemText(IDC_pause, strTemp); //获取按钮的状态  
	if (strTemp.Compare(_T("暂停")) == 0)
	{
		pause();
		SetDlgItemText(IDC_pause, _T("恢复"));
	}

	if (strTemp.Compare(_T("恢复")) == 0)
	{
		resume();
		SetDlgItemText(IDC_pause, _T("暂停"));
	}
}



void CMusicDlg::OnBnClickedstop()
{
	// TODO:  在此添加控件通知处理程序代码
	stop();
	SetDlgItemText(IDC_pause, _T("暂停"));
	GetDlgItem(IDC_play)->EnableWindow(false); //当按下stop的时候,播放和暂停不可选  
	GetDlgItem(IDC_pause)->EnableWindow(false);
}


BOOL CMusicDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	m_music_list.InsertColumn(0, _T("音乐名"), 0, 200);

	
	// TODO:  在此添加额外的初始化

	return TRUE;  // return TRUE unless you set the focus to a control
	// 异常:  OCX 属性页应返回 FALSE
}


void CMusicDlg::OnDblclkMusicList(NMHDR *pNMHDR, LRESULT *pResult)
{
	UpdateData(TRUE);
	USES_CONVERSION;
	LPNMITEMACTIVATE pNMItemActivate = reinterpret_cast<LPNMITEMACTIVATE>(pNMHDR);
	// TODO:  在此添加控件通知处理程序代码
	NM_LISTVIEW*p = (NM_LISTVIEW*)pNMHDR;
	int nSel = p->iItem;

	if (nSel < 0)
		return;
	CString str=m_music_list.GetItemText(p->iItem, 0);
	POSITION pos = theApp.m_musiclist.GetHeadPosition();
	POSITION pos1 = theApp.m_pathlist.GetHeadPosition();
	while (pos)
	{
		if (!strcmp(T2A(theApp.m_musiclist.GetAt(pos)), T2A(str)))
		{
			Load(this->m_hWnd, theApp.m_pathlist.GetAt(pos1));
			play();
			SetDlgItemText(IDC_pause, _T("暂停"));
			//theApp.m_pathlist.GetNext(pos1);
			//while (pos1)
			//{
			//	Load(this->m_hWnd, theApp.m_pathlist.GetAt(pos1));
			//	play();
			//	//SetDlgItemText(IDC_pause, _T("暂停"));
			//	theApp.m_pathlist.GetNext(pos1);
			//}
			break;
			
		}
		theApp.m_musiclist.GetNext(pos);
		theApp.m_pathlist.GetNext(pos1);
	}
	
	*pResult = 0;
}


void CMusicDlg::OnPaint()
{
	CPaintDC dc(this);
	CRect rect;
	GetClientRect(&rect);
	CDC dcMem;
	dcMem.CreateCompatibleDC(&dc);
	CBitmap bmpBackground;
	bmpBackground.LoadBitmap(IDB_BITMAP6);
	BITMAP bitmap;
	bmpBackground.GetBitmap(&bitmap);
	CBitmap *pbmpOld = dcMem.SelectObject(&bmpBackground);
	dc.SetStretchBltMode(HALFTONE);             //*添加于此
	dc.StretchBlt(0, 0, rect.Width(), rect.Height(), &dcMem, 0, 0,
		bitmap.bmWidth, bitmap.bmHeight, SRCCOPY);
}
