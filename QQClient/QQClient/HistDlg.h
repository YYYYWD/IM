#pragma once
#include "afxcmn.h"


// CHistDlg 对话框

class CHistDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CHistDlg)

public:
	CHistDlg(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CHistDlg();

// 对话框数据
	enum { IDD = IDD_CHAT_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	UserInfo m_info;
	CRichEditCtrl m_hist;
};
