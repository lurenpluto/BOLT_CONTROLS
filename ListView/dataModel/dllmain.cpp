#include "MainFrm.h"
#include "PostMessageToUIThread.h"

static unsigned int s_uiThreadRef = 0;
static CMainFrame* s_pWndMain = 0;

CMainFrame* MyMain()
{
	CMainFrame* pWndMain = new CMainFrame();
	if(pWndMain->CreateEx() == NULL)
	{
		ATLTRACE(_T("Main window creation failed!\n"));
		return 0;
	}
	pWndMain->ShowWindow(SW_HIDE);
	return pWndMain;
}

void PostMessageToUIThread( void *pUserData, PFNMAINTHREADCALLBACK pfnMainThreadCallback)
{
	if (s_pWndMain)
	{
		WPARAM wParam = (WPARAM)pUserData;
		LPARAM	 lParam = (LPARAM)pfnMainThreadCallback;
		s_pWndMain->PostMessage(WM_MY_MESSAGE, wParam, lParam);
	}
}

void InitUIThread()
{
	s_uiThreadRef++;
	//һ�����صĺ�̨����, ������Ŀ���ǵõ�����UI�߳��¼����еķ���
	if (!s_pWndMain)
		s_pWndMain = MyMain();
}

void UnInitUIThread()
{
	s_uiThreadRef--;
	if (s_uiThreadRef == 0)
	{
		if (s_pWndMain)
		{
			delete s_pWndMain;
			s_pWndMain = NULL;
		}
	}
}