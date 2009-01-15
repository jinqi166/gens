/***************************************************************************
 * mdZ80: Gens Z80 Emulator                                                *
 * mdZ80.c: Main Z80 emulation functions.                                  *
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

#include "mdZ80.h"

// C includes.
#include <string.h>

// Z80 flag and state definitions.
#include "mdZ80_flags.h"


/**
 * z80_Get_PC(): Get the Z80 program counter.
 * @param z80 Pointer to Z80 context.
 * @return Z80 program counter, or -1 (0xFFFFFFFF) if the Z80 is running.
 */
unsigned int z80_Get_PC(Z80_CONTEXT *z80)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return -1;
	
	// Subtract the BasePC from PC to get the actual Z80 program counter.
	return (z80->PC.d - z80->BasePC);
}


/**
 * z80_Set_PC(): Set the Z80 program counter.
 * @param z80 Pointer to Z80 context.
 * @param PC New program counter.
 */
void z80_Set_PC(Z80_CONTEXT *z80, unsigned int PC)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return;
	
	// TODO: 32-bit specific code will break on 64-bit!
	PC &= 0xFFFF;
	unsigned int newPC = (unsigned int)(z80->Fetch[PC >> 8]);
	z80->BasePC = newPC;
	z80->PC.d = newPC + PC;
}


/**
 * z80_Reset(): Reset the Z80 CPU.
 * @param z80 Pointer to Z80 context.
 */
void z80_Reset(Z80_CONTEXT *z80)
{
	// Save the Z80 Cycle Count.
	unsigned int cycleCnt = z80->CycleCnt;
	
	// Clear the Z80 struct up to CycleSup.
	memset(z80, 0x00, 23*4);
	
	// Restore the Z80 Cycle Count.
	z80->CycleCnt = cycleCnt;
	
	// Initialize the program counter.
	z80_Set_PC(z80, 0);
	
	// Initialize the index and flag registers.
	z80->IX.d = 0xFFFF;
	z80->IY.d = 0xFFFF;
	z80->AF.d = 0x4000;
}


/**
 * z80_Get_AF(): Get the AF register.
 * @param z80 Pointer to Z80 context.
 * @return AF register, or -1 during z80_Exec().
 */
unsigned int z80_Get_AF(Z80_CONTEXT *z80)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return -1;
	
	// F register.
	// The X and Y flags are stored separately from the
	// rest of the flags for some reason.
	unsigned char F = (z80->AF.b.F & ~(Z80_FLAG_X | Z80_FLAG_Y)) |
			  (z80->AF.b.FXY & (Z80_FLAG_X | Z80_FLAG_Y));
	
	// Return AF.
	return ((z80->AF.b.A << 8) | F);
}


/**
 * z80_Set_AF(): Set the AF register.
 * @param z80 Pointer to Z80 context.
 * @param newAF New AF register value.
 */
void z80_Set_AF(Z80_CONTEXT *z80, unsigned int newAF)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return;
	
	// Set the A register.
	z80->AF.b.A = (newAF >> 8) & 0xFF;
	
	// Set the F register.
	newAF &= 0xFF;
	z80->AF.b.F = newAF & ~(Z80_FLAG_X | Z80_FLAG_Y);
	
	// Set the FXY register.
	z80->AF.b.FXY = newAF & (Z80_FLAG_X | Z80_FLAG_Y);
}


/**
 * z80_Get_AF2(): Get the AF' register.
 * @param z80 Pointer to Z80 context.
 * @return AF' register, or -1 during z80_Exec().
 */
unsigned int z80_Get_AF2(Z80_CONTEXT *z80)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return -1;
	
	// F' register.
	// The X and Y flags are stored separately from the
	// rest of the flags for some reason.
	unsigned char F2 = (z80->AF2.b.F2 & ~(Z80_FLAG_X | Z80_FLAG_Y)) |
			  (z80->AF2.b.FXY2 & (Z80_FLAG_X | Z80_FLAG_Y));
	
	// Return AF'.
	return ((z80->AF2.b.A2 << 8) | F2);
}


/**
 * z80_Set_AF2(): Set the AF' register.
 * @param z80 Pointer to Z80 context.
 * @param newAF New AF' register value.
 */
void z80_Set_AF2(Z80_CONTEXT *z80, unsigned int newAF2)
{
	if (z80->Status & Z80_STATE_RUNNING)
		return;
	
	// Set the A' register.
	z80->AF2.b.A2 = (newAF2 >> 8) & 0xFF;
	
	// Set the F' register.
	newAF2 &= 0xFF;
	z80->AF2.b.F2 = newAF2 & ~(Z80_FLAG_X | Z80_FLAG_Y);
	
	// Set the FXY2 register.
	z80->AF2.b.FXY2 = newAF2 & (Z80_FLAG_X | Z80_FLAG_Y);
}


/**
 * z80_Interrupt(): Raise a Z80 interrupt.
 * TODO: Figure out the exact purpose of this function.
 * @param z80 Pointer to Z80 context.
 * @param vector Interrupt vector.
 */
void z80_Interrupt(Z80_CONTEXT *z80, unsigned char vector)
{
	// Set the interrupt data.
	z80->IntVect = vector;
	z80->IntLine = Z80_FLAG_P;	// because of IFF mask
	
	// If the Z80 is currently running, don't do anything else.
	if (z80->Status & Z80_STATE_RUNNING)
		return;
	
	// Shift the cycle variables.
	z80->CycleSup = z80->CycleIO;
	z80->CycleIO = 0;
}
