#include "stdafx.h"

#include "datamodel.h"
#include "XmlDataModel.h"
#include "./LuaDataModelClass.h"

bool RegisterDataModelClass()
{
	XL_LRT_ENV_HANDLE hEnv = XLLRT_GetEnv(NULL);
	LuaDataModelClass::RegisterClass("XmlDataModel", hEnv);
	LuaDataModelClassFactory::RegisterObj("XmlDataModel", hEnv);
	//luaruntime������Ͷ��ǻ������ü�����һ��ԭ�������з���ֵ�����������ü�����ʹ�����Ҫ�ͷ�
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