/***************************************************************************
 * MDP: Game Genie.                                                        *
 *                                                                         *
 * Copyright (c) 1999-2002 by Stéphane Dallongeville                       *
 * Copyright (c) 2003-2004 by Stéphane Akhoun                              *
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

#ifndef MDP_MISC_GAME_GENIE_HPP
#define MDP_MISC_GAME_GENIE_HPP

#ifdef __cplusplus
extern "C" {
#endif

#include "mdp/mdp.h"
#include "mdp/mdp_host.h"
#include "mdp/mdp_constants.h"

DLL_LOCAL int MDP_FNCALL gg_init(mdp_host_t *host_srv);
DLL_LOCAL int MDP_FNCALL gg_end(void);

DLL_LOCAL extern mdp_host_t *gg_host_srv;
DLL_LOCAL extern MDP_SYSTEM_ID gg_system_id;

DLL_LOCAL extern void *gg_mdp_ptr_rom_md;
DLL_LOCAL extern void *gg_mdp_ptr_ram_md;
DLL_LOCAL extern int   gg_mdp_rom_md_size;

#ifdef __cplusplus
}
#endif

#ifdef __cplusplus

// List of Game Genie codes.
#include "gg_code.h"
#include <list>
extern std::list<gg_code_t> gg_code_list;

#endif

#endif /* MDP_MISC_GAME_GENIE_HPP */
