/***************************************************************************
 * libgsft: Common functions.                                              *
 * gsft_strdup.c: strdup() implementation for older systems.               *
 *                                                                         *
 * Copyright (c) 2008-2009 by David Korth                                  *
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

#include "gsft_strdup.h"

#ifndef HAVE_STRDUP

/* strdup() is not defined. */

char* gsft_strdup(const char *s)
{
	char* tmp = (char*)malloc(strlen(s) + 1);
	strcpy(tmp, s);
	return tmp;
}

#endif /* !HAVE_STRDUPP */
