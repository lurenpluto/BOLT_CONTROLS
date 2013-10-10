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
const int WM_MY_MESSAGE = WM_USER+1; //�Զ�����ϢID
///! wtl������, ������������ص�, ����ֻ�����Զ������Ϣ����WM_MY_MESSAGE, ������ͨ��WM_MY_MESSAGE post ����Ϣ���е���Ϣ
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
		ȥ������Ĭ��wtl���̴�����ĺ���, ������һ�������Զ����¼��ķ���
	*/
	BEGIN_MSG_MAP(CMainFrame)
		MESSAGE_HANDLER( WM_MY_MESSAGE, OnMyMessage ) //�Զ�����Ϣ��ӳ��
	END_MSG_MAP()

	/*!  �û�Post message ����ԭ��:
		  PostMessageToUIThread( void *userData = 0, MainThreadCallbackFun ptrFun = 0);
		  �������������ԭ��userData�ͻص�����ָ��, Ȼ����ûص�����
	!*/
   LRESULT OnMyMessage( UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled )
   {
       //ATL::CWindow��MessageBox�ĵ���
	   void* userData = (void*)wParam;
	   MainThreadCallbackFun ptrFun = (MainThreadCallbackFun)lParam;
	   if (ptrFun)
	   {
		   ptrFun(userData);
	   }
       return 0;
   }
};
