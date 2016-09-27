#pragma once
#include "Headers.h"

LRESULT CALLBACK ConsoleProc(HWND, UINT, WPARAM, LPARAM);
HFONT consoleFont;

static TCHAR szConcoleClass[] = _T("consoleClass");

HWND CreateConsole(HWND parentHwnd) {

	HWND consoleHandle;

	WNDCLASSEX	wcex;
	wcex.cbSize = sizeof(wcex);
	wcex.style = 0;
	wcex.lpfnWndProc = ConsoleProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = GetModuleHandle(0);
	wcex.hIcon = 0;
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_WINDOW);
	wcex.lpszMenuName = 0;
	wcex.lpszClassName = szConcoleClass;
	wcex.hIconSm = 0;

	RegisterClassEx(&wcex);

	consoleHandle = CreateWindowEx(0,
		szConcoleClass, NULL,
		WS_VSCROLL | WS_HSCROLL | WS_CHILD | WS_VISIBLE | WS_BORDER,
		0, 0, 0, 0,
		parentHwnd, 0, GetModuleHandle(0),0);

	//consoleFont = (HFONT)GetStockObject(ANSI_FIXED_FONT);
	consoleFont = CreateFont(0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, TEXT("Arial"));

	return consoleHandle;
}


LRESULT CALLBACK ConsoleProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	case WM_PAINT: {

		//HDC hDC = GetDC(hWnd);
		PAINTSTRUCT ps;
		BeginPaint(hWnd, &ps);
		SelectObject(ps.hdc, consoleFont);
		TextOut(ps.hdc, 10, 10, TEXT("test"), 16);
		EndPaint(hWnd, &ps);

	}
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);

}