#include "stdafx.h"

#include "datamodel.h"
#include "./LuaDir.h"

bool RegisterDataModelClass()
{
	XL_LRT_ENV_HANDLE hEnv = XLLRT_GetEnv(NULL);
	LuaDir::RegisterClass(hEnv);
	LuaDirFactory::RegisterObj(hEnv);
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