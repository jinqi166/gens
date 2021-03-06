/***************************************************************************
 * libgsft_w32u: Win32 Unicode Translation Layer.                          *
 * w32u_libc.h: libc translation.                                          *
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

#ifndef GSFT_W32U_LIBC_H
#define GSFT_W32U_LIBC_H

#include "w32u.h"
#include <io.h>
#include <stdio.h>
#include <string.h>
#include <dirent.h>

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

#ifdef __cplusplus
extern "C" {
#endif

/** Unicode wrappers. **/
MAKE_EXTFUNCPTR(access);
#define access(path, mode) paccess(path, mode)

MAKE_EXTFUNCPTR(fopen);
#define fopen(path, mode) pfopen(path, mode)

MAKE_EXTFUNCPTR(stat);
#define stat(path, buf) pstat(path, buf)

MAKE_EXTFUNCPTR(mkdir);
#define mkdir(dirname) pmkdir(dirname)

MAKE_EXTFUNCPTR(unlink);
#define unlink(filename) punlink(filename)

MAKE_EXTFUNCPTR(opendir);
#define opendir(name) popendir(name)

MAKE_EXTFUNCPTR(readdir);
#define readdir(dirp) preaddir(dirp)

/** Unicode functions that are accessed directly. **/
MAKE_EXTFUNCPTR(_wcsicmp);

void WINAPI w32u_libc_init(void);

#ifdef __cplusplus
}
#endif

#endif /* GSFT_W32U_LIBC_H */
