/***************************************************************************
 * Gens: (GTK+) Plugin Manager Window.                                     *
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

#include "plugin_manager_window.hpp"
#include "gens/gens_window.hpp"

#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <stdint.h>

#include "emulator/g_main.hpp"

#include "ui/win32/charset.hpp"
#include "ui/win32/resource.h"

// Plugin Manager
#include "plugins/pluginmgr.hpp"

// Windows includes
#include <windowsx.h>
#include <commctrl.h>

// C++ includes
#include <string>
#include <sstream>
#include <vector>
using std::endl;
using std::string;
using std::stringstream;
using std::vector;


// Window class.
WNDCLASS PluginManagerWindow::m_WndClass;

// Sizes. (TODO: Figure out a good size.)
const int PluginManagerWindow::m_fraPluginList_Width = 320;
const int PluginManagerWindow::m_fraPluginList_Height = 144;
const int PluginManagerWindow::m_fraPluginInfo_Width = 320;
const int PluginManagerWindow::m_fraPluginInfo_Height = 248;
const int PluginManagerWindow::m_WndWidth = 320+8+8;
const int PluginManagerWindow::m_WndHeight = 8+m_fraPluginList_Height+8+m_fraPluginInfo_Height+8+24+8;


PluginManagerWindow* PluginManagerWindow::m_Instance = NULL;
PluginManagerWindow* PluginManagerWindow::Instance(HWND parent)
{
	if (m_Instance == NULL)
	{
		// Instance is deleted. Initialize the General Options window.
		m_Instance = new PluginManagerWindow();
	}
	else
	{
		// Instance already exists. Set focus.
		m_Instance->setFocus();
	}
	
	// Set modality of the window.
	if (!parent)
		parent = Gens_hWnd;
	m_Instance->setModal(parent);
	
	return m_Instance;
}


/**
 * PluginManagerWindow: Create the General Options Window.
 */
PluginManagerWindow::PluginManagerWindow()
{
	m_childWindowsCreated = false;
	
	// Create the window class.
	if (m_WndClass.lpfnWndProc != WndProc_STATIC)
	{
		m_WndClass.style = CS_OWNDC | CS_HREDRAW | CS_VREDRAW;
		m_WndClass.lpfnWndProc = WndProc_STATIC;
		m_WndClass.cbClsExtra = 0;
		m_WndClass.cbWndExtra = 0;
		m_WndClass.hInstance = ghInstance;
		m_WndClass.hIcon = LoadIcon(ghInstance, MAKEINTRESOURCE(IDI_SONIC_HEAD));
		m_WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
		m_WndClass.hbrBackground = GetSysColorBrush(COLOR_3DFACE);
		m_WndClass.lpszMenuName = NULL;
		m_WndClass.lpszClassName = "Gens_Plugin_Manager";
		
		RegisterClass(&m_WndClass);
	}
	
	// Messages are processed before the object is finished being created,
	// so this assignment is needed.
	m_Instance = this;
	
	// Create the window.
	// TODO: Don't hardcode the parent window.
	m_Window = CreateWindowEx(NULL, "Gens_Plugin_Manager", "Plugin Manager",
				  WS_DLGFRAME | WS_POPUP | WS_SYSMENU | WS_CAPTION,
				  CW_USEDEFAULT, CW_USEDEFAULT,
				  m_WndWidth, m_WndHeight,
				  Gens_hWnd, NULL, ghInstance, NULL);
	
	// Set the actual window size.
	Win32_setActualWindowSize(m_Window, m_WndWidth, m_WndHeight);
	
	// Center the window on the Gens window.
	Win32_centerOnGensWindow(m_Window);
	
	UpdateWindow(m_Window);
	ShowWindow(m_Window, 1);
}


PluginManagerWindow::~PluginManagerWindow()
{
	m_Instance = NULL;
}


LRESULT CALLBACK PluginManagerWindow::WndProc_STATIC(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	return m_Instance->WndProc(hWnd, message, wParam, lParam);
}


/**
 * WndProc(): The Plugin Manager window procedure.
 * @param hWnd hWnd of the object sending a message.
 * @param message Message being sent by the object.
 * @param wParam
 * @param lParam
 * @return
 */
LRESULT CALLBACK PluginManagerWindow::WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch(message)
	{
		case WM_CREATE:
			if (!m_childWindowsCreated)
				createChildWindows(hWnd);
			break;
		
		case WM_CLOSE:
			DestroyWindow(m_Window);
			return 0;
		
		case WM_MENUSELECT:
		case WM_ENTERSIZEMOVE:
		case WM_NCLBUTTONDOWN:
		case WM_NCRBUTTONDOWN:
			// Prevent audio stuttering when one of the following events occurs:
			// - Menu is opened.
			// - Window is resized.
			// - Left/Right mouse button down on title bar.
			audio->clearSoundBuffer();
			break;
		
		case WM_COMMAND:
			switch (LOWORD(wParam))
			{
				case IDC_BTN_OK:
				case IDOK:
				case IDC_BTN_CANCEL:
				case IDCANCEL:
					DestroyWindow(m_Window);
					break;
				
				case IDC_PLUGIN_MANAGER_LSTPLUGINLIST:
					if (HIWORD(wParam) == LBN_SELCHANGE)
						lstPluginList_cursor_changed();
					break;
			}
			
			break;
		
		case WM_DESTROY:
			if (hWnd != m_Window)
				break;
			
			delete this;
			break;
	}
	
	return DefWindowProc(hWnd, message, wParam, lParam);
}


void PluginManagerWindow::createChildWindows(HWND hWnd)
{
	// Create the plugin list frame.
	createPluginListFrame(hWnd);
	
	// Create the plugin information frame.
	createPluginInfoFrame(hWnd);
	
	// Add the OK button.
	addDialogButtons(hWnd, WndBase::BAlign_Right,
			 WndBase::BUTTON_OK, WndBase::BUTTON_OK);
	
	// Populate the plugin list.
	populatePluginList();
	
	// Child windows created.
	m_childWindowsCreated = true;
}


void PluginManagerWindow::createPluginListFrame(HWND hWnd)
{
	// Create the plugin list frame.
	HWND fraPluginList;
	fraPluginList = CreateWindow(WC_BUTTON, "Internal Plugins",
				     WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
				     8, 8, m_fraPluginList_Width, m_fraPluginList_Height,
				     hWnd, NULL, ghInstance, NULL);
	SetWindowFont(fraPluginList, fntMain, true);
	
	// Create the plugin listbox.
	m_lstPluginList = CreateWindowEx(WS_EX_CLIENTEDGE, WC_LISTBOX, "",
					 WS_CHILD | WS_VISIBLE | WS_TABSTOP | WS_BORDER | WS_VSCROLL | LBS_NOTIFY,
					 8+8, 8+16, m_fraPluginList_Width-16, m_fraPluginList_Height-24,
					 hWnd, (HMENU)IDC_PLUGIN_MANAGER_LSTPLUGINLIST, ghInstance, NULL);
	SetWindowFont(m_lstPluginList, fntMain, true);
}


void PluginManagerWindow::createPluginInfoFrame(HWND hWnd)
{
	const int top = 8+m_fraPluginList_Height+8;
	
	HWND fraPluginInfo;
	fraPluginInfo = CreateWindow(WC_BUTTON, "Plugin Information",
				     WS_CHILD | WS_VISIBLE | BS_GROUPBOX,
				     8, top,
				     m_fraPluginInfo_Width, m_fraPluginInfo_Height,
				     hWnd, NULL, ghInstance, NULL);
	SetWindowFont(fraPluginInfo, fntMain, true);
	
#ifdef GENS_PNG
	// Create the plugin icon widget.
	createPluginIconWidget(hWnd);
#endif /* GENS_PNG */
	
	// Label for the main plugin info.
#ifdef GENS_PNG
	const int lblPluginMainInfo_Left = 8+8+32+8;
#else /* !GENS_PNG */
	const int lblPluginMainInfo_Left = 8+8;
#endif /* GENS_PNG */
	const int lblPluginMainInfo_Height = 96;
	
	m_lblPluginMainInfo = CreateWindow(WC_EDIT, NULL,
					   WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE,
					   lblPluginMainInfo_Left, top+16,
					   m_fraPluginInfo_Width - lblPluginMainInfo_Left, lblPluginMainInfo_Height,
					   hWnd, NULL, ghInstance, NULL);
	SetWindowFont(m_lblPluginMainInfo, fntMain, true);
	Edit_SetReadOnly(m_lblPluginMainInfo, true);
	
	// Label for secondary plugin info.
	const int lblPluginSecInfo_Height = 40;
	m_lblPluginSecInfo = CreateWindow(WC_EDIT, NULL,
					   WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE,
					   8+8, top+16+lblPluginMainInfo_Height+8,
					   m_fraPluginInfo_Width-8-8, lblPluginSecInfo_Height,
					   hWnd, NULL, ghInstance, NULL);
	SetWindowFont(m_lblPluginSecInfo, fntMain, true);
	Edit_SetReadOnly(m_lblPluginSecInfo, true);
	
	// Label for the plugin description.
	const int lblPluginDesc_Height = 72;
	m_lblPluginDesc = CreateWindow(WC_EDIT, NULL,
				       WS_CHILD | WS_VISIBLE | ES_LEFT | ES_MULTILINE,
				       8+8, top+16+lblPluginMainInfo_Height+8+lblPluginSecInfo_Height+8,
				       m_fraPluginInfo_Width-8-8, lblPluginDesc_Height,
				       hWnd, NULL, ghInstance, NULL);
	SetWindowFont(m_lblPluginDesc, fntMain, true);
	Edit_SetReadOnly(m_lblPluginDesc, true);
}


void PluginManagerWindow::populatePluginList(void)
{
	if (!m_lstPluginList)
		return;
	
	// Clear the plugin list.
	ListBox_ResetContent(m_lstPluginList);
	
	// Add all plugins to the listbox.
	char tmp[64];
	vector<MDP_t*>::iterator curPlugin;
	for (curPlugin = PluginMgr::vRenderPlugins.begin();
	     curPlugin != PluginMgr::vRenderPlugins.end(); curPlugin++)
	{
		MDP_t *plugin = (*curPlugin);
		const char *pluginName;
		if (plugin->desc && plugin->desc->name)
		{
			pluginName = plugin->desc->name;
		}
		else
		{
			// No description or name.
			// TODO: For external plugins, indicate the external file.
			sprintf(tmp, "[No name: 0x%08X]", (unsigned int)plugin);
			pluginName = tmp;
		}
		
		int index = ListBox_AddString(m_lstPluginList, pluginName);
		if (index != LB_ERR)
			ListBox_SetItemData(m_lstPluginList, index, plugin);
	}
}


void PluginManagerWindow::lstPluginList_cursor_changed(void)
{
	// Check which plugin is clicked.
	int index = ListBox_GetCurSel(m_lstPluginList);
	
	if (index == LB_ERR)
	{
		// No plugin selected.
		Edit_SetText(m_lblPluginMainInfo, "No plugin selected.");
		Edit_SetText(m_lblPluginSecInfo, NULL);
		Edit_SetText(m_lblPluginDesc, NULL);
#ifdef GENS_PNG
		clearIcon();
#endif /* GENS_PNG */
		return;
	}
	
	// Found a selected plugin.
	MDP_t *plugin = reinterpret_cast<MDP_t*>(ListBox_GetItemData(m_lstPluginList, index));
	
	// Get the plugin information.
	if (!plugin)
	{
		// Invalid plugin.
		Edit_SetText(m_lblPluginMainInfo, "Invalid plugin selected.");
		Edit_SetText(m_lblPluginSecInfo, NULL);
		Edit_SetText(m_lblPluginDesc, NULL);
#ifdef GENS_PNG
		clearIcon();
#endif /* GENS_PNG */
		return;
	}
	
	if (!plugin->desc)
	{
		Edit_SetText(m_lblPluginMainInfo, "This plugin does not have a valid description field.");
		Edit_SetText(m_lblPluginSecInfo, NULL);
		Edit_SetText(m_lblPluginDesc, NULL);
#ifdef GENS_PNG
		clearIcon();
#endif /* GENS_PNG */
		return;
	}
	
	// Fill in the descriptions.
	MDP_Desc_t *desc = plugin->desc;
	stringstream ssMainInfo;
	
	// Plugin name.
	ssMainInfo << "Name: " << (desc->name ? string(desc->name) : "(none)") << endl;
	
	// Plugin version.
	ssMainInfo << "Version: " << MDP_VERSION_MAJOR(plugin->pluginVersion)
				  << "." << MDP_VERSION_MINOR(plugin->pluginVersion)
				  << "." << MDP_VERSION_REVISION(plugin->pluginVersion) << endl;
	
	// Plugin author.
	ssMainInfo << "MDP Author: " + (desc->author_mdp ? string(desc->author_mdp) : "(none)") << endl;
	
	// Original code author.
	if (desc->author_orig)
	{
		ssMainInfo << "Original Author: " << string(desc->author_orig) << endl;
	}
	
	// Website.
	if (desc->website)
	{
		ssMainInfo << "Website: " << string(desc->website) << endl;
	}
	
	// License.
	ssMainInfo << "License: " + (desc->license ? string(desc->license) : "(none)");
	
	// Set the main plugin information.
	Edit_SetText(m_lblPluginMainInfo, ssMainInfo.str().c_str());
	
	// UUID.
	string sUUID = UUIDtoString(plugin->uuid);
	
	// Secondary plugin information.
	// Includes UUID and CPU flags.
	stringstream ssSecInfo;
	ssSecInfo << "UUID: " << sUUID << endl
		  << GetCPUFlags(plugin->cpuFlagsRequired, plugin->cpuFlagsSupported, true);
	
	// Set the secondary information label.
	Edit_SetText(m_lblPluginSecInfo, ssSecInfo.str().c_str());
	
	// Plugin description.
	if (desc->description)
	{
		string pluginDesc = string("Description:\n") + string(desc->description);
		Edit_SetText(m_lblPluginDesc, pluginDesc.c_str());
	}
	else
	{
		Edit_SetText(m_lblPluginDesc, NULL);
	}
	
#ifdef GENS_PNG
	// Plugin icon.
	if (!displayIcon(desc->icon, desc->iconLength))
	{
		// No plugin icon found. Clear the pixbuf.
		clearIcon();
	}
#endif /* GENS_PNG */
}


#ifdef GENS_PNG
/**
 * createPluginIconWidget(): Create the GTK+ plugin icon widget and pixbuf.
 * @param container Container for the plugin icon widget.
 */
inline void PluginManagerWindow::createPluginIconWidget(GtkBox *container)
{
	// Plugin icon pixbuf.
	m_pbufPluginIcon = gdk_pixbuf_new(GDK_COLORSPACE_RGB, TRUE, 8, 32, 32);
	g_object_set_data_full(G_OBJECT(m_Window), "m_pbufPluginIcon",
			       g_object_ref(m_pbufPluginIcon), (GDestroyNotify)g_object_unref);
	
	// Plugin icon widget.
	m_imgPluginIcon = gtk_image_new();
	gtk_widget_set_name(m_imgPluginIcon, "m_imgPluginIcon");
	gtk_misc_set_alignment(GTK_MISC(m_imgPluginIcon), 0.0f, 0.0f);
	gtk_widget_show(m_imgPluginIcon);
	g_object_set_data_full(G_OBJECT(m_Window), "m_imgPluginIcon",
			       g_object_ref(m_imgPluginIcon), (GDestroyNotify)g_object_unref);
	gtk_box_pack_start(GTK_BOX(container), m_imgPluginIcon, FALSE, FALSE, 0);
	
	// Clear the icon.
	clearIcon();
}


/**
 * displayIcon(): Displays the plugin icon.
 * @param icon Icon data. (PNG format)
 * @param iconLength Length of the icon data.
 * @return True if the icon was displayed; false otherwise.
 */
bool PluginManagerWindow::displayIcon(const unsigned char* icon, const unsigned int iconLength)
{
	static const unsigned char pngMagicNumber[8] = {0x89, 'P', 'N', 'G',0x0D, 0x0A, 0x1A, 0x0A};
	
	if (!icon || iconLength < sizeof(pngMagicNumber))
		return false;
	
	// Check that the icon is in PNG format.
	if (memcmp(icon, pngMagicNumber, sizeof(pngMagicNumber)))
	{
		// Not in PNG format.
		return false;
	}

	// Initialize libpng.
	
	png_structp png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
	if (!png_ptr)
		return false;
	
	png_infop info_ptr = png_create_info_struct(png_ptr);
	if (!info_ptr)
	{
		png_destroy_read_struct(&png_ptr, NULL, NULL);
		return false;
	}
	
	png_infop end_info = png_create_info_struct(png_ptr);
	if (!end_info)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}
	
	if (setjmp(png_jmpbuf(png_ptr)))
	{
		// TODO: Is setjmp() really necessary?
		png_destroy_read_struct(&png_ptr, &info_ptr, &end_info);
		return false;
	}
	
	// Set the custom read function.
	png_dataptr = icon;
	png_datalen = iconLength;
	png_datapos = 0;
	
	void *read_io_ptr = png_get_io_ptr(png_ptr);
	png_set_read_fn(png_ptr, read_io_ptr, &png_user_read_data);
	
	// Get the PNG information.
	png_read_info(png_ptr, info_ptr);
	
	// Get the PNG information.
	png_uint_32 width, height;
	int bit_depth, color_type, interlace_type, compression_type, filter_method;
	bool has_alpha = false;
	
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		     &interlace_type, &compression_type, &filter_method);
	
	
	if (width != 32 || height != 32)
	{
		// Not 32x32.
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		return false;
	}
	
	// Make sure RGB color is used.
	if (color_type == PNG_COLOR_TYPE_PALETTE)
		png_set_palette_to_rgb(png_ptr);
	else if (color_type == PNG_COLOR_TYPE_GRAY)
		png_set_gray_to_rgb(png_ptr);
	else if (color_type == PNG_COLOR_TYPE_RGB_ALPHA)
		has_alpha = true;
	
	// GTK+ expects RGBA format.
	// TODO: Check if this is the same on big-endian machines.
	
	// Convert tRNS to alpha channel.
	if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
	{
		png_set_tRNS_to_alpha(png_ptr);
		has_alpha = true;
	}
	
	// Convert 16-bit per channel PNG to 8-bit.
	if (bit_depth == 16)
		png_set_strip_16(png_ptr);
	
	// Get the new PNG information.
	png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
		     &interlace_type, &compression_type, &filter_method);
	
	// Check if the PNG image has an alpha channel.
	if (!has_alpha)
	{
		// No alpha channel specified.
		// Use filler instead.
		png_set_filler(png_ptr, 0xFF, PNG_FILLER_AFTER);
	}
	
	// Update the PNG info.
	png_read_update_info(png_ptr, info_ptr);
	
	// Create the row pointers.
	int rowstride = gdk_pixbuf_get_rowstride(m_pbufPluginIcon);
	guchar *pixels = gdk_pixbuf_get_pixels(m_pbufPluginIcon);
	png_bytep row_pointers[32];
	for (unsigned int i = 0; i < 32; i++)
	{
		row_pointers[i] = pixels;
		pixels += rowstride;
	}
	
	// Read the image data.
	png_read_image(png_ptr, row_pointers);
	
	// Close the PNG image.
	png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
	
	// Set the GTK+ image to the new icon.
	gtk_image_set_from_pixbuf(GTK_IMAGE(m_imgPluginIcon), m_pbufPluginIcon);
	
	return true;
}


/**
 * clearIcon(): Clear the plugin icon.
 */
void PluginManagerWindow::clearIcon(void)
{
	if (!m_pbufPluginIcon)
		return;
	
	guchar *pixels = gdk_pixbuf_get_pixels(m_pbufPluginIcon);
	int rowstride = gdk_pixbuf_get_rowstride(m_pbufPluginIcon);
	int height = gdk_pixbuf_get_height(m_pbufPluginIcon);
	int width = gdk_pixbuf_get_width(m_pbufPluginIcon);
	int bits_per_sample = gdk_pixbuf_get_bits_per_sample(m_pbufPluginIcon);
	int n_channels = gdk_pixbuf_get_n_channels(m_pbufPluginIcon);
	
	// The last row of the pixbuf data may not be fully allocated.
	// See http://library.gnome.org/devel/gdk-pixbuf/stable/gdk-pixbuf-gdk-pixbuf.html
	int size = (rowstride * (height - 1)) + (width * ((n_channels * bits_per_sample + 7) / 8));
	memset(pixels, 0x00, size);
	
	gtk_image_set_from_pixbuf(GTK_IMAGE(m_imgPluginIcon), m_pbufPluginIcon);
}
#endif /* GENS_PNG */