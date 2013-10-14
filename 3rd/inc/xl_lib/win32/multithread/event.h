/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : event.h
* ����ժҪ  : ��װ��windows�µ�Events�ں˶���Ŀ����Ϊ���ṩһ����ƽ̨���¼���
* ��ǰ�汾  : 1.0
* ��    ��  : ������
* �������  : 2009��11��26��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __EVENT_H_CE07AFDE_3096_4E98_9636_EB9CF6F70ED6__
#define __EVENT_H_CE07AFDE_3096_4E98_9636_EB9CF6F70ED6__

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"

XL_WIN32_NAMESPACE_BEGIN(multithread)
/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/
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
