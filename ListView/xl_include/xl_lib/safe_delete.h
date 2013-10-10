/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : safe_delete.h
* 内容摘要  : 定义安全删除等一系列宏
* 当前版本  : 1.0
* 作    者  : 杨晓虎
* 设计日期  : 2009年3月17日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__
#define __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__

/********************************** 常量和宏 **********************************/

#ifndef SAFE_DELETE
#define SAFE_DELETE(p) \
	__pragma(warning(push))		\
	__pragma(warning(disable:4127))	\
	do { if ( (p) ) { delete (p); (p) = NULL; } } while(0)\
	__pragma(warning(pop))
#endif // SAFE_DELETE

#ifndef SAFE_DELETE_ARRAY
#define SAFE_DELETE_ARRAY(p) \
	__pragma(warning(push))		\
	__pragma(warning(disable:4127))	\
	do { if ( (p) ) { delete [](p); (p) = NULL; } } while(0)\
	__pragma(warning(pop))
#endif // SAFE_DELETE_ARRAY

#ifndef SAFE_RELEASE
#define SAFE_RELEASE(p) \
	__pragma(warning(push))		\
	__pragma(warning(disable:4127))	\
	do { if ( (p) ) { (p)->Release(); (p) = NULL; } } while(0)\
	__pragma(warning(pop))
#endif // SAFE_RELEASE

#ifndef SAFE_CLOSE_HANDLE
#define SAFE_CLOSE_HANDLE(p) \
	__pragma(warning(push))		\
	__pragma(warning(disable:4127))	\
	do { if ( (p) ) { ::CloseHandle(p); (p) = NULL; } } while(0)\
	__pragma(warning(pop))
#endif // SAFE_CLOSE_HANDLE

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/

/*********************************** 类定义 ***********************************/

#endif // end of __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__
