#pragma once
#include "shockwaveflash1.h"


// CPlayGame 对话框

class CPlayGame : public CDialogEx
{
	DECLARE_DYNAMIC(CPlayGame)

public:
	CPlayGame(CWnd* pParent = NULL);   // 标准构造函数
	virtual ~CPlayGame();

// 对话框数据
	enum { IDD = IDD_DLG_PLAY };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

	DECLARE_MESSAGE_MAP()
public:
	CShockwaveflash1 flashshow;
	virtual BOOL OnInitDialog();
//	afx_msg void OnBnClickedOk();
	virtual void OnCancel();
	virtual void PostNcDestroy();
	afx_msg void OnClose();
};
