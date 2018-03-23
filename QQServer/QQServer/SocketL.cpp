// SocketL.cpp : 实现文件
//

#include "stdafx.h"
#include "QQServer.h"
#include "SocketL.h"
#include"SocketC.h"

// CSocketL

CSocketL::CSocketL()
{
}

CSocketL::~CSocketL()
{
}


// CSocketL 成员函数


void CSocketL::OnAccept(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	CSocketC *p = new CSocketC;
	if (!Accept(*p))
	{
		delete p;
		return;
	}
	theApp.m_list1.AddTail(p);
	CSocket::OnAccept(nErrorCode);

}
