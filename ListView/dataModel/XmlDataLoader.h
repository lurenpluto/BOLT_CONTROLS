#ifndef _XML_DATA_LOADER_H_
#define _XML_DATA_LOADER_H_
#pragma once 

#include "stdafx.h"

#include "PostMessageToUIThread.h"

#include "xl_lib/multithread/thread.h"
#include "xl_lib/multithread/critical_section.h"
#include "xl_lib/multithread/event.h"

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

class XmlDataLoader : public xl::win32::multithread::thread
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
	virtual xl::uint32  thread_proc();

private:
	struct StrRange;
	bool AppendRange(StrRange r);
	bool GetRange(StrRange& r);

private:
	xl::win32::multithread::critical_section m_cs;
	xl::win32::multithread::event m_event;
	XmlParser *m_pParser;
	std::vector<StrRange> m_dataRangesWaitingForExecute;
	CallbackToDataModelOnDataReady *m_pCallbackToDataModelOnDataBatchReady;
	CallbackToDataModelOnDataReady *m_pCallbackToDataModelOnSingleDataReady;
};

#endif