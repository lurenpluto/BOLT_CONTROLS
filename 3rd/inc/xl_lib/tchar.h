/*******************************************************************************
* 版权所有 (C)2009,深圳市迅雷网络技术有限公司。
* 系统名称	: 迅雷公共库
* 文件名称	: tstring.h
* 内容摘要	: 公共库对于UNICODE工程和ASCII工程定义统一的字符类型以及stl字符串类型
* 当前版本	: 1.0
* 作    者	: 杨晓虎
* 设计日期	: 2009年3月16日
* 修改记录	: 
* 日    期		版    本		修改人 		修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __TCHAR_H_A4887C1F_2762_40fb_B53F_868FB3CED0F7__  
#define __TCHAR_H_A4887C1F_2762_40fb_B53F_868FB3CED0F7__  

#include "./type.h"

/********************************** 常量和宏 **********************************/

#ifdef __LINUX__

#include <string>

NAMESPACE_BEGIN(xl)

typedef char            tchar;
typedef std::string     tstring;

#define TSTRING(text)   text

NAMESPACE_END(xl)

#elif WIN32

#include <string> // stl string
#include <fstream>
#include <sstream>
#include <strstream>

NAMESPACE_BEGIN(xl)

#if defined(UNICODE) || defined(_UNICODE)

typedef wchar_t         tchar;
typedef std::wstring    tstring;

typedef std::wistream   tistream;
typedef std::wostream   tostream;

typedef std::wfstream   tfstream;
typedef std::wifstream  tifstream;
typedef std::wofstream  tofstream;

typedef std::wstringstream  tstringstream;
typedef std::wistringstream tistringstream;
typedef std::wostringstream tostringstream;

#define TSTRING(text)   L##text

#else // #if defined(UNICODE) || defined(_UNICODE)

typedef char            tchar;
typedef std::string     tstring;

typedef std::istream   tistream;
typedef std::ostream   tostream;

typedef std::fstream   tfstream;
typedef std::ifstream  tifstream;
typedef std::ofstream  tofstream;

typedef std::stringstream  tstringstream;
typedef std::istringstream tistringstream;
typedef std::ostringstream tostringstream;

#define TSTRING(text)   text

#endif // #if defined(UNICODE) || defined(_UNICODE)

NAMESPACE_END(xl)

#endif // #ifdef __LINUX__ #elif WIN32



/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

#endif // end of __TYPE_H_41DF2D3C-69B5-4c78-B927-B55C39F23755__  
