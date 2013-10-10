#include "LuaDataModelClass.h"
#include "XmlDataModel.h"

typedef void (*PFNDATAREADYCALLBACK) (lua_State* luaState, long functionRef, int row, int column);

/*
����ļ�����, �ڱ������¼�����ʱ����һ��lua����, ���lua��������(int,int)�Ĳ���
��������Ҫ����һ��lua������ref (long), һ��lua State
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
	//luaջ��, 1���������, ��2��ʼ�ǲ���
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
		if(lua_isfunction(luaState, 3)) //��ģ������2, ��ģ���ʱ��lua��û�м���������, �ýӿڵ�ʱ�����
		{
			lua_pushvalue(luaState, 3);
			// lua������ref��unref�ֱ����DataReadyListener�Ĺ�������������е���
			// DataReadyListener��luaDataModelClass����, ��XmlDataModel����. 
			// ���һ��Ҫ����"˭����, ˭����", �ڴ˿��԰�DataReadyListener��ָ������/ָ��ָ�봫��XmlDataModel, LuaDataModelClass����DataReadyListener����������, �������б�Ҫ. 
			pDataModelClass->SetSingleDataReadyListener(new DataReadyListener(LuaDataModelClass::LuaDataReadyListener, luaState));
		} 
	}
	return 0;
}

int LuaDataModelClass::SetDataBatchReadyListener(lua_State* luaState)
{
	if (DataModelInterface *pDataModelClass = GetDataModelClassObject(luaState))
	{
		if(lua_isfunction(luaState, 3))//��ģ������2, ��ģ���ʱ��lua��û�м���������, �ýӿڵ�ʱ�����
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

	//����ԭ��XL_LRT_API(long) XLLRT_LuaCall(lua_State* luaState,int args,int results,const wchar_t* contextInfo);
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
			lua_newtable(L); // Ҫ���ص�table, �����ֽ�return table
			for ( int row = from; row <= to; row++)
			{
				lua_newtable(L);// ��һ�е�Table, ����rowtable, ����rowtable@-1
				void *pItemData = ppDataBatch[3*(row-from)];
				for ( int column = 1; column<=columnCount; column++)
				{
					lua_pushnumber(L, column);//��indexѹջ, ����rowtable@-2
					void *pItemData = ppDataBatch[3*(row-from)+column-1];
					if (strcmp(pTypes[column-1], "string") == 0) //��һ�ΰ�ֵѹջ
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
						lua_pushnil(L); //��ʹû�ж�������, ҲҪ��һ����ռλ
					}
					//����value@-1, index@-2, rowtable@-3
					lua_settable(L, -3); // �Ѹ�ѹջ��index, value��������rowtable��
				}
				lua_pushnumber(L, row);//��һά����rowѹջ
				lua_insert(L, -2); // ��ջ����һά������rowtable��һ��λ��, 
				lua_settable(L, -3); // �Ѹ�ѹջ��һά����row, ��rowtable����, ����Ҫ���ص�return table��
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
	//����ֵ������ʾ��C�����ķ���ֵ��������ѹ��ջ�еķ���ֵ������
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
			pResult = new XmlDataModel(1, argv); //ʵ��������
		}
		// �����������DataModelInterface��ʵ��, �������ﴦ��. 
		// �����µ�DataModelʱ, ������Ҫ�޸Ĺ������ʵ��, ���Ǳ�����һ��LuaDataModelClassʵ�ֵĴ����������ٵ�
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