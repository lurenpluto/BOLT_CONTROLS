/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : xl_lib.h
* 内容摘要  : 辅助头文件。包含了迅雷公共库的所有头文件，避免使用时逐一包含。
* 当前版本  : 1.0
* 作    者  : 杨晓虎
* 设计日期  : 2009年4月8日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
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

/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

#endif // end of __XL_LIB_H_42DA9D42_7D1E_46E6_8673_9D50D192158C__
