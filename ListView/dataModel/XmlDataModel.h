#pragma once

#include "stdafx.h"
#include "LuaDataModelClass.h"

#include <vector>

class XmlDataLoader;
struct StrSongInfo;

class XmlDataModel : public DataModelInterface
{
public:
	enum 
	{
		MEDIA_TAG = 0,
		COVER_COL = 1,
		NAME_COL = 2,
		SOURCE_COL = 3,
		MAX_COL
	} COL_NAMES;

	XmlDataModel(int argc = 0, const char **argv = NULL);
	virtual ~XmlDataModel();

	virtual char* GetItemAtIndex(int row,int column, void **ppItemData = 0);
	virtual bool GetDataBatch(int from, int to, void **ppDataBatch, char** pTypes);
	virtual int GetCount();
	virtual int GetColumnCount();
	virtual void PrepareData(int from, int to);
	virtual void ReleaseData(int from, int to);
	virtual void SetSingleDataReadyListener(DataReadyListenerInterface* pDataReadyListener);
	virtual void SetDataBatchReadyListener(DataReadyListenerInterface* pDataReadyListener);

	void FireDataReadyEvent(int , int );

	static void UIThreadCallbackOnDataBatch(void *pUserData);
	static void UIThreadCallbackOnSingleData(void *pUserData);

private:
	DataReadyListenerInterface *m_pDataReadyListener;
	XmlDataLoader *m_pLoader;
	std::vector<StrSongInfo*> m_playlist;
};