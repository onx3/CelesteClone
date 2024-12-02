#include <windows.h>
#include "Celeste_lib.h"

#define WIN32_LEAN_AND_MEAN
#define NOMINMAX

//----------------------------------------------------------------------------------------------------------------------------

static bool sRunning = true;
static HWND sWindow;

//----------------------------------------------------------------------------------------------------------------------------

LRESULT CALLBACK WindowCallback(HWND window, UINT msg, WPARAM wParam, LPARAM lParam)
{
	LRESULT result = 0;

	switch (msg)
	{
		case WM_CLOSE:
		{
			sRunning = false;
			break;
		}
		default:
		{
			result = DefWindowProcA(window, msg, wParam, lParam);
		}
	}
	
	return result;
}

//----------------------------------------------------------------------------------------------------------------------------

bool PlatFormCreateWindow(const int width, const int height, const char * title)
{
	HINSTANCE instance = GetModuleHandleA(0);

	WNDCLASSA wc = {};
	wc.hInstance = instance;
	wc.hIcon = LoadIcon(instance, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.lpszClassName = title;
	wc.lpfnWndProc = WindowCallback;

	if (!RegisterClassA(&wc))
	{
		return false;
	}

	int dwStyle = WS_OVERLAPPEDWINDOW;
	sWindow = CreateWindowExA(0, title,
									title, // This is the actual Title
									dwStyle, 
									100,
									100,
									width,
									height,
									NULL, // parent
									NULL, // menu
									instance,
									NULL); // lpParam

	if (sWindow == NULL)
	{
		return false;
	}

	ShowWindow(sWindow, SW_SHOW);
	return true;
}

//----------------------------------------------------------------------------------------------------------------------------

void PlatFormUpdateWindow()
{
	MSG msg;

	while (PeekMessageA(&msg, sWindow, 0, 0, PM_REMOVE))
	{
		TranslateMessage(&msg);
		DispatchMessageA(&msg);
	}
}

//----------------------------------------------------------------------------------------------------------------------------

int main()
{
	PlatFormCreateWindow(1200, 720, "Celeste");

	while (sRunning)
	{
		PlatFormUpdateWindow();
		SM_TRACE("TEST");
		SM_WARN("TEST");
		SM_ERROR("TEST");
		ASSERT(false, "Assertion hit");
	}

	return 0;
}

//----------------------------------------------------------------------------------------------------------------------------
// EOF
//----------------------------------------------------------------------------------------------------------------------------