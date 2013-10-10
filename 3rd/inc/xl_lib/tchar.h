/*******************************************************************************
* ��Ȩ���� (C)2009,������Ѹ�����缼�����޹�˾��
* ϵͳ����	: Ѹ�׹�����
* �ļ�����	: tstring.h
* ����ժҪ	: ���������UNICODE���̺�ASCII���̶���ͳһ���ַ������Լ�stl�ַ�������
* ��ǰ�汾	: 1.0
* ��    ��	: ������
* �������	: 2009��3��16��
* �޸ļ�¼	: 
* ��    ��		��    ��		�޸��� 		�޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __TCHAR_H_A4887C1F_2762_40fb_B53F_868FB3CED0F7__  
#define __TCHAR_H_A4887C1F_2762_40fb_B53F_868FB3CED0F7__  

#include "./type.h"

/********************************** �����ͺ� **********************************/

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



/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

#endif // end of __TYPE_H_41DF2D3C-69B5-4c78-B927-B55C39F23755__  
