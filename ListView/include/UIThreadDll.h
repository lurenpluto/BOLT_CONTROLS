#pragma once
///! 这个dll不需要Bolt, XLUE支持, 就是简单的完成"把一个事件放在UI线程队尾"的任务
typedef void (*MainThreadCallbackFun)(void*);

///! UIThreadDll提供的接口只有一个,就是把消息放在UI线程的队尾
///! param void *userData,用户调用时传进来的参数, 可以用来传递消息信息, 例如调用者自身的指针, 或者其他数据
///! param MainThreadCallbackFun, 调用者希望当这个事件被执行的时候回调的函数, 回调函数参数为userData
extern "C" __declspec(dllexport) void PostMessageToUIThread( void *userData = 0, MainThreadCallbackFun ptrFun = 0);