// Heroes3.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "Heroes3.h"

#define MAX_LOADSTRING	100
#define MAX_CMD_LINE	60

const LPTSTR AppClassName = _T("Heroes III");
const LPTSTR AppWinName = _T("Heroes of Might and Magic III");
const LPTSTR AppErrWinName = _T("Heroes of Might and Magic III");
const LPTSTR ErrAlreadyRunning = _T("Heroes of Might and Magic III is already running.");
const LPTSTR ErrCaptionStartup = _T("Startup error");

struct _gameConfig {
	int WinX, WinY;
	bool IsFullScreen;
} GameConfig;


// Global Variables:
HINSTANCE hH3Instance;                                // current instance
HANDLE hH3Event;
TCHAR gTextBuffer[768] = _T("");
bool IsGameInitialised = false;
TCHAR LPCmdLine[MAX_CMD_LINE + 1];
HMENU hH3Menu;
HWND hH3Wnd;

int _tWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPTSTR lpCmdLine, int nCmdShow);

// Forward declarations of functions included in this code module:
ATOM                MyRegisterClass(HINSTANCE hInstance);
bool                InitInstance();
LRESULT CALLBACK    WndProc(HWND, UINT, WPARAM, LPARAM);
INT_PTR CALLBACK    About(HWND, UINT, WPARAM, LPARAM);
bool GameInitialize();
void j_CreateDDSurfaces();
void SOD_unk_sub_4B65F0(HINSTANCE hInstance, HWND hWnd);
void MainCircle();

int APIENTRY _tWinMain(_In_ HINSTANCE hInstance,
                     _In_opt_ HINSTANCE hPrevInstance,
                     _In_ LPTSTR    lpCmdLine,
                     _In_ int       nCmdShow)
{
    // TODO: Place code here.
	HANDLE hH3Event = CreateEvent(NULL, false, false, APPNAME);
	if (!hH3Event || GetLastError() == ERROR_ALREADY_EXISTS) {
		_stprintf(gTextBuffer, ErrAlreadyRunning, AppErrWinName);
		MessageBox(NULL, gTextBuffer, ErrCaptionStartup, MB_ICONSTOP);
		return 0;
	}
	
	memset(LPCmdLine, 0, (MAX_CMD_LINE+1)*sizeof(TCHAR));
	_tcsncpy(LPCmdLine, lpCmdLine, MAX_CMD_LINE);
	
	// Minimum timer resolution, in milliseconds, for the application or device driver. A lower value specifies a higher (more accurate) resolution.
	timeBeginPeriod(1); // <== TODO: required to close with timeEndPeriod(1)

	DWORD winStyle, winExStyle;
	if (!GameInitialize() ||
		!hPrevInstance && !MyRegisterClass(hInstance) ||

	// Perform application initialization:
		!InitInstance())return 0;


    //HACCEL hAccelTable = LoadAccelerators(hInstance, MAKEINTRESOURCE(IDC_HEROES3));

	SOD_unk_sub_4B65F0(hH3Instance, hH3Wnd);

	MainCircle();
	
	/*MSG msg;

    // Main message loop:
    while (GetMessage(&msg, nullptr, 0, 0))
    {
        if (!TranslateAccelerator(msg.hwnd, NULL *//*hAccelTable*//*, &msg))
        {
            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }
    }
    return (int) msg.wParam;*/

	return 0;
}



//
//  FUNCTION: MyRegisterClass()
//
//  PURPOSE: Registers the window class.
//
inline ATOM MyRegisterClass(HINSTANCE hInstance)
{
    WNDCLASS wndClass;

	wndClass.hCursor = NULL;
	wndClass.hIcon = LoadIcon(hInstance, (LPCSTR)IDI_HEROES3SOD);
	wndClass.lpszMenuName = NULL;
	wndClass.lpszClassName = AppClassName;
	wndClass.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
	wndClass.hInstance = hInstance;
	wndClass.style = CS_BYTEALIGNCLIENT | CS_DBLCLKS | CS_HREDRAW | CS_VREDRAW; // 0x100B
	wndClass.lpfnWndProc = (WNDPROC)WndProc;
	wndClass.cbWndExtra = 0;
	wndClass.cbClsExtra = 0;

    return RegisterClass(&wndClass);
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
inline bool InitInstance()
{
	DWORD winStyle, winExStyle;
	struct tagRECT rect;

	if (GameConfig.IsFullScreen)
	{
		winStyle = WS_POPUP | WS_VISIBLE;
		winExStyle = WS_EX_TOPMOST;
	}
	else
	{
		winStyle = 0;
		winExStyle = WS_VISIBLE | WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU;
	}

	rect.left = 0;
	rect.top = 0;
	rect.right = 800;
	rect.bottom = 600;
	AdjustWindowRect(&rect, winStyle, !GameConfig.IsFullScreen);

	hH3Wnd = CreateWindowEx(winExStyle, AppClassName, AppWinName, winStyle, 
		GameConfig.WinX, GameConfig.WinY, rect.right - rect.left, rect.bottom - rect.top,
		NULL, GameConfig.IsFullScreen ? NULL : hH3Menu, hH3Instance, NULL);

	if (!hH3Wnd)return false;


	j_CreateDDSurfaces();
	HCURSOR gameCursor = LoadCursor(NULL, (LPCSTR)IDC_ARROW);
	SetCursor(gameCursor);

   return true;
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
                DialogBox(hH3Instance, MAKEINTRESOURCE(IDD_ABOUTBOX), hWnd, About);
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

bool GameInitialize()
{
	hH3Menu = LoadMenu(hH3Instance, (LPTSTR)IDM_HEROES3);
	return false;
}

void j_CreateDDSurfaces() 
{

}

void SOD_unk_sub_4B65F0(HINSTANCE hInstance, HWND hWnd)
{

}

void MainCircle()
{

}
