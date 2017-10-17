// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//
#pragma comment(lib, "winmm.lib")
#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // Exclude rarely-used stuff from Windows headers

//****** HQ Comment ******************
// Remove next 3 lines for Unicode version or invert them
#define _MBCS
#undef _UNICODE			// for tchar.h
#undef UNICODE			// for winnt.h

//#undef _MBCS
//#define _UNICODE			// for tchar.h
//#define UNICODE			// for winnt.h

// Windows Header Files:
#include <windows.h>

// C RunTime Header Files
#include <stdlib.h>
#include <malloc.h>
#include <memory.h>
#include <tchar.h>


// TODO: reference additional headers your program requires here
#include <stdio.h> 
#include <TimeAPI.h>


#define h3int		int32_t 
#define h3bool		int32_t 
#define h3minus1	((int32_t)0xFFFFFFFF)