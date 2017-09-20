// Heroes3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Heroes3.h"

#define MAX_LOADSTRING 100
const PTCHAR AppClassName = _T("Heroes III");
const PTCHAR AppWinName = _T("Heroes of Might and Magic III");
const PTCHAR AppErrWinName = _T("Heroes of Might and Magic III");
const PTCHAR ErrAlreadyRunning = _T("Heroes of Might and Magic III is already running.");
const PTCHAR ErrCaptionStartup = _T("Startup error");

TCHAR gTextBuffer[768] = _T("");

// Global Variables:
HINSTANCE hInst;                                // current instance
WCHAR szTitle[MAX_LOADSTRING];                  // The title bar text
WCHAR szWindowClass[MAX_LOADSTRING];            // the main window class name

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
BOOL                InitInstance(HINSTANCE, int);
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);

int APIENTRY HQ_WINMAIN(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPWSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    UNREFERENCED_PARAMETER(hPrevInstance);
    UNREFERENCED_PARAMETER(lpCmdLine);

    // TODO: Place code here.
	HANDLE hObject = CreateEvent(NULL, FALSE, FALSE, APPNAME);
	DWORD lastError = GetLastError();
	if (hObject && lastError != ERROR_ALREADY_EXISTS) {
	
	}
	else {
		sprintf((PTCHAR)gTextBuffer, (const PTCHAR)ErrAlreadyRunning, AppErrWinName);
		MessageBox(NULL, gTextBuffer, (PTCHAR)ErrCaptionStartup, MB_ICONSTOP);
	}

    // Initialize global strings
    //LoadStringW(hInstance, IDS_APP_TITLE, szTitle, MAX_LOADSTRING);
    //LoadStringW(hInstance, IDC_HEROES3, szWindowClass, MAX_LOADSTRING);
    MyRegisterClass(hInstance);

    // Perform application initialization:
    if (!InitInstance (hInstance, nCmdShow))
    {
        return FALSE;
    }

    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HEROES3));

    MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL /*hAccelTable*/, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }

    return (int) msg.wParam;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASSEXW wcex;

    wcex.cbSize = sizeof(WNDCLASSEX);

    wcex.style          = CS_HREDRAW | CS_VREDRAW;
    wcex.lpfnWndProc    = WndProc;
    wcex.cbClsExtra     = 0;
    wcex.cbWndExtra     = 0;
    wcex.hInstance      = hInstance;
    wcex.hIcon          = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_HEROES3));
    wcex.hCursor        = LoadCursor(nullptr, IDC_ARROW);
    wcex.hbrBackground  = (HBRUSH)(COLOR_WINDOW+1);
	wcex.lpszMenuName = _T("HHHHHHHHHH"); // MAKEINTRESOURCEW(IDC_HEROES3);
    wcex.lpszClassName  = szWindowClass;
    wcex.hIconSm        = LoadIcon(wcex.hInstance, MAKEINTRESOURCE(IDI_HEROES3));

    return RegisterClassExW(&wcex);
}

//
//   FUNCTION: InitInstance(HINSTANCE, int)
//
//   PURPOSE: Saves instance handle and creates main window
//
//   COMMENTS:
//
//        In this function, we save the instance handle in a global variable and
//        create and display the main program window.
//
BOOL InitInstance(HINSTANCE hInstance, int nCmdShow)
{
   hInst = hInstance; // Store instance handle in our global variable

   HWND hWnd = CreateWindowW(szWindowClass, szTitle, WS_OVERLAPPEDWINDOW,
      CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

   if (!hWnd)
   {
      return FALSE;
   }

   ShowWindow(hWnd, nCmdShow);
   UpdateWindow(hWnd);

   return TRUE;
}

//
//  FUNCTION: WndProc(HWND, UINT, WPARAM, LPARAM)
//
//  PURPOSE:  Processes messages for the main window.
//
//  WM_COMMAND  - process the application menu
//  WM_PAINT    - Paint the main window
//  WM_DESTROY  - post a quit message and return
//
//
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
    switch (message)
    {
    case WM_COMMAND:
        {
            int wmId = LOWORD(wParam);
            // Parse the menu selections:
            switch (wmId)
            {
            case IDM_ABOUT:
                DialogBox(hInst, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
                break;
            case IDM_QUIT:
                DestroyWindow(hWnd);
                break;
            default:
                return DefWindowProc(hWnd, message, wParam, lParam);
            }
        }
        break;
    case WM_PAINT:
        {
            PAINTSTRUCT ps;
            HDC hdc = BeginPaint(hWnd, &ps);
            // TODO: Add any drawing code that uses hdc here...
            EndPaint(hWnd, &ps);
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        break;
    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// Message handler for about box.
INT_PTR CALLBACK About(HWND hDlg, UINT message, WPARAM wParam, LPARAM lParam)
{
    UNREFERENCED_PARAMETER(lParam);
    switch (message)
    {
    case WM_INITDIALOG:
        return (INT_PTR)TRUE;

    case WM_COMMAND:
        if (LOWORD(wParam) == IDOK || LOWORD(wParam) == IDCANCEL)
        {
            EndDialog(hDlg, LOWORD(wParam));
            return (INT_PTR)TRUE;
        }
        break;
    }
    return (INT_PTR)FALSE;
}


int __stdcall WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nShowCmd)
{
	DWORD v4; // eax@1
	DWORD v5; // esi@7
	DWORD v6; // edi@7
	HCURSOR v7; // eax@10
	WNDCLASSA WndClass; // [sp+Ch] [bp-38h]@5
	struct tagRECT Rect; // [sp+34h] [bp-10h]@9

	hH3Instance = hInstance;
	hObject = CreateEventA(0, 0, 0, gameName);
	v4 = GetLastError();
	if (hObject && v4 != 183)
	{
		memset(&LPCmdLine, 0, 0x3Cu);
		*(&LPCmdLine + 60) = 0;
		strncpy(&LPCmdLine, lpCmdLine, 0x3Cu);
		timeBeginPeriod(1u);
		if (GameInitialize())
		{
			if (hPrevInstance
				|| (WndClass.hCursor = 0,
					WndClass.hIcon = LoadIconA(hInstance, (LPCSTR)0x73),
					WndClass.lpszMenuName = 0,
					WndClass.lpszClassName = h3ClassName,
					WndClass.hbrBackground = (HBRUSH)6,
					WndClass.hInstance = hInstance,
					WndClass.style = 4107,
					WndClass.lpfnWndProc = (WNDPROC)sub_4F8290,
					WndClass.cbWndExtra = 0,
					WndClass.cbClsExtra = 0,
					RegisterClassA(&WndClass)))
			{
				if (*(_DWORD *)&MDS_60_MainGameFullScreen)
				{
					v5 = -1879048192;
					v6 = 8;
				}
				else
				{
					v6 = 0;
					v5 = 281673728;
				}
				Rect.left = 0;
				Rect.top = 0;
				Rect.right = 800;
				Rect.bottom = 600;
				AdjustWindowRect(&Rect, v5, *(_DWORD *)&MDS_60_MainGameFullScreen == 0);
				hHeroes3Wnd = CreateWindowExA(
					v6,
					h3ClassName,
					H3WindowName,
					v5,
					*(int *)&MDS_58_MainGameX,
					*(int *)&MDS_5C_MainGameY,
					Rect.right - Rect.left,
					Rect.bottom - Rect.top,
					0,
					(HMENU)(*(_DWORD *)&MDS_60_MainGameFullScreen == 0 ? (unsigned int)hMainMenu : 0),
					hInstance,
					0);
				if (hHeroes3Wnd)
				{
					j_CreateDDSurfaces();
					v7 = LoadCursorA(0, (LPCSTR)0x7F00);
					SetCursor(v7);
					SOD_unk_sub_4B65F0((int)hH3Instance, hHeroes3Wnd);
					gameStart();
					return 0;
				}
			}
		}
	}
	else
	{
		sprintf((char *)&txtBuff, aHeroesOfMigh_1, aHeroesOfMigh_0);
		MessageBoxA(0, &txtBuff, aStartupError, 0x10u);
	}
	return 0;
}
