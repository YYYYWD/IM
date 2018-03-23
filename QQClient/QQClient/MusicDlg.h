#pragma once
#include "afxcmn.h"


// CMusicDlg 对话框

class CMusicDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CMusicDlg)

public:
	CMusicDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMusicDlg();

// 对话框数据
	enum { IDD = IDD_DLG_MUSIC };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedexitbtn();
	afx_msg void OnBnClickedfilechoice();
	afx_msg void OnBnClickedplay();
	afx_msg void OnBnClickedpause();
	afx_msg void OnBnClickedstop();
	virtual BOOL OnInitDialog();
	CListCtrl m_music_list;
	afx_msg void OnDblclkMusicList(NMHDR *pNMHDR, LRESULT *pResult);
	CString m_path;
	afx_msg void OnPaint();
};
