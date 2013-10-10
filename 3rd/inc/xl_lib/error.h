/*******************************************************************************
* 版权所有 (C)2009 深圳市迅雷网络技术有限公司。
* 系统名称  : 迅雷公共库
* 文件名称  : error.h
* 内容摘要  : 定义错误码类型，读写函数，给全公司各个产品分配错误码段
* 当前版本  : 1.0
* 作    者  : 杨晓虎
* 设计日期  : 2009年3月17日
* 修改记录  : 
* 日    期      版    本        修改人      修改摘要
*******************************************************************************/
/**************************** 条件编译选项和头文件 ****************************/
#ifndef __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__
#define __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__

#include "./type.h"
#include "./tchar.h"

/********************************** 常量和宏 **********************************/

NAMESPACE_BEGIN(xl)

/* 错误码类型定义 */
typedef         uint32              error_code;


/* 迅雷内部错误码范围定义 */
#define         NO_ERR              (0)
#define         ERR_XL_MIN          (20000000)
#define         ERR_XL_MAX          (30000000)

/* 迅雷公共库 */
#define         ERR_XL_LIB_MIN      (ERR_XL_MIN + 100000)

#define         ERR_WRONG_PARA		(ERR_XL_LIB_MIN + 1) // 输入参数出错
#define         ERR_WRONG_FORMAT    (ERR_XL_LIB_MIN + 2) // 格式错误
#define         ERR_NONE_SYMLINK    (ERR_XL_LIB_MIN + 3) // 非符号链接错误
#define         ERR_FILE_INVALID    (ERR_XL_LIB_MIN + 4) // 文件打开失败
#define         ERR_FILE_IO_ERROR   (ERR_XL_LIB_MIN + 5) // 文件读写失败
#define         ERR_INSUFF_BUFFER   (ERR_XL_LIB_MIN + 6) // 传入缓冲区太小
#define         ERR_CHAR_INVALID    (ERR_XL_LIB_MIN + 7) // 非法字符
#define         ERR_LOGIC_ERROR     (ERR_XL_LIB_MIN + 8) // 程序出现逻辑错误
#define         ERR_NO_MEMORY       (ERR_XL_LIB_MIN + 9) // 内存非配失败
#define         ERR_TOO_MANY_TIMER  (ERR_XL_LIB_MIN + 10) // 定时器太多
#define         ERR_INVALID_TIMER_ID (ERR_XL_LIB_MIN + 11) // 无效的定时器ID
#define         ERR_RSA_ERROR       (ERR_XL_LIB_MIN + 12) // 非对称加密算法rsa内部错误
#define         ERR_FUNCTION_CALL   (ERR_XL_LIB_MIN + 13) // 错误的函数调用
#define         ERR_RSA_PUBLIC_KEY  (ERR_XL_LIB_MIN + 14) // 无效的rsa公钥
#define         ERR_AES_KEY         (ERR_XL_LIB_MIN + 15) // 无效的aes key
#define         ERR_PEL_VERSION     (ERR_XL_LIB_MIN + 16) // 无效的PEL协议
#define         ERR_INVALID_RSA     (ERR_XL_LIB_MIN + 17) // rsa没有初始化
#define         ERR_NEED_MORE_DATA  (ERR_XL_LIB_MIN + 18) // 流式解析时需要更多的数据
#define         ERR_INVALID_OBJ     (ERR_XL_LIB_MIN + 19) // 对象指针实效

// 定义"格式化码流编解码组件"中的错误
#define         ERR_PROTOBUF_MIN    (ERR_XL_LIB_MIN + 1000)
#define         ERR_INVALID_VERSION (ERR_PROTOBUF_MIN + 0) // 无效的message版本号
#define         ERR_DUP_VERSION     (ERR_PROTOBUF_MIN + 1) // 重迭的message版本号
#define         ERR_MESSAGE_DEFINE  (ERR_PROTOBUF_MIN + 2) // message的定义出错
#define         ERR_INVALID_FIELD   (ERR_PROTOBUF_MIN + 3) // 无效的message域信息
#define         ERR_NOT_ENOUGH_BUF  (ERR_PROTOBUF_MIN + 4) // 用来解码的缓存长度不够
#define         ERR_STRING_SIZE     (ERR_PROTOBUF_MIN + 5) // 字符串太长
#define         ERR_ARRAY_SIZE      (ERR_PROTOBUF_MIN + 6) // 数组太大了

// 定义"xl_socket"中的错误
#define         ERR_SOCKET_MIN      (ERR_XL_LIB_MIN + 2000)
#define         ERR_WRONG_PACKET    (ERR_SOCKET_MIN + 0) // 包的内容错误
#define         ERR_WRONG_COMMAND   (ERR_SOCKET_MIN + 1) // 错误的通讯命令
#define         ERR_WRONG_STATE     (ERR_SOCKET_MIN + 2) // 错误的网络状态
#define         ERR_SYN             (ERR_SOCKET_MIN + 3) // 网络同步失败
#define         ERR_PERSIST_RETRY   (ERR_SOCKET_MIN + 4) // persist重试的次数太多
#define         ERR_TRANSMIT_RETRY  (ERR_SOCKET_MIN + 5) // 数据包重传的次数太多
#define         ERR_PACEKT_LOST     (ERR_SOCKET_MIN + 6) // 网络丢包严重

/* 迅雷5 */
#define         ERR_XUNLEI5_MIN     (ERR_XL_MIN + 200000)


/* 迅雷5.9 */
#define         ERR_XUNLEI6_MIN     (ERR_XL_MIN + 300000)


/* 网页迅雷 */
#define         ERR_WEB_XUNLEI_MIN  (ERR_XL_MIN + 400000)


/* 迅雷影音 */
#define         ERR_XMP_MIN         (ERR_XL_MIN + 500000)


/* 社区 */
#define         ERR_COMMUNITY_MIN   (ERR_XL_MIN + 600000)


/* 游游 */
#define         ERR_UU_MIN          (ERR_XL_MIN + 700000)


/* TIPS */
#define         ERR_TIPS_MIN        (ERR_XL_MIN + 800000)


/* GougouBar */
#define         ERR_GOUGOUBAR_MIN   (ERR_XL_MIN + 900000)


/* 软件助手 */
#define         ERR_SOFTASSIST_MIN  (ERR_XL_MIN + 1000000)


/* 看看 */
#define         ERR_KANKAN_MIN      (ERR_XL_MIN + 1100000)


/* 会员版迅雷 */
#define         ERR_VIP_XUNLEI_MIN  (ERR_XL_MIN + 1200000)


/* 下载库 */
#define         ERR_DOWNLOADLIB_MIN (ERR_XL_MIN + 1300000)


/* 随身盘 */
#define         ERR_WALKBOX_MIN     (ERR_XL_MIN + 1400000)  // 21400000 - 21499999


/* xl_data */
#define         ERR_XL_DATA_MIN     (ERR_XL_MIN + 5000000)

#define         ERR_INVALID_TYPE    (ERR_XL_DATA_MIN + 1)       // xl_data 的类型非法
#define         ERR_MAP_EMPTY       (ERR_XL_DATA_MIN + 2)       // MAP 为空
#define         ERR_MAP_MISMATCH    (ERR_XL_DATA_MIN + 3)       // MAP 的结构有问题，键在访问序列中，但是不在 MAP 中
#define         ERR_INT_INVALID     (ERR_XL_DATA_MIN + 4)       // 读出的整型值不合法，超出了预期的大小
#define         ERR_IO_FAIL         (ERR_XL_DATA_MIN + 5)       // 读写不到预期的字节数
#define         ERR_DECODE_NOTHING  (ERR_XL_DATA_MIN + 6)       // 二进制解码中发现没有预期的字段
#define         ERR_LIST_INVALID    (ERR_XL_DATA_MIN + 7)       // 二进制解码中发现LIST无法解析预期的元素
#define         ERR_XML_INVALID     (ERR_XL_DATA_MIN + 8)       // XML解码中发现XML格式错误
#define         ERR_XML_NOT_UTF8    (ERR_XL_DATA_MIN + 9)       // XML不是UTF8
#define         ERR_ITEM_NOT_IN_MAP (ERR_XL_DATA_MIN + 10)       // XML中ITEM不在MAP中
#define         ERR_ITEM_NO_KEY     (ERR_XL_DATA_MIN + 11)       // XML中ITEM没有key
#define         ERR_UNKNOWN_ELEMENT (ERR_XL_DATA_MIN + 12)       // XML中出现未知的element
//#define         ERR_WSTR_IN_BEN     (ERR_XL_DATA_MIN + 13)       // bencoding 编码不支持宽字符串
//#define         ERR_UI8_IN_BEN      (ERR_XL_DATA_MIN + 14)       // bencoding 编码不支持 uint8
//#define         ERR_UI16_IN_BEN     (ERR_XL_DATA_MIN + 15)       // bencoding 编码不支持 uint16
//#define         ERR_UI32_IN_BEN     (ERR_XL_DATA_MIN + 16)       // bencoding 编码不支持 uint32
#define         ERR_BEN_INVALID     (ERR_XL_DATA_MIN + 17)       // bencoding 编码格式错误
#define         ERR_ZIP_FAIL        (ERR_XL_DATA_MIN + 18)       // zip 压缩失败
#define         ERR_UNZIP_FAIL      (ERR_XL_DATA_MIN + 19)       // zip 解压缩失败
#define         ERR_HEX_STR_INVALID (ERR_XL_DATA_MIN + 20)       // 非法的十六进制字符串
#define         ERR_INVALID_FORMAT  (ERR_XL_DATA_MIN + 21)       // 非法的格式
#define         ERR_MULTI_ROOT      (ERR_XL_DATA_MIN + 22)       // XML RAW格式编码，出现了多个根元素

/* xl_client */
#define         ERR_XL_CLIENT_MIN       (ERR_XL_MIN + 6000000)  

#define         ERR_CONNECTION_CLOSED   (ERR_XL_CLIENT_MIN + 1)  // 连接被正常关闭

#define         ERR_HTTP_REDIRECT_LOOP  (ERR_XL_CLIENT_MIN + 2)     // HTTP 重复重定向超过5次
#define         ERR_HTTP_INVALID_LOCATION (ERR_XL_CLIENT_MIN + 3)   // HTTP 重复 URL 非法
#define         ERR_HTTP_HEADER_INVALID (ERR_XL_CLIENT_MIN + 4)     // xl_client中的HttpWrapper接收的HTTP Header中不含Content-Length
#define         ERR_UDT_DLL_INVALID     (ERR_XL_CLIENT_MIN + 5)     // udt.dll加载失败
#define         ERR_UNKNOWN_CMD         (ERR_XL_CLIENT_MIN + 6)     // 接收到未知命令
#define         ERR_HTTP_CHUNK_SIZE_ERR (ERR_XL_CLIENT_MIN + 7)     // HTTP chunked body 中的 chunk_size 解析失败
#define         ERR_HTTP_CHUNK_END_ERR  (ERR_XL_CLIENT_MIN + 8)     // HTTP chunked body 中的 chunk 末尾\r\n解析失败
#define         ERR_HTTP_CHUNK_TRAILER_ERR  (ERR_XL_CLIENT_MIN + 9) // HTTP chunked body 中的 chunk trailer 解析失败
#define         ERR_HTTP_SURPLUS        (ERR_XL_CLIENT_MIN + 10)    // HTTP 回复收到了多余的数据

/* xap */
#define         ERR_XAP_MIN         (ERR_XL_MIN + 7000000)

/********************************** 数据类型 **********************************/

/********************************** 函数声明 **********************************/


/*******************************************************************************
* 函数名称  : set_last_error
* 功能描述  : 设置最后一次错误的错误码
* 参　　数  : error_code err 错误码，该错误码保存在线程私有数据中，多线程之间不会互相冲突
* 返 回 值  : void
* 作　　者  : 杨晓虎
* 设计日期  : 2009年3月17日
* 修改日期         修改人         修改内容
*******************************************************************************/
void set_last_error( error_code err );

/*******************************************************************************
* 函数名称  : get_last_error
* 功能描述  : 获取最后一次错误的错误码。
* 返 回 值  : error_code 错误码
* 作　　者  : 杨晓虎
* 设计日期  : 2009年3月17日
* 修改日期         修改人         修改内容
*******************************************************************************/
error_code get_last_error();

/*******************************************************************************
* 函数名称  : get_error_desc
* 功能描述  : 获取指定错误码的描述
* 参　　数  : error_code err 错误码。也可以使用windows系统的错误码。
* 返 回 值  : tstring 描述文本。如果没有找到，则返回 ""。
* 作　　者  : 杨晓虎
* 设计日期  : 2009年3月17日
* 修改日期         修改人         修改内容
*******************************************************************************/
tstring get_error_desc( error_code err );

/*******************************************************************************
* 函数名称  : get_error_desc
* 功能描述  : 获取当前错误码的描述
* 返 回 值  : tstring 描述文本。如果没有找到，则返回 ""。
* 作　　者  : 王卫华
* 设计日期  : 2009年8月20日
* 修改日期         修改人         修改内容
*******************************************************************************/
tstring get_error_desc();

/*********************************** 类定义 ***********************************/

NAMESPACE_END(xl)

#endif // end of __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__
