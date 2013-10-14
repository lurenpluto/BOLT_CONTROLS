/*******************************************************************************
* 版权所有 (C)2009,深圳市迅雷网络技术有限公司。
* 系统名称	: 迅雷公共库
* 文件名称	: mutex.h
* 内容摘要	: 定义Mutex互斥锁封装类。Mutex 为Windows内核对象，效率低于临界区(critial section)
              只有在跨进程的时候建议使用 Mutex。
* 当前版本	: 1.0
* 作    者	: 杨晓虎修订
* 设计日期	: 2009年2月25日
* 修改记录	: 
* 日    期		版    本		修改人 		修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __MUTEX_H_0F5DC9C1_6D3A_49CA_8124_557485831AE3__
#define __MUTEX_H_0F5DC9C1_6D3A_49CA_8124_557485831AE3__

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"
#include "xl_lib/win32/multithread/lock_guard.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)

/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

class mutex
{
public:
    mutex();
    mutex( bool open_existing, const tchar* mutex_name );
    virtual ~mutex();

    mutex( const mutex& mx );
    mutex& operator=( const mutex& mx );

    void lock();
    void unlock();
    bool try_lock( uint32 wait_millisec = 0 );

    operator HANDLE() const
    {
        return m_mutex;
    }

private:
    HANDLE      m_mutex;
};

typedef lock_guard<mutex>    mx_lock_guard;
typedef lock_guard<mutex>    mutex_lock_guard;

XL_WIN32_NAMESPACE_END(multithread)

#endif // end of __MUTEX_H_0F5DC9C1_6D3A_49CA_8124_557485831AE3__
