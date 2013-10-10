#include "stdafx.h"

#include "datamodel.h"
#include "XmlDataModel.h"
#include "./LuaDataModelClass.h"

bool RegisterDataModelClass()
{
	XL_LRT_ENV_HANDLE hEnv = XLLRT_GetEnv(NULL);
	LuaDataModelClass::RegisterClass("XmlDataModel", hEnv);
	LuaDataModelClassFactory::RegisterObj("XmlDataModel", hEnv);
	//luaruntime库的类型都是基于引用计数，一个原则是所有返回值都会增持引用计数，使用完毕要释放
	XLLRT_ReleaseEnv(hEnv);
	return true;
}

BOOL APIENTRY DllMain( HANDLE hModule, 
                       DWORD  ul_reason_for_call, 
                       LPVOID lpReserved
					 )
{
	return TRUE;
}

__declspec(dllexport) void NoUse()
{

}