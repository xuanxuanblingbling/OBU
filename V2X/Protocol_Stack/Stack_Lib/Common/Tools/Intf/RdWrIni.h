/*
 * RdWrIni.h
 *
 *  Created on: Aug 16, 2019
 *      Author: ljm
 */

#ifndef HTTP_RDWRINI_H_
#define HTTP_RDWRINI_H_

#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <pthread.h>
#define FALSE 0
#define TRUE  1
#define MAX_PATH 260
typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned long  DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;
#define Min(a,b) (((a)<(b))?(a):(b))

BOOL CopyFile(LPCSTR lpExistingFileName, // name of an existing file
			  LPCSTR lpNewFileName,      // name of new file
			  BOOL bFailIfExists         // operation if file exists
			  );

INT	GetLine(LPSTR pLine, DWORD dwOffset, DWORD dwSize);
BOOL IsComment(LPCSTR pLine);
BOOL IsSection(LPCSTR pLine) ;
BOOL IsSectionName(LPCSTR pLine, LPCSTR pSection);
BOOL IsKey(LPSTR pLine , LPCSTR pKeyName, LPSTR* pValue, DWORD* dwValLen );
DWORD GetString( LPCSTR lpAppName,LPCSTR lpKeyName,
                LPSTR lpReturnedString, DWORD nSize,LPCSTR lpFileName);
INT ReadIniFile(LPCSTR lpFileName);

extern DWORD GetPrivateProfileString(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpDefault,
    LPSTR  lpReturnedString,
    DWORD   Size,
    LPCSTR lpFileName );

UINT GetPrivateProfileInt(
  LPCSTR lpAppName,
  LPCSTR lpKeyName,
  INT nDefault,
  LPCSTR lpFileName );

void WriteLine(INT hOutput , LPCSTR pLine);

BOOL WritePrivateProfileString(
  LPCSTR lpAppName,
  LPCSTR lpKeyName,
  LPCSTR lpString,
  LPCSTR lpFileName);

BOOL WritePrivateProfileInt(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    INT     Value,
    LPCSTR lpFileName) ;

void WriteValue(INT fdOutput, LPCSTR pAppName, LPCSTR pKeyName, LPCSTR pString);
extern int  ReadConfigData( LPCSTR ConfigAppName,LPCSTR ConfigKeyName,
 LPSTR ConfigReturnedString, DWORD ConfigSize,LPCSTR ConfigFileName);
extern int  WriteConfigData( LPCSTR ConfigAppName,LPCSTR ConfigKeyName,
 LPSTR ConfigValue,LPCSTR ConfigFileName);
extern char g_pData[40960];


#endif /* HTTP_RDWRINI_H_ */