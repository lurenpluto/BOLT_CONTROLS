#include "XmlDataModel.h"
#include "XmlParser.h"
#include "XmlDataLoader.h"

#include <string>

XmlDataModel::XmlDataModel(int argc, const char *argv[])
: m_pLoader(NULL)
, m_pDataReadyListener(NULL)
{
	if (argc && argv)
	{
		InitUIThread();
		m_pLoader = new XmlDataLoader();
		m_pLoader->LoadPlaylist(m_playlist, argv[0]);
		m_pLoader->start();
	}
}

XmlDataModel::~XmlDataModel()
{
	if (m_pLoader)
	{
		delete m_pLoader;
		m_pLoader = NULL;
	}
	if (m_pDataReadyListener)
	{
		delete m_pDataReadyListener;
		m_pDataReadyListener = NULL;
	}
	while (!m_playlist.empty())
	{
		StrSongInfo *pSong = m_playlist.front();
		m_playlist.erase(m_playlist.begin());
		delete pSong;
	}

	UnInitUIThread();
}

int XmlDataModel::GetCount()
{
	return m_playlist.size();
}

int XmlDataModel::GetColumnCount()
{
	return MAX_COL-1;
}

bool XmlDataModel::GetDataBatch(int from, int to, void **ppDataBatch, char** pTypes)
{
	bool ret = false;
	if (pTypes)
	{
		pTypes[0] = "bitmap";
		pTypes[1] = "string";
		pTypes[2] = "string";
		if (from < 1) from = 1;
		if (to > (int)m_playlist.size()) to = m_playlist.size();
		if (from <= to)
		{
			for ( int row = from; row <= to; row++)
			{
				ppDataBatch[3*(row-from)] = &(m_playlist.at(row - 1)->hBitmap);
				ppDataBatch[3*(row-from)+1] = (void*)m_playlist.at(row - 1)->name.c_str();
				ppDataBatch[3*(row-from)+2] = (void*)m_playlist.at(row - 1)->source.c_str();
			}
			ret = true;
		}
	}
	return ret;
}

char* XmlDataModel::GetItemAtIndex(int irow,int icolumn, void **ppItemData)
{
	size_t row(irow);
	size_t column(icolumn);
	char *dataType = "nil";

	if (row >= 1 && row <= m_playlist.size())
	{
		if (column == COVER_COL)
		{
			if(m_playlist.at(row-1)->hBitmap == NULL)
			{
				m_playlist.at(row-1)->hBitmap = m_pLoader->LoadImage(m_playlist.at(row-1)->cover.c_str());
			}
			*ppItemData = m_playlist.at(row-1)->hBitmap;
			dataType = "bitmap";
		}
		else if (column == NAME_COL)
		{
			*ppItemData = (void*)m_playlist.at(row-1)->name.c_str();
			dataType = "string";
		}
		else if (column == SOURCE_COL)
		{
			*ppItemData = (void*)m_playlist.at(row-1)->source.c_str();
			dataType = "string";
		}
	}
	return dataType;
}

void XmlDataModel::PrepareData(int from, int to)
{
	//准备的数据在m_playlist中的索引是from-1~to-1
	from = from <= 0 ? 1 : from;
	to = to > (int)m_playlist.size() ? m_playlist.size() : to;
	m_pLoader->PrepareData(from, to, m_playlist);
}

void XmlDataModel::ReleaseData(int from, int to)
{
	//准备的数据在m_playlist中的索引是from-1~to-1
	from = from <= 0 ? 1 : from;
	to = to > (int)m_playlist.size() ? m_playlist.size() : to;
	if (from <= to)
	{
		m_pLoader->ReleaseData(from, to, m_playlist);
		for(int i = from; i <= to; i++)
		{
			m_playlist[i-1]->hBitmap = 0;
		}
	}
}

void XmlDataModel::FireDataReadyEvent(int row, int column)
{
	if (m_pDataReadyListener)
	{
		m_pDataReadyListener->OnDataReady(row, column);
	}
}

void XmlDataModel::SetSingleDataReadyListener(DataReadyListenerInterface *pDataReadyListener)
{
	if (m_pDataReadyListener)
	{
		delete m_pDataReadyListener;
		m_pDataReadyListener = NULL;
	} 
	else 
	{
		m_pLoader->SetSingleDataReadyListener(XmlDataModel::UIThreadCallbackOnSingleData, (void*)this);
	}
	m_pDataReadyListener = pDataReadyListener;
}

void XmlDataModel::SetDataBatchReadyListener(DataReadyListenerInterface *pDataReadyListener)
{
	if (m_pDataReadyListener)
	{
		delete m_pDataReadyListener;
		m_pDataReadyListener = NULL;
	}
	else
	{
		m_pLoader->SetDataBatchReadyListener(XmlDataModel::UIThreadCallbackOnDataBatch, (void*)this);
	}
	m_pDataReadyListener = pDataReadyListener;
}

void XmlDataModel::UIThreadCallbackOnDataBatch(void *pUserData)
{
	if (PostDataBatchMessageToUIThreadUserData *pMyData = (PostDataBatchMessageToUIThreadUserData*)pUserData)
	{
		if (XmlDataModel *pDataModel = (XmlDataModel*)pMyData->pCaller)
		{
			pDataModel->FireDataReadyEvent(pMyData->from, pMyData->from+pMyData->list.size()-1);
		}
		delete pMyData;
	}
}

void XmlDataModel::UIThreadCallbackOnSingleData(void *pUserData)
{
	if (PostSingleDataMessageToUIThreadUserData *pMyData = (PostSingleDataMessageToUIThreadUserData*)pUserData)
	{
		if (XmlDataModel *pDataModel = (XmlDataModel*)pMyData->pCaller)
		{
			for (int col = 1; col <= pDataModel->GetColumnCount(); col++)
			{
				pDataModel->FireDataReadyEvent(pMyData->row, col);
			}
		}
		delete pMyData;
	}
}