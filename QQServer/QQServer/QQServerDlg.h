
// QQServerDlg.h : 头文件
//

#pragma once
#include"SocketL.h"
#include"SocketC.h"
#include "afxwin.h"
#include "afxcmn.h"
#include"LoginDlg.h"
#include"User.h"
// CQQServerDlg 对话框
class CQQServerDlg : public CDialogEx
{
// 构造
public:
	CQQServerDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_QQSERVER_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	CSocketL m_sock;
	_ConnectionPtr m_pConn;
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	int OnAdd(UserInfo info);
	int OnLogin(UserInfo info);
	void OnReceive(UserInfo info);
	CEdit m_hist;
	CListCtrl m_ListCtrl_UserInfo;
	int i = 0;
	int m_user_number;
	void OnUpdata();
	afx_msg LRESULT OnNcHitTest(CPoint point);
	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
	CLoginDlg m_dlg;
	afx_msg void OnDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);
	CUser dlg;
	afx_msg void OnEnChangeEdtUsernumber();
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CStatic m_static;
	CEdit m_now;
};
