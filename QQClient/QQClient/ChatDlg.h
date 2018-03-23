#pragma once
#include "stdafx.h"
#include "afxcmn.h"
#include"HistDlg.h"
#include <afxole.h>
#include <richole.h>
#include "shockwaveflash1.h"
#define MAX_FILE_SIZE 5000
// CChatDlg 对话框

class CChatDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CChatDlg)

public:
	CChatDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CChatDlg();

// 对话框数据
	enum { IDD = IDD_CHAR_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	UserInfo info;
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedOk();
	CString m_input;
	CRichEditCtrl m_hist;
	CProgressCtrl m_progress_Info;
	afx_msg void OnBnClickedBtnSelection();
	afx_msg void OnBnClickedBtnStart();
	afx_msg void OnBnClickedCancel();
	afx_msg void OnPaint();
	afx_msg void OnBnClickedBtnHist();
	CHistDlg m_Hist_Dlg;
	void InsertBitmap(CString pBmpFile);
	afx_msg void OnBnClickedBtnPicture();
	CShockwaveflash1 m_flash;
};
