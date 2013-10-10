/*******************************************************************************
* ��Ȩ���� (C)2009,������Ѹ�����缼�����޹�˾��
* ϵͳ����	: Ѹ�׹�����
* �ļ�����	: type.h
* ����ժҪ	: ������ʹ���������͵Ķ���
* ��ǰ�汾	: 1.0
* ��    ��	: ������
* �������	: 2009��3��2��
* �޸ļ�¼	: 
* ��    ��		��    ��		�޸��� 		�޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __TYPE_H_41DF2D3C_69B5_4c78_B927_B55C39F23755__  
#define __TYPE_H_41DF2D3C_69B5_4c78_B927_B55C39F23755__  

/********************************** �����ͺ� **********************************/
// ���������ռ�
#define NAMESPACE_BEGIN(a) namespace a {
#define NAMESPACE_END(a) }

// ����Ѹ�������ռ�
#define XL_NAMESPACE_BEGIN(a) namespace xl { namespace a {
#define XL_NAMESPACE_END(a) } }

// ����Ѹ��Linux�����ռ�
// linux �в�����ʹ�������ռ�linux��ֻ���������ռ�lnx
#define XL_LINUX_NAMESPACE_BEGIN(a) namespace xl { namespace lnx { namespace a {
#define XL_LINUX_NAMESPACE_END(a) } } }

// ����Ѹ��Windows�����ռ�
#define XL_WIN32_NAMESPACE_BEGIN(a) namespace xl { namespace win32 { namespace a {
#define XL_WIN32_NAMESPACE_END(a) } } }

#ifdef __LINUX__

#include <sys/types.h>

NAMESPACE_BEGIN(xl)

#define XL_MAX_PATH_LEN 512

#define SINT8_MAX	127
#define SINT8_MIN	(-128)
#define UINT8_MAX	255

#define SINT16_MAX 32767
#define SINT16_MIN (-32768)
#define UINT16_MAX 65535

#define SINT32_MAX 2147483647
#define SINT32_MIN (-2147483648)
#define UINT32_MAX 4294967295U

#define SINT64_MAX 9223372036854775807LL
#define SINT64_MIN (-9223372036854775808LL)
#define UINT64_MAX 18446744073709551615ULL

/********************************** �������� **********************************/

typedef unsigned char   byte;
typedef unsigned char   uint8;
typedef signed char     sint8;
typedef u_int16_t       uint16;
typedef int16_t         sint16;
typedef u_int32_t       uint32;
typedef int32_t         sint32;
typedef u_int64_t       uint64;
typedef int64_t         sint64;
typedef float           float32;
typedef double          float64;

NAMESPACE_END(xl)

#elif WIN32

#include <limits.h>

NAMESPACE_BEGIN(xl)

typedef unsigned char       byte;
typedef unsigned __int8     uint8;
typedef signed __int8       sint8;
typedef unsigned short      uint16;
typedef signed short        sint16;
typedef unsigned long       uint32;
typedef signed long         sint32;
typedef unsigned __int64    uint64;
typedef signed __int64      sint64;
typedef float               float32;
typedef double              float64;

#define SINT8_MIN           _I8_MIN
#define SINT8_MAX           _I8_MAX
#define UINT8_MAX           _UI8_MAX

#define SINT16_MIN          _I16_MIN
#define SINT16_MAX          _I16_MAX
#define UINT16_MAX          _UI16_MAX

#define SINT32_MIN          _I32_MIN
#define SINT32_MAX          _I32_MAX
#define UINT32_MAX          _UI32_MAX

#define SINT64_MIN          _I64_MIN
#define SINT64_MAX          _I64_MAX
#define UINT64_MAX          _UI64_MAX

//const sint8     SINT8_MIN   =   _I8_MIN;
//const sint8     SINT8_MAX   =   _I8_MAX;
//const uint8     UINT8_MAX   =   _UI8_MAX;
//
//const sint16    SINT16_MIN  =   _I16_MIN;
//const sint16    SINT16_MAX  =   _I16_MAX;
//const uint16    UINT16_MAX  =   _UI16_MAX;
//
//const sint32    SINT32_MIN  =   _I32_MIN;
//const sint32    SINT32_MAX  =   _I32_MAX;
//const uint32    UINT32_MAX  =   _UI32_MAX;
//
//const sint64    SINT64_MIN  =   _I64_MIN;
//const sint64    SINT64_MAX  =   _I64_MAX;
//const uint64    UINT64_MAX  =   _UI64_MAX;

NAMESPACE_END(xl)

#endif // __LINUX__

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

#endif // end of __TYPE_H_41DF2D3C-69B5-4c78-B927-B55C39F23755__  
