#pragma once

// CSocketC ÃüÁîÄ¿±ê

class CSocketC : public CSocket
{
public:
	CSocketC();
	virtual ~CSocketC();
	virtual void OnReceive(int nErrorCode);
//	void OnBrow();
};


