#pragma once
///! ���dll����ҪBolt, XLUE֧��, ���Ǽ򵥵����"��һ���¼�����UI�̶߳�β"������
typedef void (*MainThreadCallbackFun)(void*);

///! UIThreadDll�ṩ�Ľӿ�ֻ��һ��,���ǰ���Ϣ����UI�̵߳Ķ�β
///! param void *userData,�û�����ʱ�������Ĳ���, ��������������Ϣ��Ϣ, ��������������ָ��, ������������
///! param MainThreadCallbackFun, ������ϣ��������¼���ִ�е�ʱ��ص��ĺ���, �ص���������ΪuserData
extern "C" __declspec(dllexport) void PostMessageToUIThread( void *userData = 0, MainThreadCallbackFun ptrFun = 0);