/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : xl_lib.h
* ����ժҪ  : ����ͷ�ļ���������Ѹ�׹����������ͷ�ļ�������ʹ��ʱ��һ������
* ��ǰ�汾  : 1.0
* ��    ��  : ������
* �������  : 2009��4��8��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __XL_LIB_H_42DA9D42_7D1E_46E6_8673_9D50D192158C__
#define __XL_LIB_H_42DA9D42_7D1E_46E6_8673_9D50D192158C__

#include "xl_lib/type.h"
#include "xl_lib/error.h"
#include "xl_lib/safe_delete.h"
#include "xl_lib/tchar.h"

#include "xl_lib/text/format_utility.h"
#include "xl_lib/text/string_utility.h"
#include "xl_lib/text/transcode.h"

#include "xl_lib/filesystem/dir_utility.h"
#include "xl_lib/filesystem/disk_utility.h"
#include "xl_lib/filesystem/file_utility.h"
#include "xl_lib/filesystem/path_utility.h"

#include "xl_lib/crypto/aes.h"
#include "xl_lib/crypto/md4.h"
#include "xl_lib/crypto/md5.h"
#include "xl_lib/crypto/sha1.h"
#include "xl_lib/crypto/base64.h"

#include "xl_lib/encoding/bencoding.h"

#include "xl_lib/config/config.h"

#include "xl_lib/product/xunlei/cid.h"
#include "xl_lib/product/xunlei/cid_utility.h"
#include "xl_lib/product/xunlei/peerid.h"
#include "xl_lib/product/xunlei/thunder_url.h"

#if defined(WIN32)

#include "xl_lib/win32/com_utility.h"
#include "xl_lib/win32/ie_proxy_setting.h"
#include "xl_lib/win32/version_utility.h"

#include "xl_lib/win32/multithread/lock_guard.h"
#include "xl_lib/win32/multithread/critical_section.h"
#include "xl_lib/win32/multithread/mutex.h"
#include "xl_lib/win32/multithread/thread.h"

#include "xl_lib/win32/multiprocess/share_memory.h"
#include "xl_lib/win32/multiprocess/process_messenger.h"

#include "xl_lib/win32/net/net_utility.h"
#include "xl_lib/win32/net/local_host.h"

#elif defined(__LINUX__)

#include "xl_lib/linux/xl_linux_lib.h"

#endif

/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

#endif // end of __XL_LIB_H_42DA9D42_7D1E_46E6_8673_9D50D192158C__
