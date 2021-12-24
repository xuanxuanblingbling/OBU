#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "SecLayer.h"


void usr_hex_dump(const char *str,unsigned char *data, int datalen)
{
    int i;

    printf("%s L=%d | ",str,datalen);
    for(i=0;i<datalen;i++)
    {
        if(0 == i%16) printf("\n  ");
        printf("%02x ", data[i]);
    }
    printf("\n");
}

static int32_t GetFileContent(unsigned char *file_path, unsigned char *pbBuf, int *nBufLen)
{
    long file_len = 0;
    FILE *fp = NULL;
    fp = fopen((const char *)file_path, "rb+");
    if (NULL == fp)
    {
        return -1;
    }
    fseek(fp, 0L, SEEK_END); // 读取文件长度
    file_len = ftell(fp);
    if (*nBufLen < file_len)
    {
        return -1;
    }
    *nBufLen = file_len;
    fseek(fp, 0L, SEEK_SET);
    fread(pbBuf, file_len, 1, fp); // 读取文件
    fclose(fp);
    return 0;
}

static int32_t SetFileContent(unsigned char *file_path, unsigned char *pbBuf, int nBufLen)
{
    FILE *fp = NULL;
    fp = fopen((const char *)file_path, "wb+");
    if (NULL == fp)
    {
        return -1;
    }
    fwrite(pbBuf, 1, nBufLen, fp); // 读取文件
    fclose(fp);
    return 0;
}


int main()
{
    int ret = 0;
    MsgLayData_st MsgLayData;
    MsgLayData.nAID = 111;
    memcpy(&MsgLayData.pu8MsgLayData,"abcdefghigklmn",9);
    MsgLayData.n32MsgLayDataLen = 9;
    MsgLayData.nEmergencyEventFlag = 0;
    MsgLayData.u8UseCerType = 2;
    MsgLayData.dLatitude = 0;
    MsgLayData.dLongitude = 0;

    ret = SecureLayerInit(0, NULL, "/mnt/APP/Config/Config_ProtocolStack.ini");
    if(ret != 0)
    {
        printf("test-SecureLayerInit-error\n");
        return -1;
    }
     printf("test-SecureLayerInit-ok\n");
    uint8_t pu8SecLayData[512] = {0};
    int32_t pn32SecLayDataLen = 512;
    ret = SignSecuredMessage(MsgLayData, pu8SecLayData, &pn32SecLayDataLen);
    printf("test-SignSecuredMessage-ret = %d\n,",ret);
    if(ret != 0)
    {
        printf("test-SignSecuredMessage-error\n");
    }
    printf("test-SignSecuredMessage--------ret = %d\n,",ret);
    usr_hex_dump("spdu",pu8SecLayData, pn32SecLayDataLen);
    // SetFileContent("./RSUsign", pu8SecLayData, pn32SecLayDataLen);
    printf("setFile-ok\n");

    MsgLayData_st outMsgLayData = {0};
    outMsgLayData.n32MsgLayDataLen = 9;
    outMsgLayData.nAID = 111;
    // GetFileContent("./RSUsign", pu8SecLayData, &pn32SecLayDataLen);
    ret = VerifySecuredMessage(pu8SecLayData, pn32SecLayDataLen, &outMsgLayData);
    if(ret != 0)
    {
        printf("test-VerifySecuredMessage-error\n");
    }
    printf("test-VerifySecuredMessage-ok\n");
    usr_hex_dump("pdu",outMsgLayData.pu8MsgLayData, outMsgLayData.n32MsgLayDataLen);

    ret = SecureLayerDeinit();
    if(ret != 0)
    {
        printf("test-VerifySecuredMessage-error\n");
    }
    printf("test-SecureLayerDeinit-ok\n");
    return 0;
}