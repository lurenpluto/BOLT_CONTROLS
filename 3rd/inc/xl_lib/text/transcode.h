/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : transcode.h
* ����ժҪ  : ���ڸ��ֳ������ַ�������ת��
* ��ǰ�汾  : 1.0
* ��    ��  : ���Ǵ�ԭ�����������޶����
* �������  : 2009��3��24��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __TRANSCODE_H_13458E82_E2D0_4516_9475_B6EA0ECE0C57__
#define __TRANSCODE_H_13458E82_E2D0_4516_9475_B6EA0ECE0C57__

#include "xl_lib/tchar.h"

#ifdef WIN32
#else
#include <iconv.h>
#endif

XL_NAMESPACE_BEGIN(text)

/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

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

