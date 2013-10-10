/*******************************************************************************
* 版权所有 (C)2009,深圳市迅雷网络技术有限公司。
* 系统名称    : 迅雷公共库
* 文件名称    : string_utility.h
* 内容摘要    : 处理和字符串的有关的操作
* 当前版本    : 1.0
* 作    者    : 王卫华
* 设计日期    : 2009年3月6日
* 修改记录    : 
* 日    期        版    本        修改人         修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __STRING_UTILITY_H_7916A1DE_EA43_4721_B814_AAA697AAE649__  
#define __STRING_UTILITY_H_7916A1DE_EA43_4721_B814_AAA697AAE649__  

#include <string>
#include <vector>

#include "xl_lib/type.h"
#include "xl_lib/tchar.h"

XL_NAMESPACE_BEGIN(text)

/********************************** 常量和宏 **********************************/

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

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
    * 函数名称	: string_utility_t<_char>::split_string
    * 功能描述	: 把源字符串(以delim为分隔符)分割为多个字符串保存在result_list中
    * 参　　数	: const _string& source					需要分割的字符串
    * 参　　数	: const _char* delim					字符串分割符
    * 参　　数	: std::vector<_string>& result_list		保存分割的结果
    * 参　　数	: bool tolerant_empty_string			是否容忍空字符串。如果为true并source中连续出现分隔符，则在result_list中添加空字符串,
                                                        如果为false并source中连续出现分隔符，则不在result_list中添加空字符串
    * 返 回 值	: uint32                                分割结果的数目
    * 作　　者	: 王卫华 杨晓虎
    * 设计日期	: 2009年3月9日
    * 修改日期		   修改人		  修改内容
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
                // 找到连续的分隔符
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
    * 函数名称	: string_utility_t<_char>::merge_string
    * 功能描述	: 把源字符串source_list通过分隔符delim链接成为一个字符串result_string
    * 参　　数	: const std::vector<_string>& source_list	需要链接的字符串，这个vector中可能包括空字符串
    * 参　　数	: const _char* delim						字符串分割符
    * 参　　数	: _string& result_string					保存字符串链接后的结果
    * 参　　数	: bool tolerant_empty_string				是否容忍空字符串。如果为true并source_list中出现空字符串，则在result_string中添加该空字符串对应的分隔符,
                                                            如果为false并source_list中出现空字符串，则在result_string中不添加该空字符串对应的分隔符
    * 返 回 值	: void
    * 作　　者	: 王卫华
    * 设计日期	: 2009年4月1日
    * 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::is_empty_string
* 功能描述	: 判断一个字符串是否为空字符串
* 参　　数	: const _char* str		需要判断的字符串
* 返 回 值	: bool					true表示为空字符串，false表示不是空字符串
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月10日
* 修改日期		   修改人		  修改内容
*******************************************************************************/
template<class _char>
bool string_utility_t<_char>::is_empty_string(const _char* str)
{
    // 没有用strlen(str)来判断是因为strlen()比较耗时
    return (NULL == str || '\0' == str[0]);
}

/*******************************************************************************
* 函数名称  : string_utility_t<_char>::find_nocase
* 功能描述  : 不区分大小写的字符串查找
* 参　　数  : const _char* src      源字符串
* 参　　数  : const _char* sub      在源字符串中查找该字符串
* 返 回 值  : const _char*          若找到则返回找到位置的地址，否则返回NULL
* 作　　者  : 杨晓虎
* 设计日期  : 2009年4月2日
* 修改日期         修改人         修改内容
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
* 函数名称	: string_utility_t<_char>::trim_whitespace
* 功能描述	: 去掉字符串前面的指定字符串
* 参　　数	: _string& str		需要处理的字符串
* 参　　数	: _char trim_char	指定去除字符串
* 返 回 值	: _string			处理后的字符串
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月6日
* 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::trim_right
* 功能描述	: 去掉字符串后面的指定字符串
* 参　　数	: const _string& str	需要处理的字符串
* 参　　数	: _char trim_char		指定去除字符串
* 返 回 值	: _string				处理后的字符串
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月26日
* 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::trim
* 功能描述	: 去掉字符串前后的指定字符串
* 参　　数	: const _string& str	需要处理的字符串
* 参　　数	: _char trim_char		指定去除字符串
* 返 回 值	: _string				处理后的字符串	
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月26日
* 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::upper
* 功能描述	: 把字符串全部转换为大写
* 参　　数	: _char* str			需要处理的字符串
* 返 回 值	: void
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月6日
* 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::to_upper
* 功能描述	: 把字符串全部转换为大写
* 参　　数	: const _string& str	需要处理的字符串
* 返 回 值	: _string				处理后的字符串
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月26日
* 修改日期		   修改人		  修改内容
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::to_upper(const std::basic_string<_char>& str)
{
    _string ret = str;

    size_t i = 0, len = ret.size();
    for( i = 0; i < len; i ++) 
    {
        ret[i] = toupper(str[i]); // ret[i] 效率较低
    }

    return ret;
}

/*******************************************************************************
* 函数名称	: string_utility_t<_char>::lower
* 功能描述	: 把字符串全部转换为小写
* 参　　数	: _char* str			需要处理的字符串
* 返 回 值	: void
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月6日
* 修改日期		   修改人		  修改内容
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
* 函数名称	: string_utility_t<_char>::to_lower
* 功能描述	: 把字符串全部转换为小写
* 参　　数	: _char* str			需要处理的字符串
* 返 回 值	: _string				处理后的字符串
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月26日
* 修改日期		   修改人		  修改内容
*******************************************************************************/
template<class _char>
std::basic_string<_char> string_utility_t<_char>::to_lower(const std::basic_string<_char>& str)
{
    _string ret = str;

    size_t i = 0, len = ret.size();
    for( i = 0; i < len; i ++) 
    {
        ret[i] = tolower(str[i]); // ret[i] 效率较低
    }

    return ret;
}

/*******************************************************************************
* 函数名称  : string_utility_t<_char>::is_begin_with
* 功能描述  : 判断字符串是否包括指定的前缀
* 参　　数  : const _string& fullstr        需要比较的完整字符串
* 参　　数  : const _string& prefix         需要比较的子字符串
* 返 回 值  : bool						    true表示字符串fullstr的前缀为prefix
* 作　　者  : 王卫华 杨晓虎
* 设计日期  : 2009年4月14日
* 修改日期         修改人         修改内容
*******************************************************************************/
template<class _char>
bool string_utility_t<_char>::is_begin_with(const std::basic_string<_char>& fullstr, const std::basic_string<_char>& prefix)
{
    return fullstr.size() >= prefix.size() 
        && 0 == fullstr.compare(0, prefix.size(), prefix);
}

/*******************************************************************************
* 函数名称	: string_utility_t<_char>::ends_with
* 功能描述	: 判断字符串fullstr的后缀是否为substr
* 参　　数	: const _char* fullstr		需要比较的完整字符串	
* 参　　数	: const _char* suffix		需要比较的子字符串
* 返 回 值	: bool						true表示字符串fullstr的后缀为substr
* 作　　者	: 王卫华 杨晓虎
* 设计日期	: 2009年3月7日
* 修改日期		   修改人		  修改内容
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
        return ret; // 参数错误，返回空字符串
    }

    if ( !replace_src[0] ) // 源替换字符串是空的，也就是说什么都不替换，原样返回
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
* 函数名称  : string_utility_t<_char>::strnstr
* 功能描述  : 在指定的字符串中寻找子字符串。类似 strstr，但是严格指定长度，不依赖字符串末尾0。
* 参　　数  : const _char * str     用于寻找的源字符串
* 参　　数  : uint32 str_len        str的长度
* 参　　数  : const _char * sub     被寻找的子字符串
* 参　　数  : uint32 sub_len        sub的长度
* 返 回 值  : _char*                返回sub在str中首次出现的地址。如果没有找到，则返回NULL。
* 作　　者  : 杨晓虎
* 设计日期  : 2010年1月6日
* 修改日期         修改人         修改内容
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
