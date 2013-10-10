// MainFrm.h : interface of the CMainFrame class
//
/////////////////////////////////////////////////////////////////////////////

#pragma once

#include <atlbase.h>
#include <atlapp.h>
#include <atlwin.h>
#include "atlframe.h"

extern CAppModule _Module;
typedef void (*MainThreadCallbackFun)(void*);
const int WM_MY_MESSAGE = WM_USER+1; //自定义消息ID
///! wtl窗口类, 这个窗口是隐藏的, 我们只处理自定义的消息类型WM_MY_MESSAGE, 来处理通过WM_MY_MESSAGE post 到消息队列的消息
#define IDR_MAINFRAME				128
class CMainFrame : public CFrameWindowImpl<CMainFrame>, public CUpdateUI<CMainFrame>,
		public CMessageFilter, public CIdleHandler
{
public:
	DECLARE_FRAME_WND_CLASS(NULL, IDR_MAINFRAME)

	virtual BOOL PreTranslateMessage(MSG* pMsg)
	{
		return CFrameWindowImpl<CMainFrame>::PreTranslateMessage(pMsg);
	}

	virtual BOOL OnIdle()
	{
		return FALSE;
	}

	BEGIN_UPDATE_UI_MAP(CMainFrame)
	END_UPDATE_UI_MAP()

	/*!
		去掉其他默认wtl工程窗口类的函数, 加了这一个处理自定义事件的方法
	*/
	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER( WM_MY_MESSAGE, OnMyMessage ) //自定义消息的映射
	END_MSG_MAP()

	/*!  用户Post message 方法原型:
		  PostMessageToUIThread( void *userData = 0, MainThreadCallbackFun ptrFun = 0);
		  在这里参数被还原成userData和回调函数指针, 然后调用回调函数
	!*/
   LRESULT OnMyMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
   {
       //ATL::CWindow的MessageBox的调用
	   void* userData = (void*)wParam;
	   MainThreadCallbackFun ptrFun = (MainThreadCallbackFun)lParam;
	   if (ptrFun)
	   {
		   ptrFun(userData);
	   }
       return 0;
   }
};
