#ifndef _LUA_DIR_H_
#define _LUA_DIR_H_

#include "stdafx.h"

class LuaDir
{
public:
	static int DeleteSelf(lua_State *luaState);
	static void RegisterClass(XL_LRT_ENV_HANDLE hEnv);
	static int GetSubDirs(lua_State *luaState);
private:
	static XLLRTGlobalAPI s_LuaDirMemberFunctions[];
};

class LuaDirFactory
{
public:
	static LuaDirFactory * __stdcall Instance(void*);
	static int CreateInstance(lua_State *luaState);
	static void RegisterObj(XL_LRT_ENV_HANDLE hEnv);
private:
	static XLLRTGlobalAPI s_LuaDirFactoryMemberFunctions[];
};

#endif