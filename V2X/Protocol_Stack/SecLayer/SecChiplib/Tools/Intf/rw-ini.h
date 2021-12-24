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
#define TRUE 1
#define MAX_PATH 260
#define Min(a, b) (((a) < (b)) ? (a) : (b))

typedef char *LPSTR;
typedef const char *LPCSTR;
typedef unsigned long DWORD;
typedef int BOOL;
typedef int INT;
typedef unsigned int UINT;
typedef unsigned char BYTE;

//extern
DWORD SecGetPrivateProfileString(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    LPCSTR lpDefault,
    LPSTR lpReturnedString,
    DWORD Size,
    LPCSTR lpFileName);

UINT SecGetPrivateProfileInt(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    INT nDefault,
    LPCSTR lpFileName);

BOOL SecWritePrivateProfileInt(
    LPCSTR lpAppName,
    LPCSTR lpKeyName,
    INT Value,
    LPCSTR lpFileName);

//extern
int SecReadConfigData(LPCSTR ConfigAppName, LPCSTR ConfigKeyName,
                      LPSTR ConfigReturnedString, DWORD ConfigSize, LPCSTR ConfigFileName);

#endif /* HTTP_RDWRINI_H_ */