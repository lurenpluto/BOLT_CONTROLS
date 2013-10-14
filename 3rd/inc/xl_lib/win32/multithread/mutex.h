/*******************************************************************************
* ��Ȩ���� (C)2009,������Ѹ�����缼�����޹�˾��
* ϵͳ����	: Ѹ�׹�����
* �ļ�����	: mutex.h
* ����ժҪ	: ����Mutex��������װ�ࡣMutex ΪWindows�ں˶���Ч�ʵ����ٽ���(critial section)
              ֻ���ڿ���̵�ʱ����ʹ�� Mutex��
* ��ǰ�汾	: 1.0
* ��    ��	: �������޶�
* �������	: 2009��2��25��
* �޸ļ�¼	: 
* ��    ��		��    ��		�޸��� 		�޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __MUTEX_H_0F5DC9C1_6D3A_49CA_8124_557485831AE3__
#define __MUTEX_H_0F5DC9C1_6D3A_49CA_8124_557485831AE3__

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"
#include "xl_lib/win32/multithread/lock_guard.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)

/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

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
