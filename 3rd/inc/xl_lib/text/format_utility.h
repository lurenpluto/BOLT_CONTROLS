/*******************************************************************************
* ��Ȩ���� (C)2009,������Ѹ�����缼�����޹�˾��
* ϵͳ����	: Ѹ�׹�����
* �ļ�����	: format_utility.h
* ����ժҪ	: ���ָ�ʽ���ַ���֮���ת��
* ��ǰ�汾	: 1.0
* ��    ��	: ������
* �������	: 2009��3��9��
* �޸ļ�¼	: 
* ��    ��		��    ��		�޸��� 		�޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __FORMAT_UTILITY_H_DA84050F_6692_40f3_95E1_9CFA4122D924__  
#define __FORMAT_UTILITY_H_DA84050F_6692_40f3_95E1_9CFA4122D924__

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"

XL_NAMESPACE_BEGIN(text)
/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/
template<class _char> class format_utility_t;

typedef format_utility_t<tchar> format_utility;

template<class _char>
class format_utility_t
{
public:
    typedef std::basic_string<_char> _string;

    static _string      to_string(uint8 i);
    static _string      to_string(sint8 i);

    static _string      to_string(uint16 i);
    static _string      to_string(sint16 i);

    static _string      to_string(uint32 i);
    static _string      to_string(sint32 i);

    static _string      to_string(uint64 i);
    static _string      to_string(sint64 i);

    static _string      to_string(float32 f);
    static _string      to_string(float64 f);

    static uint8        str_to_uint8(const _string& s);
    static sint8        str_to_sint8(const _string& s);

    static uint8        str_to_uint8(const _char* s);
    static sint8        str_to_sint8(const _char* s);

    static uint16       str_to_uint16(const _string& s);
    static sint16       str_to_sint16(const _string& s);

    static uint16       str_to_uint16(const _char* s);
    static sint16       str_to_sint16(const _char* s);

    static uint32       str_to_uint32(const _string& s);
    static uint32       str_to_uint32(const _char* s);

    static sint32       str_to_sint32(const _string& s);
    static sint32       str_to_sint32(const _char* s);

    static uint64       str_to_uint64(const _string& s);
    static uint64       str_to_uint64(const _char* s);

    static sint64       str_to_sint64(const _string& s);
    static sint64       str_to_sint64(const _char* s);

    static float32      str_to_float32(const _string& s);
    static float32      str_to_float32(const _char* s);

    static float64      str_to_float64(const _string& s);
    static float64      str_to_float64(const _char* s);

    static _string      to_string(bool b);
    static bool         str_to_bool(const _string& s);
    static bool         str_to_bool(const _char* s);

    static bool         is_readable(byte ch);
    static bool         is_readable(_char ch);

    static bool         is_hex(byte ch);
    static bool         is_hex(_char ch);
    static bool         is_hex_string(const byte* str, uint32 len);
    static bool         is_hex_string(const _char* str, uint32 len);
    static bool         is_hex_string(const _string& str);

    static sint32       hex_to_int(byte ch);
    static sint32       hex_to_int(_char ch);	

    static bool         byte_to_hex(byte data, _char* buf, uint32 len = 2);

    static _string      bytes_to_hex_string(const byte* data, uint32 len);
    static _string      bytes_to_hex_string(const std::string& bytes);

    static sint32       hex_string_to_bytes(const byte* hex_buffer, uint32 hex_len, byte* buffer, uint32 buffer_len);	
    static sint32       hex_string_to_bytes(const _char* hex_buffer, uint32 hex_len, byte* buffer, uint32 buffer_len);
    static sint32       hex_string_to_bytes(const _string& hex, byte* buffer, uint32 buffer_len);    
    static std::string  hex_string_to_bytes(const _string& hex);

    static _string      kilo_format( float64 n );

private:
	static _char        s_hex_data_map[];
};




/*********************************** ��ʵ�� ***********************************/

template<class _char>
_char format_utility_t<_char>::s_hex_data_map[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

template<class _char>
std::basic_string<_char> format_utility_t<_char>::to_string(uint8 i)
{
    return to_string((uint32)i);
}

template<class _char>
std::basic_string<_char> format_utility_t<_char>::to_string(sint8 i)
{
    return to_string((sint32)i);
}

template<class _char>
std::basic_string<_char> format_utility_t<_char>::to_string(uint16 i)
{
    return to_string((uint32)i);
}

template<class _char>
std::basic_string<_char> format_utility_t<_char>::to_string(sint16 i)
{
    return to_string((sint32)i);
}

template<class _char>
uint8 format_utility_t<_char>::str_to_uint8(const std::basic_string<_char>& s)
{
    return (uint8)str_to_uint32(s);	
}

template<class _char>
sint8 format_utility_t<_char>::str_to_sint8(const std::basic_string<_char>& s)
{
    return (sint8)str_to_sint32(s);
}

template<class _char>
uint8 format_utility_t<_char>::str_to_uint8(const _char* s)
{
    return (uint8)str_to_uint32(s);	
}

template<class _char>
sint8 format_utility_t<_char>::str_to_sint8(const _char* s)
{
    return (sint8)str_to_sint32(s);
}

template<class _char>
uint16 format_utility_t<_char>::str_to_uint16(const std::basic_string<_char>& s)
{
    return (uint16)str_to_uint32(s);
}

template<class _char>
sint16 format_utility_t<_char>::str_to_sint16(const std::basic_string<_char>& s)
{
    return (sint16)str_to_sint32(s);
}

template<class _char>
uint16 format_utility_t<_char>::str_to_uint16(const _char* s)
{
    return (uint16)str_to_uint32(s);
}

template<class _char>
sint16 format_utility_t<_char>::str_to_sint16(const _char* s)
{
    return (sint16)str_to_sint32(s);
}

template<class _char>
uint32 format_utility_t<_char>::str_to_uint32(const std::basic_string<_char>& s)
{
    return str_to_uint32(s.c_str());
}


template<class _char>
sint32 format_utility_t<_char>::str_to_sint32(const std::basic_string<_char>& s)
{
    return str_to_sint32(s.c_str());
}


template<class _char>
uint64 format_utility_t<_char>::str_to_uint64(const std::basic_string<_char>& s)
{
    return str_to_uint64(s.c_str());
}


template<class _char>
sint64 format_utility_t<_char>::str_to_sint64(const std::basic_string<_char>& s)
{
    return str_to_sint64(s.c_str());
}


template<class _char>
float32 format_utility_t<_char>::str_to_float32(const std::basic_string<_char>& s)
{
    return str_to_float32(s.c_str());
}


template<class _char>
float64 format_utility_t<_char>::str_to_float64(const std::basic_string<_char>& s)
{
    return str_to_float64(s.c_str());
}

template<class _char>
std::basic_string<_char> format_utility_t<_char>::to_string(bool b)
{
    _char t[] = { 't', 'r', 'u', 'e', '\0' };
    _char f[] = { 'f', 'a', 'l', 's', 'e', '\0' };
    return b ? t : f;
}

template<class _char>
bool format_utility_t<_char>::str_to_bool(const std::basic_string<_char>& s)
{
    return str_to_bool( s.c_str() );
}


/*******************************************************************************
* ��������	: format_utility_t<_char>::is_readable
* ��������	: �ж�һ���ַ��Ƿ�ɶ�����ASCII������[32,126]
* �Ρ�����	: byte ch				Ҫ�жϵ��ַ�
* �� �� ֵ	: bool					true��ʾ�ɶ���false��ʾ���ɶ�
* ��������	: ������ ������
* �������	: 2009��3��11��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_readable(byte ch)
{
    return (ch > 31 && ch < 127);
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_readable
* ��������	: �ж�һ���ַ��Ƿ�ɶ�����ASCII������[32,126]
* �Ρ�����	: _char ch				Ҫ�жϵ��ַ�
* �� �� ֵ	: bool					true��ʾ�ɶ���false��ʾ���ɶ�
* ��������	: ������ ������
* �������	: 2009��4��8��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_readable(_char ch)
{
    return (ch > 31 && ch < 127);
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_hex
* ��������	: �ж�һ���ַ��Ƿ�Ϊ16�����ַ�
* �Ρ�����	: byte ch			Ҫ������ַ�
* �� �� ֵ	: bool				true��ʾ��16�����ַ���false��ʾ����16�����ַ�
* ��������	: ������ ������
* �������	: 2009��3��9��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_hex(byte ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return true;
    }
    if(ch >= 'a' && ch <= 'f')
    {
        return true;
    }
    if(ch >= 'A' && ch <= 'F')
    {
        return true;
    }

    return false;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_hex
* ��������	: �ж�һ���ַ��Ƿ�Ϊ16�����ַ�
* �Ρ�����	: _char ch			Ҫ������ַ�
* �� �� ֵ	: bool				true��ʾ��16�����ַ���false��ʾ����16�����ַ�
* ��������	: ������ ������
* �������	: 2009��4��8��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_hex(_char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return true;
    }
    if(ch >= 'a' && ch <= 'f')
    {
        return true;
    }
    if(ch >= 'A' && ch <= 'F')
    {
        return true;
    }

    return false;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_hex_string
* ��������	: �ж�һ���ַ����Ƿ�Ϊ16�����ַ���
* �Ρ�����	: const byte* str		Ҫ�жϵ��ַ���
* �Ρ�����	: uint32 len			�ַ�������
* �� �� ֵ	: bool					true��ʾΪ16�����ַ�����false��ʾ����16�����ַ���
* ��������	: ������ ������
* �������	: 2009��3��11��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_hex_string(const byte* str, uint32 len)
{
    if(NULL == str || 0 == len)
    {
        return false;
    }

    for(uint32 i = 0; i < len; i ++)
    {
        if(!is_hex(str[i]))
        {
            return false;
        }
    }

    return true;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_hex_string
* ��������	: �ж�һ���ַ����Ƿ�Ϊ16�����ַ���
* �Ρ�����	: const _char* str		Ҫ�жϵ��ַ���
* �Ρ�����	: uint32 len			�ַ�������
* �� �� ֵ	: bool					true��ʾΪ16�����ַ�����false��ʾ����16�����ַ���
* ��������	: ������ ������
* �������	: 2009��4��8��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_hex_string(const _char* str, uint32 len)
{
    if(NULL == str || 0 == len)
    {
        return false;
    }

    for(uint32 i = 0; i < len; i ++)
    {
        if(!is_hex(str[i]))
        {
            return false;
        }
    }

    return true;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::is_hex_string
* ��������	: �ж�һ���ַ����Ƿ�Ϊ16�����ַ���
* �Ρ�����	: const std::string& str		Ҫ�жϵ��ַ���
* �� �� ֵ	: bool					true��ʾΪ16�����ַ�����false��ʾ����16�����ַ���
* ��������	: ������ ������
* �������	: 2009��3��11��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::is_hex_string(const std::basic_string<_char>& str)
{
    if(str.empty())
    {
        return false;
    }

    return is_hex_string(str.c_str(), str.length());
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::hex_2_int
* ��������	: ��ʮ�����ַ���ʾΪʮ��������,��'A'ת��Ϊ10
* �Ρ�����	: byte ch				16�����ַ�
* �� �� ֵ	: sint32				��Ӧ��ֵ����16�����ַ�������Ϊ-1
* ��������	: ������ ������
* �������	: 2009��3��9��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
sint32 format_utility_t<_char>::hex_to_int(byte ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if(ch >= 'A' && ch <= 'F')
    {
        return ch - 'A' + 10;
    }
    else if(ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    else
    {
        return -1;
    }
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::hex_to_int
* ��������	: ��ʮ�����ַ���ʾΪʮ��������,��'A'ת��Ϊ10
* �Ρ�����	: _char ch					16�����ַ�
* �� �� ֵ	: sint32					��Ӧ��ֵ����16�����ַ�������Ϊ-1
* ��������	: ������ ������
* �������	: 2009��4��8��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
sint32 format_utility_t<_char>::hex_to_int(_char ch)
{
    if(ch >= '0' && ch <= '9')
    {
        return ch - '0';
    }
    else if(ch >= 'A' && ch <= 'F')
    {
        return ch - 'A' + 10;
    }
    else if(ch >= 'a' && ch <= 'f')
    {
        return ch - 'a' + 10;
    }
    else
    {
        return -1;
    }
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::byte_to_hex
* ��������	: ��һ���ַ�ת��Ϊ16����
* �Ρ�����	: byte data				Ҫ��������ַ�
* �Ρ�����	: _char* buf			���洦������ݵĻ���ָ��
* �Ρ�����	: uint32 len			���洦������ݵĻ����С
* �� �� ֵ	: bool					true��ʾ��ȷ����false��ʾ����
* ��������	: ������ ������
* �������	: 2009��3��9��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool format_utility_t<_char>::byte_to_hex(byte data, _char* buf, uint32 len)
{
    if(NULL == buf || len < 2)
    {
        return false;
    }

    uint8 h1 = (data & 0xF0) >> 4;
    uint8 h2 = data & 0xF;

    buf[0] = s_hex_data_map[h1];
    buf[1] = s_hex_data_map[h2];

    return true;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::bytes_to_hex_string
* ��������	: ��һ���ַ�ת����16����
* �Ρ�����	: const byte* data		Ҫ��������ַ���
* �Ρ�����	: uint32 len			Ҫ��������ַ���
* �� �� ֵ	: std::string				����������
* ��������	: ������ ������
* �������	: 2009��3��9��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> format_utility_t<_char>::bytes_to_hex_string(const byte* data, uint32 len)
{
    if(NULL == data || 0 == len)
    {
        return std::basic_string<_char>();
    }

    std::basic_string<_char> str(len * 2, '*');
    _char* buff = (_char*)str.c_str();
    for(uint32 i = 0; i < len; i++)
    {
        byte_to_hex(*(data + i), (buff + i * 2));
    }

    return str;
}

/*******************************************************************************
* ��������  : format_utility_t<_char>::bytes_to_hex_string
* ��������  : ��һ���ֽ�����ת��Ϊʮ�������ַ���
* �Ρ�����  : const std::string& bytes  �ֽ�����
* �� �� ֵ  : std::string                   ʮ�������ַ���
* ��������  : ������ ������
* �������  : 2009��4��2��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> format_utility_t<_char>::bytes_to_hex_string(const std::string& bytes)
{
    return bytes_to_hex_string( (const byte*)bytes.c_str(), (uint32)bytes.size() );
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::hex_text2bytes
* ��������	: ��16���Ƶ����ݻ�ԭΪ�ַ���
* �Ρ�����	: const _char* hex_buffer		��Ҫ�����16��������
* �Ρ�����	: uint32 hex_len				16�������ݳ���
* �Ρ�����	: byte* buffer					���洦������ݵĻ���ָ��
* �Ρ�����	: uint32 buffer_len				���洦������ݵĻ����С
* �� �� ֵ	: sint32						������ַ������ȣ�-1��ʾ����
* ��������	: ������ ������
* �������	: 2009��3��11��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
sint32 format_utility_t<_char>::hex_string_to_bytes(const byte* hex_buffer, uint32 hex_len, byte* buffer, uint32 buffer_len)
{
    if(NULL == hex_buffer || NULL == buffer)
    {
        return -1;
    }
    if(hex_len % 2 != 0)
    {
        return -1;
    }

    uint32 nbytes = hex_len / 2;
    if(buffer_len < nbytes)
    {
        return -1;
    }	

    for(uint32 i = 0; i < nbytes; i++)
    {
        byte c1 = hex_buffer[i * 2];
        sint32 h1 = hex_to_int(c1);
        if(h1 < 0)
        {
            return -1;
        }

        byte c2 = hex_buffer[i * 2 + 1];
        sint32 h2 = hex_to_int(c2);
        if(h2 < 0)
        {
            return -1;
        }

        byte b = (byte)((h1 << 4) | h2);
        buffer[i] = b;			
    }	

    return nbytes;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::hex_string_to_bytes
* ��������	: ��16���Ƶ����ݻ�ԭΪ�ַ���
* �Ρ�����	: const _char* hex_buffer		��Ҫ�����16��������
* �Ρ�����	: uint32 hex_len				16�������ݳ���
* �Ρ�����	: byte* buffer					���洦������ݵĻ���ָ��
* �Ρ�����	: uint32 buffer_len				���洦������ݵĻ����С
* �� �� ֵ	: sint32						������ַ������ȣ�-1��ʾ����
* ��������	: ������ ������
* �������	: 2009��4��8��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
sint32 format_utility_t<_char>::hex_string_to_bytes(const _char* hex_buffer, uint32 hex_len, byte* buffer, uint32 buffer_len)
{	
    if(hex_len % 2 != 0 || NULL == buffer)
    {
        return -1;
    }

    uint32 nbytes = hex_len / 2;
    if(buffer_len < nbytes)
    {
        return -1;
    }	

    for(uint32 i = 0; i < nbytes; i++)
    {
        _char c1 = hex_buffer[i * 2];
        sint32 h1 = hex_to_int(c1);
        if(h1 < 0)
        {
            return -1;
        }

        _char c2 = hex_buffer[i * 2 + 1];
        sint32 h2 = hex_to_int(c2);
        if(h2 < 0)
        {
            return -1;
        }

        byte b = (byte)((h1 << 4) | h2);
        buffer[i] = b;			
    }	

    return nbytes;
}

/*******************************************************************************
* ��������	: format_utility_t<_char>::hex_string_to_bytes
* ��������	: ��16���Ƶ��ַ�����ԭΪ�ֽ�����
* �Ρ�����	: const std::string& hex		��Ҫ�����16��������
* �Ρ�����	: byte* buffer				���洦������ݵĻ���ָ��
* �Ρ�����	: sint32 buffer_len			���洦������ݵĻ����С
* �� �� ֵ	: sint32					������ַ������ȣ�-1��ʾ����
* ��������	: ������ ������
* �������	: 2009��3��9��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
sint32 format_utility_t<_char>::hex_string_to_bytes(const std::basic_string<_char>& hex, byte* buffer, uint32 buffer_len)
{
    return hex_string_to_bytes( hex.c_str(), (uint32)hex.size(), buffer, buffer_len );
}

/*******************************************************************************
* ��������  : format_utility_t<_char>::hex_string_to_bytes
* ��������  : ��ʮ�����Ƶ��ַ�����ԭΪ�ֽ�����
* �Ρ�����  : const std::string& hex        ʮ�������ַ���
* �� �� ֵ  : std::string               �洢�ֽ����ݵ��ַ�������������·��ؿ��ַ���
* ��������  : ������ ������
* �������  : 2009��4��2��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
template<class _char>
std::string format_utility_t<_char>::hex_string_to_bytes(const std::basic_string<_char>& hex)
{
    std::string ret;
    ret.resize( hex.size() / 2 );
    sint32 len = hex_string_to_bytes( hex.c_str(), (uint32)hex.size(), (byte*)ret.c_str(), (uint32)ret.size() );
    if ( len == -1 )
    {
        ret.erase();
    }
    else
    {
        ret.resize( len );
    }
    return ret;
}

XL_NAMESPACE_END(text)

#endif // end of __FORMAT_UTILITY_H_DA84050F_6692_40f3_95E1_9CFA4122D924__
