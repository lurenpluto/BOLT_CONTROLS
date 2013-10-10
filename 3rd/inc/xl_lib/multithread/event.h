/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : event.h
* 内容摘要  : 封装了windows下的Events内核对象，目的是为了提供一个跨平台的事件类
* 当前版本  : 1.0
* 作    者  : 杨晓虎
* 设计日期  : 2009年11月26日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __EVENT_H_CE07AFDE_3096_4E98_9636_EB9CF6F70ED6__
#define __EVENT_H_CE07AFDE_3096_4E98_9636_EB9CF6F70ED6__

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)
/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/
class event
{
public:
    event( bool initial_set = false, bool auto_reset = false );
    event( bool open_existing, const tchar* event_name, bool initial_set = false, bool auto_reset = false );
    virtual ~event();

    event( const event& evt );
    event& operator=( const event& evt );

    void set_event();
    void reset_event();
    bool wait_event( uint32 wait_millisec = INFINITE );
    bool is_event_set();

    operator HANDLE()
    {
        return m_event;
    }

protected:
    void reset();

    HANDLE m_event;
};

XL_WIN32_NAMESPACE_END(multithread)

#endif // end of __EVENT_H_CE07AFDE_3096_4E98_9636_EB9CF6F70ED6__
