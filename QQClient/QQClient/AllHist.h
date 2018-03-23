#pragma once
#include "afxcmn.h"


// CAllHist 对话框

class CAllHist : public CDialogEx
{
	DECLARE_DYNAMIC(CAllHist)

public:
	CAllHist(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CAllHist();

// 对话框数据
	enum { IDD = IDD_DLG_ALL_HIST };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CRichEditCtrl m_hist;
	virtual BOOL OnInitDialog();
	UserInfo m_info;
};
