/*
 * RdWrInit.h
 *
 *  Created on: Aug 16, 2019
 *      Author: ljm
 */

#ifndef RDWRINIT_H_
#define RDWRINIT_H_


#include <stdio.h>
#include <unistd.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define FALSE 0
#define TRUE  1
#define MAX_PATH 260

#define Min(a,b) (((a)<(b))?(a):(b))
/*
static BOOL CopyFile(LPCSTR lpExistingFileName, // name of an existing file
              LPCSTR lpNewFileName,      // name of new file
              BOOL bFailIfExists         // operation if file exists
              );

static INT    GetLine(LPSTR pLine, DWORD dwOffset, DWORD dwSize);
static BOOL IsComment(LPCSTR pLine);
static BOOL IsSection(LPCSTR pLine) ;
static BOOL IsSectionName(LPCSTR pLine, LPCSTR pSection);
static BOOL IsKey(LPSTR pLine , LPCSTR pKeyName, LPSTR* pValue, DWORD* dwValLen );
static DWORD GetString( LPCSTR lpAppName,LPCSTR lpKeyName,
                LPSTR lpReturnedString, DWORD nSize,LPCSTR lpFileName);
static INT ReadIniFile(LPCSTR lpFileName);

static void WriteLine(INT hOutput , LPCSTR pLine);

static BOOL WritePrivateProfileString(
  LPCSTR lpAppName,
  LPCSTR lpKeyName,
  LPCSTR lpString,
  LPCSTR lpFileName);

static void WriteValue(INT fdOutput, LPCSTR pAppName, LPCSTR pKeyName, LPCSTR pString);

BOOL WritePrivateProfileInt(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    INT     Value,
    LPCSTR lpFileName) ;*/

//extern char g_pData;


#endif /* RDWRINIT_H_ */
