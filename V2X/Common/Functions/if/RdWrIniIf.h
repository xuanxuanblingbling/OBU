/*
 * RdWrInit_Interface.h
 *
 *  Created on: May 18, 2020
 *      Author: lyy
 */

#ifndef RDWRINIT_INTERFACE_H_
#define RDWRINIT_INTERFACE_H_

#include "MiscIf.h"


extern int  ReadConfigData( LPCSTR p_pn8ConfigAppName,LPCSTR p_pn8ConfigKeyName,LPCSTR p_pn8ConfigReturnValue, DWORD p_u64ConfigSize,LPCSTR p_pn8ConfigFileName);
extern int  WriteConfigData( LPCSTR p_pn8ConfigAppName,LPCSTR p_pn8ConfigKeyName,LPSTR p_pn8ConfigValue,LPCSTR p_pn8ConfigFileName);
extern DWORD GetPrivateProfileString(LPCSTR lpAppName,LPCSTR lpKeyName,LPCSTR lpDefault,LPSTR  lpReturnedString,DWORD   Size,LPCSTR lpFileName );
extern UINT GetPrivateProfileInt(LPCSTR lpAppName,LPCSTR lpKeyName,INT nDefault,LPCSTR lpFileName );

#endif /* RDWRINIT_INTERFACE_H_ */
