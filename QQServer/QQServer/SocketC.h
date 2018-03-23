#pragma once

// CSocketC ÃüÁîÄ¿±ê

class CSocketC : public CSocket
{
public:
	CSocketC();
	virtual ~CSocketC();
	virtual void OnReceive(int nErrorCode);
//	virtual void OnClose(int nErrorCode);
	void OnBrow();
	virtual void OnClose(int nErrorCode);
	void SendText(UserInfo info);
	void SendFile(int nCount);
	void OnUpdata();
	void Send_All_Text(UserInfo info);
	static void OnExit(UserInfo info);
	void OnPicture(UserInfo info);
	void OnAllPicture(UserInfo info);
};


