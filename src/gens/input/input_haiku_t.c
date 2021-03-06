/***************************************************************************
 * Gens: Input Handler - Haiku Backend. (input_backend_t struct)           *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
 * Copyright (c) 2008-2009 by David Korth                                  *
 * Copyright (c) 2009 by Phil Costin                                       *
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

#include "input_haiku_t.h"
#include "input_haiku.hpp"

// Input Backend struct.
const input_backend_t input_backend_haiku =
{
	.init			= input_haiku_init,
	.end			= input_haiku_end,
	
	.keymap_default		= &input_haiku_keymap_default[0],
	
	.update			= input_haiku_update,
	.check_key_pressed	= input_haiku_check_key_pressed,
	.get_key		= input_haiku_get_key,
	.joy_exists		= input_haiku_joy_exists,
	.get_key_name		= input_haiku_get_key_name
};
