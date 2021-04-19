#include "Headers\WinExcludes.h"
#include "Headers\app.h"
#include <optional>
#include "Headers\ExceptionHandler.h"
#include "Headers\WindowsMessageMap.h"
#include "Headers\ConOut.h""
//#include "Headers\Keyboard.h"
//#include "Headers\Window.h"
char ConMsgOut(char message);

char ConMsgOut(char message)
{
	AllocConsole();
	const char* lpBuff = &message;
	DWORD dwSize = 0;
	WriteConsole(GetStdHandle(STD_OUTPUT_HANDLE), lpBuff, lstrlen(lpBuff), &dwSize, NULL);
	return ConMsgOut(message);
}
LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
	static WindowsMessageMap mm;
	//OutputDebugString(mm(msg, lParam, wParam).c_str());
	switch (msg)
	{
	case WM_CLOSE:
		PostQuitMessage(69);
		break;
	}
	return DefWindowProc(hWnd, msg, wParam, lParam);
}
int CALLBACK WinMain(
	_In_		HINSTANCE	hInstance,
	_In_opt_	HINSTANCE	hPrevInstance,
	_In_		LPSTR		lpCmdLine,
	_In_		int			nShowCmd ) //not sure why the pre-fixes are needed, but they get rid of inconsistency in CALLBACK.
{
	try
	{
		ConMsgOut("Hi from Win32");
		const auto pClassName = "Some Shitbox";
		WNDCLASSEX wc = { 0 };
		wc.cbSize = sizeof(wc);
		wc.style = CS_OWNDC;
		wc.lpfnWndProc = WndProc;
		wc.cbClsExtra = 0;
		wc.cbWndExtra = 0;
		wc.hInstance = hInstance;
		wc.hIcon = nullptr;
		wc.hCursor = nullptr;
		wc.hbrBackground = nullptr;
		wc.lpszMenuName = nullptr;
		wc.lpszClassName = pClassName;
		wc.hIconSm = nullptr;
		RegisterClassEx(&wc);
		HWND hWnd = CreateWindowEx(
			0, pClassName, "Some Shitbox",
			WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU|WS_MAXIMIZEBOX,
			200, 200, 640, 480,
			nullptr, nullptr, hInstance, nullptr);
		ShowWindow(hWnd, SW_SHOW);

		MSG msg;
		BOOL gResult;
		while ((gResult = GetMessage(&msg, nullptr, 0, 0)) > 0)
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		if (gResult == -1) 
		{
			return -1;
		}
		else
		{
			return msg.wParam;
		}
		
		//return App{}.Go();
	}
	catch (const ExceptionHandler& e)
		{
		MessageBox(nullptr, e.what(), e.GetType(), MB_OK | MB_ICONEXCLAMATION);
		}
	catch (const std::exception& e)
	{
		MessageBox(nullptr, e.what(), "Standard Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	catch (...)
	{
		MessageBox(nullptr,"No details available", "Unknown Exception", MB_OK | MB_ICONEXCLAMATION);
	}
	return 0;
}