#ifndef _LUA_DATAMODEL_CLASS_H_
#define _LUA_DATAMODEL_CLASS_H_
#pragma once 

#include "stdafx.h"

/*
	这个监听者接口在监听事件触发时调用一个接收(int, int)参数的方法
	具体的DataModelClass只需要知道这个接口的OnDataReady方法就够了
	接口的实现者处理具体事务
*/
class DataReadyListenerInterface
{
public:
	/*
		析构方法为纯虚函数带有实现的目的: 
		virtual ~DataReadyListenerInterface() = 0{}
		虚析构方法保证基类析构方法被调用, 资源释放
		这个接口一定是个抽象类, 在接口OnDataReady被去掉以后也不希望被实例化, 纯虚析构方法保证了这一点
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
		需要被创建的DataModel类名称在lua函数第一个参数, 也就是lua栈上第二个位置
	*/
	static int CreateInstance(lua_State *luaState);
	/*!
		@param dataModelClassName是这个要被注册的DataModel的类名, 注册时候会分别加上.factory. class和.factory.object注册到lua环境中
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
		如果用户提供给ListView的DataModelCallbackTable中包含SetDataBatchReadyListener, 那么ListView会调用该方法传给LuaDataModelClass一个Lua回调方法DataReadyCallback在数据准备好的时候通知ListView
		LuaDataModelClass会把DataReadyCallback连同回调时需要的参数dwUserData1, dwUserData2原封不动地传给DataModel, 当DataModel准备好数据的时候应该调用DataReadyCallback. 但是DataModel不应该直接操作lua接口, 所以除了lua方法DataReadyCallback和dwUserData1, dwUserData2之外, LuaDataModelClass会把自己的方法LuaDataModelClass::LuaDataReadyListener也作为参数传给DataModel, DataModel回调这个方法通知数据准备好了就可以了. 
		///sa AttachDataReadyListener
	*/
	static int SetDataBatchReadyListener(lua_State *luaState);
	/*!
		这个方法和LuaDataModelClass::SetDataBatchReadyListener的用法是一样的. 不同之处在于SetDataBatchReadyListener的回调方法DataBatchReady会在一批数据准备好的时候被调用. 例如ItemView调用PrepareData(1, 100), 那么在这个100个数据准备好以后, DataModel应该调用DataBatchReady来通知ListView有一批数据已经可以被调用了. 而SetSingleDataReadyListener传入的回调方法应该在每一个单元格的数据就绪之后都被调用一次, 回调传的参数是就绪单元格的行与列
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