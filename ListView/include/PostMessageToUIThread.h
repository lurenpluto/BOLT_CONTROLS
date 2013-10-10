#pragma once
typedef void (*PFNMAINTHREADCALLBACK)(void*);

///! UIThreadDll提供的接口只有一个,就是把消息放在UI线程的队尾
///! param void *userData,用户调用时传进来的参数, 可以用来传递消息信息, 例如调用者自身的指针, 或者其他数据
///! param PFNMAINTHREADCALLBACK, 调用者希望当这个事件被执行的时候回调的函数, 回调函数参数为userData
void PostMessageToUIThread( void *pUserData = 0, PFNMAINTHREADCALLBACK pfnMainThreadCallback = 0);
void InitUIThread();
void UnInitUIThread();