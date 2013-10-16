#ifndef _XML_DATA_LOADER_H_
#define _XML_DATA_LOADER_H_
#pragma once 

#include "stdafx.h"

#include "PostMessageToUIThread.h"

#include <vector>

class XmlParser;
struct StrSongInfo;

// when data is ready, data model expected to be called through ptrCaller->funCallback()
// no distinguish between databatch ready or single data ready, data model class assign different funCallback when set listener
struct CallbackToDataModelOnDataReady
{
	PFNMAINTHREADCALLBACK pfnOnDataReadyCallback;
	void *pCaller;
};

// data loader post to ui thread
// uithread call back on data model
struct PostDataBatchMessageToUIThreadUserData
{	
	int from;
	std::vector<StrSongInfo*> list;
	void *pCaller;
};

struct PostSingleDataMessageToUIThreadUserData
{
	int row;
	StrSongInfo* pSong;
	void *pCaller;
};

class DemoThread
{
public:
    DemoThread();
    virtual ~DemoThread();
    
    BOOL Start(); 
    BOOL Suspend();
    virtual BOOL Run();
    BOOL Stop();

protected:
    static unsigned __stdcall StartAddress( void * obj);

public:
    HANDLE m_hThread; 
    HANDLE m_hEventSuspend;
    BOOL m_status;
    unsigned  m_thrdAddr;
};

class XmlDataLoader : public DemoThread
{
public:
	XmlDataLoader();
	virtual ~XmlDataLoader();

	bool LoadPlaylist(std::vector<StrSongInfo*> & playlist, const char* fileName);
	XL_BITMAP_HANDLE LoadImage(const char* lpFile);

	bool PrepareData(int from, int to, const std::vector<StrSongInfo*>& allList);
	bool ReleaseData(int from, int to, const std::vector<StrSongInfo*>& allList );
	void SetDataBatchReadyListener(PFNMAINTHREADCALLBACK pfnCallback, void* ptrCaller);
	void SetSingleDataReadyListener(PFNMAINTHREADCALLBACK pfnCallback, void* ptrCaller);

protected:
	virtual BOOL Run();

private:
	struct StrRange;
	bool AppendRange(StrRange r);
	bool GetRange(StrRange& r);

private:
	CRITICAL_SECTION m_cs;
	//xl::win32::multithread::critical_section m_cs;
	XmlParser *m_pParser;
	std::vector<StrRange> m_dataRangesWaitingForExecute;
	CallbackToDataModelOnDataReady *m_pCallbackToDataModelOnDataBatchReady;
	CallbackToDataModelOnDataReady *m_pCallbackToDataModelOnSingleDataReady;
};

#endif