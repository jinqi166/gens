/***************************************************************************
 * libgsft_w32u: Win32 Unicode Translation Layer.                          *
 * w32u_windowsx.h: windowsx.h translation. (common code)                  *
 *                                                                         *
 * Copyright (c) 2009 by David Korth.                                      *
 *                                                                         *
 * This program is free software; you can redistribute it and/or modify it *
 * under the terms of the GNU General Public License as published by the   *
 * Free Software Foundation; either version 2 of the License, or (at your  *
 * option) any later version.                                              *
 *                                                                         *
 * This program is distributed in the hope that it will be useful, but     *
 * WITHOUT ANY WARRANTY; without even the implied warranty of              *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 * GNU General Public License for more details.                            *
 *                                                                         *
 * You should have received a copy of the GNU General Public License along *
 * with this program; if not, write to the Free Software Foundation, Inc., *
 * 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.           *
 ***************************************************************************/

#ifndef GSFT_W32U_WINDOWSX_H
#define GSFT_W32U_WINDOWSX_H

#include "w32u.h"
#include "w32u_windows.h"
#include <windowsx.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Font macros. **/
#define GetWindowFontU(hwnd,hfont,fRedraw)	(HFONT)(UINT)(DWORD)(pSendMessageU((hwnd),WM_GETFONT,0,0))
#define SetWindowFontU(hwnd,hfont,fRedraw)	(void)(pSendMessageU((hwnd),WM_SETFONT,(WPARAM)(HFONT)(hfont),(LPARAM)(BOOL)(fRedraw)))

/** Button macros. **/
#define Button_GetCheckU(hwndCtl)		((int)(DWORD)pSendMessageU((hwndCtl),BM_GETCHECK,0,0))
#define Button_GetTextU(hwndCtl,lpch,cchMax)	pGetWindowTextU((hwndCtl),(lpch),(cchMax))
#define Button_GetTextLengthU(hwndCtl)		pGetWindowTextLengthU(hwndCtl)
#define Button_SetCheckU(hwndCtl,check)		((void)pSendMessageU((hwndCtl),BM_SETCHECK,(WPARAM)(int)(check),0))
#define Button_SetTextU(hwndCtl,lpsz)		pSetWindowTextU((hwndCtl),(lpsz))

/** ComboBox macros. **/
#define ComboBox_AddStringU(hwndCtl, lpsz)	((int)(DWORD)pSendMessageU_LPCSTR((hwndCtl),CB_ADDSTRING,CB_ADDSTRING,0,(LPARAM)(lpsz)))
#define ComboBox_GetCurSelU(hwndCtl)		((int)(DWORD)pSendMessageU((hwndCtl),CB_GETCURSEL,0,0))
#define ComboBox_GetTextLengthU(hwndCtl)	pGetWindowTextLengthU(hwndCtl)
#define ComboBox_ResetContentU(hwndCtl)		((int)(DWORD)pSendMessageU((hwndCtl),CB_RESETCONTENT,0,0))
#define ComboBox_SetCurSelU(hwndCtl,index)	((int)(DWORD)pSendMessageU((hwndCtl),CB_SETCURSEL,(WPARAM)(int)(index),0))
#define ComboBox_SetTextU(hwndCtl,lpsz)		pSetWindowTextU((hwndCtl),(lpsz))

/** Edit macros. **/
#define Edit_GetTextU(hwndCtl,lpch,cchMax)	pGetWindowTextU((hwndCtl),(lpch),(cchMax))
#define Edit_GetTextLengthU(hwndCtl)		pGetWindowTextLengthU(hwndCtl)
#define Edit_LimitTextU(hwndCtl,cchMax)		((void)pSendMessageU((hwndCtl),EM_LIMITTEXT,(WPARAM)(cchMax),0))
#define Edit_SetReadOnlyU(hwndCtl,fReadOnly)	((BOOL)(DWORD)pSendMessageU((hwndCtl),EM_SETREADONLY,(WPARAM)(BOOL)(fReadOnly),0))
#define Edit_SetTextU(hwndCtl,lpsz)		pSetWindowTextU((hwndCtl),(lpsz))

/** ListBox macros. **/
#define ListBox_AddStringU(hwndCtl,lpsz)		((int)(DWORD)pSendMessageU_LPCSTR((hwndCtl),LB_ADDSTRING,LB_ADDSTRING,0,(LPARAM)(lpsz)))
#define ListBox_DeleteStringU(hwndCtl,index)		((int)(DWORD)pSendMessageU((hwndCtl),LB_DELETESTRING,(WPARAM)(int)(index),0))
#define ListBox_GetCountU(hwndCtl)			((int)(DWORD)pSendMessageU((hwndCtl),LB_GETCOUNT,0,0))
#define ListBox_GetCurSelU(hwndCtl)			((int)(DWORD)pSendMessageU((hwndCtl),LB_GETCURSEL,0,0))
#define ListBox_GetItemDataU(hwndCtl,index)		((LRESULT)(DWORD)pSendMessageU((hwndCtl),LB_GETITEMDATA,(WPARAM)(int)(index),0))
extern int (WINAPI *pListBox_GetTextU)(HWND hwndCtl, int index, LPSTR lpszBuffer);
#define ListBox_GetTextLenU(hwndCtl,index)		((int)(DWORD)pSendMessageU((hwndCtl),LB_GETTEXTLEN,(WPARAM)(int)(index),0))
#define ListBox_InsertStringU(hwndCtl,index,lpsz)	((int)(DWORD)pSendMessageU_LPCSTR((hwndCtl), LB_INSERTSTRING, LB_INSERTSTRING, \
								(WPARAM)(int)(index), (LPARAM)(LPCTSTR)(lpsz)))
#define ListBox_ResetContentU(hwndCtl)			((BOOL)(DWORD)pSendMessageU((hwndCtl),LB_RESETCONTENT,0,0))
#define ListBox_SetCurSelU(hwndCtl,index)		((int)(DWORD)pSendMessageU((hwndCtl),LB_SETCURSEL,(WPARAM)(int)(index),0))
#define ListBox_SetItemDataU(hwndCtl,index,data)	((int)(DWORD)pSendMessageU((hwndCtl),LB_SETITEMDATA,(WPARAM)(int)(index),(LPARAM)(data)))

/** Static macros. **/
#define Static_SetTextU(hwndCtl,lpsz)	pSetWindowTextU((hwndCtl),(lpsz))
#define Static_GetTextLengthU(hwndCtl)	pGetWindowTextLengthU(hwndCtl)

void WINAPI w32u_windowsx_init(void);

#ifdef __cplusplus
}
#endif

#endif /* GSFT_W32U_WINDOWSX_H */
