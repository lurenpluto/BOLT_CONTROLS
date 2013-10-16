#include "XmlDataLoader.h"
#include "PostMessageToUIThread.h"
#include "XmlParser.h"

#include "xl_lib/text/Win32Transcode.h"
#include <windows.h>

struct XmlDataLoader::StrRange
{
	enum
	{
		Prepare,
		Release, 
		Invalid
	};
	XmlDataLoader::StrRange(int _type)
		:pPlaylist(NULL)
		, type(_type){}
	XmlDataLoader::StrRange()
		:pPlaylist(NULL)
		, type(Invalid){}
	~StrRange(){}
	int from;
	int type;
	std::vector<StrSongInfo*> *pPlaylist;
};

XmlDataLoader::XmlDataLoader()
:m_pParser(NULL)
, m_pCallbackToDataModelOnDataBatchReady(NULL)
, m_pCallbackToDataModelOnSingleDataReady(NULL)
{
	m_pParser = new XmlParser();
	InitializeCriticalSection(&m_cs);
}

XmlDataLoader::~XmlDataLoader()
{
	DemoThread::Stop();
	if (m_pParser)
	{
		delete m_pParser;
		m_pParser = NULL;
	}
	if (m_pCallbackToDataModelOnDataBatchReady)
	{
		delete m_pCallbackToDataModelOnDataBatchReady;
		m_pCallbackToDataModelOnDataBatchReady = NULL;
	}
	if (m_pCallbackToDataModelOnSingleDataReady)
	{
		delete m_pCallbackToDataModelOnSingleDataReady;
		m_pCallbackToDataModelOnSingleDataReady = NULL;
	}
	/*
		Ϊʲô��Ҫ��������waitingForExecute��range�е�pPlaylist:
		clear()�����range����������, ����range��ָ���ԱpPlaylist���ᱻ����, ֻ�����ٶ���
		Ϊʲô��������range����������������pPlaylist:
		range����Ϊ���󴫵ݵ�, �뿪������ͻᱻ����
	*/
	while(!m_dataRangesWaitingForExecute.empty())
	{
		StrRange r = m_dataRangesWaitingForExecute.front();
		m_dataRangesWaitingForExecute.erase(m_dataRangesWaitingForExecute.begin());
		delete r.pPlaylist;
	}
}

bool XmlDataLoader::LoadPlaylist(std::vector<StrSongInfo*> & playlist, const char* fileName)
{
	return m_pParser->LoadPlaylist(playlist, fileName);
}

/*!
����һ���򵥵�ʾ��, ��ListView����DataModel��PrepareDataʱ, Ӧ��׼����������. 
��ʵ��Ӧ����, DataModel��PrepareData�ǲ�������������, ��������Demo������ֱ�Ӵ�list�ж�ȡ.
*/
bool XmlDataLoader::PrepareData(int from, int to, const std::vector<StrSongInfo*>& allList)
{
	std::vector<StrSongInfo*> *pPlaylist = new std::vector<StrSongInfo*>(to-from+1);
	std::vector<StrSongInfo*>::const_iterator it = allList.begin();
	std::vector<StrSongInfo*>::const_iterator itBegin = it + from-1;
	std::vector<StrSongInfo*>::const_iterator itEnd = it + to;//���һ������������
	pPlaylist->assign(itBegin, itEnd);

	StrRange r(StrRange::Prepare);
	r.from = from;
	r.pPlaylist = pPlaylist;

	AppendRange(r);
	return true;
}

bool XmlDataLoader::ReleaseData(int from, int to, const std::vector<StrSongInfo*> &allList)
{
	std::vector<StrSongInfo*> *list = new std::vector<StrSongInfo*>(to-from+1);
	std::vector<StrSongInfo*>::const_iterator it = allList.begin();
	std::vector<StrSongInfo*>::const_iterator itBegin = it + from-1;
	std::vector<StrSongInfo*>::const_iterator itEnd = it + to;//���һ������������
	list->assign(itBegin, itEnd);
	StrRange r(StrRange::Release);
	r.from = from;
	r.pPlaylist = list;

	AppendRange(r);
	return true;
}	
	
void XmlDataLoader::SetSingleDataReadyListener(PFNMAINTHREADCALLBACK pfnCallback, void *ptrCaller)
{
	if (m_pCallbackToDataModelOnSingleDataReady)
	{
		delete m_pCallbackToDataModelOnSingleDataReady;
	}
	m_pCallbackToDataModelOnSingleDataReady = new CallbackToDataModelOnDataReady();
	m_pCallbackToDataModelOnSingleDataReady->pfnOnDataReadyCallback = pfnCallback;
	m_pCallbackToDataModelOnSingleDataReady->pCaller = ptrCaller;
}

void XmlDataLoader::SetDataBatchReadyListener(PFNMAINTHREADCALLBACK pfnCallback, void* ptrCaller)
{
	if (m_pCallbackToDataModelOnDataBatchReady)
	{
		delete m_pCallbackToDataModelOnDataBatchReady;
	}
	m_pCallbackToDataModelOnDataBatchReady = new CallbackToDataModelOnDataReady();
	m_pCallbackToDataModelOnDataBatchReady->pfnOnDataReadyCallback = pfnCallback;
	m_pCallbackToDataModelOnDataBatchReady->pCaller = ptrCaller;
}

BOOL XmlDataLoader::Run()
{
		StrRange r;	
		r.type = StrRange::Invalid;
		GetRange(r);
		if (r.type == StrRange::Prepare)
		{
			for (size_t i = 0; i < r.pPlaylist->size(); i++)	
			{
					r.pPlaylist->at(i)->hBitmap = LoadImage(r.pPlaylist->at(i)->cover.c_str());
					if(m_pCallbackToDataModelOnSingleDataReady)
					{
						//�����̴߳���, UI�߳�����?
						PostSingleDataMessageToUIThreadUserData *u = new PostSingleDataMessageToUIThreadUserData();
						u->row = r.from+i;
						u->pSong = r.pPlaylist->at(i);
						u->pCaller = m_pCallbackToDataModelOnSingleDataReady->pCaller;
						PostMessageToUIThread((void*)u, m_pCallbackToDataModelOnSingleDataReady->pfnOnDataReadyCallback);
						//! �˴���û���ر����Դ�Ĳ���,Ϊ���ڽ��濴��һ��һ��FireDataReadyEvent()��Ч��,ͣ��10msec�ٲ�����һ��.
						Sleep(10);
					}
			}
			if (m_pCallbackToDataModelOnDataBatchReady)
			{
				PostDataBatchMessageToUIThreadUserData *u = new PostDataBatchMessageToUIThreadUserData();
				u->list.assign(r.pPlaylist->begin(), r.pPlaylist->end());
				u->from = r.from;
				u->pCaller = m_pCallbackToDataModelOnDataBatchReady->pCaller;
				PostMessageToUIThread((void*)u, m_pCallbackToDataModelOnDataBatchReady->pfnOnDataReadyCallback);
			}
		} 
		else if (r.type == StrRange::Release)
		{
			for (size_t i = 0; i < r.pPlaylist->size(); i++)
			{
				if(r.pPlaylist->at(i)->hBitmap != NULL)
				{
					XL_ReleaseBitmap(r.pPlaylist->at(i)->hBitmap);
					r.pPlaylist->at(i)->hBitmap = NULL;
				}
			}
		}
		if (r.pPlaylist)
		{
			delete r.pPlaylist;
		}
	return 1;
}

bool XmlDataLoader::AppendRange(XmlDataLoader::StrRange r)
{
	EnterCriticalSection(&m_cs);
	m_dataRangesWaitingForExecute.push_back(r);
	if (m_dataRangesWaitingForExecute.size() == 1)
	{
		DemoThread::Start();
	}
	LeaveCriticalSection(&m_cs);
	return true;
}

bool XmlDataLoader::GetRange(XmlDataLoader::StrRange &r)
{
	EnterCriticalSection(&m_cs);
	if (!m_dataRangesWaitingForExecute.empty())
	{
		r = m_dataRangesWaitingForExecute.front();
		m_dataRangesWaitingForExecute.erase(m_dataRangesWaitingForExecute.begin());
	}
	if (m_dataRangesWaitingForExecute.size() == 0)
	{
		DemoThread::Suspend();
	}
	LeaveCriticalSection(&m_cs);
	return true;
}

XL_BITMAP_HANDLE XmlDataLoader::LoadImage(const char* lpFile)
{
	std::string strFile(lpFile);
	std::wstring wlpFile;
	Win32Transcode::UTF8_to_Unicode(lpFile, strlen(lpFile), wlpFile);
	const wchar_t* lpExt = ::PathFindExtension(wlpFile.c_str());
	if (lpExt && ::lstrcmpi(lpExt, L".png") == 0)
	{
		XL_BITMAP_HANDLE hBitmap = XL_LoadBitmapFromFile(wlpFile.c_str(), XLGRAPHIC_CT_ARGB32);
		assert(hBitmap);
		return hBitmap;
	}
	return NULL;
}
DemoThread::DemoThread()
{
    m_hEventSuspend = CreateEvent(0,TRUE,FALSE,NULL);
    m_status = TRUE;

    m_hThread = (HANDLE)_beginthreadex(NULL,0,DemoThread::StartAddress,this,0,&m_thrdAddr);
}

DemoThread::~DemoThread()
{
    CloseHandle(m_hEventSuspend);
    CloseHandle(m_hThread );
}

BOOL DemoThread::Start()
{
    return SetEvent(m_hEventSuspend);
}

BOOL DemoThread::Suspend()
{
    return ResetEvent(m_hEventSuspend);
}

BOOL DemoThread::Run()
{
    return TRUE;
}

BOOL DemoThread::Stop()
{
    m_status = FALSE;
    Start();
    WaitForSingleObject(m_hThread,INFINITE);

    return TRUE;
}

unsigned __stdcall DemoThread::StartAddress(void * obj)
{
    DemoThread* pthread = static_cast<DemoThread*>(obj);

    while(pthread->m_status)
    {
        WaitForSingleObject(pthread->m_hEventSuspend,INFINITE);
        if (!pthread->Run())
		{
            break;
		}
    }
    _endthreadex(0);

    return 0;
}
