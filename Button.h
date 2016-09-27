#pragma once
#include "Headers.h"
#include "Defines.h"


HWND CreateButton(HWND parentHWnd) {

	HWND button = CreateWindowEx(0, "Button", "Click", WS_VISIBLE | WS_CHILD, 30, 30, 60, 30, parentHWnd, (HMENU)DEF_BUT_PLAY, GetModuleHandle(NULL), NULL);

	return button;
}