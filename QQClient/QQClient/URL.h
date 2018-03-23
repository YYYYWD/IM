#pragma once


// CURL 对话框

class CURL : public CDialogEx
{
	DECLARE_DYNAMIC(CURL)

public:
	CURL(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CURL();

// 对话框数据
	enum { IDD = IDD_DLG_URL };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CString m_Add;
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedCancel();
};
