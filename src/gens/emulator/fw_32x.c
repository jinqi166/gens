/***************************************************************************
 * Gens: Reverse-engineered 32X firmware.                                  *
 *                                                                         *
 * Copyright (c) 2005 by DevSter (Joseph Norman)                           *
 * Visit DevSter's website: http://devster.monkeeh.com/segapage.html       *
 *                                                                         *
 * Gens/GS port Copyright (c) 2008 by David Korth                          *
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

#include "fw_32x.h"

const unsigned char fw_32X_mc68000[272] =
{
	0x00, 0x00, 0x00, 0x00, 0x41, 0x88, 0x02, 0x00, 0x42, 0x88, 0x02, 0x06, 0x43, 0x88, 0x02, 0x0C,
	0x44, 0x88, 0x02, 0x12, 0x45, 0x88, 0x02, 0x18, 0x46, 0x88, 0x02, 0x1E, 0x47, 0x88, 0x02, 0x24,
	0x48, 0x88, 0x02, 0x2A, 0x49, 0x88, 0x02, 0x30, 0x4A, 0x88, 0x02, 0x36, 0x4B, 0x88, 0x02, 0x3C,
	0x4C, 0x88, 0x02, 0x42, 0x4D, 0x88, 0x02, 0x48, 0x4E, 0x88, 0x02, 0x4E, 0x4F, 0x88, 0x02, 0x54,
	0x50, 0x88, 0x02, 0x5A, 0x51, 0x88, 0x02, 0x60, 0x52, 0x88, 0x02, 0x66, 0x53, 0x88, 0x02, 0x6C,
	0x54, 0x88, 0x02, 0x72, 0x55, 0x88, 0x02, 0x78, 0x56, 0x88, 0x02, 0x7E, 0x57, 0x88, 0x02, 0x84,
	0x58, 0x88, 0x02, 0x8A, 0x59, 0x88, 0x02, 0x90, 0x5A, 0x88, 0x02, 0x96, 0x59, 0x88, 0x02, 0x9C,
	0x58, 0x88, 0x02, 0xA2, 0x57, 0x88, 0x02, 0xA8, 0x56, 0x88, 0x02, 0xAE, 0x55, 0x88, 0x02, 0xB4,
	0x54, 0x88, 0x02, 0xBA, 0x53, 0x88, 0x02, 0xC0, 0x52, 0x88, 0x02, 0xC6, 0x51, 0x88, 0x02, 0xCC,
	0x50, 0x88, 0x02, 0xD2, 0x4F, 0x88, 0x02, 0xD8, 0x4E, 0x88, 0x02, 0xDE, 0x4D, 0x88, 0x02, 0xE4,
	0x4C, 0x88, 0x02, 0xEA, 0x4B, 0x88, 0x02, 0xF0, 0x4A, 0x88, 0x02, 0xF6, 0x49, 0x88, 0x02, 0xFC,
	0x48, 0x88, 0x03, 0x02, 0x47, 0x88, 0x03, 0x08, 0x46, 0x88, 0x03, 0x0E, 0x45, 0x88, 0x03, 0x14,
	0x08, 0xF9, 0x00, 0x00, 0x00, 0xA1, 0x51, 0x07, 0x12, 0x80, 0x08, 0xB9, 0x00, 0x00, 0x00, 0xA1,
	0x51, 0x07, 0x4E, 0x75, 0x48, 0xE7, 0x80, 0x20, 0x08, 0xF9, 0x00, 0x00, 0x00, 0xA1, 0x51, 0x07,
	0x45, 0xF9, 0x00, 0xA1, 0x30, 0xF1, 0x7E, 0x07, 0x14, 0x98, 0xD4, 0xFC, 0x00, 0x02, 0x51, 0xC8,
	0xFF, 0xF8, 0x08, 0xB9, 0x00, 0x00, 0x00, 0xA1, 0x51, 0x07, 0x4C, 0xDF, 0x04, 0x01, 0x4E, 0x75,
	0x42, 0x69, 0x6F, 0x73, 0x20, 0x42, 0x79, 0x20, 0x44, 0x65, 0x76, 0x53, 0x74, 0x65, 0x72, 0x20
};

const unsigned char fw_32X_msh2[712] =
{
	0x00, 0x00, 0x01, 0x40, 0x06, 0x04, 0x00, 0x00, 0x00, 0x00, 0x01, 0x40, 0x06, 0x04, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3C, 0x20, 0x10, 0x04, 0x00,
	0x20, 0x10, 0x04, 0x20, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x50, 0x6F, 0x6F, 0x72, 0x6D, 0x61, 0x6E, 0x27, 0x73, 0x20, 0x42, 0x69,
	0x6F, 0x73, 0x20, 0x42, 0x79, 0x20, 0x44, 0x65, 0x76, 0x53, 0x74, 0x65, 0x72, 0x00, 0x68, 0x74,
	0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x64, 0x65, 0x76, 0x73, 0x74, 0x65, 0x72, 0x2E, 0x72, 0x65, 0x74,
	0x72, 0x6F, 0x64, 0x65, 0x76, 0x2E, 0x63, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0xAF, 0xFE, 0x00, 0x09,
	0xD0, 0x12, 0x40, 0x0E, 0xD1, 0x46, 0xD2, 0x47, 0x60, 0x16, 0x12, 0x00, 0x60, 0x16, 0x12, 0x01,
	0x60, 0x16, 0x12, 0x02, 0x60, 0x16, 0x12, 0x03, 0x60, 0x16, 0x12, 0x04, 0x60, 0x16, 0x12, 0x05,
	0x60, 0x16, 0x12, 0x06, 0xD0, 0x3D, 0x40, 0x1E, 0xD1, 0x3F, 0xE0, 0x00, 0x21, 0x01, 0xC4, 0x00,
	0xC8, 0x02, 0x8B, 0x0F, 0xD0, 0x06, 0xE1, 0x01, 0x30, 0x18, 0x88, 0x00, 0x8B, 0xFC, 0xC1, 0x01,
	0xD1, 0x3A, 0xE0, 0x9F, 0x21, 0x00, 0x00, 0x1B, 0xAF, 0xFE, 0x00, 0x09, 0x00, 0x00, 0x00, 0xF0,
	0x00, 0x01, 0x00, 0x00, 0xD1, 0x35, 0xE0, 0x00, 0x21, 0x00, 0xD1, 0x35, 0xE0, 0x11, 0x21, 0x00,
	0xD1, 0x34, 0xD2, 0x35, 0xE0, 0x00, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x21, 0x06, 0x32, 0x10,
	0x8B, 0xF9, 0xC4, 0x00, 0xC8, 0x01, 0x8B, 0x31, 0xD4, 0x36, 0xD0, 0x37, 0x60, 0x01, 0x60, 0x0D,
	0x88, 0x00, 0x89, 0x0F, 0xD0, 0x35, 0x61, 0x02, 0xD0, 0x35, 0x31, 0x08, 0x41, 0x01, 0xD0, 0x35,
	0x21, 0x09, 0x71, 0x01, 0xE0, 0x00, 0xD3, 0x34, 0x62, 0x45, 0x22, 0x39, 0x30, 0x2C, 0x20, 0x39,
	0x41, 0x10, 0x8B, 0xF9, 0xC1, 0x14, 0xD1, 0x26, 0x62, 0x16, 0x63, 0x16, 0x60, 0x16, 0xD1, 0x09,
	0x32, 0x1C, 0xD1, 0x09, 0x33, 0x1C, 0xE4, 0x04, 0x61, 0x26, 0x23, 0x12, 0x73, 0x04, 0x30, 0x48,
	0x88, 0x00, 0x8B, 0xF9, 0xD1, 0x1E, 0x50, 0x15, 0x40, 0x2E, 0x51, 0x13, 0xD0, 0x1D, 0xC2, 0x08,
	0x41, 0x2B, 0x00, 0x09, 0x22, 0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0xD1, 0x1A, 0xC6, 0x08,
	0x31, 0x00, 0x8B, 0xFC, 0xE0, 0x80, 0xC0, 0x00, 0xC4, 0x00, 0xC8, 0x80, 0x89, 0xFC, 0xD8, 0x17,
	0x59, 0x80, 0x50, 0x81, 0x5A, 0x82, 0x5B, 0x83, 0x78, 0x20, 0xD3, 0x15, 0xE4, 0x00, 0xE2, 0x04,
	0x61, 0x86, 0x29, 0x12, 0x79, 0x04, 0x30, 0x28, 0x33, 0x28, 0x33, 0x40, 0x89, 0x01, 0x88, 0x00,
	0x8B, 0xF6, 0xD0, 0x0C, 0xC2, 0x08, 0x4B, 0x2E, 0x4A, 0x2B, 0x00, 0x09, 0x20, 0x00, 0x40, 0x00,
	0x00, 0x00, 0x02, 0xAC, 0xFF, 0xFF, 0xFF, 0xE0, 0xFF, 0xFF, 0x84, 0x46, 0xFF, 0xFF, 0xFE, 0x91,
	0xFF, 0xFF, 0xFE, 0x92, 0x26, 0x04, 0x00, 0x00, 0x26, 0x00, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF,
	0x22, 0x00, 0x03, 0xD4, 0x4D, 0x5F, 0x4F, 0x4B, 0x5F, 0x43, 0x44, 0x5F, 0x24, 0x00, 0x00, 0x18,
	0x00, 0x01, 0xFF, 0xE0, 0x22, 0x00, 0x02, 0x00, 0x22, 0x00, 0x01, 0x8E, 0x22, 0x00, 0x01, 0xA4,
	0x00, 0x00, 0x02, 0x00, 0x00, 0x3F, 0xFF, 0xFF, 0x00, 0x00, 0xFF, 0xFF, 0xA5, 0x5A, 0x00, 0x01,
	0xA5, 0x5A, 0x00, 0xA8, 0xA5, 0x5A, 0x00, 0x55, 0xA5, 0x5A, 0x0A, 0xB8, 0xA5, 0x5A, 0x00, 0x08,
	0xA5, 0x5A, 0x00, 0x00, 0xA5, 0x5A, 0x00, 0x59
};

const unsigned char fw_32X_ssh2[532] =
{
	0x00, 0x00, 0x01, 0x40, 0x06, 0x03, 0xF8, 0x00, 0x00, 0x00, 0x01, 0x40, 0x06, 0x03, 0xF8, 0x00,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x3C, 0x20, 0x10, 0x04, 0x00,
	0x20, 0x10, 0x04, 0x20, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x50, 0x6F, 0x6F, 0x72, 0x6D, 0x61, 0x6E, 0x27, 0x73, 0x20, 0x42, 0x69,
	0x6F, 0x73, 0x20, 0x42, 0x79, 0x20, 0x44, 0x65, 0x76, 0x53, 0x74, 0x65, 0x72, 0x00, 0x68, 0x74,
	0x74, 0x70, 0x3A, 0x2F, 0x2F, 0x64, 0x65, 0x76, 0x73, 0x74, 0x65, 0x72, 0x2E, 0x72, 0x65, 0x74,
	0x72, 0x6F, 0x64, 0x65, 0x76, 0x2E, 0x63, 0x6F, 0x6D, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C,
	0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0x00, 0x00, 0x01, 0x3C, 0xAF, 0xFE, 0x00, 0x09,
	0xD0, 0x0C, 0x40, 0x0E, 0xD1, 0x24, 0xD2, 0x25, 0x60, 0x16, 0x12, 0x00, 0x60, 0x16, 0x12, 0x01,
	0x60, 0x16, 0x12, 0x02, 0x60, 0x16, 0x12, 0x03, 0x60, 0x16, 0x12, 0x04, 0x60, 0x16, 0x12, 0x05,
	0x60, 0x16, 0x12, 0x06, 0xD0, 0x1B, 0x40, 0x1E, 0xC4, 0x00, 0xC8, 0x02, 0x8B, 0x04, 0x00, 0x1B,
	0xAF, 0xFE, 0x00, 0x09, 0x00, 0x00, 0x00, 0xF0, 0xD1, 0x19, 0xE0, 0x00, 0x21, 0x00, 0xD1, 0x19,
	0xE0, 0x11, 0x21, 0x00, 0xC4, 0x00, 0xC8, 0x01, 0x8B, 0x16, 0xB0, 0x08, 0x00, 0x09, 0xD1, 0x18,
	0x50, 0x12, 0x40, 0x2E, 0x61, 0x12, 0xD0, 0x15, 0xC2, 0x09, 0x41, 0x2B, 0x00, 0x09, 0xE0, 0x28,
	0xE1, 0x01, 0x30, 0x18, 0x88, 0x00, 0x8B, 0xFC, 0xC6, 0x08, 0xD1, 0x02, 0x31, 0x00, 0x8B, 0xF6,
	0x00, 0x0B, 0x00, 0x09, 0x4D, 0x5F, 0x4F, 0x4B, 0xD1, 0x0B, 0xC6, 0x08, 0x31, 0x00, 0x8B, 0xFC,
	0xBF, 0xED, 0x00, 0x09, 0xD1, 0x0B, 0x52, 0x13, 0x51, 0x15, 0xD0, 0x08, 0xC2, 0x09, 0x41, 0x2E,
	0x42, 0x2B, 0x00, 0x09, 0x20, 0x00, 0x40, 0x00, 0x00, 0x00, 0x01, 0xF8, 0xFF, 0xFF, 0xFF, 0xE0,
	0xFF, 0xFF, 0xFE, 0x91, 0xFF, 0xFF, 0xFE, 0x92, 0x5F, 0x43, 0x44, 0x5F, 0x53, 0x5F, 0x4F, 0x4B,
	0x22, 0x00, 0x03, 0xE4, 0x24, 0x00, 0x00, 0x18, 0xA5, 0x5A, 0x00, 0x01, 0xA5, 0x5A, 0x00, 0xA8,
	0xA5, 0x5A, 0x00, 0x55, 0xA5, 0x5A, 0x0A, 0xB8, 0xA5, 0x5A, 0x00, 0x08, 0xA5, 0x5A, 0x00, 0x00,
	0xA5, 0x5A, 0x00, 0x59
};
