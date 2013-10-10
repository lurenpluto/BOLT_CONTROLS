/*******************************************************************************
* ��Ȩ���� (C)2009 ������Ѹ�����缼�����޹�˾��
* ϵͳ����  : Ѹ�׹�����
* �ļ�����  : safe_delete.h
* ����ժҪ  : ���尲ȫɾ����һϵ�к�
* ��ǰ�汾  : 1.0
* ��    ��  : ������
* �������  : 2009��3��17��
* �޸ļ�¼  : 
* ��    ��      ��    ��        �޸���      �޸�ժҪ
*******************************************************************************/
/**************************** ��������ѡ���ͷ�ļ� ****************************/
#ifndef __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__
#define __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__

/********************************** �����ͺ� **********************************/

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

/********************************** �������� **********************************/

/********************************** �������� **********************************/

/*********************************** �ඨ�� ***********************************/

#endif // end of __SAFE_DELETE_H_08DB7FE7_97A7_46F2_BE72_531E3E704E9F__
