/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : critical_section.h
* ����ժҪ  : �����ٽ������ٽ����뻥������mutex����ȣ�Ч��Ҫ�ߡ�������Ϊ�ٽ�������
              ���Ķ��󣬶����������û�̬������һ������¶��Ƽ�ʹ���ٽ�����
* ��ǰ�汾  : 1.0
* ��    ��  : ������
* �������  : 2009��4��3��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__
#define __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__

#include "xl_lib/type.h"
#include "xl_lib/win32/multithread/lock_guard.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)

/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

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
    CRITICAL_SECTION	m_cs;		// Windows�е��ٽ���

    typedef BOOL (*TryEnterCriticalSectionProc)(
        LPCRITICAL_SECTION lpCriticalSection  // critical section
        );

    static TryEnterCriticalSectionProc  m_fnTryEnterCriticalSection;
};

typedef lock_guard<critical_section>    cs_lock_guard;
typedef lock_guard<critical_section>    critical_section_lock_guard;

XL_WIN32_NAMESPACE_END(multithread)

#endif // end of __CRITICAL_SECTION_H_EDE4FC3C_DAEB_4FC1_9BF3_6F36B689B3E9__
