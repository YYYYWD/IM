// SocketC.cpp : 实现文件
//

#include "stdafx.h"
#include "QQServer.h"
#include "SocketC.h"
#include<atlconv.h>
#include"QQServerDlg.h"
#define MAX_FILE_SIZE 5000
// CSocketC

CSocketC::CSocketC()
{
}

CSocketC::~CSocketC()
{
}


// CSocketC 成员函数


void CSocketC::OnReceive(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	USES_CONVERSION;
	int nCmd;
	CString szIP;
	UINT nPort;
	GetPeerName(szIP, nPort);//获取客户端IP和端口号
	Receive(&nCmd, sizeof(nCmd));
	CQQServerDlg*dlg = (CQQServerDlg*)AfxGetMainWnd();
	switch (nCmd)
	{
	case INFO_ADD:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		
		int a = 0;
		a=dlg->OnAdd(info);
		Send(&a, sizeof(a));
		if (a == INFO_ADD)
		{
			CString str;
			COleDateTime time = COleDateTime::GetCurrentTime();
			str.Format(_T("\r\n%d年%d月%d日 %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());
			CString str1;
			str1.Format(_T("%s成功注册！\r\n"), (CStringW)info.Username);
			CFile Write_File;
			str += str1;
			CStringA str2(str);
			Write_File.Open(_T("服务器日志.txt"), CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
			Write_File.SeekToEnd();
			Write_File.Write(str2, str2.GetLength());
			Write_File.Close();

		}
		break;
		
	}
	case INFO_LOGIN:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		info.nPort = nPort;
		info.pSock = this;
	//	strcpy_s(info.sIP, T2A(szIP));
		int a = 0;
		a = dlg->OnLogin(info);
		Send(&a, sizeof(a));
		if (a == INFO_LOGIN)
		{
			dlg->OnReceive(info);
			theApp.m_list.AddTail(info);
		}
		
		break;
	}
	case INFO_BROW:
	{
		OnBrow();
		break;
	}
	case INFO_TEXT:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		SendText(info);
		
		break;
	}
	case INFO_ALLTEXT:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		Send_All_Text(info);
		break;
	}
	case INFO_FILE:
	{
		int nCount = 0;
		this->Receive(&nCount, sizeof(nCount));
		SendFile(nCount);

		break;
	}
	case INFO_PICTRUE:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		OnPicture(info);
		break;
	}
	case INFO_ALLPICTURE:
	{
		UserInfo info;
		this->Receive(&info, sizeof(info));
		OnAllPicture(info);
		break;
	}
	}






	CSocket::OnReceive(nErrorCode);
}



void CSocketC::OnBrow()
{
	
	int nCount = theApp.m_list.GetCount();
	int nCmd = 0;
	nCmd = INFO_BROW;
	Send(&nCmd, sizeof(nCmd));
	Send(&nCount, sizeof(nCount));
	POSITION pos = theApp.m_list.GetHeadPosition();
	while (pos != NULL)
	{
		UserInfo &Oldinfo = theApp.m_list.GetNext(pos);
		Send(&Oldinfo, sizeof(Oldinfo));
	}

}


void CSocketC::OnClose(int nErrorCode)
{
	// TODO:  在此添加专用代码和/或调用基类
	USES_CONVERSION;
	// TODO:  在此添加专用代码和/或调用基类
	CQQServerDlg*Dlg = (CQQServerDlg*)AfxGetMainWnd();
	POSITION pos = theApp.m_list.GetHeadPosition();
	while (pos)
	{
		if (theApp.m_list.GetAt(pos).pSock == this)
		{
			USES_CONVERSION;
			CString str;
			CString str1;
			COleDateTime time = COleDateTime::GetCurrentTime();
			str1.Format(_T("\r\n%d年%d月%d日 %02d:%02d:%02d\r\n"), time.GetYear(), time.GetMonth(), time.GetDay(), time.GetHour(), time.GetMinute(), time.GetSecond());


			//将CSocketC的OnReceive函数发送过来的IP,端口,消息处理成一条语句
			str.Format(_T("%s- %d:\r\n %s\r已经离线！\n"), A2T(theApp.m_list.GetAt(pos).sIP), theApp.m_list.GetAt(pos).nPort, A2T(theApp.m_list.GetAt(pos).Username));
			str1 += str;
			int nLen = Dlg->m_hist.GetWindowTextLength();
			Dlg->m_hist.SetSel(nLen, -1);//m_szText是编辑框添加的控件变量
			Dlg->m_hist.ReplaceSel(str1);
			theApp.m_list.RemoveAt(pos);
			CFile Write_File;
			CStringA str2(str1);
			Write_File.Open(_T("服务器日志.txt"), CFile::shareDenyNone | CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite);
			Write_File.SeekToEnd();
			Write_File.Write(str2,str2.GetLength());
			Write_File.Close();
			break;
		}
		theApp.m_list.GetNext(pos);
	}
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos1)
	{
		if (theApp.m_list1.GetAt(pos1) == this)
		{
			theApp.m_list1.RemoveAt(pos1);
			break;
		}
		theApp.m_list.GetNext(pos1);
	}

	delete this;
	Dlg->OnUpdata();
	Dlg->i--;
	if (Dlg->i < 0)
		Dlg->i = 0;
	Dlg->m_user_number = Dlg->i;
	
	Dlg->UpdateData(FALSE);
	CSocket::OnClose(nErrorCode);
}


void CSocketC::SendText(UserInfo info)
{
	int nCmd = 0;
	nCmd = INFO_TEXT;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (!strcmp(theApp.m_list.GetAt(pos2).Username, info.Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&info, sizeof(info));
			break;
		}
		theApp.m_list.GetNext(pos2);
	}

}


void CSocketC::SendFile(int nCount)
{
	int nCmd = 0;
	nCmd = INFO_FILE;
	int Count = nCount;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	UserInfo Send_Info;
	//int nOther = MAX_FILE_SIZE;
	//CFile Rece_File;
	//CString str1;
	//Rece_File.Open(_T("E:\\HHH.jpg"), CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);

	//str1.Format(_T("E:\\%s"),CStringW(Send_Info.fileName));
	//Rece_File.Open(str1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeWrite);
	//if (Send_Info.fileLen < MAX_FILE_SIZE)
	//nOther = Send_Info.fileLen;
	////Rece_File.Write(Send_Info.sendFile, nOther);
	//for (int i = 1; i < nCount; i++)
	//{
	//	
	//	if (i == nCount - 1) //如果是最后一次
	//	{
	//		nOther = (Send_Info.fileLen)% MAX_FILE_SIZE;//设定读和写的大小
	//	}

	//	this->Receive(&Send_Info, sizeof(Send_Info));
	//	//Rece_File.Write(Send_Info.sendFile, nOther);
	//}
	//	Rece_File.Flush();
	//Rece_File.Close();



	this->Receive(&Send_Info, sizeof(Send_Info));
	long fileOffset = 0;
	while (pos2)
	{
		if (!strcmp(theApp.m_list.GetAt(pos2).Username, Send_Info.Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&Send_Info, sizeof(Send_Info));
			break;
		}
		theApp.m_list.GetNext(pos2);
	}

	//CFile Read_File;
	//
	//Read_File.Open(str1, CFile::modeRead);
	//UserInfo To_Info(Send_Info);
	//int i = 0;
	//for (i = 1; i < nCount; i++)
	//{
	//	
	//	
	//	int Other = MAX_FILE_SIZE;
	//	if (i == nCount - 1) //如果是最后一次
	//	{
	//		Other = To_Info.fileLen % MAX_FILE_SIZE;//设定读和写的大小
	//	}
	//	ZeroMemory(To_Info.sendFile, Other);
	//	
	//	Read_File.Seek(fileOffset, CFile::begin);

	//	Read_File.Read(To_Info.sendFile, nOther);

	//	fileOffset += Other;

	//	(theApp.m_list.GetAt(pos2).pSock)->Send(&To_Info, sizeof(To_Info));


	//}
	//Read_File.Close();
	//theApp.m_list.GetAt(pos2).pSock->Send(&To_Info, sizeof(To_Info));
	//if (Send_Info.fileLen < MAX_FILE_SIZE)
		//nOther = Send_Info.fileLen;
	////Rece_File.Write(Send_Info.sendFile, nOther);
	//for (int i = 1; i < nCount; i++)
	//{
	//	
	//	if (i == nCount - 1) //如果是最后一次
	//	{
	//		nOther = (Send_Info.fileLen)% MAX_FILE_SIZE;//设定读和写的大小
	//	}

	//	this->Receive(&Send_Info, sizeof(Send_Info));
	//	//Rece_File.Write(Send_Info.sendFile, nOther);
	//}
//	Rece_File.Flush();
	//Rece_File.Close();

	
	
	//this->Receive(&Send_Info, sizeof(Send_Info));

	//while (pos2)
	//{
	//	if (!strcmp(theApp.m_list.GetAt(pos2).Username, Send_Info.Username))
	//	{
	//		(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
	//		//(theApp.m_list.GetAt(pos2).pSock)->Send(&nCount, sizeof(nCount));
	//		(theApp.m_list.GetAt(pos2).pSock)->Send(&Send_Info, sizeof(Send_Info));
	//		break;
	//	}
	//	theApp.m_list.GetNext(pos2);
	//}
	//CFile Read_File;
	//fileOffset = 0;
	//Read_File.Open(str1, CFile::modeCreate | CFile::modeNoTruncate | CFile::modeReadWrite|CFile::typeBinary);
	//for (int i = 0; i < nCount; i++)
	//{
	//	ZeroMemory(buff, MAX_FILE_SIZE);
	//	int nOther = MAX_FILE_SIZE;//每次读和写的大小，最开始初始为缓冲区大小
	//	if (i == nCount - 1) //如果是最后一次
	//	{
	//		nOther = Send_Info.fileLen % MAX_FILE_SIZE;//设定读和写的大小
	//	}
	//	Read_File.Seek(fileOffset, CFile::begin);
	//	Read_File.Read(buff, nOther);

	//	(theApp.m_list.GetAt(pos2).pSock)->Send(buff, nOther);
	//	fileOffset += nOther;
	//}

	//CFile Read_File;
	//
	//Read_File.Open(str1, CFile::modeRead);
	//UserInfo To_Info(Send_Info);
	//int i = 0;
	//for (i = 1; i < nCount; i++)
	//{
	//	
	//	
	//	int Other = MAX_FILE_SIZE;
	//	if (i == nCount - 1) //如果是最后一次
	//	{
	//		Other = To_Info.fileLen % MAX_FILE_SIZE;//设定读和写的大小
	//	}
	//	ZeroMemory(To_Info.sendFile, Other);
	//	
	//	Read_File.Seek(fileOffset, CFile::begin);

	//	Read_File.Read(To_Info.sendFile, nOther);

	//	fileOffset += Other;

	//	(theApp.m_list.GetAt(pos2).pSock)->Send(&To_Info, sizeof(To_Info));


	//}
	//Read_File.Close();
	//theApp.m_list.GetAt(pos2).pSock->Send(&To_Info, sizeof(To_Info));
	

}


void CSocketC::OnUpdata()
{
	int nCmd = 0;
	nCmd = INFO_BROW;
	
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	POSITION pos3 = theApp.m_list1.GetHeadPosition();
	while (pos3)
	{
		while (pos2)
		{
			UserInfo info = theApp.m_list.GetAt(pos2);
			theApp.m_list1.GetAt(pos3)->Send(&nCmd, sizeof(nCmd));
			theApp.m_list1.GetAt(pos3)->Send(&info,sizeof(info));
			theApp.m_list.GetNext(pos2);
		}
		theApp.m_list1.GetNext(pos3);
		
	}
}


void CSocketC::Send_All_Text(UserInfo info)
{
	int nCmd = INFO_ALLTEXT;
	/*POSITION pos1 = theApp.m_list1.GetHeadPosition();
	
	while (pos1&&theApp.m_list1.GetAt(pos1)!=this)
	{
		theApp.m_list1.GetAt(pos1)->Send(&nCmd, sizeof(nCmd));
		theApp.m_list1.GetAt(pos1)->Send(&info, sizeof(info));
		theApp.m_list1.GetNext(pos1);
	}
*/
	
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (strcmp(theApp.m_list.GetAt(pos2).Username, info.From_Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&info, sizeof(info));
			
		}
		theApp.m_list.GetNext(pos2);
	}
	/*POSITION pos2 = theApp.m_list1.GetHeadPosition();
	while (pos2)
	{
		theApp.m_list1.GetAt(pos2)->Send(&nCmd, sizeof(nCmd));
		theApp.m_list1.GetAt(pos2)->Send(&info, sizeof(info));
		theApp.m_list1.GetNext(pos2);
	}
*/
}
void CSocketC::OnExit(UserInfo info)
{
	int nCmd = 0;
	nCmd = INFO_BYE;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (!strcmp(theApp.m_list.GetAt(pos2).Username, info.Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&info, sizeof(info));
			break;
		}
		theApp.m_list.GetNext(pos2);
	}
}

void CSocketC::OnPicture(UserInfo info)
{
	int nCmd = 0;
	nCmd = INFO_PICTRUE;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (!strcmp(theApp.m_list.GetAt(pos2).Username, info.Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&info, sizeof(info));
			break;
		}
		theApp.m_list.GetNext(pos2);
	}
}


void CSocketC::OnAllPicture(UserInfo info)
{
	int nCmd = 0;
	nCmd = INFO_ALLPICTURE;
	POSITION pos = theApp.m_list.GetHeadPosition();
	POSITION pos1 = theApp.m_list1.GetHeadPosition();
	while (pos)
	{
		theApp.m_list.GetAt(pos).pSock = theApp.m_list1.GetAt(pos1);
		theApp.m_list.GetNext(pos);
		theApp.m_list1.GetNext(pos1);
	}
	POSITION pos2 = theApp.m_list.GetHeadPosition();
	while (pos2)
	{
		if (strcmp(theApp.m_list.GetAt(pos2).Username, info.From_Username))
		{
			(theApp.m_list.GetAt(pos2).pSock)->Send(&nCmd, sizeof(nCmd));
			(theApp.m_list.GetAt(pos2).pSock)->Send(&info, sizeof(info));

		}
		theApp.m_list.GetNext(pos2);
	}
}
