/***************************************************************************
 * MDP: Blargg's NTSC Filter. (Window Code) (Win32)                        *
 *                                                                         *
 * Copyright (c) 2006 by Shay Green                                        *
 * MDP version Copyright (c) 2008-2010 by David Korth                      *
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

// Win32 includes.
#include "libgsft/w32u/w32u_windows.h"
#include "libgsft/w32u/w32u_windowsx.h"
#include "libgsft/w32u/w32u_commctrl.h"

// C includes.
#include <math.h>
#include <stdio.h>

#include "ntsc_window.h"
#include "ntsc_window_common.h"

#include "mdp_render_blargg_ntsc.h"
#include "mdp_render_blargg_ntsc_plugin.h"
#include "md_ntsc.hpp"

// MDP error codes.
#include "mdp/mdp_error.h"

// libgsft includes.
#include "libgsft/gsft_win32.h"
#include "libgsft/gsft_win32_gdi.h"
#include "libgsft/gsft_szprintf.h"

// Window.
static HWND ntsc_window = NULL;
static WNDCLASS ntsc_window_wndclass;
static BOOL ntsc_window_child_windows_created;

// Widgets.
static HWND cboPresets;
static HWND chkScanline;
static HWND chkInterp;
static HWND chkCXA2025AS;
static HWND lblCtrlValues[NTSC_CTRL_COUNT];
static HWND hscCtrlValues[NTSC_CTRL_COUNT];

// Widget IDs.
#define IDC_NTSC_PRESETS  	0x1000
#define IDC_NTSC_SCANLINE	0x1001
#define IDC_NTSC_INTERP		0x1002
#define IDC_NTSC_CXA2025AS	0x1003
#define IDC_NTSC_TRACKBAR 	0x1100

// Window Procedure.
static LRESULT CALLBACK ntsc_window_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam);

// Create Child Windows function.
static void ntsc_window_create_child_windows(HWND hWnd);

// Callbacks.
static void	ntsc_window_callback_cboPresets_changed(void);
static void	ntsc_window_callback_hscCtrlValues_value_changed(int setting);

static BOOL	ntsc_window_do_callbacks;

// Window size. (NOTE: THESE ARE IN DIALOG UNITS, and must be converted to pixels using DLU_X() / DLU_Y().)
#define NTSC_WINDOW_WIDTH  235
#define NTSC_WINDOW_HEIGHT 232

// HINSTANCE.
// TODO: Move to DllMain().
static HINSTANCE ntsc_hInstance;


/**
 * ntsc_window_show(): Show the NTSC Plugin Options window.
 * @param parent Parent window.
 */
void ntsc_window_show(void *parent)
{
	if (ntsc_window)
	{
		// NTSC Plugin Options window is already visible.
		// Set focus.
		// TODO
		return;
	}
	
	// Initialize the Win32 Unicode Translation Layer.
	w32u_init();
	
	ntsc_window_child_windows_created = FALSE;
	
	// If no HINSTANCE was specified, use the main executable's HINSTANCE.
	if (!ntsc_hInstance)
		ntsc_hInstance = pGetModuleHandleU(NULL);
	
	// Create the window class.
	if (ntsc_window_wndclass.lpfnWndProc != ntsc_window_wndproc)
	{
		ntsc_window_wndclass.style = 0;
		ntsc_window_wndclass.lpfnWndProc = ntsc_window_wndproc;
		ntsc_window_wndclass.cbClsExtra = 0;
		ntsc_window_wndclass.cbWndExtra = 0;
		ntsc_window_wndclass.hInstance = ntsc_hInstance;
		ntsc_window_wndclass.hIcon = NULL; //LoadIconA(ntsc_hInstance, MAKEINTRESOURCE(IDI_NTSC));
		ntsc_window_wndclass.hCursor = LoadCursorA(NULL, IDC_ARROW);
		ntsc_window_wndclass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		ntsc_window_wndclass.lpszMenuName = NULL;
		ntsc_window_wndclass.lpszClassName = "ntsc_window_wndclass";
		
		pRegisterClassU(&ntsc_window_wndclass);
	}
	
	// Create the window.
	ntsc_window = pCreateWindowU("ntsc_window_wndclass", "Blargg's NTSC Filter",
					WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION,
					CW_USEDEFAULT, CW_USEDEFAULT,
					DLU_X(NTSC_WINDOW_WIDTH), DLU_Y(NTSC_WINDOW_HEIGHT),
					(HWND)parent, NULL, ntsc_hInstance, NULL);
	
	// Load the current settings.
	ntsc_window_load_settings();
	
	// Window adjustment.
	gsft_win32_set_actual_window_size(ntsc_window, DLU_X(NTSC_WINDOW_WIDTH), DLU_Y(NTSC_WINDOW_HEIGHT));
	gsft_win32_center_on_window(ntsc_window, (HWND)parent);
	
	UpdateWindow(ntsc_window);
	ShowWindow(ntsc_window, TRUE);
	
	// Register the window with MDP Host Services.
	ntsc_host_srv->window_register(&mdp, ntsc_window);
}


// These are in Dialog Units.
#define NTSC_WIDGETNAME_WIDTH  45
#define NTSC_WIDGETNAME_HEIGHT 10
#define NTSC_VALUELABEL_WIDTH  20
#define NTSC_VALUELABEL_HEIGHT 10
#define NTSC_TRACKBAR_WIDTH  (NTSC_WINDOW_WIDTH-5-10-NTSC_WIDGETNAME_WIDTH-5-NTSC_VALUELABEL_WIDTH-5-5)
#define NTSC_TRACKBAR_HEIGHT 16
#define NTSC_TRACKBAR_STYLE  (WS_CHILD | WS_VISIBLE | WS_TABSTOP | TBS_HORZ | TBS_BOTTOM | TBS_NOTICKS)
/**
 * ntsc_window_create_child_windows(): Create child windows.
 * @param hWnd Parent window.
 */
static void ntsc_window_create_child_windows(HWND hWnd)
{
	if (ntsc_window_child_windows_created)
		return;
	
	// Don't do any callbacks yet.
	ntsc_window_do_callbacks = FALSE;
	
	// Initialize libgsft_win32_gdi.
	gsft_win32_gdi_init(hWnd);
	
	// Create the main frame.
	HWND grpBox = pCreateWindowU(WC_BUTTON, "NTSC Configuration",
					WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
					DLU_X(5), DLU_Y(5),
					DLU_X(NTSC_WINDOW_WIDTH-10), DLU_Y(NTSC_WINDOW_HEIGHT-5-10-14),
					hWnd, NULL, ntsc_hInstance, NULL);
	SetWindowFontU(grpBox, w32_fntMessage, TRUE);
	
	// Add a label for the presets dropdown.
	HWND lblPresets = pCreateWindowU(WC_STATIC, "&Presets:",
						WS_CHILD | WS_VISIBLE | SS_LEFT,
						DLU_X(5+5), DLU_Y(5+10+2),
						DLU_X(40), DLU_Y(10),
						hWnd, NULL, ntsc_hInstance, NULL);
	SetWindowFontU(lblPresets, w32_fntMessage, TRUE);
	
	// Add the presets dropdown.
	cboPresets = pCreateWindowU(WC_COMBOBOX, NULL,
					WS_CHILD | WS_VISIBLE | WS_TABSTOP | CBS_DROPDOWNLIST,
					DLU_X(5+40+5), DLU_Y(5+10),
					DLU_X(60), DLU_Y(14*NTSC_PRESETS_COUNT),
					hWnd, (HMENU)IDC_NTSC_PRESETS, ntsc_hInstance, NULL);
	SetWindowFontU(cboPresets, w32_fntMessage, TRUE);
	
	// Add the presets to the dropdown.
	int i;
	for (i = 0; i < NTSC_PRESETS_COUNT; i++)
	{
		ComboBox_AddStringU(cboPresets, ntsc_presets[i].name);
	}
	
	// Scanlines checkbox.
	chkScanline = pCreateWindowU(WC_BUTTON, "S&canlines",
					WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					DLU_X(5+40+5+60+5), DLU_Y(5+10+1),
					DLU_X(45), DLU_Y(10),
					hWnd, (HMENU)IDC_NTSC_SCANLINE, ntsc_hInstance, NULL);
	SetWindowFontU(chkScanline, w32_fntMessage, TRUE);
	
	// Interpolation checkbox.
	chkInterp = pCreateWindowU(WC_BUTTON, "&Interpolation",
					WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					DLU_X(5+40+5+60+5+45+5), DLU_Y(5+10+1),
					DLU_X(55), DLU_Y(10),
					hWnd, (HMENU)IDC_NTSC_INTERP, ntsc_hInstance, NULL);
	SetWindowFontU(chkInterp, w32_fntMessage, TRUE);
	
	// Interpolation checkbox.
	chkCXA2025AS = pCreateWindowU(WC_BUTTON, "Use Sony C&X2025AS US decoder.",
					WS_CHILD | WS_VISIBLE | BS_AUTOCHECKBOX,
					DLU_X(5+5), DLU_Y(5+10+15),
					DLU_X(128), DLU_Y(10),
					hWnd, (HMENU)IDC_NTSC_CXA2025AS, ntsc_hInstance, NULL);
	SetWindowFontU(chkCXA2025AS, w32_fntMessage, TRUE);
	
	// Create the adjustment widgets.
	int hscTop = DLU_Y(5+10+10+15);
	for (i = 0; i < NTSC_CTRL_COUNT; i++)
	{
		// Label.
		HWND lblWidgetName = pCreateWindowU(WC_STATIC, ntsc_controls[i].name_mnemonic,
							WS_CHILD | WS_VISIBLE | SS_LEFT,
							DLU_X(5+5), hscTop+DLU_Y(2),
							DLU_X(NTSC_WIDGETNAME_WIDTH), DLU_Y(NTSC_WIDGETNAME_HEIGHT),
							hWnd, NULL, ntsc_hInstance, NULL);
		SetWindowFontU(lblWidgetName, w32_fntMessage, TRUE);
		
		// Value Label.
		lblCtrlValues[i] = pCreateWindowU(WC_STATIC, NULL,
							WS_CHILD | WS_VISIBLE | SS_RIGHT,
							DLU_X(5+5+NTSC_WIDGETNAME_WIDTH+5), hscTop+DLU_Y(2),
							DLU_X(NTSC_VALUELABEL_WIDTH), DLU_Y(NTSC_VALUELABEL_HEIGHT),
							hWnd, NULL, ntsc_hInstance, NULL);
		SetWindowFontU(lblCtrlValues[i], w32_fntMessage, TRUE);
		
		// Trackbar.
		hscCtrlValues[i] = pCreateWindowU(TRACKBAR_CLASS, NULL, NTSC_TRACKBAR_STYLE,
							DLU_X(5+5+NTSC_WIDGETNAME_WIDTH+5+NTSC_VALUELABEL_WIDTH+5), hscTop,
							DLU_X(NTSC_TRACKBAR_WIDTH), DLU_Y(NTSC_TRACKBAR_HEIGHT),
							hWnd, (HMENU)(IDC_NTSC_TRACKBAR + i), ntsc_hInstance, NULL);
		pSendMessageU(hscCtrlValues[i], TBM_SETUNICODEFORMAT, w32u_is_unicode, 0);
		pSendMessageU(hscCtrlValues[i], TBM_SETPAGESIZE, 0, ntsc_controls[i].step);
		pSendMessageU(hscCtrlValues[i], TBM_SETRANGE, TRUE, MAKELONG(ntsc_controls[i].min, ntsc_controls[i].max));
		pSendMessageU(hscCtrlValues[i], TBM_SETPOS, TRUE, 0);
		
		// Next widget.
		hscTop += DLU_Y(16);
	}
	
	// Create the "Close" button.
	HWND btnClose = pCreateWindowU(WC_BUTTON, "&Close",
					WS_CHILD | WS_VISIBLE | WS_TABSTOP,
					DLU_X(NTSC_WINDOW_WIDTH-50-5), DLU_Y(NTSC_WINDOW_HEIGHT-14-5),
					DLU_X(50), DLU_Y(14),
					hWnd, (HMENU)IDCLOSE, ntsc_hInstance, NULL);
	SetWindowFontU(btnClose, w32_fntMessage, TRUE);
	
	// Child windows created.
	ntsc_window_child_windows_created = TRUE;
}


/**
 * ntsc_wndproc(): Window procedure.
 * @param hWnd hWnd of the object sending a message.
 * @param message Message being sent by the object.
 * @param wParam
 * @param lParam
 * @return
 */
static LRESULT CALLBACK ntsc_window_wndproc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
		case WM_CREATE:
			ntsc_window_create_child_windows(hWnd);
			break;
		
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDCANCEL:
				case IDCLOSE:
					// Close.
					ntsc_window_close();
					break;
				
				case IDC_NTSC_PRESETS:
					if (HIWORD(wParam) == CBN_SELCHANGE)
					{
						// Presets selection has changed.
						ntsc_window_callback_cboPresets_changed();
					}
					break;
				
				case IDC_NTSC_SCANLINE:
					if (Button_GetCheck(chkScanline) == BST_CHECKED)
						mdp_md_ntsc_effects |= MDP_MD_NTSC_EFFECT_SCANLINE;
					else
						mdp_md_ntsc_effects &= ~MDP_MD_NTSC_EFFECT_SCANLINE;
					break;
				
				case IDC_NTSC_INTERP:
					if (Button_GetCheck(chkInterp) == BST_CHECKED)
						mdp_md_ntsc_effects |= MDP_MD_NTSC_EFFECT_INTERP;
					else
						mdp_md_ntsc_effects &= ~MDP_MD_NTSC_EFFECT_INTERP;
					break;
				
				case IDC_NTSC_CXA2025AS:
					if (Button_GetCheck(chkCXA2025AS) == BST_CHECKED)
						mdp_md_ntsc_effects |= MDP_MD_NTSC_EFFECT_CXA2025AS;
					else
						mdp_md_ntsc_effects &= ~MDP_MD_NTSC_EFFECT_CXA2025AS;
					mdp_md_ntsc_reinit_setup(); // Changing the decoder matrix requires reinitializing the filter.
					break;
				
				default:
					break;
			}
			break;
		
		case WM_HSCROLL:
		{
			// Determine which control this is.
			// TODO: Use a hash table instead of a for loop.
			int i;
			for (i = 0; i < NTSC_CTRL_COUNT; i++)
			{
				if (hscCtrlValues[i] == (HWND)lParam)
				{
					// NTSC control has been adjusted.
					ntsc_window_callback_hscCtrlValues_value_changed(i);
					break;
				}
			}
			break;
		}
		
		case WM_DESTROY:
			ntsc_window_close();
			break;
	}
	
	return pDefWindowProcU(hWnd, message, wParam, lParam);
}


/**
 * ntsc_window_close(): Close the NTSC Plugin Options window.
 */
void ntsc_window_close(void)
{
	if (!ntsc_window)
		return;
	
	// Unregister the window from MDP Host Services.
	ntsc_host_srv->window_unregister(&mdp, ntsc_window);
	
	// Destroy the window.
	HWND tmp = ntsc_window;
	ntsc_window = NULL;
	DestroyWindow(tmp);
	
	// Shut down libgsft_win32_gdi.
	gsft_win32_gdi_end();
	
	// Shut down the Win32 Unicode Translation Layer.
	w32u_end();
}


/**
 * ntsc_window_load_settings(): Load the NTSC settings.
 */
void MDP_FNCALL ntsc_window_load_settings(void)
{
	if (!ntsc_window)
		return;
	
	ntsc_window_do_callbacks = FALSE;
	
	// Set the preset dropdown box.
	int i;
	for (i = 0; i < NTSC_PRESETS_COUNT; i++)
	{
		if (!ntsc_presets[i].setup)
		{
			// "Custom". This is the last item in the predefined list.
			// Since the current setup doesn't match anything else,
			// it must be a custom setup.
			ComboBox_SetCurSelU(cboPresets, i);
			break;
		}
		else
		{
			// Check if this preset matches the current setup.
			if (!memcmp(mdp_md_ntsc_setup.params,
					ntsc_presets[i].setup->params,
					sizeof(mdp_md_ntsc_setup.params)))
			{
				// Match found!
				ComboBox_SetCurSelU(cboPresets, i);
				break;
			}
		}
	}
	
	// Scanlines / Interpolation / CXA2025AS
	Button_SetCheckU(chkScanline, ((mdp_md_ntsc_effects & MDP_MD_NTSC_EFFECT_SCANLINE) ? BST_CHECKED : BST_UNCHECKED));
	Button_SetCheckU(chkInterp, ((mdp_md_ntsc_effects & MDP_MD_NTSC_EFFECT_INTERP) ? BST_CHECKED : BST_UNCHECKED));
	Button_SetCheckU(chkCXA2025AS, ((mdp_md_ntsc_effects & MDP_MD_NTSC_EFFECT_CXA2025AS) ? BST_CHECKED : BST_UNCHECKED));
	
	// Load all settings.
	for (i = 0; i < NTSC_CTRL_COUNT; i++)
	{
		pSendMessageU(hscCtrlValues[i], TBM_SETPOS, TRUE,
				ntsc_internal_to_display(i, mdp_md_ntsc_setup.params[i]));
		ntsc_window_callback_hscCtrlValues_value_changed(i);
	}
	
	ntsc_window_do_callbacks = TRUE;
}


/**
 * ntsc_window_callback_cboPresets_changed(): The "Presets" combo box has been changed.
 */
static void ntsc_window_callback_cboPresets_changed(void)
{
	if (!ntsc_window_do_callbacks)
		return;
	
	// Load the specified preset setup.
	int i = ComboBox_GetCurSelU(cboPresets);
	if (i == -1 || i >= NTSC_PRESETS_COUNT)
		return;
	
	if (!ntsc_presets[i].setup)
		return;
	
	// Reinitialize the NTSC filter with the new settings.
	mdp_md_ntsc_setup = *(ntsc_presets[i].setup);
	mdp_md_ntsc_reinit_setup();
	
	// Load the new settings in the window.
	ntsc_window_load_settings();
}


/**
 * ntsc_window_callback_hscCtrlValues_value_changed(): One of the adjustment controls has been changed.
 * @param setting Setting ID.
 */
static void ntsc_window_callback_hscCtrlValues_value_changed(int setting)
{
	if (setting < 0 || setting >= NTSC_CTRL_COUNT)
		return;
	
	// Update the label for the adjustment widget.
	char tmp[16];
	int val = pSendMessageU(hscCtrlValues[setting], TBM_GETPOS, 0, 0);
	
	// Adjust the value to have the appropriate number of decimal places.
	if (setting == 0)
	{
		// Hue. No decimal places.
		szprintf(tmp, sizeof(tmp), "%d" NTSC_DEGREE_SYMBOL, val);
	}
	else
	{
		// Other adjustment. 2 decimal places.
		szprintf(tmp, sizeof(tmp), "%0.2f", ((double)val / 100.0));
	}
	
	Static_SetTextU(lblCtrlValues[setting], tmp);
	
	if (!ntsc_window_do_callbacks)
		return;
	
	// Adjust the NTSC filter.
	mdp_md_ntsc_setup.params[setting] = ntsc_display_to_internal(setting, val);
	
	// Set the "Presets" dropdown to "Custom".
	ComboBox_SetCurSelU(cboPresets, NTSC_PRESETS_COUNT-1);
	
	// Reinitialize the NTSC filter with the new settings.
	mdp_md_ntsc_reinit_setup();
}
