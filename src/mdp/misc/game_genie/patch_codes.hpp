/***************************************************************************
 * Gens: [MDP] Game Genie - Patch Codes Handler.                           *
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

#ifndef __MDP_GAME_GENIE_PATCH_CODES_HPP
#define __MDP_GAME_GENIE_PATCH_CODES_HPP

#include <stdint.h>

#include <string>

class PatchCodes
{
	public:
		PatchCodes();
		PatchCodes(const std::string& code, CPU cpu = CPU_M68K);
		~PatchCodes();
			
		enum CPU
		{
			CPU_INVALID = 0,
			CPU_M68K    = 1,
			CPU_S68K    = 2,
			CPU_Z80     = 3,
			CPU_MSH2    = 4,
			CPU_SSH2    = 5,
		};
		
		enum DataSize
		{
			DS_INVALID = 0,
			DS_BYTE    = 1, // 8-bit
			DS_WORD    = 2, // 16-bit
			DS_DWORD   = 3, // 32-bit
		};
		
		void setCode(const std::string& code, CPU cpu = CPU_M68K);
		
		uint32_t address(void);
		uint32_t data(void);
		DataSize dataSize(void);
		
	protected:
		bool decodeGG(const std::string& code);
		
		uint32_t m_address;
		uint32_t m_data;
		DataSize m_dataSize;
		CPU m_cpu;
};

#endif /* __MDP_GAME_GENIE_PATCH_CODES_HPP */
