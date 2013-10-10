/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : error.h
* ����ժҪ  : ������������ͣ���д��������ȫ��˾������Ʒ����������
* ��ǰ�汾  : 1.0
* ��    ��  : ������
* �������  : 2009��3��17��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__
#define __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__

#include "./type.h"
#include "./tchar.h"

/********************************** �����ͺ� **********************************/

NAMESPACE_BEGIN(xl)

/* ���������Ͷ��� */
typedef         uint32              error_code;


/* Ѹ���ڲ������뷶Χ���� */
#define         NO_ERR              (0)
#define         ERR_XL_MIN          (20000000)
#define         ERR_XL_MAX          (30000000)

/* Ѹ�׹����� */
#define         ERR_XL_LIB_MIN      (ERR_XL_MIN + 100000)

#define         ERR_WRONG_PARA		(ERR_XL_LIB_MIN + 1) // �����������
#define         ERR_WRONG_FORMAT    (ERR_XL_LIB_MIN + 2) // ��ʽ����
#define         ERR_NONE_SYMLINK    (ERR_XL_LIB_MIN + 3) // �Ƿ������Ӵ���
#define         ERR_FILE_INVALID    (ERR_XL_LIB_MIN + 4) // �ļ���ʧ��
#define         ERR_FILE_IO_ERROR   (ERR_XL_LIB_MIN + 5) // �ļ���дʧ��
#define         ERR_INSUFF_BUFFER   (ERR_XL_LIB_MIN + 6) // ���뻺����̫С
#define         ERR_CHAR_INVALID    (ERR_XL_LIB_MIN + 7) // �Ƿ��ַ�
#define         ERR_LOGIC_ERROR     (ERR_XL_LIB_MIN + 8) // ��������߼�����
#define         ERR_NO_MEMORY       (ERR_XL_LIB_MIN + 9) // �ڴ����ʧ��
#define         ERR_TOO_MANY_TIMER  (ERR_XL_LIB_MIN + 10) // ��ʱ��̫��
#define         ERR_INVALID_TIMER_ID (ERR_XL_LIB_MIN + 11) // ��Ч�Ķ�ʱ��ID
#define         ERR_RSA_ERROR       (ERR_XL_LIB_MIN + 12) // �ǶԳƼ����㷨rsa�ڲ�����
#define         ERR_FUNCTION_CALL   (ERR_XL_LIB_MIN + 13) // ����ĺ�������
#define         ERR_RSA_PUBLIC_KEY  (ERR_XL_LIB_MIN + 14) // ��Ч��rsa��Կ
#define         ERR_AES_KEY         (ERR_XL_LIB_MIN + 15) // ��Ч��aes key
#define         ERR_PEL_VERSION     (ERR_XL_LIB_MIN + 16) // ��Ч��PELЭ��
#define         ERR_INVALID_RSA     (ERR_XL_LIB_MIN + 17) // rsaû�г�ʼ��
#define         ERR_NEED_MORE_DATA  (ERR_XL_LIB_MIN + 18) // ��ʽ����ʱ��Ҫ���������
#define         ERR_INVALID_OBJ     (ERR_XL_LIB_MIN + 19) // ����ָ��ʵЧ

// ����"��ʽ��������������"�еĴ���
#define         ERR_PROTOBUF_MIN    (ERR_XL_LIB_MIN + 1000)
#define         ERR_INVALID_VERSION (ERR_PROTOBUF_MIN + 0) // ��Ч��message�汾��
#define         ERR_DUP_VERSION     (ERR_PROTOBUF_MIN + 1) // �ص���message�汾��
#define         ERR_MESSAGE_DEFINE  (ERR_PROTOBUF_MIN + 2) // message�Ķ������
#define         ERR_INVALID_FIELD   (ERR_PROTOBUF_MIN + 3) // ��Ч��message����Ϣ
#define         ERR_NOT_ENOUGH_BUF  (ERR_PROTOBUF_MIN + 4) // ��������Ļ��泤�Ȳ���
#define         ERR_STRING_SIZE     (ERR_PROTOBUF_MIN + 5) // �ַ���̫��
#define         ERR_ARRAY_SIZE      (ERR_PROTOBUF_MIN + 6) // ����̫����

// ����"xl_socket"�еĴ���
#define         ERR_SOCKET_MIN      (ERR_XL_LIB_MIN + 2000)
#define         ERR_WRONG_PACKET    (ERR_SOCKET_MIN + 0) // �������ݴ���
#define         ERR_WRONG_COMMAND   (ERR_SOCKET_MIN + 1) // �����ͨѶ����
#define         ERR_WRONG_STATE     (ERR_SOCKET_MIN + 2) // ���������״̬
#define         ERR_SYN             (ERR_SOCKET_MIN + 3) // ����ͬ��ʧ��
#define         ERR_PERSIST_RETRY   (ERR_SOCKET_MIN + 4) // persist���ԵĴ���̫��
#define         ERR_TRANSMIT_RETRY  (ERR_SOCKET_MIN + 5) // ���ݰ��ش��Ĵ���̫��
#define         ERR_PACEKT_LOST     (ERR_SOCKET_MIN + 6) // ���綪������

/* Ѹ��5 */
#define         ERR_XUNLEI5_MIN     (ERR_XL_MIN + 200000)


/* Ѹ��5.9 */
#define         ERR_XUNLEI6_MIN     (ERR_XL_MIN + 300000)


/* ��ҳѸ�� */
#define         ERR_WEB_XUNLEI_MIN  (ERR_XL_MIN + 400000)


/* Ѹ��Ӱ�� */
#define         ERR_XMP_MIN         (ERR_XL_MIN + 500000)


/* ���� */
#define         ERR_COMMUNITY_MIN   (ERR_XL_MIN + 600000)


/* ���� */
#define         ERR_UU_MIN          (ERR_XL_MIN + 700000)


/* TIPS */
#define         ERR_TIPS_MIN        (ERR_XL_MIN + 800000)


/* GougouBar */
#define         ERR_GOUGOUBAR_MIN   (ERR_XL_MIN + 900000)


/* ������� */
#define         ERR_SOFTASSIST_MIN  (ERR_XL_MIN + 1000000)


/* ���� */
#define         ERR_KANKAN_MIN      (ERR_XL_MIN + 1100000)


/* ��Ա��Ѹ�� */
#define         ERR_VIP_XUNLEI_MIN  (ERR_XL_MIN + 1200000)


/* ���ؿ� */
#define         ERR_DOWNLOADLIB_MIN (ERR_XL_MIN + 1300000)


/* ������ */
#define         ERR_WALKBOX_MIN     (ERR_XL_MIN + 1400000)  // 21400000 - 21499999


/* xl_data */
#define         ERR_XL_DATA_MIN     (ERR_XL_MIN + 5000000)

#define         ERR_INVALID_TYPE    (ERR_XL_DATA_MIN + 1)       // xl_data �����ͷǷ�
#define         ERR_MAP_EMPTY       (ERR_XL_DATA_MIN + 2)       // MAP Ϊ��
#define         ERR_MAP_MISMATCH    (ERR_XL_DATA_MIN + 3)       // MAP �Ľṹ�����⣬���ڷ��������У����ǲ��� MAP ��
#define         ERR_INT_INVALID     (ERR_XL_DATA_MIN + 4)       // ����������ֵ���Ϸ���������Ԥ�ڵĴ�С
#define         ERR_IO_FAIL         (ERR_XL_DATA_MIN + 5)       // ��д����Ԥ�ڵ��ֽ���
#define         ERR_DECODE_NOTHING  (ERR_XL_DATA_MIN + 6)       // �����ƽ����з���û��Ԥ�ڵ��ֶ�
#define         ERR_LIST_INVALID    (ERR_XL_DATA_MIN + 7)       // �����ƽ����з���LIST�޷�����Ԥ�ڵ�Ԫ��
#define         ERR_XML_INVALID     (ERR_XL_DATA_MIN + 8)       // XML�����з���XML��ʽ����
#define         ERR_XML_NOT_UTF8    (ERR_XL_DATA_MIN + 9)       // XML����UTF8
#define         ERR_ITEM_NOT_IN_MAP (ERR_XL_DATA_MIN + 10)       // XML��ITEM����MAP��
#define         ERR_ITEM_NO_KEY     (ERR_XL_DATA_MIN + 11)       // XML��ITEMû��key
#define         ERR_UNKNOWN_ELEMENT (ERR_XL_DATA_MIN + 12)       // XML�г���δ֪��element
//#define         ERR_WSTR_IN_BEN     (ERR_XL_DATA_MIN + 13)       // bencoding ���벻֧�ֿ��ַ���
//#define         ERR_UI8_IN_BEN      (ERR_XL_DATA_MIN + 14)       // bencoding ���벻֧�� uint8
//#define         ERR_UI16_IN_BEN     (ERR_XL_DATA_MIN + 15)       // bencoding ���벻֧�� uint16
//#define         ERR_UI32_IN_BEN     (ERR_XL_DATA_MIN + 16)       // bencoding ���벻֧�� uint32
#define         ERR_BEN_INVALID     (ERR_XL_DATA_MIN + 17)       // bencoding �����ʽ����
#define         ERR_ZIP_FAIL        (ERR_XL_DATA_MIN + 18)       // zip ѹ��ʧ��
#define         ERR_UNZIP_FAIL      (ERR_XL_DATA_MIN + 19)       // zip ��ѹ��ʧ��
#define         ERR_HEX_STR_INVALID (ERR_XL_DATA_MIN + 20)       // �Ƿ���ʮ�������ַ���
#define         ERR_INVALID_FORMAT  (ERR_XL_DATA_MIN + 21)       // �Ƿ��ĸ�ʽ
#define         ERR_MULTI_ROOT      (ERR_XL_DATA_MIN + 22)       // XML RAW��ʽ���룬�����˶����Ԫ��

/* xl_client */
#define         ERR_XL_CLIENT_MIN       (ERR_XL_MIN + 6000000)  

#define         ERR_CONNECTION_CLOSED   (ERR_XL_CLIENT_MIN + 1)  // ���ӱ������ر�

#define         ERR_HTTP_REDIRECT_LOOP  (ERR_XL_CLIENT_MIN + 2)     // HTTP �ظ��ض��򳬹�5��
#define         ERR_HTTP_INVALID_LOCATION (ERR_XL_CLIENT_MIN + 3)   // HTTP �ظ� URL �Ƿ�
#define         ERR_HTTP_HEADER_INVALID (ERR_XL_CLIENT_MIN + 4)     // xl_client�е�HttpWrapper���յ�HTTP Header�в���Content-Length
#define         ERR_UDT_DLL_INVALID     (ERR_XL_CLIENT_MIN + 5)     // udt.dll����ʧ��
#define         ERR_UNKNOWN_CMD         (ERR_XL_CLIENT_MIN + 6)     // ���յ�δ֪����
#define         ERR_HTTP_CHUNK_SIZE_ERR (ERR_XL_CLIENT_MIN + 7)     // HTTP chunked body �е� chunk_size ����ʧ��
#define         ERR_HTTP_CHUNK_END_ERR  (ERR_XL_CLIENT_MIN + 8)     // HTTP chunked body �е� chunk ĩβ\r\n����ʧ��
#define         ERR_HTTP_CHUNK_TRAILER_ERR  (ERR_XL_CLIENT_MIN + 9) // HTTP chunked body �е� chunk trailer ����ʧ��
#define         ERR_HTTP_SURPLUS        (ERR_XL_CLIENT_MIN + 10)    // HTTP �ظ��յ��˶��������

/* xap */
#define         ERR_XAP_MIN         (ERR_XL_MIN + 7000000)

/********************************** �������� **********************************/

/********************************** �������� **********************************/


/*******************************************************************************
* ��������  : set_last_error
* ��������  : �������һ�δ���Ĵ�����
* �Ρ�����  : error_code err �����룬�ô����뱣�����߳�˽�������У����߳�֮�䲻�ụ���ͻ
* �� �� ֵ  : void
* ��������  : ������
* �������  : 2009��3��17��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
void set_last_error( error_code err );

/*******************************************************************************
* ��������  : get_last_error
* ��������  : ��ȡ���һ�δ���Ĵ����롣
* �� �� ֵ  : error_code ������
* ��������  : ������
* �������  : 2009��3��17��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
error_code get_last_error();

/*******************************************************************************
* ��������  : get_error_desc
* ��������  : ��ȡָ�������������
* �Ρ�����  : error_code err �����롣Ҳ����ʹ��windowsϵͳ�Ĵ����롣
* �� �� ֵ  : tstring �����ı������û���ҵ����򷵻� ""��
* ��������  : ������
* �������  : 2009��3��17��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
tstring get_error_desc( error_code err );

/*******************************************************************************
* ��������  : get_error_desc
* ��������  : ��ȡ��ǰ�����������
* �� �� ֵ  : tstring �����ı������û���ҵ����򷵻� ""��
* ��������  : ������
* �������  : 2009��8��20��
* �޸�����         �޸���         �޸�����
*******************************************************************************/
tstring get_error_desc();

/*********************************** �ඨ�� ***********************************/

NAMESPACE_END(xl)

#endif // end of __ERROR_H_985C7C53_0F2D_4543_802C_34CA2DC612C8__
