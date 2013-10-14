/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : critical_section.h
* 内容摘要  : 定义临界区。临界区与互斥锁（mutex）相比，效率要高。这是因为临界区不是
              核心对象，而是运行在用户态，所以一般情况下都推荐使用临界区。
* 当前版本  : 1.0
* 作    者  : 杨晓虎
* 设计日期  : 2009年4月3日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__
#define __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__

#include "xl_lib/type.h"
#include "xl_lib/win32/multithread/lock_guard.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)

/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

class critical_section
{
public:
    critical_section();
    virtual ~critical_section();

    void lock();
    void unlock();
    bool try_lock();

    operator CRITICAL_SECTION()
    {
        return m_cs;
    }
    CRITICAL_SECTION* operator &()
    {
        return &m_cs;
    }
private:
    CRITICAL_SECTION	m_cs;		// Windows中的临界区

    typedef BOOL (*TryEnterCriticalSectionProc)(
        LPCRITICAL_SECTION lpCriticalSection  // critical section
        );

    static TryEnterCriticalSectionProc  m_fnTryEnterCriticalSection;
};

typedef lock_guard<critical_section>    cs_lock_guard;
typedef lock_guard<critical_section>    critical_section_lock_guard;

XL_WIN32_NAMESPACE_END(multithread)

#endif // end of __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__
