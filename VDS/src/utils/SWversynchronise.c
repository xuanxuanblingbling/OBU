#include "stdio.h"
#include "cJSON.h"
#include <sys/stat.h>
#include <unistd.h>
#include "stdlib.h"
#include <fcntl.h>
//#include "SimpleIni.h"
#include "file.h"

#define  DatePos 16

#define  VDS  "VDS"
#define  NET  "NET"
#define  SYS  "SYS"
#define  APP  "APP"
#define  V2X  "V2X"

enum {
	ERR_FILEOPEN = 10,
    ERR_FILEREAD,
	ERR_FILETOJSON,
	ERR_GETKEYNAME,
	ERR_MOUDLENAME,
	ERR_VERSIONCHANGED,
	ERR_JSONTOSTRING,
	ERR_FILEWRITE
};

/*********************
 * @ name: int SW_versionsync()
 * @ describe: synconors the software version to json file
 * @ input: module : the software module name
 *          swversion:the software version
 * @ output: NULL
 * @ return: 0 : function execute successly
 *           1 :function execute failed
 * ============================
 * write by cbs 20201123
 * ********************/
int SW_versionHASHSUM(void)
{
    const char *pfilename = "/mnt/APP/Config/obu/DevInfo/DevInfo.json";
	const char *OBUInfofile = "/mnt/APP/Config/obu/net/Config_OBUInfo.ini";
    int ret = 0;
	int SUM = 0;
    char tmpstring[16] = {0}; 
    char hashstring[200] = {0};
	int  lc = 0;
	int  versionlen = 22;
	unsigned  int hash = 0;
	char *phashstr = hashstring;
	char resultstring[20] = {0};
	char l_version[64] ={0};
	int SoftWareDate[5] = {0};
	int SoftWareDateMax = 0;   
	int fd = open(pfilename,02);
	int i = 0;
	if(0 == fd)
	{
		ret = ERR_FILEOPEN;
		return ret;
	}
    
	struct stat l_buf;
	if((fstat(fd,&l_buf)) < 0)
	{ /* return*/}
     
    char * l_pfilebuf =NULL ;
	l_pfilebuf = (char *)malloc((size_t)(l_buf.st_size)+1);
    
    if(read(fd,l_pfilebuf,l_buf.st_size)<=0)
	{
		ret = ERR_FILEREAD;
		goto ERR_EXIT;
	}

    printf("=== [test] file data \n : %s ==\n",l_pfilebuf);
    // 修改 json数据
	cJSON *pfiledatajson = cJSON_Parse(l_pfilebuf);
	if(NULL == pfiledatajson)
	{
        ret = ERR_FILETOJSON;
		goto ERR_EXIT;	
	}
	cJSON *pAppSoftware = cJSON_GetObjectItem(pfiledatajson,"ApplicationSoftwareVersion");
    if(NULL == pAppSoftware)
	{
        ret = ERR_GETKEYNAME;
		goto ERR_EXIT;	
	}   
	
	cJSON *pVDSVersion = cJSON_GetObjectItem(pAppSoftware,VDS);
	if(NULL == pVDSVersion)
	{
        ret = ERR_MOUDLENAME;
		goto ERR_EXIT;	
	}
	memcpy(tmpstring,&pVDSVersion->valuestring[DatePos],6); 
    SUM += atoi(tmpstring);
	memcpy(tmpstring,&pVDSVersion->valuestring[11],8);
	SoftWareDate[0] = atoi(tmpstring);
	printf("=== [test] VDS Date is : %d  \n :==\n",SoftWareDate[0]); 
	memcpy(&hashstring[lc],pVDSVersion->valuestring,versionlen);
    lc += versionlen;

	cJSON *pNETVersion = cJSON_GetObjectItem(pAppSoftware,NET);
	if(NULL == pNETVersion)
	{
        ret = ERR_MOUDLENAME;
		goto ERR_EXIT;	
	}
    memcpy(tmpstring,&pNETVersion->valuestring[DatePos],6);
    SUM += atoi(tmpstring);
	memcpy(tmpstring,&pNETVersion->valuestring[11],8);
	SoftWareDate[1] = atoi(tmpstring);
	printf("=== [test] NET Date is : %d  \n :==\n",SoftWareDate[1]); 
	memcpy(&hashstring[lc],&pNETVersion->valuestring[0],versionlen);
	lc += versionlen;

	cJSON *pSYSVersion = cJSON_GetObjectItem(pAppSoftware,SYS);
	if(NULL == pSYSVersion)
	{
        ret = ERR_MOUDLENAME;
		goto ERR_EXIT;	
	}
	memcpy(tmpstring,&pSYSVersion->valuestring[DatePos],6);
    SUM += atoi(tmpstring);
	memcpy(tmpstring,&pSYSVersion->valuestring[11],8);
	SoftWareDate[2] = atoi(tmpstring);
	printf("=== [test] SYS Date is : %d  \n :==\n",SoftWareDate[2]);     
	memcpy(&hashstring[lc],&pSYSVersion->valuestring[0],versionlen);
	lc += versionlen;

	cJSON *pV2XVersion = cJSON_GetObjectItem(pAppSoftware,V2X);
	if(NULL == pV2XVersion)
	{
        ret = ERR_MOUDLENAME;
		goto ERR_EXIT;	
	}
    memcpy(tmpstring,&pV2XVersion->valuestring[DatePos],6);
    SUM += atoi(tmpstring);
	memcpy(tmpstring,&pV2XVersion->valuestring[11],8);
	SoftWareDate[3] = atoi(tmpstring);
	printf("=== [test] V2X Date is : %d  \n :==\n",SoftWareDate[3]);     
	memcpy(&hashstring[lc],&pV2XVersion->valuestring[0],versionlen);
	lc += versionlen;
    
	printf("=== [test] SUM   %d  \n :==\n",SUM);
	// string hash calculat
	for(int i = 0; i< lc; i++ )  
    {   
        hash = (*phashstr++) + (hash << 6) + (hash << 16) - hash;
    } 
	SoftWareDateMax = SoftWareDate[0];
	for ( i = 0; i < 5; i++)
	{
		if (SoftWareDateMax < SoftWareDate[i])
		{
			SoftWareDateMax = SoftWareDate[i];
		}
	}
    //close file and free memery
	close(fd);
    free(l_pfilebuf);
	printf("=== [test] HASH   %x  \n ",hash);
    //copy Max SortWare Max Date 
	sprintf(tmpstring,"%d-",SoftWareDateMax);
	memcpy(&resultstring,tmpstring,9); 
	printf("=== [test] SoftWare Max Date Date is : %s\n",resultstring);     	 
    //copy hash value 
    sprintf(tmpstring,"%08x",hash);
	printf("=== [test] resultstring-2   %s  \n :==\n",tmpstring);
	memcpy(&resultstring[9],tmpstring,8);
	printf("=== [test] resultstring-3   %s  \n :==\n",resultstring);
    ret = ConfigGetKey(OBUInfofile, "ObuBaseInfo", "AppVersion", l_version);
	printf("=== [test] l_version   %s    ==%d  \n :==\n",l_version , ret);
	memcpy(&l_version[14],resultstring,17);
	printf("=== [test] l_version   %s  \n :==\n",l_version);
	ConfigSetKey(OBUInfofile, "ObuBaseInfo", "AppVersion", l_version);
    return ret;
ERR_EXIT:
    close(fd);
    free(l_pfilebuf);
	return ret;
}


/*********************
 * @ name: int SW_versionsync()
 * @ describe: synconors the software version to json file
 * @ input: module : the software module name
 *          swversion:the software version
 * @ output: NULL
 * @ return: 0 : function execute successly
 *           1 :function execute failed
 * ============================
 * write by cbs 20201123
 * ********************/

int SW_versionsync(char * modulename, char * sw_version)
{
    const char *pfilename = "/mnt/APP/Config/obu/DevInfo/DevInfo.json";
    int ret = 0;

	int fd = open(pfilename,02);
	if(0 == fd)
	{
		ret = ERR_FILEOPEN;
		return ret;
	}

	struct stat l_buf;
	if((fstat(fd,&l_buf)) < 0)
	{ /* return*/}
     
    char * l_pfilebuf =NULL ;
	l_pfilebuf = (char *)malloc((size_t)(l_buf.st_size)+1);
    
    if(read(fd,l_pfilebuf,l_buf.st_size)<=0)
	{
		ret = ERR_FILEREAD;
		goto ERR_EXIT;
	}
    printf("=== [test] file data \n : %s ==\n",l_pfilebuf);
    // 修改 json数据
	cJSON *pfiledatajson = cJSON_Parse(l_pfilebuf);
	if(NULL == pfiledatajson)
	{
         ret = ERR_FILETOJSON;
		 goto ERR_EXIT;	
	}
	cJSON *pAppSoftware = cJSON_GetObjectItem(pfiledatajson,"ApplicationSoftwareVersion");
    if(NULL == pAppSoftware)
	{
         ret = ERR_GETKEYNAME;
		 goto ERR_EXIT;	
	}
	cJSON *pModuleSoftware = cJSON_GetObjectItem(pAppSoftware,modulename);
	if(NULL == pModuleSoftware)
	{
         ret = ERR_MOUDLENAME;
		 goto ERR_EXIT;	
	}
    
	if(cJSON_ReplaceItemInObject(pAppSoftware,modulename,cJSON_CreateString(sw_version)) < 0)
	{
	    ret = ERR_VERSIONCHANGED;
		goto ERR_EXIT;	
	}

    // 修改后json数据 存入文件
	char *l_pnewfiledata = cJSON_Print(pfiledatajson);
	if(l_pnewfiledata == NULL)
	{
         ret = ERR_JSONTOSTRING;
		 goto ERR_EXIT;			
	}
    printf("=== [test] file data \n : %s ==\n",l_pnewfiledata);
    //if(fwrite(l_pnewfiledata,strlen(l_pnewfiledata),1,fd) < 0)
    
    ftruncate(fd,0);      //清空文件
    lseek(fd,0,SEEK_SET);  //重新设置文件偏移量
    if(write(fd,l_pnewfiledata,strlen(l_pnewfiledata)) <= 0)
	{
		ret = ERR_FILEWRITE;
		goto ERR_EXIT;
	}
	close(fd);
    free(l_pfilebuf);

    SW_versionHASHSUM();

    return ret;

ERR_EXIT:
    close(fd);
    free(l_pfilebuf);
	return ret;
}
