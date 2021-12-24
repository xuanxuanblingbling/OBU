/*
 * RdWrIni.c
 *
 *  Created on: Aug 16, 2019
 *      Author: ljm
 */


/********************************************************************
created:    2009/10/10
filename:   RdWrIni.cpp,RdWrIni.h
author:     YRC
purpose:    Read and Write Ini file
*********************************************************************/

#include "RdWrIni.h"
// LPSTR g_pData = NULL;    // xinchuang.xing
char g_pData[40960] = {'\0'};
/************************************************************************
**º¯Êý£ºCopyFile
**¹ŠÄÜ£ºThe CopyFile function copies an existing file to a new file.

**²ÎÊý£º
		lpExistingFileName[in] -Pointer to a null-terminated string
							    that specifies the name of an existing file.
		lpNewFileName[in]      - Pointer to a null-terminated string that specifies the name of the new file.
		bFailIfExists[in]      - Specifies how this operation is to proceed if a file of the same name as that
							      specified by lpNewFileName already exists.
								   If this parameter is TRUE and the new file already exists, the function fails.
									If this parameter is FALSE and the new file already exists,
									the function overwrites the existing file and succeeds.
**·µ»Ø£º
		TRUE - success
		FALSE - fail
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
************************************************************************/

BOOL CopyFile(LPCSTR lpExistingFileName, // name of an existing file
			  LPCSTR lpNewFileName,      // name of new file
			  BOOL bFailIfExists         // operation if file exists
			  )
{
	INT fdIn = 0, fdOut = 0;
	struct stat statinfo;
	DWORD dwSize =0;
	void *pSrc =NULL, *pDst = NULL;

	memset(&statinfo,0, sizeof(statinfo));
	if (!lpExistingFileName || !lpExistingFileName)
	{
		return FALSE;
	}

	fdIn = open(lpExistingFileName, O_RDONLY);
	if (fdIn<0)
	{
		perror("CopyFile open");
		return FALSE;
	}
	// get file info
	if (fstat(fdIn, &statinfo) < 0)
	{
		perror("CopyFile fstat ");
	}
	dwSize = statinfo.st_size;
	if (bFailIfExists)
	{
		fdOut = open(lpNewFileName, O_RDWR | O_CREAT | O_EXCL,S_IRWXU);
		if (fdOut== -1)
		{
			perror("CopyFile new file fail");
			return FALSE;
		}
	}
	else
	{
		fdOut = open(lpNewFileName, O_RDWR | O_CREAT |O_TRUNC,S_IRWXU);
		if (fdOut== -1)
		{
			perror("CopyFile new file fail ");
			return FALSE;
		}
	}
	if (lseek(fdOut, dwSize - 1, SEEK_SET) == -1)
	{
		perror("CopyFile lseek ");
		return FALSE;
	}

	if (write(fdOut, "", 1) != 1)
	{
		perror("the file isn't writable ");
		return FALSE;
	}
	if ((pSrc = mmap(NULL, dwSize, PROT_READ, MAP_SHARED, fdIn, 0)) == MAP_FAILED)
	{
		perror("mmap ");
		return FALSE;
	}
	if ((pDst = mmap(NULL, dwSize, PROT_READ|PROT_WRITE, MAP_SHARED, fdOut, 0)) == MAP_FAILED)
	{
		perror("mmap ");
		return FALSE;
	}
	memcpy(pDst,pSrc, dwSize);
	close(fdOut);
	close(fdIn);

//	if (pSrc)
//	{
//		free(pSrc);
//	}
//	if (pDst)
//	{
//		free(pDst);
//	}
//	printf("CopyFile exit\n");
	return TRUE;
}

/************************************************************************
**º¯Êý£ºGetLine
**¹ŠÄÜ£º»ñÈ¡ÔÚg_pDataÖÐŽÓdwOffsetÎ»ÖÃ¿ªÊŒµÄÒ»ÐÐÊýŸÝ²¢±£ŽæµœpLine£¬Í¬Ê±°ÑÆ«ÒÆÁ¿dwOffset
		ÒÆµœÏÂÒ»ÐÐÐÐÊ×
**²ÎÊý£º
		pLine[out]   - œÓÊÕÒ»ÐÐÊýŸÝ(²»°üÀš\r\n)
		dwOffset[in] - Òª¶ÁÈ¡µÄÄÇÒ»ÐÐµÄ¿ªÊŒÎ»ÖÃ
		dwSize[in]   - INIÎÄŒþŽóÐ¡
**·µ»Ø£º
		ÕýÈ· - ÏÂÒ»ÐÐÐÐÊ×µÄÎ»ÖÃ
		ŽíÎó - 0
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.19
**±ž×¢£º
************************************************************************/
INT	GetLine(LPSTR pLine, DWORD dwOffset, DWORD dwSize)
{
	int len = 0;
    int len2 = 0;
    // Look for the end of the line.
    while ( dwOffset + len < dwSize
        && '\r' != g_pData[dwOffset+len] && '\n' != g_pData[dwOffset+len])
    {
        if( g_pData[dwOffset+len]==0 )
            break;
        pLine[len] = g_pData[dwOffset+len] ;
        ++len;
    }

    pLine[len] = 0 ;
    // Now push the internal offset past the newline.
    // (We assume \r\n pairs are always in this order)
    if (dwOffset + len + len2 < dwSize && '\r' == g_pData[dwOffset+len+len2])
        ++len2;
    if (dwOffset + len + len2+1 < dwSize && '\n' == g_pData[dwOffset+len+len2])
        ++len2;
    if (2 >= len + len2 && (dwOffset +2 >=dwSize) )
        return 0;

    dwOffset += len + len2;
    return dwOffset;
}

/************************************************************************
**º¯Êý£ºIsComment
**¹ŠÄÜ£ºÅÐ¶ÏÊÇ²»ÊÇ×¢ÊÍÐÐ
**²ÎÊý£º
		pLine[in] - INIµÄÒ»ÐÐÊýŸÝ
**·µ»Ø£º
		1 - ×¢ÊÍÐÐ
		0 - ²»ÊÇ×¢ÊÍÐÐ
**±ž×¢£º
		1). ¿ÕÐÐÒ²ÊÓÎª×¢ÊÍÐÐ
************************************************************************/

BOOL IsComment(LPCSTR pLine)
{
	if (!pLine || 0 == strlen(pLine) || ';' == *pLine)
        return TRUE;
    return FALSE;
}

/************************************************************************
**函数：IsSection
**功能：判断是不是段名
**参数：
		pLine[in] - INI的一行数据
**返回：
		1 - 是段名
		0 - 不是
************************************************************************/
BOOL IsSection(LPCSTR pLine)
{
    if (pLine && '[' == *pLine)
        return TRUE;
    return FALSE;
}

/************************************************************************
**º¯Êý£ºIsSectionName
**¹ŠÄÜ£ºÅÐ¶ÏÊÇINIÎÄŒþµÄÒ»ÐÐ(pLine)ÊÇ²»ÊÇÒªÕÒµÄ¶ÎÃû(pSection)
**²ÎÊý£º
pLine[in]    - INIÎÄŒþµÄÒ»ÐÐÊýŸÝ
pSection[in] - ÒªÕÒµÄ¶ÎÃû
**·µ»Ø£º
1 - ÊÇ
0 - ²»ÊÇ
**±ž×¢£º
************************************************************************/
BOOL IsSectionName(LPCSTR pLine, LPCSTR pSection)
{
    if (IsSection(pLine))
    {
        DWORD len = strlen(pSection);
        if (strlen(pLine) - 2 == len && 0 == strncasecmp(pLine+1, pSection, len))
            return TRUE;
    }
    return FALSE;
}


/************************************************************************
**函数：IsKey
**功能：判断INI文件中一行的数据是不是要找的键名,如果是并读取键值
**参数：
		pLine[in] - INI文件某行数据
		pKeyName[in] - 要寻找的键名
		pValue[out] - 键值
		dwValLen[out] - 键值pValue大小(in bytes)
**返回：
		1 - 是，同时pValue返回键值
		0 - 不是，pValue为NULL
**作者：YRC
**日期：09.10.19
**备注：
************************************************************************/
BOOL IsKey(LPSTR pLine , LPCSTR pKeyName, LPSTR* pValue, DWORD* dwValLen )
{
    LPSTR pEqual = NULL;
    DWORD  len = 0;	//length = 0,

    if(!pLine || !pKeyName)
        return FALSE;

    // pLineÊÇ²»ÊÇ×¢ÊÍÐÐ
    if (IsComment( pLine ))
        return FALSE;

    // Ñ°ÕÒ"="ºÅ
    pEqual = strchr(pLine, '=' );
    if (!pEqual)
        return FALSE;

/*    // Ñ°ÕÒŒüÃû×îºóÒ»×Ö·ûµÄÎ»ÖÃ
    //while (pEqual - 1 >= pLine && iswspace(*(pEqual-1)))
	while(pEqual - 1 >= pLine && ((*(pEqual-1)) == ""))
//    while(pEqual - 1 >= pLine && ((*(pEqual-1)) == ' '))
        --pEqual;
    // Badly formed file.
    if (pEqual - 1 < pLine)
        return FALSE;

    // ŒüÃû³€¶È
    length = pEqual - pLine;*/

    len = strlen(pKeyName);
    //if (len == length && 0 == _wcsnicmp(pLine, pKeyName, len))
    if ( 0 == strncasecmp(pLine, pKeyName, len))
    {
        *pValue = strchr(pLine, '=' );
        ++(*pValue);
        *dwValLen = strlen(pLine) - ((*pValue) - pLine);

        // È¥µôœôžúÔÚ"="ºÅºóµÄËùÓÐ¿Õžñ
        //while (0 < *dwValLen && iswspace(**pValue))
//		while (0 < *dwValLen && ((**pValue) == ""))
        while (0 < *dwValLen && ((**pValue) == ' '))
        {
            ++(*pValue);
            --(*dwValLen);
        }
//        while (0 < *dwValLen && ((*pValue)[*dwValLen-1] == ""))
        while (0 < *dwValLen && ((*pValue)[*dwValLen-1] == ' '))
        {
            --(*dwValLen);
        }
        // If the string is surrounded by quotes, remove them.
        if ('"' == (**pValue))
        {
            ++(*pValue);
            --(*dwValLen);
            if ('"' == (*pValue)[*dwValLen-1])
            {
                --(*dwValLen);
            }
        }
        return TRUE;
    }
    else
    {
        *pValue = NULL;
        return FALSE;
    }
}

/************************************************************************
**函数：ReadIniFile
**功能：打开文件，并将文件数据拷贝到一缓冲区g_pData中
**参数：
		lpFileName[in] - INI文件名，如果没有路径，默认路径当前应用程序路劲
**返回：
		非0 - 该INI文件的大小(in bytes)
		0   - 失败
**作者：YRC
**日期：09.10.20
**备注：


************************************************************************/
INT ReadIniFile(LPCSTR lpFileName)
{
    int nReturn = 0;
	struct stat stat;
    int fdFile =0;
    DWORD dwSize =0 ;
    DWORD  bRet = 0; 
    //BOOL  bRet = FALSE; // bUnicode - ±êÖŸINIÎÄŒþÊÇ²»ÊÇUnicodeÎÄŒþ
    char* pData = NULL;
	char buf[255] = {0};


    if (!lpFileName)
    {
        nReturn = 0;
        goto exit;
    }

    // ReadIniFile the file.
	fdFile = open(lpFileName, O_RDONLY);
	if(fdFile < 0)
	{
		perror("Open file fail");
		nReturn = 0;
        goto exit;
	}
	//printf("+++++++fdFile = %d\n", fdFile);
	if(read(fdFile, buf,sizeof(buf))>0)
	{
//		printf("++++++buf :%s \n",buf);	//deleted by ljm
	}

    // Get its size.
	if((fstat(fdFile,&stat)) < 0)
	{
		nReturn = 0;
        goto exit;
	}

	dwSize = stat.st_size;

    // Next, load the data.
    //printf("ReadIniFile, the size of ini file [%s] is [%d]\n", lpFileName, dwSize);
    if (0 < dwSize)
    {
        pData = (char *)malloc((dwSize + sizeof(char)));
        if (!pData)
        {
			printf("ReadIniFile, no enough memory\n");
            nReturn = 0;
            goto exit;
        }
        memset(pData,0,dwSize + sizeof(char));
		lseek(fdFile, 0, SEEK_SET);
		bRet = read(fdFile, pData, dwSize);
        close(fdFile);
        if (bRet != dwSize)
        {
            printf("ReadIniFile, ReadFile fail, err = %s\n",strerror(errno));
            nReturn = 0;
            goto exit;
        }
		memcpy(&g_pData, pData, dwSize);
        dwSize--; // includes the NULL termination character
        nReturn = dwSize;
    }
	else
	{
		goto exit;
	}

    

exit:
    if(pData)
    {   //printf("ReadIniFile free\n");
        free(pData);
        pData = NULL;
    }
    if(fdFile)
    {
		//printf("ReadIniFile close\n");
        close(fdFile);
        fdFile = 0;
    }
	//printf("exit ReadIniFile\n");
    return nReturn;
}


/************************************************************************
**函数：GetString
**功能：读INI文件
**参数：
		lpAppName[in]         - 字段名
		lpKeyName[in]         - 键名
		lpReturnedString[out] - 键值
		nSize[in]             - 键值缓冲区大小(in characters )
		lpFileName[in]        - 完整的INI文件名
**返回：Returns the number of bytes read.
**作者：YRC
**日期：09.10.20
**备注：
************************************************************************/
DWORD GetString( LPCSTR lpAppName,LPCSTR lpKeyName,
                LPSTR lpReturnedString, DWORD nSize,LPCSTR lpFileName)
{
    DWORD dwSize , cchCopied;
    DWORD dwOffset = 0;
    char pLine[MAX_PATH] = {0} ;
    DWORD dwValLen = 0;

    if (!lpAppName || !lpFileName)
        return 0;

    //Žò¿ªÎÄŒþ£¬œ«ÎÄŒþÊýŸÝ¿œ±Žµœ»º³åÇøg_pDataÖÐ£¬·µ»ØINIÎÄŒþŽóÐ¡
    if (0 == (dwSize = ReadIniFile(lpFileName)))
    {
        return 0;
    }
    cchCopied = 0;
    while ( 0 != (dwOffset = GetLine( pLine , dwOffset , dwSize )))
    {
        //RETAILMSG(1,(_T("%s\n"),szLine));
        // ÊÇ²»ÊÇ×¢ÊÍÐÐ
        if (IsComment(pLine))
            continue;

        // ÊÇ²»ÊÇ¶ÎÃû
        if (IsSection(pLine))
        {
            // ÊÇ²»ÊÇÎÒÃÇÒªÕÒµÄ¶ÎÃû
            if (IsSectionName(pLine,lpAppName))
            {
                // Ñ°ÕÒÎÒÃÇÒªµÄŒüÃû
                while ( 0 != (dwOffset = GetLine(pLine , dwOffset , dwSize)))
                {
                    LPSTR pValue=NULL;

                    if (IsSection(pLine))
                        break;

                    if (IsKey(pLine , lpKeyName, &pValue, &dwValLen))
                    {
                        cchCopied = Min(dwValLen, nSize-1);
                        memcpy(lpReturnedString, pValue, cchCopied);
                        lpReturnedString[cchCopied] = '\0';//xinchuang.xing
                        // We're done.
                        break;
                    }
                }
                break;
            }
        }
    }
    return cchCopied;
}

/************************************************************************
**º¯Êý£ºGetPrivateProfileString
**¹ŠÄÜ£ºLINUXÏÂ¶ÁÈ¡INIÎÄŒþÖÐÄ³¶ÎÃû/ŒüÃûµÄŒüÖµµÄ×Ö·ûŽ®
**²ÎÊý£º
		lpAppName[in]         - points to section name
		lpKeyName[in]         - points to key name
		lpDefault[in]         - points to default string
		lpReturnedString[out] - points to destination buffer
		nSize[in]             - size of destination buffer "lpReturnedString"(in characters)
		lpFileName[in]        - points to initialization filename
**·µ»Ø£ºThe return value is the number of characters copied to the buffer,
		not including the terminating null character.
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
1). Èç¹ûINIÎÄŒþÃ»ÓÐÄã¹ØÐÄµÄÊýŸÝ£¬·µ»ØÄ¬ÈÏÖµlpDefault
************************************************************************/
DWORD GetPrivateProfileString(
							  LPCSTR lpAppName,
							  LPCSTR lpKeyName,
							  LPCSTR lpDefault,
							  LPSTR  lpReturnedString,
							  DWORD   Size,
							  LPCSTR lpFileName )
{
    DWORD dwRc = 0, dwReturn = 0;
    if(!lpAppName || !lpKeyName || !lpReturnedString || !lpFileName || Size<=0 )
        return 0;

    //pthread_mutex_lock(&g_MutexProtectOprIni);

    dwRc = GetString(lpAppName,lpKeyName,lpReturnedString,Size,lpFileName);
    if(dwRc != 0)
    {
        dwReturn = dwRc;
    }
    else
    {
        if(lpDefault)
        {
            memcpy(lpReturnedString, lpDefault, Size);
            lpReturnedString[Size-1] = '\0';//0;//NULL;
        }
        else
            *lpReturnedString = 0;
        dwReturn = strlen(lpReturnedString);
    }

    //pthread_mutex_unlock(&g_MutexProtectOprIni);

    return dwReturn;
}

/************************************************************************
**º¯Êý£ºGetPrivateProfileInt
**¹ŠÄÜ£º retrieves an integer associated with a key in the
		specified section of the given initialization file
**²ÎÊý£º
		LPCTSTR lpAppName,  // address of section name
		LPCTSTR lpKeyName,  // address of key name
		INT nDefault,       // return value if key name is not found
		LPCTSTR lpFileName  // address of initialization filename
**·µ»Ø£º
		The return value is the integer equivalent of the string following
		the specified key name in the specified initialization file. If the
		key is not found, the return value is the specified default value.
		If the value of the key is less than zero, the return value is zero.
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
************************************************************************/
UINT GetPrivateProfileInt(
						  LPCSTR lpAppName,
						  LPCSTR lpKeyName,
						  INT nDefault,
						  LPCSTR lpFileName )
{
    char szRet[80] ={0};
	DWORD cch =0;

    if(!lpAppName || !lpKeyName || !lpFileName )
        return 0;

    //pthread_mutex_lock(&g_MutexProtectOprIni);

    cch = GetString(lpAppName, lpKeyName, szRet, sizeof(szRet)/sizeof(char), lpFileName);

    //pthread_mutex_unlock(&g_MutexProtectOprIni);

    if (cch)
        return atoi(szRet);
    else
        return nDefault;
}

/************************************************************************
**º¯Êý£ºWriteLine
**¹ŠÄÜ£ºÏòÎÄŒþÐŽÈëÒ»ÐÐÊýŸÝ(°üÀš»Ø³µ»»ÐÐ·û)
**²ÎÊý£º
		hOutput[in] - ÒÑŽò¿ªµÄÎÄŒþŸä±ú
		pLine[in]   - ÒªÐŽÈëµÄÒ»ÐÐÊýŸÝ
**·µ»Ø£ºNONE
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
		1). ÐŽÈëÒ»ÐÐÊýŸÝ£¬Ò²°üÀšÐŽÈëÐÐÄ©µÄ"\r\n"Áœžö×Ö·û
		3). ×¢Òâ²»Òªœ«œáÊø·ûÒ²ÐŽÈëÎÄŒþ
************************************************************************/
void WriteLine(INT hOutput , LPCSTR pLine)
{
	if (pLine)
	{
		write(hOutput, pLine, strlen(pLine)*sizeof(char));
		write(hOutput, "\r\n", 2*sizeof(char));
	}
}

/************************************************************************
**函数：WritePrivateProfileString
**功能：LINUX环境下，向指定INI文件指定段名写入字符串数据
**参数：
		lpAppName[in]
		Pointer to a null-terminated string containing section name. If
		the section does not exit, it is created.
		lpKeyName[in]
		Pointer to a null-terminated string containing key name. If the
		key does not exit in the specified section pointed to by the lpAppName
		parameter, it's created. If this parameter is NULL, the ertire section,
		including all keys within the section, is deleted. When deleting a
		section, leave the comments intact.
		lpString[in]
		pointer to a null-terminated string to be written to the file.
		If this parameter is NULL, the key pointed to by the lpKeyName
		parameter is deleted.
		lpFileName[in]
		Pointer to a null-terminated string that names the initialization file.
**返回：
		FALSE - fail
		TRUE  - success
**作者：YRC
**日期：09.10.20
**备注：
		1). 先将要修改的INI文件的全部数据读取到全局内存g_pData中
		2). 在g_pData中定位到我们要修改的位置，将其它数据和我们修改的数据写入一临时ini文件
		3). 最后将临时ini文件覆盖原来的ini文件，再删除临时ini文件
		4). 主要的API函数：
		creat、lseek、close、remove、open、mmap
		5). 如果lpKeyName == NULL, 删除整个段, 如果lpString == NULL, 删除健
************************************************************************/
BOOL WritePrivateProfileString(
							   LPCSTR lpAppName,
							   LPCSTR lpKeyName,
							   LPCSTR lpString,
							   LPCSTR lpFileName)
{
    DWORD dwSize, dwOffset;                // dwSize - iniÎÄŒþŽóÐ¡, dwOffset - Æ«ÒÆÁ¿
    BOOL  bReadLine = TRUE;
    BOOL  bWrote = FALSE;
    char pszLine[MAX_PATH] = {0};         // ŽæŽ¢Ò»ÐÐµÄÊýŸÝ
    char pszIniFileTemp[MAX_PATH] = {0};  // ÁÙÊ±iniÎÄŒþµÄÃû³Æ(°üÀšÂ·Ÿ¶)
    INT  fdOutputFile ;
    LPSTR pValue;
    DWORD dwValLen;

    dwOffset = 0;
    if (!lpFileName)
        return FALSE;

    //pthread_mutex_lock(&g_MutexProtectOprIni);

    // ¶ÁÈ¡INIÎÄŒþÄÚÈÝµœÈ«ŸÖ±äÁ¿g_pDataÄÚŽæÖÐ
    dwSize = ReadIniFile(lpFileName);

    //RETAILMSG(1, (TEXT("lpFileName=[%s], dwSize=[%d]"), lpFileName, dwSize));

    // Create the output file.
    //wcscpy(pszIniFileTemp, lpFileName);

    sprintf(pszIniFileTemp, "%s.ini.tmp",lpAppName);
//	printf("pszIniFileTemp = %s\n", pszIniFileTemp);

    fdOutputFile = creat(pszIniFileTemp, S_IRWXU| S_IRWXO |S_IRWXG);
    //fdOutputFile = open(pszIniFileTemp, O_CREAT | O_TRUNC | O_WRONLY);

    if (-1 == fdOutputFile)
    {
        perror("Could not open output file");

        //pthread_mutex_unlock(&g_MutexProtectOprIni);
        return FALSE;
    }

    // œ«ËùÓÐÊýŸÝÐŽÈëÁÙÊ±iniÎÄŒþ
    for (;;)
    {
        // The bReadLine flag is used to not read a new line after we break
        // out of the inner loop. We've already got a line to process.
        if (bReadLine)
        {
            dwOffset = GetLine( pszLine , dwOffset , dwSize );
            if (!dwOffset)
			{
				//printf("dwOffset = %d \n", dwOffset);
                break;
			}
        }
        bReadLine = TRUE;
        // Skip past comments.
        if (IsComment(pszLine))
        {
            WriteLine(fdOutputFile , pszLine);
            continue;
        }
        // Found a section name.
        if (IsSection(pszLine))
        {
            // It's the section we want.
            if (IsSectionName(pszLine , lpAppName))
            {
                // ÒÔÏÂÈç¹ûlpKeyNameÎªNULL£¬ÉŸ³ýÕûžö¶Î
                if (lpKeyName)
                    WriteLine(fdOutputFile , pszLine);

                // Process the whole section.
                while (0 != (dwOffset = GetLine( pszLine , dwOffset , dwSize )))
                {
                    // Reached the end of the section.
                    if (IsSection(pszLine))
                    {
                        bReadLine = FALSE;
                        // This line will be written in the outer loop.
                        break;
                    }
                    // When deleting a section, leave the comments intact.
                    else if (IsComment(pszLine))
                    {
                        WriteLine(fdOutputFile , pszLine);
                        continue;
                    }
                    // Got the value we want.
                    if (!bWrote && IsKey(pszLine , lpKeyName, &pValue, &dwValLen))
                    {
                        bWrote = TRUE;
                        // Èç¹ûlpStringÎªNULL£¬ÉŸ³ýœ¡lpKeyName
                        if(lpString)
                            WriteValue(fdOutputFile , NULL, lpKeyName, lpString);
                    }
                    else
                    {
                        if (lpKeyName)
                            WriteLine(fdOutputFile , pszLine);
                    }

                    if(dwOffset >= dwSize)
                        break ;
                }

                // Èç¹ûÔÚ¶ÎÃûlpAppNameÏÂŒüÃûlpKeyName²»ŽæÔÚ£¬ÔòÐÂœšŒüÃûlpKeyNameºÍŒüÖµlpString
                if (!bWrote)
                {
                    bWrote = TRUE;
                    WriteValue(fdOutputFile, NULL, lpKeyName, lpString);
                }
            }
            else
                WriteLine(fdOutputFile , pszLine);
        }
        else
            WriteLine(fdOutputFile , pszLine);

        if(dwOffset ==0)
            break;
    }

    // Èç¹ûÖž¶šµÄ¶ÎÃûlpAppName²»ŽæÔÚ£¬ÔòÐÂœš¶ÎÃûlpAppNameŒ°ŒüÃûlpKeyNameºÍŒüÖµlpString
    if (!bWrote && lpKeyName && lpString)
    {
		printf("create key! lpAppName = %s, lpKeyName = %s , lpString =%s \n",lpAppName,lpKeyName,lpString);
        WriteValue(fdOutputFile , lpAppName, lpKeyName, lpString);
    }

    // ÓÃÁÙÊ±iniÎÄŒþž²žÇÔ­ÀŽµÄiniÎÄŒþ²¢ÉŸ³ýÁÙÊ±iniÎÄŒþ
    if (-1 != fdOutputFile)
    {
        lseek(fdOutputFile, 0, SEEK_END);
        close(fdOutputFile);
        CopyFile(pszIniFileTemp, lpFileName, FALSE);
        if(remove(pszIniFileTemp) !=0)
		{
			perror("remove file fail ");
		}

    }
    //pthread_mutex_unlock(&g_MutexProtectOprIni);

    return TRUE;
}

/************************************************************************
**º¯Êý£ºWritePrivateProfileInt
**¹ŠÄÜ£ºLINUX»·Ÿ³ÏÂ£¬ÏòÖž¶šINIÎÄŒþÖž¶š¶ÎÃûÐŽÈëÕûÐÍÊýŸÝ
**²ÎÊý£º²Î¿ŒWritePrivateProfileStringº¯Êý
**·µ»Ø£º
		FALSE - fail
		TRUE  - success
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
************************************************************************/
BOOL WritePrivateProfileInt(
							LPCSTR lpAppName,
							LPCSTR lpKeyName,
							INT     Value,
							LPCSTR lpFileName)
{
    char ValBuf[16]={0};

    sprintf( ValBuf, "%d", Value);
    return( WritePrivateProfileString(lpAppName, lpKeyName, ValBuf, lpFileName) );
}

/************************************************************************
**º¯Êý£ºWriteValue
**¹ŠÄÜ£ºÏòÖž¶šINIÎÄŒþÖÐÐŽÈë¶ÎÃû¡¢ŒüÃûºÍŒüÖµ
**²ÎÊý£º
		m_hOutput[in]
		pointer to the handle of ini file.
		pAppName[in]
		Pointer to a null-terminated string containing the name of the section
		in which data is written. If this parameter is NULL, the WriteValue
		function just wirte the pKeyName and pString.
		pKeyName[in]
		Pointer to a null-terminated string containing the name of the key in
		which data is writtern.
		pString[in]
		Pointer to a null-terminated string to be written to the file.
**·µ»Ø£ºNONE
**×÷Õß£ºYRC
**ÈÕÆÚ£º09.10.20
**±ž×¢£º
		1). Òª³É¹ŠÐŽÈëINIÎÄŒþ£¬ŒüÃûpKeyNameºÍŒüÖµpString¶Œ²»ÄÜÎªNULL¡£
		2). Èç¹û¶ÎÃûpAppNameÎªNULL£¬ÔòÖ»ÐŽÈëŒüÃûpKeyNameºÍŒüÖµpString¡£
		3). ×¢ÒâÍùINIÎÄŒþÐŽÈë×Ö·ûŽ®Ê±£¬²»ÒªÐŽÈëœáÊø·û¡£
************************************************************************/
void WriteValue(INT fdOutput, LPCSTR pAppName, LPCSTR pKeyName, LPCSTR pString)
{

    if (pKeyName && pString)
    {
            if (pAppName)       
        {
			write(fdOutput, "[", sizeof(char));
			write(fdOutput, pAppName, strlen(pAppName)*sizeof(char));
			write(fdOutput, "]\r\n", 3*sizeof(char));
        }
		write(fdOutput, pKeyName, strlen(pKeyName)*sizeof(char));
		write(fdOutput, "=", sizeof(char));
		write(fdOutput, pString, strlen(pString)*sizeof(char));
		write(fdOutput, "\r\n", 2*sizeof(char));
    }
    else
    {
        //do nothing
    }   
}

/*
by xinchuang.xing
*/
int  ReadConfigData( LPCSTR ConfigAppName,LPCSTR ConfigKeyName,LPSTR ConfigReturnedString, DWORD ConfigSize,LPCSTR ConfigFileName)
{
    int nRet = 0;
    nRet = GetString(ConfigAppName,ConfigKeyName,ConfigReturnedString,ConfigSize,ConfigFileName);
    if (nRet == FALSE)
    {
        printf("Get Config Message Failed: %s\n",ConfigKeyName);
    }
    else
    {
        printf("Get %s Config Message Sccessed: %s\n",ConfigKeyName,ConfigReturnedString);
    }
    return nRet;
}

/*
by xinchuang.xing
*/
int  WriteConfigData( LPCSTR ConfigAppName,LPCSTR ConfigKeyName,LPSTR ConfigValue,LPCSTR ConfigFileName)
{
    BOOL nRet = 0;
    nRet = WritePrivateProfileString(ConfigAppName,ConfigKeyName,ConfigValue,ConfigFileName);
    if (nRet == FALSE)
    {
        printf("Write Config Message Failed: %s\n",ConfigKeyName);
    }
    else if(nRet == TRUE)
    {
        printf("%s Write %s Config Message Sccessed: %s\n",ConfigAppName,ConfigKeyName,ConfigValue);
    }
    else
    {
        printf("Write Config Message Failed: The return Value is invailed");
    } 
    return nRet;
}