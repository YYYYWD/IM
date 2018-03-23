#pragma once

// CSocketL ÃüÁîÄ¿±ê

class CSocketL : public CSocket
{
public:
	CSocketL();
	virtual ~CSocketL();
	virtual void OnAccept(int nErrorCode);
};


