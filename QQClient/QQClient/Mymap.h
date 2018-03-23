#pragma once
#include "explorer1.h"


// CMymap 对话框

class CMymap : public CDialogEx
{
	DECLARE_DYNAMIC(CMymap)

public:
	CMymap(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CMymap();

// 对话框数据
	enum { IDD = IDD_DLG_MAP };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CExplorer1 m_ie;
	virtual BOOL OnInitDialog();
	CString m_start1;
	CString m_end1;
	CString m_start2;
	CString m_end2;
	CString m_find;
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
};
