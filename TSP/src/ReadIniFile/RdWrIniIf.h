/*
 * RdWrInit_Interface.h
 *
 *  Created on: May 18, 2020
 *      Author: lyy
 */

#ifndef RDWRINIT_INTERFACE_H_
#define RDWRINIT_INTERFACE_H_

#include "MiscIf.h"

#define FALSE 0
#define TRUE  1

extern int  ReadConfigData( LPCSTR p_pn8ConfigAppName,LPCSTR p_pn8ConfigKeyName,LPSTR p_pn8ConfigReturnValue, DWORD p_u64ConfigSize,LPCSTR p_pn8ConfigFileName);
extern int  WriteConfigData( LPCSTR p_pn8ConfigAppName,LPCSTR p_pn8ConfigKeyName,LPSTR p_pn8ConfigValue,LPCSTR p_pn8ConfigFileName);
extern DWORD GetPrivateProfileString(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR  lpReturnedString,DWORD   Size,LPCSTR lpFileName );
extern UINT GetPrivateProfileInt(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault,LPCSTR lpFileName );
extern BOOL WritePrivateProfileString(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpString,LPCSTR lpFileName);
extern BOOL WritePrivateProfileInt(LPCSTR lpAppName,LPCSTR lpKeyName,INT     Value,LPCSTR lpFileName);
extern double GetPrivateProfileDouble(LPCSTR lpAppName,LPCSTR lpKeyName,double nDefault,LPCSTR lpFileName );

#endif /* RDWRINIT_INTERFACE_H_ */
