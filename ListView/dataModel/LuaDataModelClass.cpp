#include "LuaDataModelClass.h"
#include "XmlDataModel.h"

typedef void (*PFNDATAREADYCALLBACK) (lua_State* luaState, long functionRef, int row, int column);

/*
具体的监听者, 在被监听事件发生时调用一个lua方法, 这个lua方法接受(int,int)的参数
监听者需要保存一个lua方法的ref (long), 一个lua State
*/
class DataReadyListener : public DataReadyListenerInterface
{
public:
	DataReadyListener(PFNDATAREADYCALLBACK pfnCallback, lua_State *luaState)
		: m_pfnCallBack(pfnCallback)
		, m_luaState(luaState)
	{
		m_functionRef = luaL_ref(m_luaState, LUA_REGISTRYINDEX);
	}
	virtual ~DataReadyListener()
	{
		luaL_unref(m_luaState, LUA_REGISTRYINDEX, m_functionRef);
	}
	virtual void OnDataReady(const int & arg1, const int & arg2)
	{
		m_pfnCallBack(m_luaState, m_functionRef, arg1, arg2);
	}
private:
	PFNDATAREADYCALLBACK m_pfnCallBack;
	lua_State *m_luaState;
	long m_functionRef;
};

XLLRTGlobalAPI LuaDataModelClass::s_LuaDataModelClassMemberFunctions[] = 
{
	{"GetItemAtIndex",LuaDataModelClass::GetItemAtIndex},
	{"GetDataBatch",LuaDataModelClass::GetDataBatch},
	{"GetCount",LuaDataModelClass::GetCount},
	{"GetColumnCount",LuaDataModelClass::GetColumnCount},
	{"PrepareData",LuaDataModelClass::PrepareData},
	{"ReleaseData",LuaDataModelClass::ReleaseData},
	{"SetDataBatchReadyListener", LuaDataModelClass::SetDataBatchReadyListener},
	{"SetSingleDataReadyListener", LuaDataModelClass::SetSingleDataReadyListener},
	{"__gc",LuaDataModelClass::DeleteSelf},
	{NULL,NULL}
};

void LuaDataModelClass::RegisterClass(const char * dataModelClassName, XL_LRT_ENV_HANDLE hEnv)
{
	if(hEnv == NULL)
	{
		return;
	}

	long nLuaResult =  XLLRT_RegisterClass(hEnv, dataModelClassName, s_LuaDataModelClassMemberFunctions, NULL, 0);
}

DataModelInterface *LuaDataModelClass::GetDataModelClassObject(lua_State *luaState)
{
	//lua栈中, 1是类对象本身, 从2开始是参数
	const char* dataModelClassName = lua_tostring(luaState,2);
	if (!dataModelClassName)
	{
		dataModelClassName = "XmlDataModel";
	}
	DataModelInterface **ppDataModelInstance = reinterpret_cast<DataModelInterface**>(luaL_checkudata(luaState, 1, dataModelClassName));
	if(ppDataModelInstance && (*ppDataModelInstance))
	{
		return *ppDataModelInstance;
	}
	return NULL;
}

int LuaDataModelClass::SetSingleDataReadyListener(lua_State* luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		if(lua_isfunction(luaState, 3)) //在模板中是2, 用模板的时候lua端没有加类名参数, 用接口的时候加了
		{
			lua_pushvalue(luaState, 3);
			// lua方法的ref和unref分别放在DataReadyListener的构造和析构方法中调用
			// DataReadyListener被luaDataModelClass创建, 被XmlDataModel销毁. 
			// 如果一定要遵守"谁创建, 谁销毁", 在此可以把DataReadyListener的指针引用/指针指针传给XmlDataModel, LuaDataModelClass负责DataReadyListener的生命周期, 不觉得有必要. 
			pDataModelClass->SetSingleDataReadyListener(new DataReadyListener(LuaDataModelClass::LuaDataReadyListener, luaState));
		} 
	}
	return 0;
}

int LuaDataModelClass::SetDataBatchReadyListener(lua_State* luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		if(lua_isfunction(luaState, 3))//在模板中是2, 用模板的时候lua端没有加类名参数, 用接口的时候加了
		{
			lua_pushvalue(luaState, 3);
			pDataModelClass->SetDataBatchReadyListener(new DataReadyListener(LuaDataModelClass::LuaDataReadyListener, luaState));
		}
	}
	return 0;
}

// lua is listening to "data ready" call from c++
void LuaDataModelClass::LuaDataReadyListener(lua_State* luaState, long functionRef, int row, int column)
{
	int nNowTop = lua_gettop(luaState);
	lua_rawgeti(luaState, LUA_REGISTRYINDEX, functionRef);

	lua_pushinteger(luaState, row);
	lua_pushinteger(luaState, column);

	//函数原型XL_LRT_API(long) XLLRT_LuaCall(lua_State* luaState,int args,int results,const wchar_t* contextInfo);
	int nLuaResult = XLLRT_LuaCall(luaState, 2, 0, L"LuaDataModelClass::LuaDataReadyListener");
	lua_settop(luaState, nNowTop);
	return;
}

int LuaDataModelClass::PrepareData(lua_State *luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		int from = static_cast<int>(lua_tointeger(luaState, 3));
		int to = static_cast<int>(lua_tointeger(luaState, 4));
		pDataModelClass->PrepareData(from, to);
		return 0;
	}
	return 0;
}

int LuaDataModelClass::ReleaseData(lua_State *luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		int from = static_cast<int>(lua_tointeger(luaState, 3));
		int to = static_cast<int>(lua_tointeger(luaState, 4));
		pDataModelClass->ReleaseData(from, to);
		return 0;
	}
	return 0;
}

int LuaDataModelClass::GetDataBatch(lua_State *L)
{
	if(DataModelInterface *pDataModelClass = GetDataModelClassObject(L))
	{
		int from = static_cast<int>(lua_tointeger(L, 3));
		int to = static_cast<int>(lua_tointeger(L, 4));
		int columnCount = pDataModelClass->GetColumnCount();
		char** pTypes = new char*[columnCount];
		void** ppDataBatch = new void*[columnCount*(to-from+1)];
		if (from <= 0) from = 1;
		if (to > pDataModelClass->GetCount()) to =  pDataModelClass->GetCount();

		if (pDataModelClass->GetDataBatch(from, to, ppDataBatch, pTypes))
		{
			lua_newtable(L); // 要返回的table, 起名字叫return table
			for ( int row = from; row <= to; row++)
			{
				lua_newtable(L);// 这一行的Table, 叫它rowtable, 现在rowtable@-1
				void *pItemData = ppDataBatch[3*(row-from)];
				for ( int column = 1; column<=columnCount; column++)
				{
					lua_pushnumber(L, column);//把index压栈, 现在rowtable@-2
					void *pItemData = ppDataBatch[3*(row-from)+column-1];
					if (strcmp(pTypes[column-1], "string") == 0) //这一段把值压栈
					{
						char* cData = (char*)pItemData;
						lua_pushstring(L, cData);
					} 
					else if (strcmp(pTypes[column-1], "bitmap") == 0)
					{
						XL_BITMAP_HANDLE *hBitmap = (XL_BITMAP_HANDLE*)pItemData;	
						if (*hBitmap)
							XLUE_PushBitmap(L, *hBitmap);
						else
							lua_pushnil(L);
					} else
					{
						lua_pushnil(L); //即使没有读到数据, 也要放一个空占位
					}
					//现在value@-1, index@-2, rowtable@-3
					lua_settable(L, -3); // 把刚压栈的index, value弹出放在rowtable中
				}
				lua_pushnumber(L, row);//把一维索引row压栈
				lua_insert(L, -2); // 把栈顶的一维索引和rowtable换一下位置, 
				lua_settable(L, -3); // 把刚压栈的一维索引row, 和rowtable弹出, 放在要返回的return table中
			}
			delete []pTypes;
			delete []ppDataBatch;
			return 1;
		}
	}
	return 1;
}

int LuaDataModelClass::GetItemAtIndex(lua_State *luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		int row = static_cast<int> (lua_tointeger(luaState, 3));
		int column = static_cast<int>(lua_tointeger(luaState, 4));
		void *pItemData;
		char* dataType = pDataModelClass->GetItemAtIndex(row, column, &pItemData);
		if (strcmp(dataType, "string") == 0)
		{
			char* cData = (char*)pItemData;
			lua_pushstring(luaState, cData);
		} 
		else if (strcmp(dataType, "bitmap") == 0)
		{
			XL_BITMAP_HANDLE hBitmap = pItemData;	
			XLUE_PushBitmap(luaState, hBitmap);
		}
		else 
		{
			lua_pushnil(luaState);
		}
		return 1;
	}
	lua_pushnil(luaState);
	return 1;
}

int LuaDataModelClass::GetCount(lua_State *luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		int rowCount = pDataModelClass->GetCount();
		lua_pushinteger(luaState, rowCount);
		return 1;
	}
	lua_pushnil(luaState);
	return 1;
}


int LuaDataModelClass::GetColumnCount(lua_State *luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		int columnCount = pDataModelClass->GetColumnCount();
		lua_pushinteger(luaState, columnCount);
		return 1;
	}
	lua_pushnil(luaState);
	return 1;
}

int LuaDataModelClass::DeleteSelf(lua_State *luaState)
{
	if(DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		delete pDataModelClass;
	}
	//返回值用于提示该C函数的返回值数量，即压入栈中的返回值数量。
	return 0;
}

int LuaDataModelClassFactory::CreateInstance(lua_State* luaState)
{
	if (lua_isstring(luaState, 2) && lua_isstring(luaState, 3))
	{
		DataModelInterface* pResult = NULL;
		const char *dataModelClassName = lua_tostring(luaState, 2);
		const char *userdata = lua_tostring(luaState, 3);
		const char *argv[1] = {userdata};
		if (strcmp(dataModelClassName, "XmlDataModel") == 0)
		{
			pResult = new XmlDataModel(1, argv); //实例化问题
		}
		// 如果还有其他DataModelInterface的实现, 放在这里处理. 
		// 在有新的DataModel时, 还是需要修改工厂类的实现, 但是比增加一个LuaDataModelClass实现的代码量还是少的
		XLLRT_PushXLObject(luaState,dataModelClassName,pResult);
	}
	return 1;
}

LuaDataModelClassFactory* __stdcall LuaDataModelClassFactory::Instance(void*)
{
	static LuaDataModelClassFactory* s_pTheOne = NULL;
	if (s_pTheOne == NULL)
	{
		s_pTheOne = new LuaDataModelClassFactory();
	}
	return s_pTheOne;
}

XLLRTGlobalAPI LuaDataModelClassFactory::s_LuaDataModelClassFactoryMemberFunctions[] = 
{
	{"CreateInstance",LuaDataModelClassFactory::CreateInstance},
	{NULL,NULL}
};

void LuaDataModelClassFactory::RegisterObj(const char *dataModelClassName, XL_LRT_ENV_HANDLE hEnv)
{
	if(hEnv == NULL)
	{
		return ;
	}

	XLLRTObject factoryObject;
	char factoryClassName[100];
	strcpy_s(factoryClassName, dataModelClassName);
	strcat_s(factoryClassName, ".Factory.Class");
	char factoryObjectName[100];
	strcpy_s(factoryObjectName, dataModelClassName);
	strcat_s(factoryObjectName, ".Factory.Object");
	factoryObject.ClassName = factoryClassName;
	factoryObject.MemberFunctions = s_LuaDataModelClassFactoryMemberFunctions;
	factoryObject.ObjName = factoryObjectName;

	factoryObject.userData = NULL;
	factoryObject.pfnGetObject = (fnGetObject)LuaDataModelClassFactory::Instance;

	XLLRT_RegisterGlobalObj(hEnv,factoryObject); 
}