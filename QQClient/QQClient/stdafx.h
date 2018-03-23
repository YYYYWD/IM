
// stdafx.h : 标准系统包含文件的包含文件，
// 或是经常使用但不常更改的
// 特定于项目的包含文件

#pragma once

#ifndef VC_EXTRALEAN
#define VC_EXTRALEAN            // 从 Windows 头中排除极少使用的资料
#endif

#include "targetver.h"

#define _ATL_CSTRING_EXPLICIT_CONSTRUCTORS      // 某些 CString 构造函数将是显式的

// 关闭 MFC 对某些常见但经常可放心忽略的警告消息的隐藏
#define _AFX_ALL_WARNINGS

#include <afxwin.h>         // MFC 核心组件和标准组件
#include <afxext.h>         // MFC 扩展


#include <afxdisp.h>        // MFC 自动化类



#ifndef _AFX_NO_OLE_SUPPORT
#include <afxdtctl.h>           // MFC 对 Internet Explorer 4 公共控件的支持
#endif
#ifndef _AFX_NO_AFXCMN_SUPPORT
#include <afxcmn.h>             // MFC 对 Windows 公共控件的支持
#endif // _AFX_NO_AFXCMN_SUPPORT
#include "SkinPPWTL.h"   //在这个地方加
#pragma comment(lib,"SkinPPWTL.lib")
#include <afxcontrolbars.h>     // 功能区和控件条的 MFC 支持


#include <afxsock.h>            // MFC 套接字扩展

enum
{
	INFO_ADD = 0X1234,//注册
	INFO_LOGIN,//登录
	INFO_BYE,//下线
	INFO_HELLO,//点击
	INFO_TEXT,//聊天
	INFO_FILE,//文件
	INFO_BROW,//更新
	INFO_FAILLOFIN,//登陆失败
	INFO_FAILADD,//注册失败
	INFO_ALLTEXT,//群聊
	INFO_ACTIVE,//自动刷新
	INFO_PICTRUE,
	INFO_ALLPICTURE,
};
class CSocketC;
struct UserInfo
{
	char Username[16];
	char Password[16];
	char sIP[16];
	CSocketC *pSock;
	UINT nPort;
	char Text[2048];
	char From_Username[16];
	char From_sIP[16];
	char From_Path[1000];
	//文件传输
	BOOL isFile;
	BOOL isFinished;
	UINT transSize;
	UINT fileOffset;
	char sendFile[5000];
	char fileName[100];
	ULONGLONG fileLen;
};


#include <windows.h>

#include <mmsystem.h>

#pragma comment(lib, "WINMM.LIB")

#undef  WINVER  
#define WINVER 0X500  

#define WM_SHOWTASK WM_USER+1 
typedef void (WINAPI *PROCSWITCHTOTHISWINDOW) (HWND, BOOL);

#ifdef _UNICODE
#if defined _M_IX86
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='x86' publicKeyToken='6595b64144ccf1df' language='*'\"")
#elif defined _M_X64
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='amd64' publicKeyToken='6595b64144ccf1df' language='*'\"")
#else
#pragma comment(linker,"/manifestdependency:\"type='win32' name='Microsoft.Windows.Common-Controls' version='6.0.0.0' processorArchitecture='*' publicKeyToken='6595b64144ccf1df' language='*'\"")
#endif
#endif


