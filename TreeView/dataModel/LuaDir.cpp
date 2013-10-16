#include "LuaDir.h"

#include "xl_lib/text/Win32Transcode.h"

void ListDirectoryContents(lua_State *L, const char *currentDir)
{
	std::wstring wsConvert;
	Win32Transcode::UTF8_to_Unicode(currentDir, strlen(currentDir), wsConvert);
	const wchar_t *wCurrentDir =wsConvert.c_str();

	if (wcscmp(wCurrentDir, L"") == 0)
	{
		wchar_t szLogicalDriveStrings[MAX_PATH];                          //获取驱动器的内存
		wchar_t *szDrive;
		::ZeroMemory(szLogicalDriveStrings, MAX_PATH);                    //将内存清零，第一个参数是申请字符的地址
		::GetLogicalDriveStrings(MAX_PATH-1, szLogicalDriveStrings);      //获取磁盘中的所有驱动器
		szDrive=(wchar_t*)szLogicalDriveStrings;

		lua_newtable(L);
		int index = 1;

		do
		{
			int len = wcslen(szDrive);
			std::string sDriveConvert;
			Win32Transcode::Unicode_to_UTF8(szDrive, wcslen(szDrive), sDriveConvert);
			const char* volume = sDriveConvert.c_str();
			UINT uDriveType = GetDriveType(szDrive);

			lua_newtable(L);
			lua_pushnumber(L, 1);
			lua_pushboolean(L, true); // has children
			lua_settable(L, -3);

			lua_pushnumber(L, 2);
			lua_pushstring(L, volume);
			lua_settable(L, -3);

			lua_pushnumber(L, index);
			lua_insert(L, -2); // 把栈顶的一维索引和rowtable换一下位置, 
			lua_settable(L, -3); // 把刚压栈的一维索引row, 和rowtable弹出, 放在要返回的return table中
			index++;

			szDrive += (len+1);
		}
		while(*szDrive!='\x00');
	}
	else 
	{
		WIN32_FIND_DATA fdFile;
		HANDLE hFind = NULL;
		wchar_t wPath[MAX_PATH];
		wsprintf(wPath, L"%s\\*", wCurrentDir);

		if( (hFind = FindFirstFile(wPath, &fdFile)) == INVALID_HANDLE_VALUE)
		{
			return;
		}
		int index = 1;
		lua_newtable(L);
		do
		{
			if (wcscmp(fdFile.cFileName, L".") != 0 && wcscmp(fdFile.cFileName, L"..") != 0 
				&& !(fdFile.dwFileAttributes & FILE_ATTRIBUTE_REPARSE_POINT)
				&& !(fdFile.dwFileAttributes & FILE_ATTRIBUTE_HIDDEN))
			{
				lua_newtable(L);
				lua_pushnumber(L, 1);
				if (fdFile.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)
				{			
					lua_pushboolean(L, true);
				} 
				else 
				{
					lua_pushboolean(L, false);
				}
				lua_settable(L, -3);

				std::string subDirString;
				Win32Transcode::Unicode_to_UTF8(fdFile.cFileName, MAX_PATH, subDirString);

				lua_pushnumber(L, 2);
				lua_pushstring(L, subDirString.c_str());
				lua_settable(L, -3);
				
				lua_pushnumber(L, index);//把一维索引row压栈
				lua_insert(L, -2); // 把栈顶的一维索引和rowtable换一下位置, 
				lua_settable(L, -3); // 把刚压栈的一维索引row, 和rowtable弹出, 放在要返回的return table中
				index++;
			}
		} while(::FindNextFile(hFind, &fdFile));
		::FindClose(hFind);
	}
	return;
}

/*在lua语言中，以__开头的方法一般为内建方法或成员，__gc方法是lua 中引用类型对象的资源回收方法，因为lua语言是基于垃圾回收的，当一个引用类型对象不再使用时，垃圾回收程序会将该对象从lua环境中释放，并且调用其上的__gc方法来释放该对象占用的资源（参见lua黄书）。当在lua环境中创建LuaMyClass的实例时，在堆上创建了一个MyClass的实例，对称的，当LuaMyClass实例在乱环境中被回收时，需要在__gc方法中从堆上释放对应的MyClass的实例。
*/
XLLRTGlobalAPI LuaDir::s_LuaDirMemberFunctions[] = 
{
	{"GetSubDirs", LuaDir::GetSubDirs},
    {"__gc",LuaDir::DeleteSelf},
    {NULL,NULL}
};

XLLRTGlobalAPI LuaDirFactory::s_LuaDirFactoryMemberFunctions[] = 
{
   {"CreateInstance",LuaDirFactory::CreateInstance},
    {NULL,NULL}
};

int LuaDir::DeleteSelf(lua_State *luaState)
{
	LuaDir **ppLuaDirInstance = reinterpret_cast<LuaDir**>(luaL_checkudata(luaState, 1, "LuaDir"));
	if (ppLuaDirInstance && *ppLuaDirInstance)
	{
		delete *ppLuaDirInstance;
	}
	return 0;
}

int LuaDir::GetSubDirs(lua_State *L)
{
	const char* currentDir = lua_tostring(L, 2);
	ListDirectoryContents(L, currentDir);
	return 1;
}

void LuaDir::RegisterClass(XL_LRT_ENV_HANDLE hEnv)
{
    if(hEnv == NULL)
    {
        return;
    }
	long nLuaResult =  XLLRT_RegisterClass(hEnv, "LuaDir", s_LuaDirMemberFunctions, NULL, 0);
}

// create instance of LuaDir class
int LuaDirFactory::CreateInstance(lua_State* luaState)
{
	LuaDir *luaDir = new LuaDir(); 
	XLLRT_PushXLObject(luaState, "LuaDir", luaDir);
	return 1;
}

// get instance of LuaDirFactory
LuaDirFactory* __stdcall LuaDirFactory::Instance(void*)
{
    static LuaDirFactory* s_pTheOne = NULL;
    if(s_pTheOne == NULL)
    {
        s_pTheOne = new LuaDirFactory();
    }
    return s_pTheOne;
}

void LuaDirFactory::RegisterObj(XL_LRT_ENV_HANDLE hEnv)
{
    if(hEnv == NULL)
	{
        return ;
	}

    XLLRTObject factoryObject;
	factoryObject.ClassName = "LuaDir.Factory.";
    factoryObject.MemberFunctions = s_LuaDirFactoryMemberFunctions;
	factoryObject.ObjName = "LuaDir.Factory.Object";

    factoryObject.userData = NULL;
    factoryObject.pfnGetObject = (fnGetObject)LuaDirFactory::Instance;

    XLLRT_RegisterGlobalObj(hEnv, factoryObject); 
}