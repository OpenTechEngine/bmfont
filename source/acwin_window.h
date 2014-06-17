/*
   AngelCode Tool Box Library
   Copyright (c) 2004-2014 Andreas Jonsson
  
   This software is provided 'as-is', without any express or implied 
   warranty. In no event will the authors be held liable for any 
   damages arising from the use of this software.

   Permission is granted to anyone to use this software for any 
   purpose, including commercial applications, and to alter it and 
   redistribute it freely, subject to the following restrictions:

   1. The origin of this software must not be misrepresented; you 
      must not claim that you wrote the original software. If you use
      this software in a product, an acknowledgment in the product 
      documentation would be appreciated but is not required.

   2. Altered source versions must be plainly marked as such, and 
      must not be misrepresented as being the original software.

   3. This notice may not be removed or altered from any source 
      distribution.
  
   Andreas Jonsson
   andreas@angelcode.com
*/


// 2014-06-16  SetMenu and SetAccelerator takes an integer representing the resource
// 2014-06-16  Removed #include <windows.h> in this header to, instead it needs to be included where Windows API is used
// 2014-06-16  Added ConvertTCharToUtf8 and ConvertUtf8ToTChar
// 2011-07-30  Undefined some macros from windows.h


// To compile with this class you must link with:
// user32.lib gdi32.lib


#ifndef ACWIN_WINDOW_H
#define ACWIN_WINDOW_H

#ifndef _INC_WINDOWS
#error Must include <windows.h> in .cpp file before <acwin_windows.h>
#endif

#include <string>

namespace acWindow
{
#define EWND_NO_WINDOW_CLASS           -1
#define EWND_CREATE_WINDOW_FAILED      -2
#define EWND_REGISTER_CLASS_FAILED     -3
#define EWND_LOAD_RESOURCE_FAILED      -4
#define EWND_ALREADY_ATTACHED          -5
#define EWND_OTHER_IS_ALREADY_ATTACHED -6
#define EWND_HOOK_FAILED               -7
#define EWND_NOT_ATTACHED              -8

#define AC_REGDEFBRUSH  HBRUSH(-1)
#define AC_REGDEFICON   HICON(-1)
#define AC_REGDEFCURSOR HCURSOR(-1)

class CWindow
{
public:
	CWindow();
	virtual ~CWindow();

	int  Create(const char *title, int width, int height, DWORD style, DWORD styleEx, CWindow *parent, const char *className); 
	int  SetAccelerator(int acceleratorId);
	int  SetAccelerator(ACCEL *accels, int numItems);
	int  SetMenu(int menuresourceId);

	void Invalidate(BOOL erase);

	HWND GetHandle();
	
	int Attach(HWND hWnd);
	int Detach();
	virtual int Subclass(HWND hWnd);

	static CWindow *FromHandle(HWND hWnd);
	static bool CheckMessages(bool wait);
	static int RegisterClass(const char *className, UINT style, HBRUSH bgBrush, HICON icon, HICON smallIcon, HCURSOR cursor);
	static int HookCreate(CWindow *wnd);

	virtual BOOL DrawItem(DRAWITEMSTRUCT *di);

	void UpdateWindowText(const char *text);

	bool IsVisible();

protected:
	virtual LRESULT DefWndProc(UINT msg, WPARAM wParam, LPARAM lParam);
    virtual LRESULT MsgProc(UINT msg, WPARAM wParam, LPARAM lParam);
	virtual int TranslateMessage(MSG *msg);

	void HideSystemMenuButton();

	HWND   hWnd;
	HACCEL hAccel;
	HMENU  hMenu;

	WNDPROC originalProc;

private:
	static CWindow *wndCreator;
	static HHOOK hCreateHook;
	static LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
	static LRESULT CALLBACK CreateProc(int, WPARAM, LPARAM);
};

// Helpers for converting strings between UTF8 and Windows' TCHAR
// These are prepared for both when the application is built for multibyte and when built for unicode
void ConvertTCharToUtf8(const TCHAR *buf, std::string &utf8);
void ConvertUtf8ToTChar(const std::string &utf8, TCHAR *buf, size_t bufSize);

}

#endif