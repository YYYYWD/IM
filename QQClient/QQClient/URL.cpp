// URL.cpp : 实现文件
//

#include "stdafx.h"
#include "QQClient.h"
#include "URL.h"
#include "afxdialogex.h"
#define READ_BYTE_SIZE     1024  
#include <afxinet.h>

// CURL 对话框

IMPLEMENT_DYNAMIC(CURL, CDialogEx)

CURL::CURL(CWnd* pParent /*=NULL*/)
	: CDialogEx(CURL::IDD, pParent)
	, m_Add(_T(""))
{

}

CURL::~CURL()
{
}

void CURL::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT1, m_Add);
}


BEGIN_MESSAGE_MAP(CURL, CDialogEx)
	ON_BN_CLICKED(IDOK, &CURL::OnBnClickedOk)
	ON_BN_CLICKED(IDCANCEL, &CURL::OnBnClickedCancel)
END_MESSAGE_MAP()


// CURL 消息处理程序


void CURL::OnBnClickedOk()
{
	// TODO:  在此添加控件通知处理程序代码
	CString m_PathName;
	CFileDialog    dlg(FALSE, _T("*.*"), NULL,
		OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT,
		_T("All Files (*.*)|*.*||"),
		NULL); //弹出保存对话框，
	if (dlg.DoModal() != IDOK)
		return;
	m_PathName = dlg.GetPathName();

	CInternetSession    is;
	CStdioFile        *psf;
	UpdateData();
	psf = is.OpenURL(m_Add, 1, INTERNET_FLAG_TRANSFER_BINARY | INTERNET_FLAG_RELOAD);
	CFile    file(m_PathName,
		CFile::modeCreate | CFile::modeWrite | CFile::typeBinary);//建立本地文件

	char    buf[READ_BYTE_SIZE];
	int    readbyte;
	while (1)
	{
		readbyte = psf->Read(buf, READ_BYTE_SIZE);//每次下载READ_BYTE_SIZE字节数据
		if (!readbyte)
			break;
		file.Write(buf, readbyte); //把下载的数据写入到文件中
	}

	psf->Close();
	file.Close();
	delete psf;
	CString string1 = _T("文件已经保存在");
	string1 += m_PathName;
	MessageBox(string1);
}


void CURL::OnBnClickedCancel()
{
	// TODO:  在此添加控件通知处理程序代码
	CDialogEx::OnOK();
}
