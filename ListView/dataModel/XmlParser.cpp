#include "XmlParser.h"
#include "PostMessageToUIThread.h"

#include "xl_lib/text/Win32Transcode.h"

XmlParser::XmlParser()
{
}

XmlParser::~XmlParser()
{
	// No need to destroy m_playlist since it's a reference to XmlDataLoader's
}

bool XmlParser::LoadPlaylist(std::vector<StrSongInfo*> & playlist, const char* fileName)
{
	std::wstring wplaylistName;
	Win32Transcode::UTF8_to_Unicode(fileName, strlen(fileName), wplaylistName);

	XLFS_FILE_HANDLE hFile = NULL;
	m_playlist = &playlist;

	if (XLFS_OpenFile(wplaylistName.c_str(), L"rb", &hFile, NULL) != XLFS_RESULT_SUCCESS)
		return false;

	char buffer[1024 * 16];
	__int64 nReadLength = 0;
	__int64 nFilePosition = 0;
	bool fSuccess = true;
	if (!create())
	{
		XLFS_CloseFile(hFile);
		return false;
	}

	m_attrNamesOfColumn[MEDIA_TAG] = "media";
	m_attrNamesOfColumn[COVER_COL] = "cover";
	m_attrNamesOfColumn[NAME_COL] = "name";
	m_attrNamesOfColumn[SOURCE_COL] = "src";

	while(!XLFS_IsEOF(hFile) && fSuccess)
	{
		nReadLength = XLFS_ReadFile(hFile, (unsigned char*)buffer, (int)sizeof(char) *1024 * 16);
		fSuccess = parse(buffer, (int)nReadLength, 0);
	}

	XLFS_CloseFile(hFile);
	return true;
}

/*!
XML库方法
*/
void XmlParser::OnStartElement(const XML_Char *pszName, const XML_Char **papszAttrs)
{
	if (strcmp(pszName, this->m_attrNamesOfColumn[MEDIA_TAG]) == 0)
	{
		StrSongInfo *info = new StrSongInfo();
		int attrInd = 0;
		const XML_Char * attr = papszAttrs[attrInd];
		while(attr)
		{
			if (strcmp(attr, m_attrNamesOfColumn[COVER_COL]) == 0)
			{
				attrInd++;
				attr = papszAttrs[attrInd];
				info->cover = attr;
			}
			if (strcmp(attr, m_attrNamesOfColumn[NAME_COL]) == 0)
			{
				attrInd++;
				attr = papszAttrs[attrInd];
				info->name = attr;
			}
			if (strcmp(attr, m_attrNamesOfColumn[SOURCE_COL]) == 0)
			{
				attrInd++;
				attr = papszAttrs[attrInd];
				info->source = attr;
			}
			attrInd++;
			attr = papszAttrs[attrInd];
		}
		m_playlist->push_back(info);
	}
}

/*!
XML库方法
*/
void XmlParser::OnEndElement(const XML_Char * c)
{
	return;
}

/*!
XML库方法
*/
void XmlParser::OnPostCreate()
{
	enable_element_handler();
}