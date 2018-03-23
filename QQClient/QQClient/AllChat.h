#pragma once
#include "afxcmn.h"
#include <afxole.h>
#include <richole.h>
#include"AllHist.h"

// CAllChat 对话框

class CAllChat : public CDialogEx
{
	DECLARE_DYNAMIC(CAllChat)

public:
	CAllChat(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAllChat();

// 对话框数据
	enum { IDD = IDD_ALL_CHAT };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_hist;
	CString m_input;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnPicture();
	void InsertBitmap(CString pBmpFile);
	CAllHist m_hist_dlg;
	afx_msg void OnBnClickedBtnHist();
};
