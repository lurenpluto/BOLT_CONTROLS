/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : transcode.h
* 内容摘要  : 用于各种常见的字符串编码转换
* 当前版本  : 1.0
* 作    者  : 刘智聪原作、杨晓虎修订风格
* 设计日期  : 2009年3月24日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __TRANSCODE_H_13458E82_E2D0_4516_9475_B6EA0ECE0C57__
#define __TRANSCODE_H_13458E82_E2D0_4516_9475_B6EA0ECE0C57__

#include "xl_lib/tchar.h"

#ifdef WIN32
#else
#include <iconv.h>
#endif

XL_NAMESPACE_BEGIN(text)

/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

class transcode
{
public:
    static void Unicode_to_UTF8(const wchar_t* in, uint32 len, std::string& out);
 
    static void UTF8_to_Unicode(const char* in, uint32 len, std::wstring& out);
  
    static void GBK_to_UTF8(const char* in, uint32 len, std::string& out);
  
    static void UTF8_to_GBK(const char* in, uint32 len, std::string& out);

    static void Unicode_to_GBK(const wchar_t* in, uint32 len, std::string& out);

    static void GBK_to_Unicode(const char* in, uint32 len, std::wstring& out);

    static void Unicode_to_ANSI(const wchar_t* in, uint32 len, std::string& out);

    static void ANSI_to_Unicode(const char* in, uint32 len, std::wstring& out);


    static void tstring_to_UTF8(const char* in, uint32 len, std::string& out);
    static void tstring_to_UTF8(const wchar_t* in, uint32 len, std::string& out);

    static void UTF8_to_tstring(const char* in, uint32 len, std::string& out);
    static void UTF8_to_tstring(const char* in, uint32 len, std::wstring& out);

    static void tstring_to_GBK(const char* in, uint32 len, std::string& out);
    static void tstring_to_GBK(const wchar_t* in, uint32 len, std::string& out);

    static void GBK_to_tstring(const char* in, uint32 len, std::string& out);
    static void GBK_to_tstring(const char* in, uint32 len, std::wstring& out);

    static void tstring_to_Unicode(const char* in, uint32 len, std::wstring& out);
    static void tstring_to_Unicode(const wchar_t* in, uint32 len, std::wstring& out);

    static void Unicode_to_tstring(const wchar_t* in, uint32 len, std::string& out);
    static void Unicode_to_tstring(const wchar_t* in, uint32 len, std::wstring& out);

    static void tstring_to_ANSI(const char* in, uint32 len, std::string& out);
    static void tstring_to_ANSI(const wchar_t* in, uint32 len, std::string& out);

    static void ANSI_to_tstring(const char* in, uint32 len, std::string& out);
    static void ANSI_to_tstring(const char* in, uint32 len, std::wstring& out);

};

XL_NAMESPACE_END(text)

#endif // end of __TRANSCODE_H_13458E82_E2D0_4516_9475_B6EA0ECE0C57__

