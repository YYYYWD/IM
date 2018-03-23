
// QQClientDlg.h : 头文件
//
#pragma once
#include"SocketC.h"
#include"Login.h"
#include "afxcmn.h"
#include"AllChat.h"
#include"MusicDlg.h"
#include"URL.h"
#include"Mymap.h"
#include"PlayGame.h"
// CQQClientDlg 对话框

class CQQClientDlg : public CDialogEx
{
// 构造
public:
	CQQClientDlg(CWnd* pParent = NULL);	// 标准构造函数
	~CQQClientDlg();
// 对话框数据
	enum { IDD = IDD_QQCLIENT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;
	LRESULT OnShowTask(WPARAM wParam, LPARAM lParam);
	PROCSWITCHTOTHISWINDOW SwitchToThisWindow;
	BOOL DestroyWindow();
	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

public:
	CPlayGame *m_game;
	CMymap *m_map;
	CAllChat*m_all_chatdlg;
	CURL *m_url;
	CSocketC m_sock;
	CLogin m_dlg;
	UserInfo m_info;
	NOTIFYICONDATA m_nid;
	CString m_username;
	CListCtrl m_friendlist;
//	afx_msg void OnDblclkListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedBtnRefresh();
//	afx_msg void OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnDblclkListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnLvnItemchangedListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
//	afx_msg void OnClickListUserinfo(NMHDR *pNMHDR, LRESULT *pResult);
	void OnText(UserInfo info);
	CString m_MyselfName;
	CString OnFile(UserInfo Rece_Info);
	afx_msg LRESULT OnNcHitTest(CPoint point);
//	afx_msg void OnNcLButtonDown(UINT nHitTest, CPoint point);
//	afx_msg void OnBnClickedOk();
//	afx_msg void OnBnClickedCancel();
	afx_msg void OnEnChangeMUsername();
	afx_msg void OnBnClickedBtnAllchat();
	void OnAllText(UserInfo info);
	afx_msg void OnTimer(UINT_PTR nIDEvent);
//	afx_msg void OnMouseMove(UINT nFlags, CPoint point);
	afx_msg void OnLButtonDown(UINT nFlags, CPoint point);
	CMusicDlg *m_Music_dlg;
	afx_msg void OnBnClickedBynPlay();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedBtnMap();
	afx_msg void OnClose();
	afx_msg void OnBnClickedBtnPaly();
	afx_msg void OnBnClickedBtnMenu();
//	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	afx_msg HBRUSH OnCtlColor(CDC* pDC, CWnd* pWnd, UINT nCtlColor);
	CString m_MyIP;
	void OnPicture(UserInfo info);
	void OnAllPicture(UserInfo info);
};
