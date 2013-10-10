/*******************************************************************************
* ��Ȩ���� (C)2009,������Ѹ�����缼�����޹�˾��
* ϵͳ����    : Ѹ�׹�����
* �ļ�����    : string_utility.h
* ����ժҪ    : ������ַ������йصĲ���
* ��ǰ�汾    : 1.0
* ��    ��    : ������
* �������    : 2009��3��6��
* �޸ļ�¼    : 
* ��    ��        ��    ��        �޸���         �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __STRING_UTILITY_H_7916A1DE_EA43_4721_B814_AAA697AAE649__  
#define __STRING_UTILITY_H_7916A1DE_EA43_4721_B814_AAA697AAE649__  

#include <string>
#include <vector>

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"

XL_NAMESPACE_BEGIN(text)

/********************************** �����ͺ� **********************************/

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

template<class _char> class string_utility_t;
typedef string_utility_t<tchar> string_utility;

template<class _char>
class string_utility_t
{
public:    
    typedef std::basic_string<_char> _string;
    typedef std::vector<_string>     _string_vector;

    static bool         is_empty_string(const _char* str);

    static const _char* find_nocase(const _char* src, const _char* sub);
    static sint32       compare_nocase(const _char* str1, const _char* str2);
    static sint32       compare_nocase(const _char* str1, const _char* str2, xl::uint32 len);

    static _string      trim_left(const _string& str, _char trim_char=' ');
    static _string      trim_right(const _string& str, _char trim_char=' ');
    static _string      trim(const _string& str, _char trim_char=' ');

    static void         upper(_char* str);
    static _string      to_upper(const _string& str);

    static void         lower(_char* str);
    static _string      to_lower(const _string& str);
    
    static bool         is_begin_with(const _string& fullstr, const _string& prefix);
    static bool         is_end_with(const _string& fullstr, const _string& suffix);

    static _string      replace(const _char* str, const _char* replace_src, const _char* replace_dst, bool nocase );

#ifdef WIN32
    static _string      get_substr_by_display_width( const _char* str, uint32 display_width );
#endif

    /*******************************************************************************
    * ��������	: string_utility_t<_char>::split_string
    * ��������	: ��Դ�ַ���(��delimΪ�ָ���)�ָ�Ϊ����ַ���������result_list��
    * �Ρ�����	: const _string& source					��Ҫ�ָ���ַ���
    * �Ρ�����	: const _char* delim					�ַ����ָ��
    * �Ρ�����	: std::vector<_string>& result_list		����ָ�Ľ��
    * �Ρ�����	: bool tolerant_empty_string			�Ƿ����̿��ַ��������Ϊtrue��source���������ַָ���������result_list����ӿ��ַ���,
                                                        ���Ϊfalse��source���������ַָ���������result_list����ӿ��ַ���
    * �� �� ֵ	: uint32                                �ָ�������Ŀ
    * ��������	: ������ ������
    * �������	: 2009��3��9��
    * �޸�����		   �޸���		  �޸�����
    *******************************************************************************/
    static uint32 split_string(const std::basic_string<_char>& source, const _char* delim, _string_vector& result_list, bool tolerant_empty_string = false)
    {
        if(source.empty() || NULL == delim || '\0' == delim[0])
        {
            return 0;
        }

        result_list.clear();
        size_t len = _string(delim).length();	

        std::string::size_type pos_start = 0, pos_end = 0;
        while(true)
        {
            pos_end = source.find(delim, pos_start);
            if(_string::npos == pos_end)
            {
                result_list.push_back(source.substr(pos_start, source.size() - pos_start));
                break;
            }
            else
            {
                // �ҵ������ķָ���
                if(pos_start == pos_end)
                {		
                    if(tolerant_empty_string)
                    {
                        result_list.push_back(_string());
                    }

                    pos_start += len;
                }
                else
                {
                    result_list.push_back(source.substr(pos_start, pos_end - pos_start));
                    pos_start = pos_end + len;
                }

                if(pos_start >= source.size())
                {
                    break;
                }
            }
        }

        return (uint32)result_list.size();
    }

    /*******************************************************************************
    * ��������	: string_utility_t<_char>::merge_string
    * ��������	: ��Դ�ַ���source_listͨ���ָ���delim���ӳ�Ϊһ���ַ���result_string
    * �Ρ�����	: const std::vector<_string>& source_list	��Ҫ���ӵ��ַ��������vector�п��ܰ������ַ���
    * �Ρ�����	: const _char* delim						�ַ����ָ��
    * �Ρ�����	: _string& result_string					�����ַ������Ӻ�Ľ��
    * �Ρ�����	: bool tolerant_empty_string				�Ƿ����̿��ַ��������Ϊtrue��source_list�г��ֿ��ַ���������result_string����Ӹÿ��ַ�����Ӧ�ķָ���,
                                                            ���Ϊfalse��source_list�г��ֿ��ַ���������result_string�в���Ӹÿ��ַ�����Ӧ�ķָ���
    * �� �� ֵ	: void
    * ��������	: ������
    * �������	: 2009��4��1��
    * �޸�����		   �޸���		  �޸�����
    *******************************************************************************/
    static void merge_string(const _string_vector& source_list, const _char* delim, std::basic_string<_char>& result_string, bool tolerant_empty_string=false)
    {
        if(source_list.empty() || NULL == delim || '\0' == delim[0])
        {
            return;
        }

        result_string.clear();

        for(uint32 i = 0; i < source_list.size(); i ++)
        {
            if(source_list[i].empty())
            {
                if(tolerant_empty_string)
                {				
                    result_string.append(delim);
                }
            }
            else
            {
                result_string.append(source_list[i]);
                result_string.append(delim);
            }
        }
    }


    static const _char * strnstr(const _char * str, uint32 str_len, const _char * sub, uint32 sub_len );
};

/*******************************************************************************
* ��������	: string_utility_t<_char>::is_empty_string
* ��������	: �ж�һ���ַ����Ƿ�Ϊ���ַ���
* �Ρ�����	: const _char* str		��Ҫ�жϵ��ַ���
* �� �� ֵ	: bool					true��ʾΪ���ַ�����false��ʾ���ǿ��ַ���
* ��������	: ������ ������
* �������	: 2009��3��10��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool string_utility_t<_char>::is_empty_string(const _char* str)
{
    // û����strlen(str)���ж�����Ϊstrlen()�ȽϺ�ʱ
    return (NULL == str || '\0' == str[0]);
}

/*******************************************************************************
* ��������  : string_utility_t<_char>::find_nocase
* ��������  : �����ִ�Сд���ַ�������
* �Ρ�����  : const _char* src      Դ�ַ���
* �Ρ�����  : const _char* sub      ��Դ�ַ����в��Ҹ��ַ���
* �� �� ֵ  : const _char*          ���ҵ��򷵻��ҵ�λ�õĵ�ַ�����򷵻�NULL
* ��������  : ������
* �������  : 2009��4��2��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
template<class _char>
const _char* string_utility_t<_char>::find_nocase(const _char* src, const _char* sub)
{    
    if( NULL == src || '\0' == src[0] || NULL == sub || '\0' == sub[0] )
    {
        return NULL;
    }
    _string src1 = src, sub1 = sub;
    lower( (_char*)src1.c_str() );
    lower( (_char*)sub1.c_str() );
    size_t pos = src1.find( sub1 );
    return pos == _string::npos ? NULL : (src + pos);
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::trim_whitespace
* ��������	: ȥ���ַ���ǰ���ָ���ַ���
* �Ρ�����	: _string& str		��Ҫ������ַ���
* �Ρ�����	: _char trim_char	ָ��ȥ���ַ���
* �� �� ֵ	: _string			�������ַ���
* ��������	: ������ ������
* �������	: 2009��3��6��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::trim_left(const std::basic_string<_char>& str, _char trim_char)
{
    size_t bpos = str.find_first_not_of(trim_char);

    if(bpos == _string::npos)
    {
        return _string();
    }
    else if(0 == bpos)
    {
        return str;
    }
    else
    {
        return str.substr(bpos, str.length() - bpos);
    }
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::trim_right
* ��������	: ȥ���ַ��������ָ���ַ���
* �Ρ�����	: const _string& str	��Ҫ������ַ���
* �Ρ�����	: _char trim_char		ָ��ȥ���ַ���
* �� �� ֵ	: _string				�������ַ���
* ��������	: ������ ������
* �������	: 2009��3��26��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::trim_right(const std::basic_string<_char>& str, _char trim_char)
{
    size_t epos = str.find_last_not_of(trim_char);

    if(epos == _string::npos)
    {
        return _string();
    }
    else if(epos == (str.length() - 1))
    {
        return str;
    }
    else
    {
        return str.substr(0, epos + 1);
    }
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::trim
* ��������	: ȥ���ַ���ǰ���ָ���ַ���
* �Ρ�����	: const _string& str	��Ҫ������ַ���
* �Ρ�����	: _char trim_char		ָ��ȥ���ַ���
* �� �� ֵ	: _string				�������ַ���	
* ��������	: ������ ������
* �������	: 2009��3��26��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::trim(const std::basic_string<_char>& str, _char trim_char)
{
    size_t bpos = str.find_first_not_of(trim_char);
    size_t epos = str.find_last_not_of(trim_char);

    if(bpos == _string::npos || epos == _string::npos)
    {
        return _string();
    }
    else if(0 == bpos && epos == (str.length() - 1))
    {
        return str;
    }
    else
    {
        return str.substr(bpos, epos - bpos + 1);
    }
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::upper
* ��������	: ���ַ���ȫ��ת��Ϊ��д
* �Ρ�����	: _char* str			��Ҫ������ַ���
* �� �� ֵ	: void
* ��������	: ������ ������
* �������	: 2009��3��6��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
void string_utility_t<_char>::upper(_char* str)
{
    if(NULL == str || '\0' == str[0])
    {
        return;
    }

    for(uint32 i = 0; str[i] != 0; i ++) 
    {
        str[i] = toupper(str[i]);
    }

    return;
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::to_upper
* ��������	: ���ַ���ȫ��ת��Ϊ��д
* �Ρ�����	: const _string& str	��Ҫ������ַ���
* �� �� ֵ	: _string				�������ַ���
* ��������	: ������ ������
* �������	: 2009��3��26��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::to_upper(const std::basic_string<_char>& str)
{
    _string ret = str;

    size_t i = 0, len = ret.size();
    for( i = 0; i < len; i ++) 
    {
        ret[i] = toupper(str[i]); // ret[i] Ч�ʽϵ�
    }

    return ret;
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::lower
* ��������	: ���ַ���ȫ��ת��ΪСд
* �Ρ�����	: _char* str			��Ҫ������ַ���
* �� �� ֵ	: void
* ��������	: ������ ������
* �������	: 2009��3��6��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
void string_utility_t<_char>::lower(_char* str)
{
    if(NULL == str || '\0' == str[0])
    {
        return;
    }

    for(uint32 i = 0; str[i] != 0; i ++) 
    {
        str[i] = tolower(str[i]);
    }	
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::to_lower
* ��������	: ���ַ���ȫ��ת��ΪСд
* �Ρ�����	: _char* str			��Ҫ������ַ���
* �� �� ֵ	: _string				�������ַ���
* ��������	: ������ ������
* �������	: 2009��3��26��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::to_lower(const std::basic_string<_char>& str)
{
    _string ret = str;

    size_t i = 0, len = ret.size();
    for( i = 0; i < len; i ++) 
    {
        ret[i] = tolower(str[i]); // ret[i] Ч�ʽϵ�
    }

    return ret;
}

/*******************************************************************************
* ��������  : string_utility_t<_char>::is_begin_with
* ��������  : �ж��ַ����Ƿ����ָ����ǰ׺
* �Ρ�����  : const _string& fullstr        ��Ҫ�Ƚϵ������ַ���
* �Ρ�����  : const _string& prefix         ��Ҫ�Ƚϵ����ַ���
* �� �� ֵ  : bool						    true��ʾ�ַ���fullstr��ǰ׺Ϊprefix
* ��������  : ������ ������
* �������  : 2009��4��14��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
template<class _char>
bool string_utility_t<_char>::is_begin_with(const std::basic_string<_char>& fullstr, const std::basic_string<_char>& prefix)
{
    return fullstr.size() >= prefix.size() 
        && 0 == fullstr.compare(0, prefix.size(), prefix);
}

/*******************************************************************************
* ��������	: string_utility_t<_char>::ends_with
* ��������	: �ж��ַ���fullstr�ĺ�׺�Ƿ�Ϊsubstr
* �Ρ�����	: const _char* fullstr		��Ҫ�Ƚϵ������ַ���	
* �Ρ�����	: const _char* suffix		��Ҫ�Ƚϵ����ַ���
* �� �� ֵ	: bool						true��ʾ�ַ���fullstr�ĺ�׺Ϊsubstr
* ��������	: ������ ������
* �������	: 2009��3��7��
* �޸�����		   �޸���		  �޸�����
*******************************************************************************/
template<class _char>
bool string_utility_t<_char>::is_end_with(const _string& fullstr, const _string& suffix)
{
    return fullstr.size() >= suffix.size() 
        && 0 == fullstr.compare(fullstr.size() - suffix.size(), suffix.size(), suffix);
}

template<class _char>
std::basic_string<_char> string_utility_t<_char>::replace(const _char* str, const _char* replace_src, const _char* replace_dst, bool nocase )
{
    std::basic_string<_char> ret;   
    
    if ( !str || !str[0] || !replace_src || !replace_dst )
    {
        return ret; // �������󣬷��ؿ��ַ���
    }

    if ( !replace_src[0] ) // Դ�滻�ַ����ǿյģ�Ҳ����˵ʲô�����滻��ԭ������
    {
        return str;
    }
  
    std::basic_string<_char> replace_src_str(replace_src);
    xl::uint32 replace_src_len = (xl::uint32)replace_src_str.size();

    const _char* p = str;
    while ( *p )
    {
        bool match = false;
        if ( nocase )
        {
            match = (0==string_utility_t<_char>::compare_nocase(p, replace_src, replace_src_len));
        }
        else
        {
            match = (std::basic_string<_char>(p,replace_src_len)==replace_src_str);
        }

        if ( match )
        {
            ret += replace_dst;
            p+=replace_src_len;
        }
        else
        {
            ret += *p;
            p++;
        }
    }

    return ret;
}

/*******************************************************************************
* ��������  : string_utility_t<_char>::strnstr
* ��������  : ��ָ�����ַ�����Ѱ�����ַ��������� strstr�������ϸ�ָ�����ȣ��������ַ���ĩβ0��
* �Ρ�����  : const _char * str     ����Ѱ�ҵ�Դ�ַ���
* �Ρ�����  : uint32 str_len        str�ĳ���
* �Ρ�����  : const _char * sub     ��Ѱ�ҵ����ַ���
* �Ρ�����  : uint32 sub_len        sub�ĳ���
* �� �� ֵ  : _char*                ����sub��str���״γ��ֵĵ�ַ�����û���ҵ����򷵻�NULL��
* ��������  : ������
* �������  : 2010��1��6��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
template<class _char>
const _char * string_utility_t<_char>::strnstr(const _char * str, uint32 str_len, const _char * sub, uint32 sub_len )
{
    if ( !str || !sub )
    {
        return NULL;
    }
    const _char* p = (const _char*)str;
    uint32 unread_len = str_len;
    while( unread_len >= sub_len )
    {
        bool equal = true;
        const _char* src = p, *dst = sub;
        for ( uint32 i=0; i<sub_len; i++ )
        {
            if ( *src != *dst )
            {
                equal = false;
                break;
            }
            else
            {
                src++;
                dst++;
            }
        }
        if ( equal )
        {
            return p;
        }
        else
        {
            p++;
            unread_len--;
        }
    }
    return NULL;
}

XL_NAMESPACE_END(text)

#endif // end of __STRING_UTILITY_H_7916A1DE_EA43_4721_B814_AAA697AAE649__
