/***************************************************************************
 * Gens: Video Drawing - Text Drawing.                                     *
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

#include "vdraw_text.hpp"
#include "vdraw.h"
#include "emulator/g_main.hpp"

// C includes.
#include <string.h>

// C++ includes.
#include <list>
using std::list;

// VDP includes.
#include "gens_core/vdp/vdp_rend.h"
#include "gens_core/vdp/vdp_io.h"

// MDP Render.
#include "mdp/mdp_render.h"

// Plugin Manager.
#include "plugins/pluginmgr.hpp"

// Commodore 64 character set.
#include "C64_charset.h"


 // Text drawing values.
static uint32_t m_Transparency_Mask;


template<typename pixel>
static inline void drawChar_1x(pixel *screen, const int fullW, const int x, const int y,
			       const vdraw_style_t *style, const pixel transparentMask,
			       const unsigned char ch)
{
	unsigned short cx, cy;
	pixel* screenPos;
	unsigned char cRow;
	
	screenPos = &screen[y*fullW + x];
	for (cy = 0; cy < 8; cy++)
	{
		// Each character is 8 bytes, with each row representing 8 dots.
		// A 1 indicates the dot is opaque, while a 0 indicates the dot is transparent.
		cRow = C64_charset[ch][cy];
		for (cx = 0; cx < 8; cx++)
		{
			if (cRow & 0x80)
			{
				// Dot is opaque. Draw it.
				// TODO: Original asm version had transparency in a separate function for performance.
				// See if that would actually help.
				if (!style->transparent)
					*screenPos = style->dot_color;
				else
					*screenPos = ((style->dot_color & transparentMask) >> 1) +
						     ((*screenPos & transparentMask) >> 1);
			}
			cRow <<= 1;
			screenPos++;
		}
		screenPos += (fullW - 8);
	}
}


template<typename pixel>
static inline void drawChar_2x(pixel *screen, const int fullW, const int x, const int y,
			       const vdraw_style_t *style, const pixel transparentMask,
			       const unsigned char ch)
{
	unsigned short cx, cy;
	pixel* screenPos;
	unsigned char cRow;
	
	screenPos = &screen[y*fullW + x];
	for (cy = 0; cy < 8; cy++)
	{
		// Each character is 8 bytes, with each row representing 8 dots.
		// A 1 indicates the dot is opaque, while a 0 indicates the dot is transparent.
		cRow = C64_charset[ch][cy];
		for (cx = 0; cx < 8; cx++)
		{
			if (cRow & 0x80)
			{
				// Dot is opaque. Draw it.
				// TODO: Original asm version had transparency in a separate function for performance.
				// See if that would actually help.
				if (!style->transparent)
				{
					pixel pix = style->dot_color;
					*screenPos = pix;
					*(screenPos + 1) = pix;
					*(screenPos + fullW) = pix;
					*(screenPos + fullW + 1) = pix;
				}
				else
				{
					pixel trPix = (style->dot_color & transparentMask) >> 1;
					*screenPos = trPix + ((*screenPos & transparentMask) >> 1);
					*(screenPos + 1) = trPix + ((*(screenPos + 1) & transparentMask) >> 1);
					*(screenPos + fullW) = trPix + ((*(screenPos + fullW) & transparentMask) >> 1);
					*(screenPos + fullW + 1) = trPix + ((*(screenPos + fullW + 1) & transparentMask) >> 1);
				}
			}
			cRow <<= 1;
			screenPos += 2;
		}
		screenPos += (fullW*2 - 16);
	}
}


template<typename pixel>
void drawText_int(pixel *screen, const int fullW, const int w, const int h,
		  const char *msg, const pixel transparentMask, const vdraw_style_t *style,
		  const bool adjustForScreenSize)
{
	int msgLength, cPos;
	unsigned short linebreaks, msgWidth;
	unsigned short x, y, cx, cy;
	unsigned char charSize;
	
	const bool fullScreen = vdraw_get_fullscreen();
	
	const list<MDP_Render_t*>::iterator& rendMode = (fullScreen ? rendMode_FS : rendMode_W);
	
	// The message must be specified.
	if (!msg)
		return;
	
	// Character size
	if (style->double_size)
		charSize = 16;
	else
		charSize = 8;
	
	// Bottom-left of the screen.
	if (adjustForScreenSize)
	{
		// Adjust for screen size. (SDL/GL)
		x = ((vdraw_border_h / 2) * vdraw_scale) + 8;
		y = h - (((240 - VDP_Num_Vis_Lines) / 2) * vdraw_scale);
	}
	else
	{
		// Don't adjust for screen size. (DDraw)
		if (!fullScreen && rendMode == PluginMgr::lstRenderPlugins.begin())
		{
			// Hack for windowed 1x rendering.
			x = 8;
			y = VDP_Num_Vis_Lines * vdraw_scale;
		}
		else if (fullScreen && rendMode == PluginMgr::lstRenderPlugins.begin())
		{
			// Hacks for fullscreen 1x rendering.
			if (vdraw_get_sw_render())
			{
				x = ((vdraw_border_h / 2) * vdraw_scale);
				y = VDP_Num_Vis_Lines + 8;
			}
			else
			{
				x = 8;
				y = VDP_Num_Vis_Lines;
			}
		}
		else
		{
			x = ((vdraw_border_h / 2) * vdraw_scale);
			y = VDP_Num_Vis_Lines * vdraw_scale;
		}
		
		if (vdraw_scale > 1)
			y += (8 * vdraw_scale);
	}
	
	// Move the text down by another 2px in 1x rendering.
	if (rendMode == PluginMgr::lstRenderPlugins.begin())
	{
		y += 2;
	}
	
	// Character size is 8x8 normal, 16x16 double.
	y -= (8 + charSize);
	
	// Get the message length.
	msgLength = strlen(msg);
	
	// Determine how many linebreaks are needed.
	msgWidth = w - 16 - (vdraw_border_h * vdraw_scale);
	linebreaks = ((msgLength - 1) * charSize) / msgWidth;
	y -= (linebreaks * charSize);
	
	vdraw_style_t textShadowStyle = *style;
	textShadowStyle.dot_color = 0;
	
	cx = x; cy = y;
	for (cPos = 0; cPos < msgLength; cPos++)
	{
		if (style->double_size)
		{
			// TODO: Make text shadow an option.
			drawChar_2x(screen, fullW, cx+1, cy+1, &textShadowStyle,
				    transparentMask, (unsigned char)msg[cPos]);
			
			drawChar_2x(screen, fullW, cx-1, cy-1, style,
				    transparentMask, (unsigned char)msg[cPos]);
		}
		else
		{
			// TODO: Make text shadow an option.
			drawChar_1x(screen, fullW, cx+1, cy+1, &textShadowStyle,
				    transparentMask, (unsigned char)msg[cPos]);
			
			drawChar_1x(screen, fullW, cx, cy, style,
				    transparentMask, (unsigned char)msg[cPos]);
		}
		
		cx += charSize;
		if (cx - x >= msgWidth)
		{
			cx = x;
			cy += charSize;
		}
	}
}


/**
 * draw_text(): Draw text to the screen.
 * @param screen Pointer to screen surface.
 * @param fullW
 * @param w
 * @param h
 * @param msg Text to draw to the screen.
 * @param style Pointer to style information.
 * @param adjustForScreenSize
 */
void draw_text(void *screen, const int fullW, const int w, const int h,
	       const char *msg, const vdraw_style_t *style,
	       const BOOL adjustForScreenSize)
{
	if (!style)
		return;
	
	if (bppOut == 15 || bppOut == 16)
	{
		// 15/16-bit color.
		drawText_int((unsigned short*)screen, fullW, w, h, msg,
			     (unsigned short)m_Transparency_Mask, style,
			     adjustForScreenSize);
	}
	else //if (bppOut == 32)
	{
		// 32-bit color.
		drawText_int((unsigned int*)screen, fullW, w, h, msg,
			     m_Transparency_Mask, style,
			     adjustForScreenSize);
	}
}


/**
 * calc_text_style(): Calculate a text style.
 * @param style Pointer to text style.
 */
void calc_text_style(vdraw_style_t *style)
{
	if (!style)
		return;
	
	// Calculate the dot color.
	if (bppOut == 15)
	{
		switch (style->style & 0x07)
		{
			case STYLE_COLOR_RED:
				style->dot_color = 0x7C00;
				break;
			case STYLE_COLOR_GREEN:
				style->dot_color = 0x03E0;
				break;
			case STYLE_COLOR_BLUE:
				style->dot_color = 0x001F;
				break;
			default: // STYLE_COLOR_WHITE
				style->dot_color = 0x7FFF;
				break;
		}
	}
	else if (bppOut == 16)
	{
		switch (style->style & 0x07)
		{
			case STYLE_COLOR_RED:
				style->dot_color = 0xF800;
				break;
			case STYLE_COLOR_GREEN:
				style->dot_color = 0x7E00;
				break;
			case STYLE_COLOR_BLUE:
				style->dot_color = 0x001F;
				break;
			default: // STYLE_COLOR_WHITE
				style->dot_color = 0xFFFF;
				break;
		}
	}
	else //if (bppOut == 32)
	{
		switch (style->style & 0x07)
		{
			case STYLE_COLOR_RED:
				style->dot_color = 0xFF0000;
				break;
			case STYLE_COLOR_GREEN:
				style->dot_color = 0x00FF00;
				break;
			case STYLE_COLOR_BLUE:
				style->dot_color = 0x0000FF;
				break;
			default: // STYLE_COLOR_WHITE
				style->dot_color = 0xFFFFFF;
				break;
		}
	}
	
	style->double_size = ((style->style & STYLE_DOUBLESIZE) ? TRUE : FALSE);
	style->transparent = ((style->style & STYLE_TRANSPARENT) ? TRUE : FALSE);
}


/**
 * calc_transparency_mask(): Calculate the transparency mask.
 */
void calc_transparency_mask(void)
{
	if (bppOut == 15)
		m_Transparency_Mask = 0x7BDE;
	else if (bppOut == 16)
		m_Transparency_Mask = 0xF7DE;
	else //if (bppOut == 32)
		m_Transparency_Mask = 0xFEFEFE;
}