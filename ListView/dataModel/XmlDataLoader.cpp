#include "XmlDataLoader.h"
#include "PostMessageToUIThread.h"
#include "XmlParser.h"

#include "xl_lib/text/transcode.h"

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
}

XmlDataLoader::~XmlDataLoader()
{
	m_event.set_event();
	stop();
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

xl::uint32  XmlDataLoader::thread_proc()
{
	while(m_event.wait_event())
	{
		if (this->is_stop_event_set())
		{
			break;
		}
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
	}
	return 1;
}

bool XmlDataLoader::AppendRange(XmlDataLoader::StrRange r)
{
	m_cs.lock();
	m_dataRangesWaitingForExecute.push_back(r);
	if (m_dataRangesWaitingForExecute.size() == 1)
	{
		m_event.set_event();
	}
	m_cs.unlock();
	return true;
}

bool XmlDataLoader::GetRange(XmlDataLoader::StrRange &r)
{
	m_cs.lock();
	if (!m_dataRangesWaitingForExecute.empty())
	{
		r = m_dataRangesWaitingForExecute.front();
		m_dataRangesWaitingForExecute.erase(m_dataRangesWaitingForExecute.begin());
		if (m_dataRangesWaitingForExecute.empty())
		{
			m_event.reset_event();
		}
	}
	m_cs.unlock();
	return true;
}

XL_BITMAP_HANDLE XmlDataLoader::LoadImage(const char* lpFile)
{
	std::wstring wlpFile;
	xl::text::transcode::UTF8_to_Unicode(lpFile, strlen(lpFile), wlpFile);
	const wchar_t* lpExt = ::PathFindExtension(wlpFile.c_str());
	if (lpExt && ::lstrcmpi(lpExt, L".png") == 0)
	{
		XL_BITMAP_HANDLE hBitmap = XL_LoadBitmapFromFile(wlpFile.c_str(), XLGRAPHIC_CT_ARGB32);
		assert(hBitmap);
		return hBitmap;
	}
	return NULL;
}