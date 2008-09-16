/**
 * Gens: Video Drawing class - DirectDraw
 */

#ifndef GENS_V_DRAW_DDRAW_HPP
#define GENS_V_DRAW_DDRAW_HPP

#include <ddraw.h>

#include "v_draw.hpp"

class VDraw_DDraw : public VDraw
{
	public:
		VDraw_DDraw();
		VDraw_DDraw(VDraw *oldDraw);
		~VDraw_DDraw();
		
		int Init_Video(HWND hWnd);
		void End_Video(void);
		
		// Initialize the graphics subsystem.
		int Init_Subsystem(void);
		
		// Shut down the graphics subsystem.
		int Shut_Down(void);
		
		// Clear the screen.
		void clearScreen(void);
		//void Clear_Primary_Screen(void);
		//void Clear_Back_Screen(void);
		
		// Update VSync value.
		void updateVSync(bool fromInitSDLGL = false);
		
		// DirectDraw functions.
		int VDraw_DDraw::clearPrimaryScreen(void);
		int VDraw_DDraw::clearBackScreen(void);
		void VDraw_DDraw::restorePrimary(void);
		
	protected:
		int Init_Fail(HWND hWnd, const char *err);
		
		int Init_DDraw_Renderer(int w, int h, bool reinitSDL = true);
		
		// Flip the screen buffer. (Called by v_draw.)
		int flipInternal(void);
		
		// Adjust stretch parameters.
		void stretchAdjustInternal(void);
		
		// Update the renderer.
		void updateRenderer(void);
		
		// Stretch parameters
		float m_HStretch, m_VStretch;
		
		// X and Y resolutions.
		int Res_X;
		int Res_Y;
		
		// DirectDraw variables
		LPDIRECTDRAW lpDD_Init;
		LPDIRECTDRAW4 lpDD;
		LPDIRECTDRAWSURFACE4 lpDDS_Primary;
		LPDIRECTDRAWSURFACE4 lpDDS_Flip;
		LPDIRECTDRAWSURFACE4 lpDDS_Back;
		LPDIRECTDRAWSURFACE4 lpDDS_Blit;
		LPDIRECTDRAWCLIPPER lpDDC_Clipper;
		
		HRESULT RestoreGraphics(void);
		void CalculateDrawArea(int Render_Mode, RECT& RectDest, RECT& RectSrc, float& Ratio_X, float& Ratio_Y, int& Dep);
		
		// Win32 stuff
		virtual void reinitGensWindow(HWND hWnd);
};

#endif /* GENS_V_DRAW_DDRAW_HPP */
