#pragma once
#include "afxwin.h"


// CNewuser 对话框

class CNewuser : public CDialogEx
{
	DECLARE_DYNAMIC(CNewuser)

public:
	CNewuser(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CNewuser();

// 对话框数据
	enum { IDD = IDD_NEWUSER };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_newusername;
	CString m_newpassword1;
	CString m_newpassword2;
	afx_msg void OnBnClickedOk();
	afx_msg void OnPaint();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	virtual BOOL OnInitDialog();
	CEdit m_edt1;
	CEdit m_edt2;
	CEdit m_edt3;
};
