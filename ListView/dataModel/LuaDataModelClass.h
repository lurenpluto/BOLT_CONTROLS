#ifndef _LUA_DATAMODEL_CLASS_H_
#define _LUA_DATAMODEL_CLASS_H_
#pragma once 

#include "stdafx.h"

/*
	��������߽ӿ��ڼ����¼�����ʱ����һ������(int, int)�����ķ���
	�����DataModelClassֻ��Ҫ֪������ӿڵ�OnDataReady�����͹���
	�ӿڵ�ʵ���ߴ����������
*/
class DataReadyListenerInterface
{
public:
	/*
		��������Ϊ���麯������ʵ�ֵ�Ŀ��: 
		virtual ~DataReadyListenerInterface() = 0{}
		������������֤������������������, ��Դ�ͷ�
		����ӿ�һ���Ǹ�������, �ڽӿ�OnDataReady��ȥ���Ժ�Ҳ��ϣ����ʵ����, ��������������֤����һ��
	*/
	virtual ~DataReadyListenerInterface(){}
	virtual void OnDataReady(const int &arg1, const int &arg2) =0;
};

class DataModelInterface
{
public:
	virtual ~DataModelInterface() {}
	virtual char* GetItemAtIndex(int row,int column, void **ppItemData = 0) = 0;
	virtual int GetCount() = 0;
	virtual int GetColumnCount() = 0;
	virtual bool GetDataBatch(int from, int to, void **ppDataBatch, char** pTypes) {return false;}
	virtual void PrepareData(int from, int to) {}
	virtual void ReleaseData(int from, int to) {}
	virtual void SetSingleDataReadyListener(DataReadyListenerInterface* pDataReadyListener){}
	virtual void SetDataBatchReadyListener(DataReadyListenerInterface* pDataReadyListener) {}
};

class LuaDataModelClassFactory
{
public:
	static LuaDataModelClassFactory * __stdcall Instance(void*);
	/*!
		��Ҫ��������DataModel��������lua������һ������, Ҳ����luaջ�ϵڶ���λ��
	*/
	static int CreateInstance(lua_State *luaState);
	/*!
		@param dataModelClassName�����Ҫ��ע���DataModel������, ע��ʱ���ֱ����.factory. class��.factory.objectע�ᵽlua������
	*/
	static void RegisterObj(const char *dataModelClassName, XL_LRT_ENV_HANDLE hEnv);
private:
	static XLLRTGlobalAPI s_LuaDataModelClassFactoryMemberFunctions[];
};

class LuaDataModelClass
{
public:
	static int DeleteSelf(lua_State *luaState);
	static int GetItemAtIndex(lua_State *luaState);
	static int GetDataBatch(lua_State *luaState);
	static int GetCount(lua_State *luaState);
	static int GetColumnCount(lua_State *luaState);
	static int PrepareData(lua_State *luaState);
	static int ReleaseData(lua_State *luaState);
	/*!
		����û��ṩ��ListView��DataModelCallbackTable�а���SetDataBatchReadyListener, ��ôListView����ø÷�������LuaDataModelClassһ��Lua�ص�����DataReadyCallback������׼���õ�ʱ��֪ͨListView
		LuaDataModelClass���DataReadyCallback��ͬ�ص�ʱ��Ҫ�Ĳ���dwUserData1, dwUserData2ԭ�ⲻ���ش���DataModel, ��DataModel׼�������ݵ�ʱ��Ӧ�õ���DataReadyCallback. ����DataModel��Ӧ��ֱ�Ӳ���lua�ӿ�, ���Գ���lua����DataReadyCallback��dwUserData1, dwUserData2֮��, LuaDataModelClass����Լ��ķ���LuaDataModelClass::LuaDataReadyListenerҲ��Ϊ��������DataModel, DataModel�ص��������֪ͨ����׼�����˾Ϳ�����. 
		///sa AttachDataReadyListener
	*/
	static int SetDataBatchReadyListener(lua_State *luaState);
	/*!
		���������LuaDataModelClass::SetDataBatchReadyListener���÷���һ����. ��֮ͬ������SetDataBatchReadyListener�Ļص�����DataBatchReady����һ������׼���õ�ʱ�򱻵���. ����ItemView����PrepareData(1, 100), ��ô�����100������׼�����Ժ�, DataModelӦ�õ���DataBatchReady��֪ͨListView��һ�������Ѿ����Ա�������. ��SetSingleDataReadyListener����Ļص�����Ӧ����ÿһ����Ԫ������ݾ���֮�󶼱�����һ��, �ص����Ĳ����Ǿ�����Ԫ���������
	*/
	static int SetSingleDataReadyListener(lua_State *luaState);
	static void RegisterClass(const char * dataModelClassName, XL_LRT_ENV_HANDLE hEnv);
	static void LuaDataReadyListener(lua_State* luaState, long functionRef, int row, int column);

private:
	static DataModelInterface *GetDataModelClassObject(lua_State *luaState);

private:
	static XLLRTGlobalAPI s_LuaDataModelClassMemberFunctions[];
};

#endif