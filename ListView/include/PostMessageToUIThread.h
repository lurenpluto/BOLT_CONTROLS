#pragma once
typedef void (*PFNMAINTHREADCALLBACK)(void*);

///! UIThreadDll�ṩ�Ľӿ�ֻ��һ��,���ǰ���Ϣ����UI�̵߳Ķ�β
///! param void *userData,�û�����ʱ�������Ĳ���, ��������������Ϣ��Ϣ, ��������������ָ��, ������������
///! param PFNMAINTHREADCALLBACK, ������ϣ��������¼���ִ�е�ʱ��ص��ĺ���, �ص���������ΪuserData
void PostMessageToUIThread( void *pUserData = 0, PFNMAINTHREADCALLBACK pfnMainThreadCallback = 0);
void InitUIThread();
void UnInitUIThread();