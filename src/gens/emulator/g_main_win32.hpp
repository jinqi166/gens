/**
 * Gens: Main loop. (Win32-specific code)
 */

#ifndef G_MAIN_WIN32_HPP
#define G_MAIN_WIN32_HPP

#ifdef __cplusplus
extern "C" {
#endif

#define GENS_DIR_SEPARATOR_STR "\\"
#define GENS_DIR_SEPARATOR_CHR '\\'

#include <windows.h>

extern HINSTANCE ghInstance;

// Fonts
extern HFONT fntMain;
extern HFONT fntTitle;

void Get_Save_Path(char *buf, size_t n);
void Create_Save_Directory(const char *dir);

int PASCAL WinMain(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR lpCmdLine, int nCmdShow);

#ifdef __cplusplus
}
#endif

#endif /* G_MAIN_WIN32_HPP */
