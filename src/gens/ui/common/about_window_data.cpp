/***************************************************************************
 * Gens: About Window data.                                                *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008 by David Korth                                       *
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

#ifdef HAVE_CONFIG_H
#include <config.h>
#endif /* HAVE_CONFIG_H */

#ifdef GENS_PNG_INTERNAL
#include <png.h>
#endif

#ifdef GENS_ZLIB_INTERNAL
#include <zlib.h>
#endif

#include "about/about_window.hpp"

// git version
#include "macros/git.h"

const char* AboutWindow::StrTitle =
		"Gens/GS"
		#ifdef VERSION
		"\nVersion " VERSION
		#endif
		#ifdef GENS_GIT_VERSION
		"\n" GENS_GIT_VERSION
		#endif
		;

const char* AboutWindow::StrDescription =
		"Sega Genesis / Mega Drive,\n"
		"Sega CD / Mega CD,\n"
		"Sega 32X emulator";

const char* AboutWindow::StrCopyright =
		"(c) 1999-2002 by Stéphane Dallongeville\n"
		"(c) 2003-2004 by Stéphane Akhoun\n\n"
		"Gens/GS (c) 2008-2009 by David Korth\n\n"
		"Visit the Gens homepage:\n"
		"http://gens.consolemul.com\n\n"
		"For news on Gens/GS, visit Sonic Retro:\n"
		"http://www.sonicretro.org";

const char* AboutWindow::StrIncludedLibs =
		"Reverse-engineered 32X firmware by DevSter\n"
		"http://devster.monkeeh.com/segapage.html"
		#ifdef GENS_MP3
			"\n\n"
			"Internal mp3 decoder based on mpg123\n"
			"Copyright (c) 1995,1996,1997 by Michael Hipp."
		#endif
		#ifdef GENS_PNG_INTERNAL
			"\n\n"
			"Internal copy of libpng-" PNG_LIBPNG_VER_STRING "\n"
			"Copyright (c) 1998-2008 Glenn Randers-Pehrson."
		#endif
		#ifdef GENS_ZLIB_INTERNAL
			"\n\n"
			"Internal copy of zlib-" ZLIB_VERSION "\n"
			"Copyright (c) 1995-2005 Jean-loup Gailly and Mark Adler."
		#endif
		;

const unsigned char AboutWindow::Data[] =
{
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\003', '\063', '\063',
	'\063', '\063', '\063', '\000', '\000', '\000', '\040', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042',
	'\043', '\063', '\063', '\063', '\060', '\000', '\002', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002',
	'\042', '\043', '\063', '\063', '\063', '\060', '\000', '\040', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\000', '\000',
	'\042', '\042', '\063', '\063', '\063', '\063', '\060', '\042', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\000', '\000',
	'\002', '\042', '\043', '\064', '\104', '\063', '\063', '\042', '\040', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\040', '\000',
	'\002', '\042', '\042', '\043', '\104', '\104', '\103', '\062', '\040', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\042', '\040',
	'\000', '\042', '\053', '\252', '\063', '\105', '\104', '\103', '\042', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\043', '\042',
	'\040', '\002', '\042', '\272', '\252', '\065', '\125', '\104', '\062', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\063',
	'\062', '\063', '\062', '\273', '\104', '\125', '\125', '\124', '\103', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\043',
	'\063', '\062', '\063', '\104', '\105', '\125', '\065', '\124', '\103', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\042',
	'\063', '\042', '\064', '\125', '\105', '\127', '\163', '\125', '\104', '\060',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042',
	'\042', '\042', '\065', '\145', '\105', '\166', '\147', '\065', '\104', '\120',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002',
	'\042', '\042', '\064', '\125', '\105', '\166', '\146', '\023', '\104', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\042', '\042', '\043', '\064', '\105', '\166', '\146', '\021', '\064', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\060', '\000',
	'\002', '\042', '\043', '\063', '\105', '\166', '\146', '\021', '\121', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\003', '\063',
	'\000', '\062', '\042', '\063', '\064', '\127', '\146', '\021', '\141', '\200',
	'\000', '\000', '\000', '\007', '\167', '\167', '\171', '\206', '\220', '\063',
	'\063', '\042', '\042', '\043', '\266', '\143', '\126', '\146', '\201', '\200',
	'\000', '\000', '\167', '\146', '\146', '\146', '\151', '\206', '\233', '\252',
	'\252', '\275', '\042', '\053', '\252', '\246', '\146', '\152', '\021', '\020',
	'\000', '\000', '\231', '\231', '\231', '\147', '\171', '\210', '\233', '\273',
	'\275', '\322', '\063', '\053', '\252', '\252', '\252', '\252', '\240', '\000',
	'\000', '\000', '\000', '\011', '\146', '\171', '\231', '\231', '\000', '\002',
	'\042', '\053', '\273', '\335', '\272', '\252', '\252', '\273', '\320', '\000',
	'\000', '\000', '\000', '\226', '\171', '\230', '\200', '\002', '\042', '\042',
	'\042', '\273', '\246', '\275', '\333', '\273', '\273', '\320', '\000', '\000',
	'\000', '\000', '\000', '\031', '\230', '\161', '\042', '\042', '\043', '\063',
	'\062', '\273', '\252', '\253', '\335', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\001', '\334', '\307', '\141', '\063', '\063', '\075', '\231',
	'\323', '\073', '\252', '\252', '\260', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\001', '\314', '\306', '\146', '\140', '\001', '\335', '\211',
	'\220', '\062', '\273', '\273', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\027', '\166', '\314', '\146', '\000', '\035', '\335', '\210',
	'\220', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\027', '\146', '\154', '\335', '\000', '\035', '\335', '\335',
	'\320', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\314', '\306', '\147', '\320', '\000', '\030', '\211', '\335',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\314', '\314', '\147', '\200', '\001', '\330', '\211', '\220',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\314', '\310', '\000', '\001', '\335', '\331', '\220',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\314', '\320', '\000', '\001', '\335', '\335', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\315', '\000', '\000', '\001', '\335', '\320', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\315', '\320', '\000', '\000', '\001', '\335', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\063', '\063',
	'\063', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002',
	'\063', '\063', '\060', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\042', '\063', '\063', '\063', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\002', '\043', '\063', '\063', '\063', '\000', '\002', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\040', '\000',
	'\000', '\042', '\063', '\103', '\063', '\060', '\000', '\040', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\040', '\000',
	'\000', '\042', '\063', '\104', '\104', '\063', '\060', '\002', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\000',
	'\000', '\002', '\063', '\064', '\064', '\103', '\063', '\002', '\040', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\040',
	'\000', '\002', '\043', '\064', '\104', '\104', '\063', '\002', '\042', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\042',
	'\000', '\002', '\042', '\272', '\104', '\104', '\103', '\062', '\042', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\042',
	'\040', '\002', '\042', '\272', '\243', '\105', '\104', '\103', '\042', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\003', '\042',
	'\040', '\002', '\042', '\272', '\252', '\065', '\125', '\104', '\062', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\063',
	'\062', '\063', '\062', '\273', '\104', '\125', '\125', '\124', '\103', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\043',
	'\063', '\062', '\063', '\104', '\105', '\125', '\065', '\124', '\103', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002',
	'\063', '\042', '\064', '\125', '\105', '\127', '\163', '\125', '\104', '\060',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\000', '\002',
	'\042', '\042', '\065', '\145', '\105', '\166', '\147', '\065', '\104', '\120',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\040', '\000',
	'\042', '\042', '\064', '\125', '\105', '\166', '\146', '\023', '\104', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\000',
	'\002', '\042', '\043', '\064', '\105', '\166', '\146', '\021', '\064', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\042', '\042',
	'\002', '\042', '\043', '\063', '\105', '\166', '\146', '\021', '\121', '\020',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\002', '\042',
	'\042', '\062', '\042', '\063', '\064', '\127', '\146', '\021', '\141', '\200',
	'\000', '\000', '\000', '\007', '\167', '\167', '\171', '\206', '\220', '\063',
	'\063', '\042', '\042', '\043', '\266', '\143', '\126', '\146', '\201', '\200',
	'\000', '\000', '\167', '\146', '\146', '\146', '\151', '\206', '\233', '\252',
	'\252', '\275', '\042', '\053', '\252', '\246', '\146', '\152', '\021', '\020',
	'\000', '\000', '\231', '\231', '\231', '\147', '\171', '\210', '\233', '\273',
	'\275', '\322', '\063', '\053', '\252', '\252', '\252', '\252', '\240', '\000',
	'\000', '\000', '\000', '\011', '\146', '\171', '\231', '\231', '\002', '\042',
	'\042', '\053', '\273', '\335', '\272', '\252', '\252', '\273', '\320', '\000',
	'\000', '\000', '\000', '\226', '\171', '\230', '\202', '\042', '\042', '\042',
	'\042', '\273', '\246', '\275', '\333', '\273', '\273', '\320', '\000', '\000',
	'\000', '\000', '\001', '\031', '\227', '\141', '\063', '\063', '\063', '\063',
	'\062', '\273', '\252', '\253', '\335', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\001', '\334', '\306', '\146', '\140', '\035', '\335', '\211',
	'\323', '\073', '\252', '\252', '\260', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\027', '\174', '\314', '\146', '\140', '\035', '\335', '\210',
	'\220', '\062', '\273', '\273', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\027', '\166', '\314', '\335', '\000', '\035', '\335', '\335',
	'\320', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\314', '\146', '\147', '\335', '\000', '\030', '\215', '\335',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\314', '\306', '\147', '\200', '\001', '\330', '\211', '\235',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\314', '\310', '\000', '\001', '\335', '\331', '\220',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\314', '\320', '\000', '\001', '\335', '\335', '\220',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\034', '\314', '\315', '\000', '\000', '\001', '\335', '\320', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\001', '\315', '\320', '\000', '\000', '\001', '\335', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
	'\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000', '\000',
};

const unsigned char AboutWindow::DX[] =
{
	'\000', '\000', '\000', '\000', '\004', '\356', '\012', '\356', '\016', '\356',
	'\016', '\356', '\016', '\356', '\012', '\252', '\010', '\210', '\004', '\104',
	'\010', '\256', '\004', '\152', '\000', '\016', '\000', '\010', '\000', '\256',
	'\000', '\216', '\000', '\000', '\000', '\000', '\006', '\356', '\016', '\356',
	'\016', '\356', '\016', '\356', '\016', '\356', '\012', '\252', '\010', '\210',
	'\004', '\104', '\010', '\256', '\004', '\152', '\000', '\016', '\000', '\010',
	'\000', '\256', '\000', '\216', '\000', '\000', '\000', '\000', '\010', '\356',
	'\016', '\356', '\016', '\356', '\016', '\356', '\016', '\356', '\012', '\252',
	'\010', '\210', '\004', '\104', '\010', '\256', '\004', '\152', '\000', '\016',
	'\000', '\010', '\000', '\256', '\000', '\216', '\000', '\000', '\000', '\000',
	'\006', '\356', '\014', '\356', '\016', '\356', '\016', '\356', '\016', '\356',
	'\012', '\252', '\010', '\210', '\004', '\104', '\010', '\256', '\004', '\152',
	'\000', '\016', '\000', '\010', '\000', '\256', '\000', '\216', '\000', '\000',
	'\000', '\000', '\004', '\356', '\012', '\356', '\016', '\356', '\016', '\356',
	'\016', '\356', '\012', '\252', '\010', '\210', '\004', '\104', '\010', '\256',
	'\004', '\152', '\000', '\016', '\000', '\010', '\000', '\256', '\000', '\216',
	'\000', '\000', '\000', '\000', '\002', '\356', '\010', '\356', '\014', '\356',
	'\016', '\356', '\016', '\356', '\012', '\252', '\010', '\210', '\004', '\104',
	'\010', '\256', '\004', '\152', '\000', '\016', '\000', '\010', '\000', '\256',
	'\000', '\216', '\000', '\000', '\000', '\000', '\000', '\356', '\006', '\356',
	'\012', '\356', '\016', '\356', '\016', '\356', '\012', '\252', '\010', '\210',
	'\004', '\104', '\010', '\256', '\004', '\152', '\000', '\016', '\000', '\010',
	'\000', '\256', '\000', '\216', '\000', '\000', '\000', '\000', '\000', '\356',
	'\004', '\356', '\010', '\356', '\014', '\356', '\016', '\356', '\012', '\252',
	'\010', '\210', '\004', '\104', '\010', '\256', '\004', '\152', '\000', '\016',
	'\000', '\010', '\000', '\256', '\000', '\216', '\000', '\000', '\000', '\000',
	'\000', '\356', '\006', '\356', '\012', '\356', '\016', '\356', '\016', '\356',
	'\012', '\252', '\010', '\210', '\004', '\104', '\010', '\256', '\004', '\152',
	'\000', '\016', '\000', '\010', '\000', '\256', '\000', '\216', '\000', '\000',
	'\000', '\000', '\000', '\356', '\010', '\356', '\014', '\356', '\016', '\356',
	'\016', '\356', '\012', '\252', '\010', '\210', '\004', '\104', '\010', '\256',
	'\004', '\152', '\000', '\016', '\000', '\010', '\000', '\256', '\000', '\216',
};
