#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "common.h"
#include "glib.h"
#include "glib/gprintf.h"
#include "wj_log.h"
#include "IWALL_V2X_API.h"

#define ARR_SIZE(arr) (sizeof(arr) / sizeof(arr[0]))    /*计算数组的大小*/

#define CERT_FILE_SUFFIX            ".oer"       /*证书文件后缀*/
#define KEY_FILE_SUFFIX             ".key"       /*秘钥文件后缀*/

#define ROOT_CERT_FILE_NAME     "ROOT.oer"

/*注册证书文件名,与根证书同一个目录*/
#define EA_CERT_FILE_NAME       "EA.oer"
#define EA_PUBKEY_FILE_NAME     "EA.pubkey"
#define EA_PRIKEY_FILE_NAME     "EA.prikey"
#define EA_KEY_ID               (0)

/*应用证书文件名,与根证书同一个目录*/
#define AA_CERT_FILE_NAME       "AA.oer"
#define AA_PUBKEY_FILE_NAME     "AA.pubkey"
#define AA_PRIKEY_FILE_NAME     "AA.prikey"
#define AA_KEY_ID               (21)

/*存放证书的目录，根证书单独存放在一个目录中，并且目前支持的是大唐的根证书*/
//#define CERT_MANUFACTURE_DATANG     "datang"     /*大唐证书目录*/
#define CERT_MANUFACTURE_IWALL     "iwall"     /*信长城证书目录*/
#define CERT_MANUFACTURE_GUOQI      "guoqi"      /*国汽证书目录*/
#define CERT_MANUFACTURE_HAUWEI     "huawei"     /*华为证书目录*/
#define ROOT_CERTFILE_DIRNAME       "root"       /*存放根证书的目录*/

/*证书文件名前缀*/
#define CERT_FILE_PREFIX_ROOT   "ROOT"  /*根证书*/
#define CERT_FILE_PREFIX_ACA    "ACA"   /*应用证书验证证书*/
#define CERT_FILE_PREFIX_PCA    "PCA"   /*假名证书验证证书*/
#define CERT_FILE_PREFIX_ECA    "ECA"   /*注册证书验证证书*/
#define CERT_FILE_PREFIX_EC     "EC"    /*注册证书*/
#define CERT_FILE_PREFIX_AC     "AC"    /*应用证书*/


struct ManufactureCertType {
    uint8_t *m_u8FactoryName;       /*厂商名称*/
    int32_t m_n32FactorSerialNO;    /*厂商对应的编号*/
};

struct CertType {
    uint8_t *m_u8CertName;      /*证书类型*/
    int32_t m_n32CertType;      /*证书对应的API中使用的类型*/
};

static struct ManufactureCertType s_FaCertType[] = {  /*证书厂家与其对应的编号*/
    {CERT_MANUFACTURE_IWALL, 0},
    {CERT_MANUFACTURE_GUOQI, 1},
    {CERT_MANUFACTURE_HAUWEI, 2},
    {ROOT_CERTFILE_DIRNAME, 0}
};

static struct CertType s_CertType[] = {   /*证书类型与其对应的编号*/
    {CERT_FILE_PREFIX_ROOT, 4},
    {CERT_FILE_PREFIX_ACA, 2},
    {CERT_FILE_PREFIX_PCA, 7},
    {CERT_FILE_PREFIX_ECA, 3}
};

/*将各厂家验证证书导入到芯片中*/
static int32_t write_certfile_to_chip(int8_t *dirpath, const int8_t *dirname)
{
    GDir *dir = NULL;
    int32_t l_n32FacNo = -1;
    int32_t l_n32CertType = -1;
    int32_t i = 0;
    const gchar *filename = NULL;
    gchar *abspath = NULL;
    gchar *filecontent = NULL;
    gsize contentsize = 0;

    for (i = 0; i < ARR_SIZE(s_FaCertType); i++)    /*确定证书厂商*/
    {
        if (0 == g_strcmp0(s_FaCertType[i].m_u8FactoryName, dirname))
        {
            l_n32FacNo = s_FaCertType[i].m_n32FactorSerialNO;
            break;
        }
    }

    if (-1 == l_n32FacNo)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "manufacture(%s) not support", dirname);
        return -1;
    }

    dir = g_dir_open(dirpath, 0, NULL);
    if(NULL == dir)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "directory %s open failed", dirpath);
        return -1;
    }

    while(filename = g_dir_read_name(dir))
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "file %s in %s", filename, dirpath);
        if(g_str_has_suffix(filename, CERT_FILE_SUFFIX))    /*写入证书文件*/
        {
            abspath = g_strjoin("/", dirpath, filename, NULL);
            for (i = 0; i < ARR_SIZE(s_CertType); i++)
            {
                if (g_str_has_prefix(filename, s_CertType[i].m_u8CertName))
                {
                    l_n32CertType = s_CertType[i].m_n32CertType;
                    break;
                }
            }

            if (-1 != l_n32CertType)
            {
                LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "fat NO:%d, cert type:%d", l_n32FacNo, l_n32CertType);
                if(g_file_get_contents(abspath, &filecontent, &contentsize, NULL))
                {
                    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "file size %d, name:%s", contentsize, abspath);

                    if (0 != IWALL_ImportRootCertificate(filecontent, contentsize, abspath, l_n32CertType, l_n32FacNo))
                    {
                        LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write %s to chip failed", filename);
                    }
                    g_free(filecontent);
                }
            }

            l_n32CertType = -1;
        }
    }

    g_dir_close(dir);
    return 0;
}

/*将根证书、注册证书、应用证书导入到芯片中*/
static int32_t write_ec_ac_cert_to_chip(int8_t *basedir)
{
    gchar *certfilecontent = NULL;
    gsize certcontentsize = 0;
    gchar *pubkeyfilecontent = NULL;
    gsize pubkeycontentsize = 0;
    gchar *prikeyfilecontent = NULL;
    gsize prikeycontentsize = 0;
    gchar *abspath = NULL;
    int32_t ea_key_id = EA_KEY_ID;
    int32_t aa_key_id = AA_KEY_ID;
    int32_t ret = 0;

    /*写入注册证书和key，先写入公私钥，再写入证书*/
    abspath = g_strjoin("/", basedir, EA_PUBKEY_FILE_NAME, NULL);
    if (0 == g_file_get_contents(abspath, &pubkeyfilecontent, &pubkeycontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT;
    }

    abspath = g_strjoin("/", basedir, EA_PRIKEY_FILE_NAME, NULL);
    if (0 == g_file_get_contents(abspath, &prikeyfilecontent, &prikeycontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT_1;
    }

    if(0 != IWALL_WriteKeyPairWithKeyID(ea_key_id, 0, prikeyfilecontent, 32, pubkeyfilecontent,64))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "iwall write ea key pair failed");
        goto EXIT_2;
    }

    abspath = g_strjoin("/", basedir, EA_CERT_FILE_NAME, NULL);
    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "ea file path:%s", abspath);
    if(0 == g_file_get_contents(abspath, &certfilecontent, &certcontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT_2;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "ea file size:%d", certcontentsize);
    if(0 != IWALL_ImportEnrollmentCredential(certfilecontent, certcontentsize))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "iwall write ec file failed");
        goto EXIT_3;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "import enrollment cert success");

    g_free(certfilecontent);
    g_free(prikeyfilecontent);
    g_free(pubkeyfilecontent);


    /*写入应用证书和key,先写入公私钥，再写入证书*/
    abspath = g_strjoin("/", basedir, AA_PUBKEY_FILE_NAME, NULL);
    if (0 == g_file_get_contents(abspath, &pubkeyfilecontent, &pubkeycontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT;
    }

    abspath = g_strjoin("/", basedir, AA_PRIKEY_FILE_NAME, NULL);
    if (0 == g_file_get_contents(abspath, &prikeyfilecontent, &prikeycontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT_1;
    }


    if (0 != IWALL_WriteKeyPairWithKeyID(aa_key_id, 0, prikeyfilecontent, 32, pubkeyfilecontent,64))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "iwall write key aa pair failed");
        goto EXIT_2;
    }

    abspath = g_strjoin("/", basedir, AA_CERT_FILE_NAME, NULL);
    if(0 == g_file_get_contents(abspath, &certfilecontent, &certcontentsize, NULL))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "get %s content failed", abspath);
        goto EXIT_2;
    }

    if (0 != IWALL_ImportAplicationCertificate(certfilecontent, certcontentsize))
    {
        LogPrint(LOG_LEVEL_EMERG, MODULE_NAME, "iwall write ac file failed");
        goto EXIT_3;
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "import application cert success");
    g_free(certfilecontent);
    g_free(prikeyfilecontent);
    g_free(pubkeyfilecontent);

    return 0;

EXIT_3:
    g_free(certfilecontent);
EXIT_2:
    g_free(prikeyfilecontent);
EXIT_1:
    g_free(pubkeyfilecontent);

EXIT:
    return -1;
}

/*将根证书导入到芯片中*/
static int32_t write_root_cert_to_chip(int8_t *basedir)
{
    gchar *certfilecontent = NULL;
    gsize certcontentsize = 0;
    gchar *abspath = NULL;

    /*写入根证书*/
    abspath = g_strjoin("/", basedir, ROOT_CERT_FILE_NAME, NULL);
    if(g_file_get_contents(abspath, &certfilecontent, &certcontentsize, NULL))
    {
        if (0 != IWALL_ImportRootCertificate(certfilecontent, certcontentsize, abspath, 4, 0))
        {
            LogPrint(LOG_LEVEL_ERR, MODULE_NAME, "write %s to chip failed", abspath);
            g_free(certfilecontent);
            return -1;
        }
        g_free(certfilecontent);
    }

    LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "write root cert success");


    return 0;
}

/*将系统中预置的证书导入到芯片中*/
static int32_t write_cert(int8_t *basedir)
{
    GDir *dir = NULL;
    const gchar *filename = NULL;
    gchar *abspath = NULL;

    /*导入一次后需要重新打开dir*/
    dir = g_dir_open(basedir, 0, NULL);
    if(NULL == dir)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME,"%s directory open failed", basedir);
        return -1;
    }

    /*优先写入根证书*/
    while (filename = g_dir_read_name(dir))
    {
        if (0 == g_strcmp0(ROOT_CERTFILE_DIRNAME, filename))
        {
            abspath = g_strjoin("/", basedir, filename, NULL);
            write_root_cert_to_chip(abspath);
            break;
        }
    }
    g_dir_close(dir);

    dir = g_dir_open(basedir, 0, NULL);
    if(NULL == dir)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME,"%s directory open failed", basedir);
        return -1;
    }
    /*写入其他证书到芯片中*/
    while(filename = g_dir_read_name(dir))
    {
        if (0 == g_strcmp0(ROOT_CERTFILE_DIRNAME, filename))
        {

            LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "find root,continue");
            continue;
        }
        abspath = g_strjoin("/", basedir, filename, NULL);
        if (g_file_test(abspath, G_FILE_TEST_IS_DIR))
        {
            write_certfile_to_chip(abspath, filename);
        }
        else
        {
            LogPrint(LOG_LEVEL_NOTICE, MODULE_NAME, "%s is a regular file, invalid in this dir", filename);
        }
    }
    g_dir_close(dir);

    dir = g_dir_open(basedir, 0, NULL);
    if(NULL == dir)
    {
        LogPrint(LOG_LEVEL_ERR, MODULE_NAME,"%s directory open failed", basedir);
        return -1;
    }
    /*导入注册证书和应用证书*/
    while (filename = g_dir_read_name(dir))
    {
        LogPrint(LOG_LEVEL_DEBUG, MODULE_NAME, "PATH:%s", filename);
        if (0 == g_strcmp0(ROOT_CERTFILE_DIRNAME, filename))
        {
            abspath = g_strjoin("/", basedir, filename, NULL);
            write_ec_ac_cert_to_chip(abspath);
            break;
        }
    }

    g_dir_close(dir);

    return 0;
}


int32_t ImportCertFilesToSecureChip(void)
{
    if(0 != write_cert(LOCAL_CERTFILE_DIR))
    {
        printf("------------write_cert err----------------\n");
        return -1;
    }

    return 0;
}

