/**
* @file XdjaKeyApi.h
* @brief ��ȫ��ͨ�ýӿ�
* @author xdja
* @version 1.0.0.1
* @date 20130608
*/

#ifndef _XDJA_KEY_API_H_
#define _XDJA_KEY_API_H_

#ifdef WIN32
    #ifndef XDJAKEYAPI
        #define XDJAKEYAPI __declspec(dllimport)
    #endif
#else
    #define XDJAKEYAPI
#endif
typedef void* XKF_HANDLE;

/************************************************************************/
/* ������붨��                                                          */
/************************************************************************/
#define XKR_BASE                         0//0x0003A000
#define XKR_OK                           0x00000000                     //�ɹ�
#define XKR_PWD_N                        XKR_BASE+N                     //�������,ʣ��N���Ի���
#define XKR_NO_HANDLE                    XKR_BASE-1                     //ָ���ľ��������
#define XKR_IO_FAILED                    XKR_BASE-2                     //ͨ�����ӿ��շ�����ʧ��
#define XKR_BACK_LENGTH                  XKR_BASE-3                     //��������֮���ȴ���
#define XKR_BACK_DATA                    XKR_BASE-4                     //�������ݴ���
#define XKR_RESET_FAILED                 XKR_BASE-5                     //������ʧ��
#define XKR_NO_ROLE                      XKR_BASE-6                     //ָ���Ľ�ɫ������
#define XKR_DATAIN_SIZE                  XKR_BASE-7                     //�������ݵĳ��Ȳ�����
#define XKR_OUTBUF_SIZE                  XKR_BASE-8                     //ָ�������ݽ��ջ�������С������
#define XKR_INVALID_PARA                 XKR_BASE-9                     //�ӿڲ�������
#define XKR_PASSWORD                     XKR_BASE-10                    //�������,ʣ�����Դ���Ϊ0
#define XKR_EEPROM_WRITE                 XKR_BASE-11                    //EEPROMд�����
#define XKR_PARAMETER                    XKR_BASE-12                    //COSָ���������
#define XKR_CMD_NOTMATCH_LINE            XKR_BASE-13                    //��������·��������Ӧ
#define XKR_CMD_NOTMATCH_FAT             XKR_BASE-14                    //�������ļ��ṹ������
#define XKR_NO_POWER                     XKR_BASE-15                    //Ȩ�޲���
#define XKR_KEY_LOCKED                   XKR_BASE-16                    //��Կ������
#define XKR_DATA_PARAMETER               XKR_BASE-18                    //�������������
#define XKR_APP_LOCKED                   XKR_BASE-19                    //Ӧ������
#define XKR_FILE_NOT_EXIST               XKR_BASE-20                    //�ļ�������
#define XKR_NO_FILE_SPACE                XKR_BASE-21                    //�ļ����㹻�ռ�
#define XKR_NOT_GET_RANDOM               XKR_BASE-22                    //δȡ�����
#define XKR_FILE_EXIST                   XKR_BASE-23                    //�ļ��Ѵ���
#define XKR_FILE_CONTENT                 XKR_BASE-24                    //�ļ����ݴ���
#define XKR_WRONG_STATE                  XKR_BASE-25                    //�����״̬
#define XKR_CARD_LOCKED                  XKR_BASE-26                    //������
#define XKR_WRONG_LE                     XKR_BASE-27                    //Le����
#define XKR_NO_THIS_CMD                  XKR_BASE-28                    //�������
#define XKR_INVALID_DATA                 XKR_BASE-29                    //������Ч
#define XKR_WRONG_MAC                    XKR_BASE-30                    //MAC����
#define XKR_KEYFILE_NOT_EXIST            XKR_BASE-31                    //��Կ�ļ�������
#define XKR_KEY_NOT_EXIST                XKR_BASE-32                    //��Կ������
#define XKR_WRONG_KEY_TYPE               XKR_BASE-33                    //��Կ���Ͳ���
#define XKR_BAD_PUBKEY                   XKR_BASE-34                    //���ع�Կ���ݸ�ʽ����
#define XKR_HASH_FAILED                  XKR_BASE-35                    //HASH����ʧ��
#define XKR_RSAPUBLIC_FAILED             XKR_BASE-36                    //RSA��Կ����ʧ��
#define XKR_BAD_PRIKEY                   XKR_BASE-37                    //����˽Կ���ݸ�ʽ����
#define XKR_SIGN_CONFIRM                 XKR_BASE-38                    //�ȴ��û�ǩ��ȷ��
#define XKR_SIGN_CANCEL                  XKR_BASE-39                    //�û�ǩ��ȷ��ȡ��
#define XKR_CONDITION                    XKR_BASE-40                    //ʹ������������
#define XKR_DECRYPT_FAIL                 XKR_BASE-41                    //����ʧ��
#define XKR_NOT_FIND_DATA                XKR_BASE-42                    //�ļ�ƫ�Ƶ�ַ��������δ�ҵ�����
#define XKR_DGI_NOT_SUPPORT              XKR_BASE-43                    //DGI��֧��
#define XKR_DATA_NOCORRENT               XKR_BASE-44                    //��ȫ�������ݶ�����ȷ
#define XKR_EXAUTH_FAIL                  XKR_BASE-45                    //�ⲿ��֤ʧ��
#define XKR_RSA_NOT_FIND                 XKR_BASE-46                    //RSA��Կδ�ҵ�
#define XKR_TLOCK_FAILD	                 XKR_BASE-47                    //����������ʧ��
#define XKR_TLOCK_TIMEOUT                XKR_BASE-48                    //��������ʱ
#define XKR_BAD_CERT                     XKR_BASE-49                    //֤�����ݴ���
#define XKR_SIGN_VERIFY                  XKR_BASE-50                    //ǩ����֤ʧ��
#define XKR_GETMOUNTPATH_FAILD           XKR_BASE-51                    //��ȡ�̷�/����·��ʧ��
#define XKR_MALLOC_FALID                 XKR_BASE-95                    //�ڴ�����ʧ��
#define XKR_BUFFERISNULL                 XKR_BASE-96                    //�ڴ�Ϊ��
#define XKR_NO_KEY                       XKR_BASE-97                    //δ���밲ȫ��
#define XKR_NOT_SUPPORT                  XKR_BASE-98                    //�ݲ�֧��
#define XKR_NOT_ACTIVATED                XKR_BASE-99                    //��δ����,���ȼ����������ʹ��
#define XKR_UNKNOWN                      XKR_BASE-100                   //δ֪����
#define XKR_FP_QUERYWAITE                XKR_BASE-101                   //δ��ѯ��ָ��״̬����ȴ�
#define XKR_FP_CONDITION_NOTMET          XKR_BASE-102                   //ָ��KEYʹ������������
#define XKR_FP_NOT_MATCH                 XKR_BASE-103					//ָ����֤��ƥ��
#define XKR_FP_RECV_CANCEL               XKR_BASE-104					//�յ�ȡ������
#define XKR_FP_INVALID                   XKR_BASE-105					//��⵽��ָ��
#define XKR_FP_VALID                     XKR_BASE-106                   //��⵽��Чָ��
#define XKR_FP_WAITE_ENROLL              XKR_BASE-107					//�ȴ�ָ��¼��
#define XKR_FP_ENROLLING                 XKR_BASE-108                   //��ǰ���ڽ���ָ��¼�����������ִ������ָ��跢��ȡ��ָ��
#define XKR_FP_VERIFYING                 XKR_BASE-109					//��ǰ���ڽ���ָ����֤����������ִ������ָ��跢��ȡ��ָ��
#define XKR_FP_NOROOM					 XKR_BASE-110					//ָ�ƴ洢���ռ䲻��
#define XKR_FP_NOSTORE					 XKR_BASE-111					//�豸��������Чָ��
#define XKR_FP_CHECKFAILED				 XKR_BASE-112					//δ��⵽ָ�ƣ����м�״̬����Ҫ���·���¼��/��֤
/************************************************************************/
/* ���ͽṹ����                                                          */
/************************************************************************/

///��ȫ������(��֪)
typedef enum _CARD_TYPE
{
    CT_ALL				= 0x0000,
    CT_USBKEY			= 0x0100,   //USBKEY	              0100
    CT_USBDEV			= 0x0110,   //��������USB�豸
    CT_NET				= 0x0120,   //Win32 NET�豸,����ActiveX����USBKEY��
    //CT_USB_AISINO		=0x0130,    //AisionоƬ��USBKEY
    CT_USB_CCORE		= 0x0140,   //��ооƬ�޴洢USBKEY
    //CT_USB_CCORE_V2	=0X0150��   //��ооƬ���洢USBKEY
    CT_USBCD			= 0x0160,   //��ооƬ�޴洢USBKEY CDROM
    CT_USBKEY30			= 0x0170,   //��ооƬ���洢USBKEY
    CT_USBCCID			= 0x0180,	//USBKEY CCID����
    CT_TF				= 0x0200,   //TF
    CT_TF_XDJA		    = 0x0210,   //XDJATF��
    //CT_TF_XDJA_V1		=0x0211,    //XDJA���ļ���
    //CT_TF_XDJA_V2		=0x0212,    //XDJA���ļ���
    CT_XDJA_CHIP		= 0x0213,   //Android SD�ӿ�оƬ
    //CT_TF_XDJA_CUSTOM	=0x0214,    //XDJA�Զ����ļ���
    CT_ACE				= 0x0215,   //Win32   ACE�ֻ�
    CT_XDJA_SPI4		= 0x0216,   //����SPI�ӿ�оƬ
    CT_XDJA_SPI			= 0x0217,   //Android SPI�ӿ�оƬ
    CT_XDJA_SPI6		= 0x0218,   //����SPI�ӿ�оƬ
    CT_XDJA_UART		= 0x0219,   //UART�ӿ�оƬ
    CT_XDJA_I2C			= 0x021A,   //IIC�ӿ�оƬ
    //CT_TF_INCOMM		=0x0220,    //INCOMM��
    //CT_TF_ZTEIC_OLD	=0x0221,    //INCOMM���ٿ�1.0  0221
    //CT_TF_ZTEIC_NEW	=0x0222,    //INCOMM���ٿ�2.0  0222
    //CT_TF_INCOMM_V1	=0x0223,    //INCOMM���ļ����߹���  0223
    //CT_TF_INCOMM_V2	=0x0224,    //INCOMM���ļ����͹���  0224
    //CT_TF_INCOMM_EX	=0x0225,    //INCOMM���ļ���        0225
    //CT_TF_RDFOX		=0x0230,    //REDFOX��            0230
    //CT_TF_REDFOX_LOW	=0x0231,    //REDFOX���ٿ�     0231
    //CT_TF_REDFOX_HIGH	=0x0232,    //REDFOX���ٿ�     0232
    //CT_TIC			=0x0300,    //˫����IC��            0300
    //CT_NET			=0x0400,    //                    0400
    CT_IOS				= 0x0500,   //                    0500
    CT_TMC				= 0x0600,   //̫˼��Ĥ��              0600
    CT_TMC_XDJA			= 0x0601,	//XDJA��Ĥ��
    CT_BLE				= 0x0700,   //����KEY             0700
    CT_VHSM				= 0x0800,	//VHSMģ��V1�汾	0800
    CT_VHSMNET			= 0x0810,	//VHSMģ��V2�汾
    CT_TPARTY			= 0x0900,	//��������			0900
    CT_TEESPI			= 0x0A00,	//���TEE armƽ̨ģ��	0a00
} CARD_TYPE;
#define  CT_TF_XDJA_CHIP CT_XDJA_CHIP
#define  CT_TF_XDJA_SPI  CT_XDJA_SPI

///�豸��Ϣ
typedef struct _XDJA_DEVINFO
{
    unsigned char cardid[33];          //Ӳ�����,һ��Ϊ����32�ֽڵ��ַ���
    unsigned char cosver[65];          //COS�汾��,������64�ֽڵ��ַ���
    CARD_TYPE cardtype;                //������
    int  reserve;					   //������չ
} XDJA_DEVINFO, *PXDJA_DEVINFO;
#ifndef SKF_DEVINFO
    typedef XDJA_DEVINFO DEVINFO, *PDEVINFO;
#endif
///�豸��Ϣ��չ
typedef struct _DEVINFOEX
{
    unsigned char cardid[64];          //Ӳ�����,һ��Ϊ����32�ֽڵ��ַ���
    unsigned char mcosver[256];        //��COS�汾��,����Ϊ��
    unsigned char cosver[256];         //��COS�汾��
    CARD_TYPE cardtype;                //������
} DEVINFOEX, *PDEVINFOEX;
//������Ч���ȷ�Χ
#define PIN_MAX_LEN  16 //������󳤶�
#define PIN_MIN_LEN  3  //������С����
#define FILE_ID_LEN  2  //�ļ�ID����
#define KEY_LEN_MAX  32 //��Կֵ��󳤶�
#define DIR_NAME_LEN 8 //Ŀ¼��������ַ���
///Ŀ¼����
enum DIR_TYPE
{
    ROOT_DIR = 1, //��Ŀ¼
    APP_DIR = 2 //Ӧ��Ŀ¼
};
///Ŀ¼�ṹ
typedef struct _XDJA_DIR
{
    unsigned char       id[FILE_ID_LEN];           //Ŀ¼ID    Ӧ��Ŀ¼ʱ��Ч
    unsigned char       type;                      //��Ŀ¼��Ӧ��Ŀ¼
    unsigned short      room;                      //�ռ��С ��Ӧ��Ŀ¼ʱ��Ч�����16K
    unsigned char       create_Acl;                //����Ȩ�ޣ���Ŀ¼�´����ļ���Ȩ��
    unsigned char       delete_Acl;                //ɾ��Ȩ�ޣ���Ŀ¼��ɾ���ļ���Ȩ��
    unsigned char       key_Acl;                   //��ӶԳ���Կ������������Կ���Ȩ��
    unsigned char       name[DIR_NAME_LEN];        //Ŀ¼����
} XDJA_DIR, *PXDJA_DIR;
///�ļ�����
enum FILE_TYPE
{

    FILE_BINARY = 1,  //�������ļ�
    FILE_PUBLIC = 2,  //��Կ�ļ�
    FILE_PRIVATE = 3,  //˽Կ�ļ�
    FILE_CONTAINER = 4, //�������ļ�����
    FILE_BINARY_SAFE = 11 //����·�����Ķ������ļ�
};
///�ļ��ṹ
typedef struct _XDJA_FILE
{
    unsigned char       id[FILE_ID_LEN];    //�ļ�ID
    unsigned char       type;               //�ļ�����
    unsigned short      room;               //�ռ��С  �ļ�����Ϊ�������ļ�ʱ��Ч
    unsigned char       read_Acl;           //��ȡȨ��  ��rsa˽Կ�ļ� ��ֵ��Ч������˽Կ�������ȡ
    unsigned char       write_Acl;          //д��Ȩ��
    unsigned char       use_Acl;            //ʹ��Ȩ�� ��Ϊ��˽Կ�ļ�ʱ��Ч
} XDJA_FILE, *PXDJA_FILE;
///�����ļ��ṹ
typedef struct _XDJA_CONTAINER_FILE
{
    unsigned char       id[FILE_ID_LEN];    //�ļ�ID
    unsigned char       type;               //room type,0 bytes, 1 sector
    unsigned short      room;               //�ռ��С
    unsigned char       read_Acl;           //��ȡȨ��
    unsigned char       write_Acl;          //д��Ȩ��
    unsigned short      single_size;        //�����ļ���С
} XDJA_CONTAINER_FILE, *PXDJA_CONTAINER_FILE;
///SM1��Կ�ṹ
typedef struct  _XDJAKEY_ATTR
{
    unsigned char  id;                      //��Կ ID
    unsigned char  type;                    //��Կ���� sm1������Կ sm1������Կ ����������Կ
    unsigned char  use_Acl ;                //ʹ��Ȩ�� sm1������Կ sm1������Կʱ��Ч
    unsigned char  update_Acl;              //����Ȩ��
    unsigned char  key[KEY_LEN_MAX];        //��Կֵ ��Ч��Կ���ȸ�����Կ���;��� sm1Ϊ16�ֽڣ�����������Կ��Ч����Ϊ  PIN_MIN_LEN<=len<=PIN_MAX_LEN
    unsigned char  new_state;               //����״̬,����

    //��������������Ϊ����������Կʱ��Ч
    unsigned char  try_num;                 //���Դ���
    unsigned char  unlock_role;             //������Կ���Խ�����role
    unsigned char  len;                     //��Կ����  ��Ч����ͬ�����
} XDJAKEY_ATTR, *PXDJAKEY_ATTR;
///��Կ����
#define KEY_SM1_ENCRYPT         0x01 //SM1������Կ
#define KEY_SM1_DECRYPT	        0x02 //SM1������Կ
#define KEY_PIN_UNLOCK          0x03 //�������� 
#define KEY_PIN_ROLE            0x04 //��ɫ���� 
#define KEY_SM1_RELOAD          0x05 //SM1������װ��Կ 
#define KEY_DES_RELOAD          0x06 //3DES������װ��Կ
#define KEY_3DES_EAHTU          0x07 //3DES�ⲿ��֤��Կ
#define KEY_SM4_EAUTH           0x08 //SM4�ⲿ��֤��Կ
#define KEY_SM4_SAFE            0x09 //SM4��·������Կ
#define KEY_SM4_ENCRYPT         0x0A //SM4������Կ
#define KEY_SM4_DECRYPT         0x0B //SM4������Կ
#define KEY_3DES_ENCRYPT        0x0C //3DES������Կ
#define KEY_3DES_DECRYPT        0x0D //3DES������Կ
#define KEY_3DES24_ENCRYPT		0x0E //3DES24�ӽ�����Կ
#define KEY_AES16_ENCRYPT	    0x0F //AES16�ӽ�����Կ
#define KEY_AES24_ENCRYPT       0x10 //AES24�ӽ�����Կ    
#define KEY_AES32_ENCRYPT       0x11 //AES32�ӽ�����Կ


///�Գ��㷨�������� ���� ����
#define OP_DECRYPT  0x00
#define OP_ENCRYPT  0x01
///�Գ��㷨����ģʽ  ECB  CBC
#define ECB_MODE    0x00
#define CBC_MODE    0x10
///�Գ��㷨ģʽ���ͱ�ʶ
#define ECB_DECRYPT 0x00
#define ECB_ENCRYPT 0x01
#define CBC_DECRYPT 0x10
#define CBC_ENCRYPT 0x11
#define CFB_DECRYPT 0x20
#define CFB_ENCRYPT 0x21
#define CTR_DECRYPT 0x30
#define CTR_ENCRYPT 0x31
//�����Ӵ��㷨��ʶ
#define XDD_SHA1	0
#define XDD_SHA256	1
#define XDD_SM3		2
#define XDD_SHA384	3
#define XDD_SHA512	4
#define XDD_MD5		5

//��ʱ��Կ�㷨��ʶ
typedef enum _XDJA_TMP_ALG
{
    TMP_ALG_SM1 = 0,
    TMP_ALG_DES = 1,
    TMP_ALG_3DES = 2,
    TMP_ALG_SM4 = 3,
    TMP_ALG_AES16 = 4,
    TMP_ALG_AES24 = 5,
    TMP_ALG_AES32 = 6
} TMP_ALG;
///����RSA����ĳ���
#define CARD_RSA_LEN            128
#define CARD_PRIME_LEN          64
#define MAX_RSA_MODULUS_BITS    2048
#define MAX_CARD_RSA_LEN        256
#define MIN_CARD_PRIME_LEN      128
///RSA��Կ�ṹ
typedef struct _XDJA_RSA_PUB_KEY
{
    unsigned int  bits;							//��Կģ�����ȣ�1024��2048
    unsigned char m[MAX_CARD_RSA_LEN];			//����256�ֽڣ����㿿ǰ�洢
    unsigned int  e;							//����ȡֵ65537
} XDJA_RSA_PUB_KEY, *PXDJA_RSA_PUB_KEY;
///RSA˽Կ�ṹ
typedef struct _XDJA_RSA_PRI_KEY
{
    unsigned int bits;							//��Կģ������1024����2048
    unsigned char p[MIN_CARD_PRIME_LEN];		//����128�ֽڣ����㿿ǰ�洢
    unsigned char q[MIN_CARD_PRIME_LEN];		//����128�ֽڣ����㿿ǰ�洢
    unsigned char dp[MIN_CARD_PRIME_LEN];		//����128�ֽڣ����㿿ǰ�洢
    unsigned char dq[MIN_CARD_PRIME_LEN];		//����128�ֽڣ����㿿ǰ�洢
    unsigned char ce[MIN_CARD_PRIME_LEN];		//����128�ֽڣ����㿿ǰ�洢
} XDJA_RSA_PRI_KEY, *PXDJA_RSA_PRI_KEY;
#define KEY_LEN_SM2       32
///SM2���߲���
typedef struct _XDJA_SM2_PARAM
{
    unsigned char p[KEY_LEN_SM2];    //����p
    unsigned char a[KEY_LEN_SM2];    //ϵ��a
    unsigned char b[KEY_LEN_SM2];    //ϵ��b
    unsigned char n[KEY_LEN_SM2];    //��
    unsigned char x[KEY_LEN_SM2];    //����G��x����
    unsigned char y[KEY_LEN_SM2];    //����G��y����
} XDJA_SM2_PARAM, *PXDJA_SM2_PARAM, *PXDJA_ECC_PARAM;
///sm2˽Կ�ṹ
typedef struct _XDJA_SM2_PRIKEY
{
    unsigned char d[KEY_LEN_SM2];	//˽Կd 32�ֽ�
} XDJA_SM2_PRIKEY, *PXDJA_SM2_PRIKEY, *PXDJA_ECC_PRIKEY;
///sm2��Կ�ṹ
typedef struct _XDJA_SM2_PUBKEY
{
    unsigned char x[KEY_LEN_SM2];	//��Կx 32�ֽ�
    unsigned char y[KEY_LEN_SM2];	//��Կy 32�ֽ�
} XDJA_SM2_PUBKEY, *PXDJA_SM2_PUBKEY, *PXDJA_ECC_PUBKEY;

//ÿ�ֽ�ɫ��Ӧһ��Ȩ��,��ɫͨ����֤������,������Ϊ��ɫ����Ȩ��
//#define ROLE_NUM         5 //Ȩ������
#define ROLE_A           1     //Ȩ��1
#define ROLE_B           2
#define ROLE_C           3
#define ROLE_D           4     //Ȩ��4
#define ROLE_E           5     //Ȩ��5
#define ROLE_Q           0x11  //Ȩ��4

#define SM2_KEY_GENERATE_DICT_SEND 0   //SM2Э����Կ����
#define SM2_KEY_GENERATE_DICT_RECV 1   //SM2Э����Կ��Ӧ��
#define SM2_UID_MAX     64             //ǩ��ʱ�û�ID����󳤶�
#define SM2_BLOCK_MAX   158            //SM2����ʱ���ĵ���󳤶�

//ǩ����������
typedef enum
{
    SIGN_HASH = 0,	//ǩ�������Ѿ���ժҪ���㣬SM2�㷨ʱ����ʾԤ������eֵ
    SIGN_NOHASH = 1	//ǩ������δ����ժҪ����
} SIGN_DATA_TYPE;
///USB����
typedef enum
{
    USB_NORMAL_ZONE,  //��ͨ��
    USB_SECU_ZONE,    //������
    USB_HEDD_ZONE,    //��������
    USB_INNOSTOR_ZONE //�����̷���
} USB_FLASH_TYPE;
///USB FLASH��дģʽ
typedef enum
{
    USB_READ_TEMP,			//��ʱֻ��
    USB_WRITE_TEMP,			//��ʱ��д
    USB_READ_FOREVER,		//����ֻ��
    USB_WRITE_FORERVER,		//���ÿ�д
    INNOSTOR_WRITE_TEMP		//��������ʱ��д
} USB_FLASH_RW_MODE;

///FFCB�ļ����ƿ���Ϣ
typedef struct _XDJA_FFCB
{
    int free_ffcb;  //ȫ�ֿ�FFCB����
    int free_dfcb;  //ȫ�ֿ�DFCB����
    int cur_dfcb;   //��ǰĿ¼DFCB����
    int cur_ffcb;   //��ǰĿ¼FFCB����
} XDJA_FFCB, *PXDJA_FFCB;

///ed25519˽Կ�ṹ
typedef struct _XDJA_ED25519_PRIKEY{
	unsigned int bits;
	unsigned char priv[32];    //˽Կ32�ֽ�
}XDJA_ED25519_PRIKEY, *PXDJA_ED25519_PRIKEY;
///ed25519��Կ�ṹ
typedef struct _XDJA_ED25519_PUBKEY{
	unsigned int bits;
	unsigned char pub[32];    //��Կ32�ֽ�
}XDJA_ED25519_PUBKEY, *PXDJA_ED25519_PUBKEY;


/// SPIоƬ������Ϣ
typedef struct _SPI_CONFIG
{
	int XDJA_INT0_GPIO;		// 3276 INT1���ţ�3275INT4����
	int XDJA_INT1_GPIO;		// 3276 INT4���ţ�3275INT5����
	int XDJA_POR_GPIO;		// POR��λ���š���ѡ����ʹ�ñ���-1��
	int XDJA_POWER_GPIO;	// GPIO�������š���ѡ����ʹ�ñ���-1��
	int XDJA_QWK_GPIO;		// �͹��Ļ������š���ѡ����ʹ�ñ���-1��
	int SPI_SPEED;			// SPIƵ������,Ĭ��20/MHz
}XDJA_SPI_CONFIG, *PXDJA_SPI_CONFIG;

#ifdef __cplusplus
extern "C" {
#endif

/**
* @brief ��ȡ����汾
*
* @param[out] version   ����汾
* @param[out] verLen ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetVersion(unsigned char * version, int * verLen);

/**
* @brief ��ȡ�����������ʱ��
*
* @param[out] datatime ��������ʱ��,��ʽdata=mm:dd:yyyy,time=hh:mm:ss
* @param[out] len   ���س���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetDateTime(unsigned char * datatime, int * len);

/************************************************************************/
/* �豸������ӿ�                                                       */
/************************************************************************/

/**
* @brief ö���豸
*
* @param[in]  devType  ö�ٵ��豸���ͣ���Enum CARD_TYPE����
* @param[out] devNum   ö�ٵ����豸������XKF_OpenDev������0��ʼ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_EnumDev(int devType, int * DevNum);
/**
* @brief ͨ���豸�������豸�������豸���
* ˵������Ҫ��ö���豸
*
* @param[in]   index   �豸����,��0��ʼ,������ö�ٵ����豸��
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDev(int index, XKF_HANDLE * hHandle);

/**
* @brief ��ָ���豸,�����豸���
* ˵�����Ŵ�ݰ�USBCCID�豸ר�ã�����Ҫö���豸��
*
* @param[in]   handle window SmartCard API���صĲ������ľ��
* @param[out]  hHandle �豸���
*/
XDJAKEYAPI int XKF_OpenDevByHandle(XKF_HANDLE handle, XKF_HANDLE * hHandle);

/**
* @brief ��ָ���豸,�����豸���
*  ˵��������ö���豸
*
* @param[in]   devName TF������·��,Լ����'/'����,�� /mnt/sdcard/, j:/
                       USB�豸����,�� /dev/sdd  //./PHYSICALDRIVE4
					   SPI�豸�ڵ�,�� /dev/spidev1.0
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDevByName(const unsigned char * devName, XKF_HANDLE * hHandle);
/**
* @brief ��ָ���豸,�����豸���(��֧��ACE�豸)
*  ˵������Ҫö���豸
*
* @param[in]   sn ACE�豸���к�
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDevBySN(const char* sn, XKF_HANDLE * hHandle);
/**
* @brief ����Ӧ�ó���İ���,�����豸���(ֻ����Android4.4����)
*  ˵��������ö���豸
*
* @param[in]   packagePath ����Ӧ�ó���İ�����ͨ��getPackageName()��ȡ
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDevByNameEx(const char* packagePath, XKF_HANDLE * hHandle);
/**
* @brief �ر��豸
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CloseDev(XKF_HANDLE hHandle);
/**
* @brief  ����豸��ռʹ��Ȩ��������������
* ��ʱʱ��20��
* Ӧ�ó����ں�����ϻ��������ǰͨ���ýӿڻ�ȡ�豸��ռʹ��Ȩ����������������ͷŶ�ռȨ
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_LockDev(XKF_HANDLE hHandle);
/**
* @brief  �ͷ��豸��ռʹ��Ȩ��������������
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_UnlockDev(XKF_HANDLE hHandle);
/**
* @brief �豸�����
*
* @param[in]  hHandle �豸���
* @param[in]  pCmd    �豸���APDUָ�
* @param[in]  cmdLen  �����
* @param[out] outBuf  ���ؽ������
* @param[out] outlen  �����ʾ������ݻ����С�������ʾ�������ʵ�ʳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_Transmit(XKF_HANDLE hHandle, unsigned char * pCmd, int cmdLen, unsigned char* outBuf, unsigned int * outlen);
/**
* @brief �豸�����
* ˵�� �������ݺ�״̬�֣���ʽ������ || ״̬�֣�2�ֽڣ�
*
* @param[in]  hHandle �豸���
* @param[in]  pCmd    �豸���APDUָ�
* @param[in]  cmdLen  �����
* @param[out] outBuf  ���ذ���״̬��Ľ������
* @param[out] outlen  ��ʾ�������ʵ�ʳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_TransmitEx(XKF_HANDLE hHandle, unsigned char * pCmd, int cmdLen, unsigned char* outBuf, unsigned int * outlen);
/**
* @brief ��ȡ�豸��Ϣ��������ID��COS�汾�������͵�
*
* @param[in] hHandle �豸���
* @param[out] pDevInfo �����豸��Ϣ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetDevInfo(XKF_HANDLE hHandle, PXDJA_DEVINFO pDevInfo);
/**
* @brief ��ȡ�豸��Ϣ��չ
*
* @param[in] hHandle �豸���
* @param[out] pDevInfo �����豸��Ϣ��չ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetDevInfoEx(XKF_HANDLE hHandle, PDEVINFOEX pDevInfoEx);
/**
* @brief ��ȡ�豸ID
*
* @param[in] hHandle �豸���
* @param[out] pDevId �°�оƬID
* @param[out] idLen  ID����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetDevId(XKF_HANDLE hHandle, char* pDevId, int* idLen);
/**
* @brief ���ÿ�������־����·��
*
* @param[in] logPath ��־����·��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetLogPath(const char* logPath);
/**
* @brief ���ÿ�������־��С
*
* @param[in] logFileSize ��־�ļ���С.��λ�ֽڣ�Ĭ��2M
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetLogSize(const unsigned int logFileSize);
/**
* @brief ����Socket�豸
*
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_EnableSocket();
/*
* @brief ����оƬ�豸
*
* @param[in] hHandle �豸���
* @param[in] param   ��������
* @param[in] len     �������ӳ���(һ��Ϊ256�ֽ�)
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ActivateCard(XKF_HANDLE hHandle, unsigned char* param, unsigned int len);
/**
* @brief ��ȡоƬ����״̬
*
* @param[in] hHandle �豸���
*
* @retval XKR_OK              �Ѿ�����
* @retval XKR_NOT_ACTIVATED   δ����
*/
XDJAKEYAPI int XKF_GetActivateState(XKF_HANDLE hHandle);
/**
* @brief ����оƬCOSָ���Ƿ񷵻�MAC
*
* @param[in] hHandle �豸���
* @param[in] mode    0, ������MAC; 1,����MAC
*
* @return  ������
*/
XDJAKEYAPI int XKF_SetMacCheck(XKF_HANDLE hHandle, int mode);

/************************************************************************/
/*���ʿ�����ӿ�                                                         */
/************************************************************************/

/**
* @brief �޸�PIN
*  ˵�����޸�PIN�ɹ����Ѿ��е�ǰPINȨ�ޣ�����Ҫ����У��PIN
*
* @param[in] hHandle �豸���
* @param[in] pinRole PIN���ɫ
* @param[in] oldpin  ��PIN��
* @param[in] oldlen  ��PIN�볤��
* @param[in] newpin  ��PIN��
* @param[in] newlen  ��PIN�볤��
*
* @return ������
* @retval XKR_OK          �ɹ�
* @retval XKR_PWD_N       ����,ʣ�����Դ���
* @retval XKR_PASSWORD    �������,ʣ�����Դ���0
* @retval XKR_KEY_LOCKED  ��Կ������
*/
XDJAKEYAPI int XKF_ChangePIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* oldpin, int oldlen, const unsigned char* newpin, int newlen);
/**
* @brief ��ȡPIN��ʣ�����Դ���
*
* @param[in] hHandle �豸���
* @param[in] pinRole PIN���ɫ
*
* @return ���Դ����������
* @retval XKR_PWD_N       ����,ʣ�����Դ���
* @retval XKR_PASSWORD    ʣ�����Դ���0����������
*/
XDJAKEYAPI int XKF_GetPinTryCount(XKF_HANDLE hHandle, int pinRole);
/**
* @brief У��PIN
*  ���ڿ�����֤�Ի��ĳ�ְ�ȫ״̬
*
* @param[in] hHandle �豸���
* @param[in] pinRole PIN���ɫ
* @param[in] pin     PIN��
* @param[in] pinlen  PIN�볤��
*
* @return ������
* @retval XKR_OK          �ɹ�
* @retval XKR_PWD_N       ����,ʣ�����Դ���
* @retval XKR_PASSWORD    �������,ʣ�����Դ���0
* @retval XKR_KEY_LOCKED  ��Կ������
*/
XDJAKEYAPI int XKF_VerifyPIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* pin, int pinlen);
/**
* @brief ����PIN
*	˵����������Կֻ�ܽ����ض���ɫPIN�룬�ڳ�ʼ��ʱָ����
*
* @param[in] hHandle �豸���
* @param[in] id      ������ԿID
* @param[in] key     ������
* @param[in] keylen  �����볤��
* @param[in] newpin  ��PIN��
* @param[in] newlen  ��PIN�볤��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_UnlockPIN(XKF_HANDLE hHandle, int id, const unsigned char* key, int keylen, const unsigned char* newpin, int newlen);
/**
* @brief ��װPIN
*	˵������װ��Կ������װָ����ɫPIN�롣
* @param[in] hHandle �豸���
* @param[in] pinRole PIN���ɫ
* @param[in] key     PIN����װ��
* @param[in] keylen  ��װ�볤��
* @param[in] newpin  ��PIN��
* @param[in] newlen  ��PIN�볤��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReloadPIN(XKF_HANDLE hHandle, int pinRole, const unsigned char* key, int keylen, const unsigned char* newpin, int newlen);
/**
* @brief �����ã������ȫ״̬
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CardReset(XKF_HANDLE hHandle);
/**
* @brief �ⲿ��֤����֤ͨ�����ȡ��Կ��Ӧ��Ȩ��
*  ���̣�����ȡ����������ⲿSM1���ܣ��ٽ��������뿨�����ⲿ��֤�����ܲ��Ƚϣ�
*  Ҫ���ⲿSM1������Կ�Ϳ����ⲿ��֤��Կ��ͬ
*
* @param[in] hHandle     �豸���
* @param[in] exterAuthID �ⲿ��֤��ԿID
* @param[in] encRandom   16�ֽڵ���������ģ����ⲿSM1����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ExternalAuth(XKF_HANDLE hHandle, unsigned char exterAuthID, const unsigned char *encRandom);
/**
* @brief �ڲ���֤����ͬ��SM1���ܣ�
*  ���̣� ������������, �����뿨�����ڲ���֤����, �����ķ���; ���ɿ�����ܲ��Ƚ�
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �ⲿ��������
* @param[in]  dataLen  �ⲿ�������ݳ���(16��������)
* @param[in]  flag     ָʾ�ӽ���ģʽ,ECB_DECRYPT��ECB_ENCRYPT��CBC_DECRYPT��CBC_ENCRYPT��
* @param[in]  kID      ��Կ��ʶID(����0��SM1������Կ��SM1������Կ���ڲ���֤��Կ�������)
*                      ��KIDΪ0ʱ, ��ʾ��ʱ��Կ���ڲ���֤���㣻��kID��Ϊ��ʱ, ��ʾ��ʹ�õ���Կʶ�ţ���Կ����SM1������Կ��SM1������Կ���ڲ���֤��Կ��
* @param[in]  tmpKey   ��ʱ��Կ   ��kID=0ʱ,tmpKey��Ч
* @param[out] pDataOut SM1������
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_InternalAuth(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char kID, const unsigned char *tmpKey, unsigned char *pDataOut, unsigned char *pIV);

/************************************************************************/
/*�ļ�������ӿ�                                                         */
/************************************************************************/

/**
* @brief ����Ŀ¼
* ����:����Ӧ��Ŀ¼ʱ�����е�ǰĿ¼�£�����Ŀ¼��Ȩ��
* ������Ŀ¼ʱ����ǰ���ļ�ϵͳ����Ϊ�ա�
*
* @param[in] hHandle �豸���
* @param[in] pDir    Ŀ¼���Խṹ����XDJA_DIR
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CreateDir(XKF_HANDLE hHandle, PXDJA_DIR pDir);
/**
* @brief ��ȡ��ǰĿ¼ʣ������
*
* @param[in]  hHandle �豸���
* @param[out] size    ʣ������,��λ�ֽ�Byte
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetDirSize(XKF_HANDLE hHandle, unsigned int * size);
/**
* @brief ��ȡ��ǰĿ¼ID
*
* @param[in]  hHandle �豸���
* @param[out] fid     ��ǰĿ¼ID
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetCurDirID(XKF_HANDLE hHandle, unsigned char * fid);
/**
* @brief ��ȡоƬ�ļ�ϵͳFFCB(�ļ����ƿ���Ϣ��
*
* @param[in]  hHandle �豸���
* @param[out] ffcb    FFCB
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetFFCB(XKF_HANDLE hHandle, PXDJA_FFCB ffcb);
/**
* @brief �����ļ�
* ����:���е�ǰĿ¼�£������ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] pFile   �ļ����Խṹ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CreateFile(XKF_HANDLE hHandle, PXDJA_FILE pFile);
/**
* @brief ͨ��IDѡ���ļ���Ŀ¼
* ���ļ���ʶ��ѡ��ѡ��ǰĿ¼�»����ļ�����Ŀ¼�ļ���
* ���κ�����¾���ͨ����ʶ��3F00ѡ��MF
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ���Ŀ¼id
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SelectFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief ͨ��Ŀ¼��ѡ��Ŀ¼
* ��Ŀ¼����ѡ��ѡ��MF����ǰĿ¼������Ŀ¼���¼���Ŀ¼��
*
* @param[in] hHandle �豸���
* @param[in] name    Ŀ¼��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SelectApp(XKF_HANDLE hHandle, const unsigned char * name);

/**
* @brief ɾ���ļ�
*	˵������ҪȨ��
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID��ȫ0��ʾɾ��Ŀ¼�������ļ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DeleteFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief ȡ�ļ�����
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[out] pFile  �ļ����ԣ����ļ����ͺ��ļ���С��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetFileInfo(XKF_HANDLE hHandle, const unsigned char* fid, PXDJA_FILE pFile);
/**
* @brief ���ļ�
* ���������ж����ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] readPos ��ʼλ��
* @param[in] readLen Ҫ��ȡ�ĳ���
* @param[out] pDataout ��ȡ���ݻ�����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadFile(XKF_HANDLE hHandle, const unsigned char* fid, int readPos, int readLen, unsigned char * pDataout);
/**
* @brief ������·������Կ�İ�ȫ���ļ�
* ���������ж����ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] safekey ��Կ����֧��SM4�㷨��
* @param[in] fid     �ļ�ID
* @param[in] readPos ��ʼλ��
* @param[in] readLen Ҫ��ȡ�ĳ���
* @param[out] pDataout ��ȡ���ݻ�����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadFileSafe(XKF_HANDLE hHandle, const unsigned char* safekey, const unsigned char* fid, int readPos, int readLen, unsigned char * pDataout);
/**
* @brief д�ļ�
* ����������д���ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] writePos ��ʼλ��
* @param[in] writeLen д�����ݵĳ���
* @param[out] pDatain д������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteFile(XKF_HANDLE hHandle, const unsigned char* fid, int writePos, int writeLen, const unsigned char * pDatain);
/**
* @brief ������·������Կ�İ�ȫд�ļ�
* ����������д���ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] safekey ��Կ����֧��SM4�㷨��
* @param[in] fid     �ļ�ID
* @param[in] writePos ��ʼλ��
* @param[in] writeLen д�����ݵĳ���
* @param[out] pDatain д������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteFileSafe(XKF_HANDLE hHandle, const unsigned char* safekey, const unsigned char* fid, int writePos, int writeLen, const unsigned char * pDatain);
/**
* @brief ����ļ�����
* ����������д���ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_EmptyFile(XKF_HANDLE hHandle, const unsigned char* fid);
/**
* @brief ��RSA��Կ
* ���������ж�RSA��Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[out] pPub    RSA��Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadRsaPubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PUB_KEY pPub);
/**
* @brief дRSA��Կ
* ����������дRSA��Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] pPub    RSA��Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteRsaPubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PUB_KEY pPub);
/**
* @brief дRSA˽Կ
* ����������дRSA˽Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] pPri    RSA˽Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteRsaPriKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_RSA_PRI_KEY pPri);
/**
* @brief ��sm2��Կ
* ���������ж�sm2��Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[out] pPub    sm2��Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadSm2PubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PUBKEY pPub);
/**
* @brief дsm2��Կ
* ����������дsm2��Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] pPub    sm2��Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteSm2PubKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PUBKEY pPub);
/**
* @brief дsm2˽Կ
* ����������дsm2˽Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] fid     �ļ�ID
* @param[in] pPri    sm2˽Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteSm2PriKey(XKF_HANDLE hHandle, const unsigned char * fid, PXDJA_SM2_PRIKEY pPri);
/**
* @brief ��֤��
* ���������ж�֤���Ȩ��
*
* @param[in] hHandle   �豸���
* @param[in] fid       ֤���ļ�ID
* @param[out] certBuf  ֤����Ϣ
* @param[out] certLen  ֤����Ϣ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadCert(XKF_HANDLE hHandle, const unsigned char * fid, unsigned char *certBuf, int* certLen);
/**
* @brief д֤��
* ����������д֤���Ȩ��
*
* @param[in] hHandle   �豸���
* @param[in] fid       ֤���ļ�ID
* @param[in] certBuf   ֤����Ϣ(DER����)
* @param[in] certLen   ֤����Ϣ����
*
* @return ������
* @retval XKR_OK              �ɹ�
* @retval XKR_NO_POWER        Ȩ�޲���
* @retval XKR_FILE_NOT_EXIST  �ļ�������
*/
XDJAKEYAPI int XKF_WriteCert(XKF_HANDLE hHandle, const unsigned char * fid, const unsigned char *certBuf, int certLen);

/************************************************************************/
/*���������ӿ�                                                         */
/************************************************************************/

/**
* @brief ���ڲ��������
*
* @param[in] hHandle �豸���
* @param[in] len     ��Ҫ��ȡ�����������
* @param[out] Random ����������������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GenRandom(XKF_HANDLE hHandle, unsigned int len, unsigned char* pRandom);
/**
* @brief �����Գ���Կ
* ����:���е�ǰĿ¼�£�������Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] pAttr   �Գ���Կ���Խṹ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CreateKey(XKF_HANDLE hHandle, PXDJAKEY_ATTR pKey);
/**
* @brief ������Կ
* ���������и��¸���Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] type    ���뷽ʽ(4bit) �� ������Կ����(4bit)�����汾֧�����ĵ��롣
* @param[in] pDataIn ��Կ���ݡ���Կ��������Կ�����Զ��������ڱ��汾�У�SM1��ԿΪ16�ֽ�
* @param[in] kID     ��ԿID
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ImportKey(XKF_HANDLE hHandle, unsigned int type, const unsigned char * pDatain, unsigned char kID);
/**
* @brief ɾ����Կ
* ����������ɾ������Կ��Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] kID     ��ԿID
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DeleteKey(XKF_HANDLE hHandle, unsigned char kID);
/**
* @brief ��ȡ��Կ����
*
* @param[in] hHandle �豸���
* @param[in] kID     ��ԿID
* @param[out] type	 ��Կ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetKeyType(XKF_HANDLE hHandle, unsigned char kID, unsigned char* type);
/**
* @brief 3DES�ӽ��ܣ�Ӳ�㷨����ʹ�ÿ��ڶԳ���Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �����������
* @param[in]  dataLen  �������ݳ���
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut 3DES������
* @param[in]  kID      ��ԿID
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DES3(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief 3DES 24�ӽ��ܣ�Ӳ�㷨����ʹ�ÿ��ڶԳ���Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �����������
* @param[in]  dataLen  �������ݳ���
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��00��ʾECB���ܣ�02��ʾCBC���ܣ�03��ʾECB���ܣ�04��ʾCBC����
* @param[out] pDataOut 3DES������
* @param[in]  kID      ��ԿID
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_TDES24(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief SM1�ӽ������㣨Ӳ�㷨����ʹ�ÿ�����Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �����������
* @param[in]  dataLen  �������ݳ���
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut SM1������
* @param[in]  kID      ��ԿID
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief SM4�ӽ������㣨Ӳ�㷨����ʹ�ÿ�����Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �����������
* @param[in]  dataLen  �������ݳ���
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut SM1������
* @param[in]  kID      ��ԿID
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM4(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);
/**
* @brief ������ʱSM1��Կ
*
* @param[in] hHandle �豸���
* @param[in] tmpkey  SM1��Կ 16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ImportTmpKey(XKF_HANDLE hHandle, const unsigned char *tmpkey);
/**
* @brief ������ʱ�Գ���Կ
*
* @param[in] hHandle �豸���
* @param[in] tmpkey  ��Կ des 8�ֽ�,����16�ֽ�
* @param[in] alg     ��ʱ��Կ�㷨: 0 sm1 ,1 des, 2 3des , 3 sm4
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ImportCipherKey(XKF_HANDLE hHandle, const unsigned char *tmpkey, TMP_ALG alg);
/**
* @brief SM1�ӽ��ܣ�Ӳ�㷨����ʹ����ʱSM1��Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  ����������ݡ�
* @param[in]  dataLen  �������ݳ��ȡ�
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut SM1��������
* @param[in]  pIV      ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_TmpSM1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief �ԳƼӽ��ܣ�Ӳ�㷨����ʹ����ʱ�Գ���Կ ���㷨�ɵ�����Կʱȷ����
*	˵����ʹ�ÿ�����ʱ�Գ���Կ���㣬��Ҫ�ڵ�����ʱ��Կ����ԿЭ��֮�������ŷ����ݵȲ���֮��ʹ�á�
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  ����������ݡ�
* @param[in]  dataLen  �������ݳ��ȡ�
* @param[in]  alg      ��ʱ��Կ�㷨: 0 sm1 ,1 des, 2 3des , 3 sm4
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut ��������
* @param[in]  pIV      ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_TmpCipher(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, TMP_ALG alg, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief �ԳƼӽ��ܣ�Ӳ�㷨����ʹ����ʱ�Գ���Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  tmpkey   ��Կ des 8�ֽ�,����16�ֽ�
* @param[in]  pDataIn  ����������ݡ�
* @param[in]  dataLen  �������ݳ��ȡ�
* @param[in]  alg      ��ʱ��Կ�㷨����TMP_ALG
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut ��������
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CipherKey(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, TMP_ALG alg, int flag, unsigned char *pDataOut, unsigned char* pIV);
/**
* @brief SM1�ӽ��ܣ�Ӳ�㷨��������������Կ
*
* @param[in] hHandle  �豸���
* @param[in] tmpkey   SM1��Կ 16�ֽ�
* @param[in] pDataIn  �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen  �������ݳ��ȡ�
* @param[in] flag     ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut SM1��������
* @param[in] pIV      ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM1KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief SSF33�ӽ��ܣ�Ӳ�㷨��������������Կ (���鳤��16)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SSF33(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief ����SM4�ӽ��ܣ����㷨��������������Կ (���鳤��16)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��֧��ECB��CBC��CFB��OFB��CTRģʽ
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;����ģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM4KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief ����SM4�ӽ��ܣ����㷨��������������Կ (���鳤��16)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ��� [��λbit]
* @param[in] flag       ָʾ���ܡ�����������ģʽ��֧��ECB��CBC��CFB��OFB��CTRģʽ
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;����ģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM4KEYBits(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief ����SM4�ӽ��ܣ�Ӳ�㷨��������������Կ (���鳤��16)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM4KEYEx(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief SM6�ӽ��ܣ�Ӳ�㷨��������������Կ (���鳤��16)
*��SCB2��
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��32�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �����
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM6KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief DES�ӽ��ܣ����㷨��������������Կ (���鳤��8)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��8�ֽ�
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ8������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������8�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DESKEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief 3DES�ӽ��ܣ����㷨��������������Կ (���鳤��8)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽڻ�24�ֽ�
* @param[in] keylen     ��Կ���� ��16 24��
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ8������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������8�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DES3KEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, int keylen, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);

/**
* @brief AES�ӽ��ܣ����㷨��������������Կ (���鳤��16)
*
* @param[in] hHandle    �豸���
* @param[in] tmpkey     ��Կ��16�ֽڡ�24�ֽڻ�32�ֽ� ��128λ��192λ��256λ��
* @param[in] keylen     ��Կ���� ��16 24 32��
* @param[in] pDataIn    �������ݣ����ݳ���Ϊ16������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����������ģʽ��
* @param[out] pDataOut  �������
* @param[in] pIV        ����ECBģʽ�˲�����Ч������ΪNULL;CBCģʽʱΪ��ʼ������16�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_AESKEY(XKF_HANDLE hHandle, const unsigned char *tmpkey, int keylen, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char *pIV);
/**
* @brief AES�ӽ��ܣ�Ӳ�㷨����ʹ�ÿ��ڶԳ���Կ
*
* @param[in]  hHandle  �豸���
* @param[in]  pDataIn  �����������
* @param[in]  dataLen  �������ݳ���
* @param[in]  flag     ָʾ���ܡ�����������ģʽ��00��ʾECB���ܣ�02��ʾCBC���ܣ�03��ʾECB���ܣ�04��ʾCBC����
* @param[out] pDataOut AES������
* @param[in]  kID      ��ԿID
* @param[in,out]  pIV  ����iv���iv ��CBCʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_AES(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, int flag, unsigned char *pDataOut, unsigned char kID, unsigned char* pIV);

/**
* @brief SM4 CCMģʽ������������Կ
*
* @param[in] hHandle    �豸���
* @param[in] pDataIn    ��������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����ģʽ��OP_DECRYPT  0x00 OP_ENCRYPT  0x01
* @param[out] pDataOut  �������
* @param[in] tmpkey     ��Կ��16�ֽ�
* @param[in] keylen     ��Կ����16
* @param[in] pIV        ��ʼ������nonce������15-L���൱��GB�淶�еĿ�ʼ����S
* @param[in] Add		CCMģʽ�ĸ�����Ϣ����λ���ֽڣ�С��65536��
* @param[in] Addlen     CCM�и�����Ϣ�ĳ���
* @param[in/out] Tag    CCMģʽ����ֵ֤ flag=OP_ENCRYPT ��ʾ��� flag=OP_DECRYPT ��ʾ����
* @param[in] M			tag�ĳ��ȣ��Ϸ���ֵΪ��4, 6, 8, 10, 12, 14 ��16��openssl��ȱʡ��Ϊ12���൱��GB�淶�е�t
* @param[in] L			������ȡֵΪ2~8��openssl��ȱʡ��Ϊ8 ���൱��GB�淶�е�w
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM4CCM( XKF_HANDLE hHandle, unsigned char *pDataIn,int dataLen,int flag,unsigned char *pDataOut,unsigned char* tmpkey,int keyLen,unsigned char *pIV,unsigned char *Add, int Addlen,unsigned char* Tag,int M, int L);

/**
* @brief AES CCMģʽ������������Կ 
*
* @param[in] hHandle    �豸���
* @param[in] pDataIn    ��������
* @param[in] dataLen    �������ݳ���
* @param[in] flag       ָʾ���ܡ�����ģʽ��OP_DECRYPT  0x00 OP_ENCRYPT  0x01
* @param[out] pDataOut  �������
* @param[in] tmpkey     ��Կ��16�ֽڡ�24�ֽڻ�32�ֽ� ��128λ��192λ��256λ��
* @param[in] keylen     ��Կ���� ��16 24 32��
* @param[in] pIV        ��ʼ������nonce������15-L
* @param[in] Add		CCMģʽ�ĸ�����Ϣ
* @param[in] Addlen     CCM�и�����Ϣ�ĳ���
* @param[in/out] Tag    CCMģʽ����ֵ֤ flag=OP_ENCRYPT ��ʾ��� flag=OP_DECRYPT ��ʾ����
* @param[in] M			tag�ĳ��ȣ��Ϸ���ֵΪ��4, 6, 8, 10, 12, 14 ��16��
* @param[in] L			������ȡֵΪ2~8
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_AESCCM(XKF_HANDLE hHandle, unsigned char *pDataIn,unsigned long long dataLen,int flag,unsigned char *pDataOut,unsigned char* tmpkey,int keyLen,unsigned char *pIV,unsigned char *Add, unsigned long long Addlen,unsigned char* Tag,unsigned char M, unsigned char L);

/**
* @brief ���ڲ���RSA��Կ��
* ��������Կ�Բ�����ʱҪ����дָ����˽Կ�ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] bits    RSA��Կģ�����ȣ�1024��2048
* @param[in] pubfid  ��Կ�ļ�ID��Ϊ0x00 0x00ʱ��ʾ��Կ��������
* @param[in] prifid  ˽Կ�ļ�ID����˽Կ�ļ�ID��Ϊ0x00 0x00ʱ˽Կ�ɵ�������
* @param[in] pPub    RSA��Կ�ṹ����Կ�ļ�IDΪ0x00 0x00ʱ��Ч
* @param[in] pPri    RSA˽Կ�ṹ����˽Կ�ļ�ID��Ϊ0x00 0x00ʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GenRSAKeyPair(XKF_HANDLE hHandle, int bits, const unsigned char * pubfid, const unsigned char* prifid, PXDJA_RSA_PUB_KEY pPub, PXDJA_RSA_PRI_KEY pPri);
/**
* @brief SHA1����(���㷨)
*
* @param[in] hHandle  �豸���
* @param[in] pDataIn  ��������
* @param[in] dataLen    �������ݳ���
* @param[out]  pDataOut ��������� 20���ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SHA1(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SHA1����(Ӳ�㷨)
*
* @param[in] hHandle  �豸���
* @param[in] pDataIn  ��������
* @param[in] dataLen    �������ݳ���
* @param[out]  pDataOut ��������� 20���ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SHA1Ex(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SHA256����(Ӳ�㷨)
*
* @param[in] hHandle  �豸���
* @param[in] pDataIn  ��������
* @param[in] dataLen    �������ݳ���
* @param[out]  pDataOut ��������� 32���ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SHA256Ex(XKF_HANDLE hHandle, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut);
/**
* @brief SM3����(���㷨)
*
* @param[in] hHandle   �豸���
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[out] pDataOut ��������� 32�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM3(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, unsigned char *pDataOut);
/**
* @brief SM3���㣨Ӳ�㷨��
*
* @param[in] hHandle   �豸���
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[out] pDataOut ��������� 32�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM3Ex(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, unsigned char *pDataOut);

/**
* @brief Э�����
*
* @param[in] hHandle	�豸���
* @param[in] pucMsg		�������ݣ��Ѿ�ƴװ�õ�Э������
* @param[in] msgLen		�������ݳ���
* @param[out] pucDataOut ���������
* @param[out] puiOutLen ���������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ProtocolAcceleration(XKF_HANDLE hHandle, unsigned char* pucMsg, int msgLen, unsigned char* pucDataOut, unsigned int* puiOutLen);
/**
* @brief ��Կ��������
*
* @param[in] hHandle   �豸���
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[in] keylen    Ҫ��õ���Կ����
* @param[out] key	   ��������Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_KDF(XKF_HANDLE hHandle, const unsigned char *pDatain, int dataLen, int keylen, unsigned char *key);

/**
* @brief ժҪ���㣨һ�����㣩
*
* @param[in] hHandle   �豸���
* @param[in] alg	   �㷨����
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[out] pDataOut ���������
* @param[out] outlen   ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_Digest( XKF_HANDLE hHandle, int alg, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief ժҪ�����ʼ��
*
* @param[in] hHandle   �豸���
* @param[out] hd	   ժҪ�����ʼ������������豸�����
* @param[in] alg	   �㷨����,�������Ӵ��㷨��ʶ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DigestInit(XKF_HANDLE hHandle, void** hd, int alg);
/**
* @brief ժҪ����������
*	˵������Ҫ�ȵ���ժҪ�����ʼ��
*
* @param[in] hHandle   �豸���
* @param[in] hd		   ժҪ������
* @param[in] alg	   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DigestUpdate(XKF_HANDLE hHandle, void* hd, int alg, unsigned char *pDataIn, int dataLen);
/**
* @brief ժҪ����������
*	˵������Ҫ���ٵ���һ��ժҪ����������
*
* @param[in] hHandle   �豸���
* @param[in] hd		   ժҪ������
* @param[in] alg	   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] pDataOut  ���������
* @param[in] outlen    ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DigestFinal(XKF_HANDLE hHandle, void* hd, int alg, unsigned char *pDataOut, int *outlen);
/**
* @brief HMACժҪ���㣨һ�����㣩
*
* @param[in] hHandle   �豸���
* @param[in] hmacalg   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] key	   ��Կ
* @param[in] keylen    ��Կ����
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[out] pDataOut ���������
* @param[out] outlen   ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_HmacDigest( XKF_HANDLE hHandle, int hmacalg, const unsigned char *key, int keylen, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief HMACժҪ���㣨ָ����Կid��
*
* @param[in] hHandle   �豸���
* @param[in] hmacalg   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] keyid     ��Կid
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
* @param[out] pDataOut ���������
* @param[out] outlen   ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_HmacDigestByID( XKF_HANDLE hHandle, int hmacalg, int keyid, const unsigned char *pDataIn, int dataLen, unsigned char *pDataOut, int *outlen);
/**
* @brief HMACժҪ�����ʼ��
*
* @param[in] hHandle   �豸���
* @param[out] hd	   ժҪ�����ʼ������������豸�����
* @param[in] hmacalg   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] key	   ��Կ
* @param[in] keylen    ��Կ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_HmacDigestInit(XKF_HANDLE hHandle, void** hd, int hmacalg, const unsigned char *key, int keylen);
/**
* @brief HMACժҪ����������
*
* @param[in] hHandle   �豸���
* @param[in] hd		   ժҪ������
* @param[in] hmacalg   �㷨����,�������Ӵ��㷨��ʶ
* @param[in] pDataIn   ��������
* @param[in] dataLen   �������ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_HmacDigestUpdate(XKF_HANDLE hHandle, void* hd, int hmacalg, unsigned char *pDataIn, int dataLen);
/**
* @brief HMACժҪ����������
*	˵������Ҫ���ٵ���һ��ժҪ����������
*
* @param[in] hHandle   �豸���
* @param[in] hd		   ժҪ������
* @param[in] hmacalg   �㷨����,�������Ӵ��㷨��ʶ
* @param[out] pDataOut  ���������
* @param[out] outlen    ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_HmacDigestFinal(XKF_HANDLE hHandle, void* hd, int hmacalg, unsigned char *pDataOut, int *outlen);

/**
* @brief RSA��Կ���� ��RSAǩ����֤��
* �����������������ɵ����߽���
*
* @param[in]  hHandle   �豸���
* @param[in]  fid       RSA��Կ�ļ�ID,Ϊ0x00 0x00ʱʹ���ⲿ��Կ
* @param[in]  pPub      RSA��Կ�ṹ����Կ�ļ�IDΪ0x00 0x00ʱ��Ч
* @param[in]  pDataIn   ��������
* @param[in]  dlen      �������ݳ��ȣ�RSA1024Ϊ128��RSA2048Ϊ256
* @param[out] pDataOut  �������
* @param[out] outLen    ���������ȣ�128��256
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_RSAPubKeyCalc(XKF_HANDLE hHandle, const unsigned char *fid, PXDJA_RSA_PUB_KEY pPub, const unsigned char *pDataIn, int dlen, unsigned char * pDataOut, unsigned int *outLen);
/**
* @brief RSA˽Կ���� ��RSAǩ����
* ���������ɵ����߽�����䡣
*
* @param[in] hHandle  �豸���
* @param[in] fid       ˽ԿID
* @param[in] pDataIn   ��������
* @param[in] dlen      �������ݳ��ȣ�RSA1024Ϊ128��RSA2048Ϊ256
* @param[out] pDataOut �������
* @param[out] outLen   ���������ȣ�128��256
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_RSAPriKeyCalc(XKF_HANDLE hHandle, const unsigned char *fid, const unsigned char *pDataIn, int dlen, unsigned char* pDataOut, unsigned int *outLen);
/**
* @brief RSA˽Կ���� ��RSAǩ����
* ���������ɵ����߽�����䡣
*
* @param[in] hHandle   �豸���
* @param[in] pin	   pin��
* @param[in] pinlen	   pin����
* @param[in] pinrole   pin��ɫ
* @param[in] fid       ˽ԿID
* @param[in] pDataIn   ��������
* @param[in] dlen      �������ݳ��ȣ�RSA1024Ϊ128��RSA2048Ϊ256(�ݲ�֧��)
* @param[out] pDataOut �������
* @param[out] outLen   ���������ȣ�128��256
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_RSAPriKeyCalcEx(XKF_HANDLE hHandle, unsigned char* pin, int pinlen, int pinrole, const unsigned char *fid, const unsigned char *pDataIn, int dlen, unsigned char* pDataOut,
                                   unsigned int *outLen);
/**
* @brief RSA����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] bits            RSA��Կģ�� RSA1024Ϊ1024��RSA2048Ϊ2048��RSA1152Ϊ1152
* @param[in] prikeyid        ˽ԿID
* @param[in] datatype        �������ͣ���SIGN_DATA_TYPE
* @param[in] pDatain         ��������
* @param[in] dlen            �������ݳ��ȣ�datatype=SIGN_HASHʱ��ժҪ���ݳ��ȱ���Ϊ20��
* @param[out] signData       ���ǩ������
* @param[out] outlen         ������ݳ��� 128��256
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_RSASign(XKF_HANDLE hHandle, int bits, const unsigned char *prikeyid, int datatype, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);
/**
* @brief RSA����ǩ����֤
*
* @param[in] hHandle         �豸���
* @param[in] bits            RSA��Կģ��
* @param[in] pubkeyid        ��ԿID
* @param[in] rsaPubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] datatype        �������ͣ���SIGN_DATA_TYPE
* @param[in] pDatain         ��������
* @param[in] dlen            �������ݳ��ȣ�datatype=SIGN_HASHʱ��ժҪ���ݳ��ȱ���Ϊ20��
* @param[in] signData	     ��ǩ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_RSASignVerify(XKF_HANDLE hHandle, int bits, const unsigned char *pubkeyid, PXDJA_RSA_PUB_KEY rsaPubkey, int datatype, const unsigned char *pDatain, unsigned int dlen,
                                 unsigned char *signData);

/**
* @brief �����ŷ�
* ����16�ֽڵ��������Ϊ�Ự��Կ����ָ����Կ���ܵĽ���ͳ����⣬ͬʱ����������ڿ�����ʱ��Կ����
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��Կ�ļ�ID
* @param[in] pPubkey         �ⲿ��Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] alg             �Ự��Կ�㷨,ȡֵ1��2��3��4�ֱ��ʾSM1��DES��3DES��SM4
* @param[out] pDataout       �ŷ�����
* @param[out] outlen         �ŷ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_PackEnvelope(XKF_HANDLE hHandle, const unsigned char * pubfid, PXDJA_RSA_PUB_KEY pPubkey, int alg, unsigned char *pDataout, unsigned int * outlen);
/**
* @brief ���ŷ�
* �������������ָ����˽Կ���н��ܣ������ܺ�Ľ����������ʱ����
*
* @param[in] hHandle         �豸���
* @param[in] prikeyid        ˽Կ�ļ�ID
* @param[in] alg             �Ự��Կ�㷨,ȡֵ1��2��3��4�ֱ��ʾSM1��DES��3DES��SM4
* @param[in] pDataIn         �ŷ�����
* @param[in] dlen            �ŷ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_UnpackEnvelope(XKF_HANDLE hHandle, const unsigned char * prifid, int alg, unsigned char * pDataIn, int dlen);
/**
* @brief SM1��Կ��ɢ
* ��Կ��ɢֻ�ܶ�SM1������Կ����SM1������Կ���С��书���ǽ������������Կ������ָ������Կ���м��ܣ��������ܽ��������ʱ����
*
* @param[in] hHandle  �豸���
* @param[in] keyId    ������Կ��ɢ������Կ��SM1������Կ��������Կ
* @param[in] KeyParam ��ɢ����
* @param[in] paramLen ��ɢ���ӳ���,���ܳ���16
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_KeyDisperse(XKF_HANDLE hHandle, int keyId, unsigned char * keyParam, unsigned int paramLen);

/**
* @brief ����SM2�㷨��ݱ�ʶ
*
* @param[in] hHandle  �豸���
* @param[in] sm2id    ��ݱ�ʶ
* @param[in] dlen     ��ݱ�ʶ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetSM2Id(XKF_HANDLE hHandle, const unsigned char *sm2id, int dlen);
/**
* @brief ��ȡSM2�㷨��ݱ�ʶ
*
* @param[in]  hHandle   �豸���
* @param[out] sm2id     ��ݱ�ʶ
* @param[out] outlen    ��ݱ�ʶ����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetSM2Id(XKF_HANDLE hHandle, unsigned char *sm2id, unsigned int *outlen );
/**
* @brief ����SM2�㷨����
*
* @param[in] hHandle      �豸���
* @param[in] sm2param     �����ṹ��ָ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetSM2Param(XKF_HANDLE hHandle, PXDJA_SM2_PARAM sm2param);
/**
* @brief ȡ��SM2�㷨����
*
* @param[in] hHandle     �豸���
* @param[out] sm2param   �����ṹ��ָ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetSM2Param(XKF_HANDLE hHandle, PXDJA_SM2_PARAM sm2param);
/**
* @brief ����ECDSA�㷨����
*
* @param[in] hHandle      �豸���
* @param[in] eccparam     �����ṹ��ָ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetECDSAParam(XKF_HANDLE hHandle, PXDJA_ECC_PARAM eccparam);
/**
* @brief ȡ��ECDSA�㷨����
*
* @param[in] hHandle     �豸���
* @param[out] eccparam   �����ṹ��ָ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetECDSAParam(XKF_HANDLE hHandle, PXDJA_ECC_PARAM eccparam);

/**
* @brief ����SM2��Կ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��Կ�ļ�ID,Ϊ0x00 0x00ʱ��ʾ��Կ��������
* @param[in] prikeyid        ˽Կ�ļ�ID,��˽ԿID��Ϊ0x00 0x00ʱ��ʾ˽Կ��������
* @param[out] sm2pubkey      SM2��Կ�ṹ����Կ�ļ�IDΪ0x00 0x00ʱ��Ч
* @param[out] sm2prikey      SM2˽Կ�ṹ����˽Կ�ļ�ID��Ϊ0x00 0x00ʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GenSM2KeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_SM2_PUBKEY sm2pubkey, PXDJA_SM2_PRIKEY sm2prikey);
/**
* @brief ����ECDSA��Կ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��Կ�ļ�ID,Ϊ0x00 0x00ʱ��ʾ��Կ��������
* @param[in] prikeyid        ˽Կ�ļ�ID,��˽ԿID��Ϊ0x00 0x00ʱ��ʾ˽Կ��������
* @param[out] eccpubkey      ECC��Կ�ṹ����Կ�ļ�IDΪ0x00 0x00ʱ��Ч
* @param[out] eccprikey      ECC˽Կ�ṹ����˽Կ�ļ�ID��Ϊ0x00 0x00ʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GenECDSAKeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_ECC_PUBKEY eccpubkey, PXDJA_ECC_PRIKEY eccprikey);

/**
* @brief ʹ�ÿ���˽Կ���е������
*
* @param[in]	hHandle         �豸���
* @param[in]	type			��˻��ڵ����ߣ�type =0 ����SM2�㷨���� type=1 ECC256����
* @param[in]	prikeyid        ˽Կ�ļ�ID
* @param[in]	point			��Բ�����ϵĵ㣬x||y,64B
* @param[out]	outData			��˽����Px || Py����Ч���ݳ���64B
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ECCMult(XKF_HANDLE hHandle, int type,const unsigned char *prikeyid,unsigned char *point,unsigned char *outData);

/**
* @brief ����˽Կ��չk_new = (k_seed + f) * e + r mod the curve order
*
* @param[in]	hHandle				�豸���
* @param[in]	type				��˻��ڵ����ߣ�type =0 ����SM2�㷨���� type=1 ECC256����
* @param[in]	seedPrikeyid        ����˽Կ�ļ�ID����Ӧ��ʽ�е�k_seed
* @param[in]	newPrikeyid			��չ˽Կ�ļ�ID����Ӧ��ʽ�е�k_new
* @param[in]	f					��Ӧ��ʽ�е�f��32B
* @param[in]	e					��Ӧ��ʽ�е�e��32B
* @param[in]	r					��Ӧ��ʽ�е�r��32B
* @param[out]   sm2pubkey           ��չ˽Կ��ӦECC��Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ECCDeriveKey(XKF_HANDLE hHandle, int type,const unsigned char *seedPrikeyid,const unsigned char *newPrikeyid,unsigned char *f,unsigned char *e,unsigned char *r, PXDJA_SM2_PUBKEY sm2pubkey);

/**
* @brief SM2��Կ����
*  XDJA���Ľṹ�� 0x04 | x(32B) | y(32B) | ���� | ����HASH(32B)������0x04 C1 C2 C3
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        SM2��ԿID�����ֽڣ��ڶ����ֽ���Ч ��Ϊ0x00 0x00��ʾ��Կ�����ݴ���
* @param[in] sm2pubkey       ��Կ,��pubkeyidΪ0x00 0x00ʱ��Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����158
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ�����,���峤������Ϊdlen+97
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2Encrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outLen);
/*
* @brief SM2��Կ���ܣ����ܱ�׼��
* �������Ľṹ��  x(32B) | y(32B) | ����HASH(32B) | ���ĳ���(4B) | ���ģ�����C1 C3 C2_length C2
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        SM2��ԿID�����ֽڣ��ڶ����ֽ���Ч ��Ϊ0x00 0x00��ʾ��Կ�����ݴ���
* @param[in] sm2pubkey       ��Կ,��pubkeyidΪ0x00 0x00ʱ��Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����153
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ�����,���峤������Ϊdlen+100
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2Encrypt_GM(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outLen);
/**
* @brief SM2˽Կ����
*
* @param[in] hHandle         �豸���
* @param[in] prikeyid        SM2˽ԿID ���ֽڣ��ڶ����ֽ���Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����SM2_BLOCK_MAX+97,��ʽΪ��04 C1 C2 C3
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ����������,����������Ϊdlen-97
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_SM2Decrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen);
/**
* @brief SM2˽Կ���ܣ����ܱ�׼��
*
* @param[in] hHandle         �豸���
* @param[in] prikeyid        SM2˽ԿID ���ֽڣ��ڶ����ֽ���Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����255
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ����������,����������Ϊdlen-100
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_SM2Decrypt_GM(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen);

/**
* @brief SM2ǩ��Ԥ����
*
* @param[in] hHandle         �豸���
* @param[in] pSm2Pubkey      SM2��Կ
* @param[in] pSm2Id			 SM2ǩ����ID
* @param[in] sm2IdLen        ǩ����ID����
* @param[in] pData			 ����������
* @param[in] dataLen         ���������ݳ���
* @param[out] e				 Ԥ����֮������ݣ�����32B
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_SM2SignPreProcess(XKF_HANDLE hHandle, PXDJA_SM2_PUBKEY pSm2Pubkey, unsigned char* pSm2Id, int sm2IdLen, unsigned char* pData, int dataLen, unsigned char* e);
/**
* @brief SM2����ǩ������HASH��
* �����ǩ�������Ѿ�SM3HASH��ֱ��ǩ���������Ƚ���SM3HASH�����㷨��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID,��datatype=1ʱ,pubkeyid��Ч
* @param[in] prikeyid        ˽ԿID
* @param[in] datatype        ��������,��SIGN_DATA_TYPE
* @param[in] pDatain         ��������
* @param[in] dlen            ���ݳ���,���datatype=SIGN_HASH,���ݳ��ȱ���Ϊ32����eֵ
* @param[out] signData       ���ǩ������,���������ȱ������64�ֽڣ���ʽ��32�ֽ�r+32�ֽ�s
* @param[out] outlen         ������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2Sign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, int datatype, const unsigned char *pDatain, int dlen, unsigned char *signData,
                           unsigned int *outlen);

/**
* @brief ECDSA����ǩ
* ���ݱ������Ѿ�����ժҪ�����
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID,��datatype=1ʱ,pubkeyid��Ч
* @param[in] prikeyid        ˽ԿID
* @param[in] pDatain         �������ݣ��������Ѿ�HASH��32�ֽ�
* @param[out] signData       ���ǩ������,���������ȱ������64�ֽ�
* @param[out] outlen         ������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ECDSASign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, unsigned char *signData, unsigned int *outlen);
/**
* @brief SM2����ǩ����ӲHASH��
* �ȶԴ�ǩ�����ݽ���SM3HASH(Ӳ�㷨)����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID,��datatype=SIGN_NOHASHʱ,pubkeyid��Ч
* @param[in] prikeyid        ˽ԿID
* @param[in] pDatain         ��ǩ������
* @param[in] dlen            ��ǩ�����ݳ���
* @param[out] signData       ���ǩ������,���������ȱ������64�ֽ�
* @param[out] outlen         ������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);

/**
* @brief SM2����ǩ����֤����HASH��
* �����ǩ�������Ѿ�SM3HASH��ֱ����ǩ�������Ƚ���SM3HASH�����㷨��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID
* @param[in] datatype        �������ͣ���SIGN_DATA_TYPE
* @param[in] sm2pubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] pDatain         ����
* @param[in] dlen            ���ݳ��ȣ����datatype=SIGN_HASH,���ݳ��ȱ���Ϊ32����eֵ
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, int datatype, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *signData);
/**
* @brief ECDSA����ǩ����֤
* ���ݱ������Ѿ�HASH��32�ֽ�
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID
* @param[in] eccpubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] pDatain         ���ݣ��������Ѿ�ժҪ���32�ֽ�
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_ECDSASignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ECC_PUBKEY eccpubkey, const unsigned char *pDatain, unsigned char *signData);
/**
* @brief SM2����ǩ����֤��ӲHASH��
* �ȶԴ�ǩ�����ݽ���SM3HASH��Ӳ�㷨��������ǩ
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID
* @param[in] sm2pubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] pDatain         ��ǩ������
* @param[in] dlen            ��ǩ�����ݳ���
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief SM2����ǩ����֤��HASH��
* ��ǩ�������Ѿ�SM3HASH��ֱ����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] datatype        ��������SIGN_DATA_TYPE
* @param[in] sm2id			 sm2ǩ��id����datatype=SIGN_NOHASHʱ��Ч
* @param[in] idlen			 sm2ǩ��id����
* @param[in] pubdata1		 ��1����ǩ���ݣ���Կ 	 04+x+y �� 02/03+x
* @param[in] publen1         ��1����ǩ���ݣ���Կ����
* @param[in] pDatain1        ��1����ǩ���ݣ�����ǩ����
* @param[in] dlen1			 ��1����ǩ���ݣ�����ǩ���ݳ��ȣ������Ԥ����������ݣ����ݳ��ȱ�����32
* @param[in] signData1		 ��1����ǩ���ݣ�ǩ������
* @param[in] pubdata2		 ��2����ǩ���ݣ���Կ 	 04+x+y �� 02/03+x
* @param[in] publen2         ��2����ǩ���ݣ���Կ����
* @param[in] pDatain2        ��2����ǩ���ݣ�����ǩ����
* @param[in] dlen2			 ��2����ǩ���ݣ�����ǩ���ݳ��ȣ������Ԥ����������ݣ����ݳ��ȱ�����32
* @param[in] signData2		 ��2����ǩ���ݣ�ǩ������
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignVerifyMult(XKF_HANDLE hHandle, int datatype, unsigned char *sm2id, int idlen, unsigned char * pubdata1, int publen1, const unsigned char *pDatain1, int dlen1,
                                     unsigned char *signData1, unsigned char * pubdata2, int publen2, const unsigned char *pDatain2, int dlen2, unsigned char *signData2);

/**
* @brief ��ʽ֤�鹫Կת������Կ
* ���㹫ʽ��RP = [l]Ppc + Ppca
* @param[in] hHandle       �豸���
* @param[in] pubtype       0 SM2; 1 ECDSA
* @param[in] pcPub         ��ʽ֤�鹫Կ
* @param[in] pcaPub        PCA�еĹ�Կ
* @param[in] l             �������HASHֵ���ֽ�
* @param[in] message       ��ǩ����Ϣ
* @param[in] signData      ǩ������
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_ImCertPubConvr(XKF_HANDLE hHandle, int pubtype, PXDJA_ECC_PUBKEY pcPub, PXDJA_ECC_PUBKEY pcaPub, unsigned char * l, PXDJA_ECC_PUBKEY rpPub);

/**
* @brief ������Կ������Կ���
*
* @param[in] hHandle    �豸���
* @param[in] asymalg    �ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg     �Գ��㷨����  ����������Ĭ��0
* @param[in] i			����ֵi
* @param[in] j			����ֵj
* @param[in] ek			���ڽ���˽Կ�����ek
* @param[in] prifid		˽Կid
* @param[in] xybuf		�������ĵ�����x[32B]+y[32B]
* @param[in] xylen		64
* @param[out] outdata   ��˽����xy
* @param[out] datalen   ��˽���������
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKTmpEnPriCalc(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *prifid, unsigned char* xybuf,
                                  int xylen, unsigned char* outdata, int *datalen);



/**
* @brief ѹ����Կת������Կ
* ���㹫ʽ��y^2 = x^3 + ax + b
* @param[in] hHandle    �豸���
* @param[in] pubtype    0 SM2; 1 ECDSA
* @param[in] x          ���빫Կ x
* @param[in] y_lsb      ѹ��yֵ��0 1
* @param[out] y         �����Կ y
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_CompressPubConvr(XKF_HANDLE hHandle, int pubtype, unsigned char* x, unsigned char y_lsb, unsigned char* y);
/**
* @brief SM2����ǩ����֤��HASH��
* ��ǩ�������Ѿ�SM3HASH��ֱ����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] datatype        �������ͣ���SIGN_DATA_TYPE
* @param[in] pubtype 	     0 ��ͨ��Կ; 1 ѹ����Կ; 2 ��ʽ֤�鹫Կ
* @param[in] pubData 	     pubtype=0��ͨ��ԿTLV����;pubData= 78 20 [Pub_x] 79 20 [Pub_y]
*			                 pubtype=1ѹ����Կ��ԿTLV����; pubData=78 20 [Pub_x] 79 01 [y_lsb]
*							 pubtype=2��ʽ֤��TLV����;pubData= 6C 20 [l] 78 20 [pcPub_x] 79 20 [pcPub_y]  78 20 [pcaPub_x] 79 20 [pcaPub_y]
* @param[in] pDatain         ����
* @param[in] dlen            ���ݳ��ȣ����datatype=SIGN_HASH���ȱ���Ϊ32
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx2(XKF_HANDLE hHandle, int datatype, int pubtype, unsigned char *pubData, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief ECDSA����ǩ����֤��HASH��
*
* @param[in] hHandle         �豸���
* @param[in] pubtype 	     0 ��ͨ��Կ;1 ѹ����Կ; 2 ��ʽ֤�鹫Կ
* @param[in] pubData 	     pubtype=0��ͨ��ԿTLV����;pubData= 78 20 [Pub_x] 79 20 [Pub_y]
*			   				 pubtype=1ѹ����Կ��ԿTLV����; pubData=78 20 [Pub_x] 79 01 [y_lsb]
*							 pubtype=2��ʽ֤��TLV����;pubData= 6C 20 [l] 78 20 [pcPub_x] 79 20 [pcPub_y]  78 20 [pcaPub_x] 79 20 [pcaPub_y]
* @param[in] pDatain         ����
* @param[in] dlen            ���ݳ���,����Ϊ32
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_ECDSASignVerifyEx2(XKF_HANDLE hHandle, int pubtype, unsigned char *pubData, const unsigned char *pDatain, int dlen, unsigned char *signData);

/**
* @brief SM2����ǩ��������δhash��
* �������ݴ���COS��COS�ڲ���hash��ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] sm2pubkey       SM2��Կ�ṹ
* @param[in] prikeyid        ˽ԿID
* @param[in] sm2id			 SM2ǩ����ID
* @param[in] idlen			 ǩ����ID����
* @param[in] pDatain         ��ǩ������
* @param[in] dlen            ��ǩ�����ݳ���
* @param[out] signData       ���ǩ������,���������ȱ������64�ֽ�
* @param[out] outlen         ������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignEx3(XKF_HANDLE hHandle, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *prikeyid, const unsigned char *sm2id, unsigned int idlen, const unsigned char *pDatain, int dlen,
                              unsigned char *signData, unsigned int *outlen);

/**
* @brief SM2����ǩ����֤������δhash��
* �������ݴ���COS��COS�ڲ���hash��ǩ����֤
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID
* @param[in] sm2pubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] sm2id			 SM2ǩ����ID
* @param[in] idlen			 ǩ����ID����
* @param[in] pDatain         ��ǩ������
* @param[in] dlen            ��ǩ�����ݳ���
* @param[in] signData        ��ǩ����
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM2SignVerifyEx3(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_SM2_PUBKEY sm2pubkey, const unsigned char *sm2id, unsigned int idlen, const unsigned char *pDatain,
                                    int dlen, unsigned char *signData);

/**
* @brief SM2Э����Կ��ʼ��
*
* @param[in] hHandle          �豸���
* @param[in] pubkeyid         SM2��ԿID ���ֽ�,�ڶ����ֽ���Ч,��һ�ֽڱ���Ϊ0x00
* @param[out] pdataout        ����Э������
* @param[out] outlen          ������ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2KeyGenInit(XKF_HANDLE hHandle, const unsigned char *pubkeyid, unsigned char *pdataout, unsigned int *outlen);
/**
* @brief SM2Э����Կ ���㲽��
*
* @param[in] hHandle          �豸���
* @param[in] pubkeyid         SM2��ԿID ���ֽ�,��һ���ֱ���Ϊ0x00,�ڶ����ֽ���Ч ��dictflag=SM2_KEY_GENERATE_DICT_SEND ʱ ��ԿIDΪ0x00x00
* @param[in] prikeyid         SM2˽ԿID ���ֽ�,��һ���ֱ���Ϊ0x00,�ڶ����ֽ���Ч
* @param[in] pDatain          ��������
*								��dictflag=SM2_KEY_GENERATE_DICT_SEND ʱ����������Ϊ ��Ӧ����ID��TLV��ʽ��||��Ӧ����Կx���꣨TLV��ʽ��||��Ӧ����Կy���꣨TLV��ʽ��||��Ӧ����ʱ��Կx���꣨TLV��ʽ��||��Ӧ����ʱ��Կy����(TLV��ʽ)
*								��dictflag=SM2_KEY_GENERATE_DICT_RECV ʱ����������Ϊ ���𷽵�ID��TLV��ʽ��||���𷽹�Կx���꣨TLV��ʽ��||���𷽹�Կy���꣨TLV��ʽ��||������ʱ��Կx���꣨TLV��ʽ��||������ʱ��Կy����(TLV��ʽ)
* @param[in] dlen             �������ݳ���
* @param[out] pDataout        ����Э������
* @param[out] outlen          ������ݳ���
* @param[in] dictflag         �������,SM2_KEY_GENERATE_DICT_SENDΪ����,SM2_KEY_GENERATE_DICT_RECVΪ��Ӧ��]
* @param[in] prikeyflag       ��Կ�洢��� 1�̶�λ��,0��ʱλ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2KeyGenCompute(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,
                                    unsigned int *outlen, unsigned char dictflag, unsigned char keyflag);
/**
* @brief SM2Э����Կ ���㲽��
* ˵������֤�Զ���ݣ���֧�ַ���ʹ��
*
* @param[in] hHandle          �豸���
* @param[in] pubkeyid         SM2��ԿID ���ֽ�,��һ���ֱ���Ϊ0x00,�ڶ����ֽ���Ч ��dictflag=SM2_KEY_GENERATE_DICT_SEND ʱ ��ԿIDΪ0x00x00
* @param[in] prikeyid         SM2˽ԿID ���ֽ�,��һ���ֱ���Ϊ0x00,�ڶ����ֽ���Ч
* @param[in] pDatain          ��������
*							  ��������Ϊ ��Ӧ����ID��TLV��ʽ��||��Ӧ����Կx���꣨TLV��ʽ��||��Ӧ����Կy���꣨TLV��ʽ��||��Ӧ����ʱ��Կx���꣨TLV��ʽ��||��Ӧ����ʱ��Կy����(TLV��ʽ)
* @param[in] dlen             �������ݳ���
* @param[out] pDataout        ����Э������
* @param[out] outlen          ������ݳ���
* @param[in] dictflag         �������,��֧��SM2_KEY_GENERATE_DICT_SENDΪ����
* @param[in] prikeyflag       ��Կ�洢��� 2 ��֧�ֳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2KeyGenComputeEx(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,
                                      unsigned int *outlen, unsigned char dictflag, unsigned char keyflag);

/**
* @brief SM2Э����Կ��֤
*
* @param[in] hHandle         �豸���
* @param[in] pDatain         ��������
* @param[in] dlen            �������ݳ��� �̶�32�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2KeyGenVerify(XKF_HANDLE hHandle, const unsigned char *pDatain, int dlen);
/**
* @brief SM2Э����Կ��֤
* ˵��������ר��
*
* @param[in] hHandle         �豸���
* @param[in] pDatain         ��������
* @param[in] dlen            �������ݳ��� �̶�32�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM2KeyGenVerifyEx(XKF_HANDLE hHandle, const unsigned char *pDatain, int dlen);
/**
* @brief SM9����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ����ԿID
* @param[in] prikeyid        ǩ��˽ԿID
* @param[in] pDatain         ����
* @param[in] dlen            ����
* @param[out] signData       ���ǩ������,��������������96�ֽ�
* @param[out] outlen         ������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM9Sign(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *signData, unsigned int *outlen);
/**
* @brief SM9����ǩ����֤
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ����ԿID
* @param[in] idb             �Է���ʶ����Կ��
* @param[in] pDatain         ����
* @param[in] dlen            ����
* @param[in] signData        ��ǩ���ݣ�96�ֽ�
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_SM9Verify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, unsigned char *signData);
/**
* @brief SM9��Կ����
*  ���Ľṹ�� C1 C3 C2
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ����ԿID
* @param[in] idb             �Է���ʶ����Կ��
* @param[in] pDatain         ��������
* @param[in] dlen            ���ݳ���
* @param[in] EncID           encryption identification,0:stream cipher 1:block cipher
* @param[out] pDataout       ���ܺ�����,���峤������Ϊdlen+96
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SM9Encrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, int EncID, unsigned char *pDataout,
                              unsigned int *outLen);
/**
* @brief SM9˽Կ����
*
* @param[in] hHandle         �豸���
* @param[in] prikeyid        ˽ԿID
* @param[in] idb             �Է���ʶ����Կ
* @param[in] pDatain         �������ݣ����**
* @param[in] dlen            ���ݳ���
* @param[in] EncID           encryption identification,0:stream cipher 1:block cipher
* @param[out] pDataout       ���ܺ����������,����������Ϊdlen-96
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_SM9Decrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char * idb, const unsigned char *pDatain, int dlen, int EncID, unsigned char *pDataout,
                              unsigned int *outlen);

/************************************************************************/
/*TF��ר�ýӿ�                                                        */
/************************************************************************/
/**
* @brief ��ȡTF���豸����·��
*
* @param[in] hHandle    �豸���
* @param[out] mountpath ����·��  win32�»�ȡ�̷�   Linux�»�ȡ����·��
* @param[out] pathlen   ·������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetTFMountPath(XKF_HANDLE hHandle, char* mountpath, int * pathlen);
/**
* @brief ��ȡ���ط�������
*
* @param[in] hHandle �豸���
* @param[out] size   �������ط�����������
*
* @return ������
* @retval 0 �ɹ�
*/
XDJAKEYAPI int XKF_GetTFZoneSize(XKF_HANDLE handle, int* size);
/**
* @brief ��TF������������,���ݴ�СΪ�ֽ�
*
* @param[in]     hHandle      �豸���
* @param[in]     sectorStart  ������
* @param[out]	 pDataBuf     ���ݻ�����
* @param[in]     buffSize     ���ݴ�С
*
* @return ������
* @retval 0 �ɹ�
*/
XDJAKEYAPI int XKF_ReadTFZone(XKF_HANDLE handle, int sectorStart, unsigned char *pDataBuf, int buffSize);
/**
* @brief дTF������������,���ݴ�СΪ�ֽ�
* @param[in]     hHandle      �豸���
* @param[in]     sectorStart  ������
* @param[in]	 pDataBuf     ���ݻ�����
* @param[in]     buffSize    ���ݴ�С
*
* @return ������
* @retval 0 �ɹ�
*/
XDJAKEYAPI int XKF_WriteTFZone(XKF_HANDLE handle, int sectorStart, unsigned char *pDataBuf, int buffSize);

/************************************************************************/
/*����U��ר�ýӿ�                                                        */
/************************************************************************/

/**
* @brief ��ȡ����U��ָ�������Ĺ���·��
*
* @param[in] hHandle �豸���
* @param[in] type    �������ͣ�����ͨ�����������������̷�������
* @param[out] path   ���ظ÷����Ĺ���·��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetUsbMountPath(XKF_HANDLE hHandle, USB_FLASH_TYPE type, unsigned char* path);
/**
* @brief �޸ļ���U��FLASH��дģʽ
*
* @param[in] hHandle �豸���
* @param[in] mode    �µĶ�дģʽ����ͨ����ʱ��д����ʱֻ�������ÿ�д������ֻ������������ʱ��д ������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_SetUsbRWMode(XKF_HANDLE hHandle, USB_FLASH_RW_MODE mode);
/**
* @brief ������U����ͨ������
*
* @param[in] hHandle �豸���
* @param[in] addr    ������ʼ��ַ
* @param[in] secs    ��������
* @param[out] pdata  ���ݽ��ջ�����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadUsbNormalSecs(XKF_HANDLE hHandle, int addr, short secs, unsigned char* pdata);
/**
* @brief д����U����ͨ������
*
* @param[in] hHandle �豸���
* @param[in] addr    ������ʼ��ַ
* @param[in] secs    ��������
* @param[in] pdata  ��д���ݻ�����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteUsbNormalSecs(XKF_HANDLE hHandle, int addr, short secs, unsigned char* pdata);
/**
* @brief �򿪼���U�̼�����
*
* @param[in] hHandle �豸���
* @param[in] pass    ����
* @param[in] passlen �����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenUsbSecuZone(XKF_HANDLE hHandle, const unsigned char* pass, int passlen);
/**
* @brief �򿪼���U�̼������������̺�PIN����󶨣���Ҫ����PIN��Ӧ�Ľ�ɫ
*
* @param[in] hHandle �豸���
* @param[in] role	 PIN��ɫ
* @param[in] pass    ����
* @param[in] passlen �����
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenUsbSecuZoneEx(XKF_HANDLE hHandle, unsigned char role, const unsigned char* pass, int passlen);
/**
* @brief �رռ���U�̼�����
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CloseUsbSecuZone(XKF_HANDLE hHandle);
/**
* @brief �޸ļ���U�̼���������
* ע������ɿ����ȷ�����ڲ��ͻ����һ�ξɿ�������Դ������޸Ŀ�����Ա���Ϊ����֤�ɿ���޸��¿�������ϲ�����
*
* @param[in] hHandle �豸���
* @param[in] oldpass �ɿ���
* @param[in] oldlen  �ɿ����
* @param[in] newpass �¿���
* @param[in] newlen  �¿����
* @param[in] type    �������ͣ�1�����̿�� 2�����̽�������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ChgUsbSecuZonePin(XKF_HANDLE hHandle, const unsigned char* oldpass, int oldlen, const unsigned char* newpass, int newlen, int type);
/**
* @brief ���������̿���
* ������Ҫ��������ȷ�ļ����̽�������
*
* @param[in] hHandle �豸���
* @param[in] key     ��������
* @param[in] keyLen  ���������
* @param[in] pin     �µĿ���
* @param[in] pinLen  �¿���ĳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_UnlockUsbSecuZone(XKF_HANDLE hHandle, const unsigned char *key, int keyLen, const unsigned char *pin, int pinLen);
/**
* @brief ��ʼ������U��������
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_InitUsbHiddZone(XKF_HANDLE hHandle);
/**
* @brief ��ȡ����U������������С
*
* @param[in]  hHandle �豸���
* @param[out] hdSize  ���ش�С
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetUsbHiddZoneSize(XKF_HANDLE hHandle, unsigned int * hdSize);
/**
* @brief ������U����������
*
* @param[in] hHandle     �豸���
* @param[in] dwStartAddr ��ʼ������ַ
* @param[out] pOutBuff    ������
* @param[in] buffSize    Ҫ��ȡ�ĳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ReadUsbHiddZone(XKF_HANDLE hHandle, unsigned int dwStartAddr, void* pOutBuff, unsigned int buffSize);
/**
* @brief д����U����������
*
* @param[in] hHandle     �豸���
* @param[in] dwStartAddr ��ʼ������ַ
* @param[in] pOutBuff    д����
* @param[in] buffSize    Ҫд�볤��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_WriteUsbHiddZone(XKF_HANDLE hHandle, unsigned int dwStartAddr, void * pInBuff, unsigned int buffSize);
/**
* @brief ����USB SCSIָ��
*
* @param[in] hHandle     �豸���
* @param[in] pCDBbuff    CDB
* @param[in] cdbLength   CDB����
* @param[in] sendDataBuf �������ݻ���
* @param[in] sendDataLen �������ݳ���
* @param[out] recvDataBuf �������ݻ���
* @param[out] recvDataLen �������ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ExecUsbScsiCmd(XKF_HANDLE hHandle, void* pCDBbuff, unsigned int cdbLength, void* sendDataBuf, unsigned int sendDataLen, void * recvDataBuf, unsigned int * recvDataLen);
/***********************************************************************/
/*����U��ר�ýӿ�                                                       */
/***********************************************************************/

/**
* @brief �ж��豸�Ƿ����U��
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_Is2gKey(XKF_HANDLE hHandle);
/**
* @brief ������ǩ��
*
* @param[in] hHandle   �豸���
* @param[in] prikeyid  ˽ԿID
* @param[in] pDatain   ǩ������
* @param[in] dlen      ǩ�����ݳ���
* @param[in] pDatain   ǩ�����
* @param[in] dlen      ǩ���������
* @param[in] dataType  ǩ����������
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_2gKeySign(XKF_HANDLE hHandle, const unsigned char * prikeyid, const unsigned char * pDatain, int dlen, unsigned char *pDataout, unsigned int *outlen, int dataType);
/**
* @brief ��ȡ2����ʣ�����
*
* @param[in] hHandle �豸���
* @param[out] state  ���״̬:  1��ʾδ���, 0��ʾ���ڳ��
* @param[out] power  ����ֵΪ�ٷֱ�ֵ,���緵��10��ʾʣ��10%�ĵ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetRemainPower(XKF_HANDLE hHandle, int * state, int * power);


/***********************************************************************/
/*USBר�ýӿ�                                                          */
/***********************************************************************/

/**
* @brief ��ָ���豸,�����豸���
*  ˵��������ö���豸
*
* @param[in]   devPath ���磺\\?\USB#Vid_04e8&Pid_503b#0002F9A9828E0F06#{a5dcbf10-6530-11d2-901f-00c04fb951ed}
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDevByPath(const unsigned char * devPath, XKF_HANDLE * hHandle);
/**
* @brief ��ָ���豸,�����豸���
*  ˵��������ö���豸����Ĥ��ר��
*
* @param[in]   readerName ͨ��Windows SmartCard API����SCardListReadersö�ٵ��ľ���Reader����
* @param[out]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_OpenDevByReader(const unsigned char * readerName, XKF_HANDLE * hHandle);

/**
* @brief ��ȡ�����̴�״̬
*
* @param[in]   hHandle �豸���
* @param[out]  pucState ��״̬.0:�ر�,1:��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetSecuZoneOpenState(XKF_HANDLE hHandle, unsigned char* pucState);

/***********************************************************************/
/*���õ��������ܿ�����                                                 */
/***********************************************************************/

/**
* @brief ���õ��������ܿ�����
*
* @param[in]   pThirdPartySoName
*
* @return ��
*/
XDJAKEYAPI int XKF_SetThirdPartySoName(const char* pThirdPartySoName);

/***********************************************************************/
/*ָ��KEYר�ýӿ�                                                      */
/***********************************************************************/

/**
* @brief ¼��ָ��
*  ˵������Ҫ����PIN ������֤��ָ��¼��ɹ����Զ��󶨵�ǰ��ɫ��
*
* @param[in] hHandle �豸���
* @param[in] state	 ¼��ָ��״̬��0-����¼�� 1-��ѯ¼��״̬
* @param[out] fpIndex ����¼��ɹ���ָ�Ʊ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_EnrollFp(XKF_HANDLE hHandle, unsigned char state, unsigned char *fpIndex);

/**
* @brief ��ָ֤��
*  ˵����ָ����֤ͨ���������ָ���Ѱ󶨽�ɫ����ȫоƬ����Ϊ��Ӧ��ɫ�İ�ȫȨ��
*
* @param[in] hHandle �豸���
* @param[in] state	 ��ָ֤��״̬��0-����ָ����֤ 1-��ѯ��֤״̬
* @param[out] fpIndex ������֤�ɹ���ָ�Ʊ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_VerifyFp(XKF_HANDLE hHandle, unsigned char state, unsigned char *fpIndex);

/**
* @brief ɾ��ָ��
*  ˵����ɾ��ָ��ͬʱɾ���󶨵Ľ�ɫ��Ϣ��ɾ������ָ�ƵĲ���Ҫ���Ѵ��ڵ�ָ�ƶ�Ϊͬһ��ɫ����PIN������֤ͨ��
*
* @param[in] hHandle �豸���
* @param[in] index	 ɾ��ָ������ 0xFF-ɾ������ָ�� 00 01 02ɾ��ָ��ָ��
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_DeleteFp(XKF_HANDLE hHandle, unsigned char index);

/**
* @brief ȡ��¼��/ȡ����֤
*  ˵������ָ��ִ�гɹ�����Ҫʹ��¼��/��֤�Ĳ�ѯ״ָ̬���ȡʵ��ִ�н�����Բ�ѯ�������ս��Ϊ׼
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CancelFp(XKF_HANDLE hHandle);

/**
* @brief ��ȡָ���б�
*
* @param[in]  hHandle �豸���
* @param[out] fplist  ָ���б� �����ֽ�Ϊһ�飨������飩����һ���ֽ�Ϊ�豸ָ�Ʊ�ţ�00~02�����ڶ����ֽ�Ϊ�󶨽�ɫ��00Ϊδ�󶨣������ݳ���6��Ĭ��ȫF
* @param[out] outlen
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetFpList(XKF_HANDLE hHandle, unsigned char* fplist, unsigned int* outlen);

/**
* @brief ��ȡ��ǰָ��ģ��״̬
*
* @param[in]  hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GetFpState(XKF_HANDLE hHandle);

/***********************************************************************/
/*������Կ��ؽӿ�                                                     */
/***********************************************************************/
/**
* @brief ������Կ��ʼ��,Ӧ��������Ӧ�㷨���߲���
*	˵������������ǩ����˽Կ��a, A�������Ӽ��ܹ�˽Կ��p, P��������Գ���Կck��ek
*
* @param[in] hHandle			�豸���
* @param[in] asymalg			�ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] signSeedPriFid     ����ǩ��˽Կ�ļ�id
* @param[in] encSeedPriFid      ���Ӽ���˽Կ�ļ�id
* @param[out] A					����ǩ����ԿA���̶�����64�ֽ�
* @param[out] P					���Ӽ��ܹ�ԿP���̶�����64�ֽ�
* @param[out] ck				����ǩ����Կ��չ�����ck���̶�����16�ֽ�
* @param[out] ek				���ڼ�����Կ��չ�����ek���̶�����16�ֽ�
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKInit(XKF_HANDLE hHandle, unsigned char asymalg, const unsigned char *signSeedPriFid, const unsigned char *encSeedPriFid, unsigned char *A, unsigned char *P, unsigned char *ck,
                          unsigned char *ek);

/**
* @brief ������Կ������Կ���
*
* @param[in] hHandle    �豸���
* @param[in] asymalg    �ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg     �Գ��㷨����  ����������Ĭ��0
* @param[in] i			����ֵi
* @param[in] j			����ֵj
* @param[in] ek			���ڽ���˽Կ�����ek
* @param[in] prifid		˽Կid
* @param[in] xybuf		�������ĵ�����x[32B]+y[32B]
* @param[in] xylen		64
* @param[out] outdata   ��˽����xy
* @param[out] datalen   ��˽���������
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKTmpEnPriCalc(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *prifid, unsigned char* xybuf,
                                  int xylen, unsigned char* outdata, int *datalen);

/**
* @brief ������Կ����-CA��������
*
* @param[in] hHandle			�豸���
* @param[in] asymalg			�ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg				�Գ��㷨����  ����������Ĭ��0
* @param[in] i					����ֵi
* @param[in] j					����ֵj
* @param[in] ek					��ʼ�����ڼ�����Կ��չ�����ek
* @param[in] encSeedPriFid		���Ӽ���˽Կ�ļ�id
* @param[in] inData				�������ݣ���ʽ��04|C1|C2|C3
* @param[in] inLen				�������ݳ���
* @param[out] outData			����
* @param[out] outLen			���ĳ���
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKDecrypt(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ek, unsigned char *encSeedPriFid, unsigned char *inData,
                             int inLen, unsigned char* outData, int *outLen);

/**
* @brief ������Կ��ʽ֤��ʱ�����ݹ�Կ�ع�ֵ��������ǩ����Կ
*	˵��������ǩ����Կ��ePu + Qca������eΪCA����֤���ժҪֵ��PuΪ֤���еĹ�Կ����Bl+C��QcaΪCA��Կ
*
* @param[in] hHandle			�豸���
* @param[in] asymalg			�ǶԳ��㷨����0_SM2, 1_ECDSA, 2_brainpoolp256r1
* @param[in] e					eֵ����֤�����ݵ�ժҪֵ,�̶�����32�ֽ�
* @param[in] constructPubKey	��Կ�ع�ֵ����ʽ֤���еĹ�Կ������Bl+C���̶�����64�ֽ�
* @param[in] caPubKey			CA��Կ
* @param[out] pubKey			����ǩ����Կ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_BKCalcSignPubkey(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char * e, unsigned char* constructPubKey, unsigned char *caPubKey, unsigned char* pubKey);

/**
* @brief ������Կ��������ǩ��˽Կ
*	˵������ʽ֤��ʱ�ڼ��㣺bl+c(mod n)������blΪ��չǩ��˽Կ��cΪCA���ص�˽Կ�ع�ֵ��nΪ���߲���n��
��ʽ֤��ʱ�ڼ��㣺e*bl+r(mod n)������eΪCA����֤���ժҪֵ��blΪ��չǩ��˽Կ��rΪCA���ص�˽Կ�ع�ֵ��nΪ���߲���n��
*
* @param[in] hHandle    �豸���
* @param[in] asymalg    �ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg     �Գ��㷨����   ����������Ĭ��0
* @param[in] i			����ֵi
* @param[in] j			����ֵj
* @param[in] ck			��ʼ������ǩ����Կ��չ�����ck
* @param[in] signSeedPriFid	����ǩ��˽Կ�ļ�id
* @param[in] priFid		˽Կid
* @param[in] certType	֤������ 0 ��ʽ֤�飬 1 ��ʽ֤��
* @param[in] component  CA�˵�˽Կ�ع�ֵ ��ʽ��c����ʽ��r��
* @param[in] e			CA��֤���hashֵ��certtype==1ʱ��Ч
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKCalcSignPrikey(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ck, unsigned char *seedprifid,
                                    unsigned char *prifid, int certtype, unsigned char* component, unsigned char* e);

/**
* @brief ������Կ����.ȡ����֤�鼰������Ĺ�˽Կд����Ӧ�ļ�.
*
*
* @param[in] hHandle		�豸���
* @param[in] algType		�ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] certType		֤������,0:ExpCert��1:ImCert
* @param[in] i				����ֵi
* @param[in] j				����ֵj
* @param[in] ck				����ǩ����Կ��չ�����ck���̶�����16�ֽ�
* @param[in] ek				���ڼ�����Կ��չ�����ek���̶�����16�ֽ�
* @param[in] caPubKey		CA��Կ(x,y)
* @param[in] encCertData	֤������
* @param[in] encCertLen		֤�����ĳ���
* @param[in] signSeedPriFid	����ǩ��˽ԿID
* @param[in] encSeedPriFid	���Ӽ���˽ԿID
* @param[in] pubKeyId		��ԿID
* @param[in] priKeyId		˽ԿID
* @param[in] certFileId		֤��ID
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKCalc(XKF_HANDLE hHandle, unsigned char algType, unsigned char certType, unsigned int i, unsigned int j, unsigned char* ck, unsigned char* ek, unsigned char* caPubKey,
                          unsigned char* encCertData, int encCertLen, unsigned char* signPriFid, unsigned char* encPriFid, unsigned char* pubKeyId, unsigned char* priKeyId, unsigned char* certFileId);

/**
* @brief ������Կ����˽Կ������������ǩ��
* ˵������ʽ֤��ʱ�ڼ��㣺bl+c(mod n)������blΪ��չǩ��˽Կ��cΪCA���ص�˽Կ�ع�ֵ��nΪ���߲���n��
*��ʽ֤��ʱ���㣺e*bl+r(mod n)������eΪCA����֤���ժҪֵ��blΪ��չǩ��˽Կ��rΪCA���ص�˽Կ�ع�ֵ��nΪ���߲���n��
*SM2����ǩ��
*
* @param[in] hHandle    	�豸���
* @param[in] asymalg    	�ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg     	�Գ��㷨����   ����������Ĭ��0
* @param[in] certType   	֤������ 0 ��ʽ֤�飬 1 ��ʽ֤��
* @param[in] datatype   	��������,SIGN_HASH��ʾinDataΪ����Ԥ�����eֵ;SIGN_NOHASH��ʾԭʼ����
* @param[in] i          	����ֵi
* @param[in] j          	����ֵj
* @param[in] ck         	��ʼ��������ǩ����Կ��չ�����ck
* @param[in] signSeedPriFid ����ǩ��˽Կ�ļ�id
* @param[in] component    	CA�˵�˽Կ�ع�ֵ ��ʽ��c��|��ʽ��r��
* @param[in] e            	CA��֤���hashֵ��certtype=1(��ʽ֤��)ʱ��Ч
* @param[in] inData       	�����ǩ������
* @param[in] inLen        	���ݳ���,�����ժҪ���ݳ���(datatype=SIGN_HASH)����Ϊ32
* @param[out] signData    	���ǩ������,���������ȱ������64�ֽ�,���ݸ�ʽ��32�ֽ�r+32�ֽ�s
* @param[out] outlen      	������ݳ���
*
* @return ������
* @retval XKR_NO_POWER  Ȩ�޲���
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_BKCalcPriAndSign(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, int certType, int datatype, unsigned int i, unsigned int j, unsigned char* ck,
                                    unsigned char *signSeedPriFid, unsigned char* component, unsigned char* e, unsigned char *inData, int inLen, unsigned char* signData, int *outLen);

/**
* @brief ������Կ��չ˽Կǩ��
*
* @param[in] hHandle		�豸���
* @param[in] asymalg		�ǶԳ��㷨����0_SM2, 1_ECDSA
* @param[in] symalg			�Գ��㷨����  ����������Ĭ��0
* @param[in] i				����ֵi
* @param[in] j				����ֵj
* @param[in] ck				��ʼ��������ǩ����Կ��չ�����ck
* @param[in] signSeedPriFid ����ǩ��˽Կid
* @param[in] in				�������ݣ�SM2�㷨ʱΪԤ���������ݣ�ECDSA�㷨ʱΪsha256֮���hash����
* @param[out] out			ǩ��ֵ
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_BKPrikeySign(XKF_HANDLE hHandle, unsigned char asymalg, unsigned char symalg, unsigned int i, unsigned int j, unsigned char* ck, unsigned char *signSeedPriFid, unsigned char* in, unsigned char* out);

/**
* @brief ECC��Կ����
*  XDJA���Ľṹ�� 0x04 | x(32B) | y(32B) | ���� | HASH(32B)
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        SM2��ԿID�����ֽڣ��ڶ����ֽ���Ч ��Ϊ0x00 0x00��ʾ��Կ�����ݴ���
* @param[in] sm2pubkey       ��Կ,��pubkeyidΪ0x00 0x00ʱ��Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����158
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ�����,���峤������Ϊdlen+97
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ECIESEncrypt(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ECC_PUBKEY sm2pubkey, const unsigned char *pDatain, int dlen, unsigned char *pDataout,unsigned int *outLen);

/**
* @brief SM2˽Կ����
*
* @param[in] hHandle         �豸���
* @param[in] prikeyid        SM2˽ԿID ���ֽڣ��ڶ����ֽ���Ч
* @param[in] pDatain         ��������,��󳤶Ȳ�����SM2_BLOCK_MAX+97
* @param[in] dlen            ���ݳ���
* @param[out] pDataout       ���ܺ����������,����������Ϊdlen-97
* @param[out] outlen         ���ܺ����ݳ���
*
* @return ������
* @retval XKR_OK        �ɹ�
* @retval XKR_NO_POWER  Ȩ�޲���
*/
XDJAKEYAPI int XKF_ECIESDecrypt(XKF_HANDLE hHandle, const unsigned char *prikeyid, const unsigned char *pDatain, int dlen, unsigned char *pDataout,unsigned int *outlen);

/************************************************************************/
/*оƬ�͹�����ؽӿ�                                                    */
/************************************************************************/

/**
* @brief оƬ��������
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ChipEnterSleep(XKF_HANDLE hHandle);

/**
* @brief оƬ���볬�͹���
*
* @param[in] hHandle �豸���
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ChipEnterLowPower(XKF_HANDLE hHandle);

/**
* @brief оƬ�˳�����
*
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ChipExitSleep();

/**
* @brief �����ļ�
* ����:���е�ǰĿ¼�£������ļ���Ȩ��
*
* @param[in] hHandle �豸���
* @param[in] pFile   XDJA_CONTAINER_FILE�ļ����Խṹ
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_CreateContainerFile(XKF_HANDLE hHandle, PXDJA_CONTAINER_FILE pFile);

/**
* @brief SPI������Ϣ
* ÿ�����̴��豸ǰ��Ҫ����һ��
*
* @param[int] config ������Ϣ
*
* @return ������
* @retval XKR_OK �ɹ�
*/

XDJAKEYAPI int XKF_SPI_CONFIG(XDJA_SPI_CONFIG config);

/***********************************************************************/
/*EDDSA��ؽӿ�                                                        */
/***********************************************************************/
/**
* @brief ����ED25519��Կ�ԣ�Ŀǰ��֧����Կ�����ķ�ʽ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��Կ�ļ�ID,Ϊ0x00 0x00ʱ��ʾ��Կ��������
* @param[in] prikeyid        ˽Կ�ļ�ID,��˽ԿID��Ϊ0x00 0x00ʱ��ʾ˽Կ��������
* @param[out] pubkeyED25519��Կ�ṹ����Կ�ļ�IDΪ0x00 0x00ʱ��Ч
* @param[out] prikeyED25519˽Կ�ṹ����˽Կ�ļ�ID��Ϊ0x00 0x00ʱ��Ч
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_GenED25519KeyPair(XKF_HANDLE hHandle, const unsigned char *pubkeyid, const unsigned char *prikeyid, PXDJA_ED25519_PUBKEY pubkey, PXDJA_ED25519_PRIKEY prikey);

/**
* @brief ED25519����ǩ��
*
* @param[in] hHandle         �豸���
* @param[in] pubkey       ED25519��Կ�ṹ
* @param[in] prikeyid        ˽ԿID��Ŀǰ��֧�ֿ���˽Կ���뷽ʽ�������ֶδ���"\x00\x00"
* @param[in] prikey             ED25519˽Կ�ṹ
* @param[in] pDatain         ��ǩ������
* @param[in] dataLen         ��ǩ�����ݳ���
* @param[out] signData       ���ǩ������,���������ȹ̶�64�ֽ�
*
* @return ������
* @retval XKR_OK �ɹ�
*/
XDJAKEYAPI int XKF_ED25519Sign(XKF_HANDLE hHandle, PXDJA_ED25519_PUBKEY pubkey, const unsigned char *prikeyid, PXDJA_ED25519_PRIKEY prikey, const unsigned char *pDatain, unsigned int dataLen, unsigned char *signData);

/**
* @brief ED25519����ǩ����֤
*
* @param[in] hHandle         �豸���
* @param[in] pubkeyid        ��ԿID��Ŀǰ��֧�ֿ��⹫Կ���뷽ʽ�������ֶδ���"\x00\x00"
* @param[in] pubkey       ǩ���ù�Կ����pubkeyidΪ0x00 0x00ʱʹ��
* @param[in] pDatain         ��ǩ������
* @param[in] dataLen         ��ǩ�����ݳ���
* @param[in] signData        ��ǩ���ݣ��̶�64�ֽ�
*
* @return ������
* @retval XKR_OK        �ɹ�
*/
XDJAKEYAPI int XKF_ED25519SignVerify(XKF_HANDLE hHandle, const unsigned char *pubkeyid, PXDJA_ED25519_PUBKEY pubkey, const unsigned char *pDatain, unsigned int dataLen, unsigned char *signData);

/***********************************************************************/
/*�������������ģ��ר�ýӿ�                                           */
/***********************************************************************/
//XDJAKEYAPI int XKF_VHSMInitModule( int devType, unsigned char* pin, int plen );
#ifdef __cplusplus
}

#endif

#endif

