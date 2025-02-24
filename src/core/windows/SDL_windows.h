/*
  Simple DirectMedia Layer
  Copyright (C) 1997-2019 Sam Lantinga <slouken@libsdl.org>

  This software is provided 'as-is', without any express or implied
  warranty.  In no event will the authors be held liable for any damages
  arising from the use of this software.

  Permission is granted to anyone to use this software for any purpose,
  including commercial applications, and to alter it and redistribute it
  freely, subject to the following restrictions:

  1. The origin of this software must not be misrepresented; you must not
     claim that you wrote the original software. If you use this software
     in a product, an acknowledgment in the product documentation would be
     appreciated but is not required.
  2. Altered source versions must be plainly marked as such, and must not be
     misrepresented as being the original software.
  3. This notice may not be removed or altered from any source distribution.
*/

/* This is an include file for windows.h with the SDL build settings */

#ifndef _INCLUDED_WINDOWS_H
#define _INCLUDED_WINDOWS_H
#if defined(__WIN32__)
#define WIN32_LEAN_AND_MEAN
#define STRICT
#ifndef UNICODE
#define UNICODE 1
#endif
#undef _WIN32_WINNT
#define _WIN32_WINNT  0x501   /* Need 0x410 for AlphaBlend() and 0x500 for EnumDisplayDevices(), 0x501 for raw input */
#endif
#include <windows.h>
#include <basetyps.h>   /* for REFIID with broken mingw.org headers */

/* Routines to convert from UTF8 to native Windows text */
#if UNICODE
#define WIN_StringToUTF8(S) SDL_iconv_string("UTF-8", "UTF-16LE", (char *)(S), (SDL_wcslen(S)+1)*sizeof(WCHAR))
#define WIN_UTF8ToString(S) (WCHAR *)SDL_iconv_string("UTF-16LE", "UTF-8", (char *)(S), SDL_strlen(S)+1)
#else
/* !!! FIXME: UTF8ToString() can just be a SDL_strdup() here. */
#define WIN_StringToUTF8(S) SDL_iconv_string("UTF-8", "ASCII", (char *)(S), (SDL_strlen(S)+1))
#define WIN_UTF8ToString(S) SDL_iconv_string("ASCII", "UTF-8", (char *)(S), SDL_strlen(S)+1)
#endif
/* Sets an error message based on a given HRESULT */
extern int WIN_SetErrorFromHRESULT(const char *prefix,HRESULT hr);
/* Sets an error message based on GetLastError(). Always return -1. */
extern int WIN_SetError(const char *prefix);
/* Wrap up the oddities of CoInitialize() into a common function. */
extern HRESULT WIN_CoInitialize(void);
extern void WIN_CoUninitialize(void);
/* Returns SDL_TRUE if we're running on Windows Vista and newer */
extern BOOL WIN_IsWindowsVistaOrGreater(void);
/* Returns SDL_TRUE if we're running on Windows 7 and newer */
extern BOOL WIN_IsWindows7OrGreater(void);
/* You need to SDL_free() the result of this call. */
extern char *WIN_LookupAudioDeviceName(const WCHAR *name,const GUID *guid);
/* Checks to see if two GUID are the same. */
extern BOOL WIN_IsEqualGUID(const GUID *a,const GUID *b);
extern BOOL WIN_IsEqualIID(REFIID a,REFIID b);
#endif /* _INCLUDED_WINDOWS_H */

/* vi: set ts=4 sw=4 expandtab: */
