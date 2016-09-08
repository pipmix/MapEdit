#pragma once
#include "Headers.h"

void AddMenus(HWND hWnd) {

	HMENU hMenuMainBar;
	HMENU hMenuFile;
	HMENU hMenuEdit;

	hMenuMainBar = CreateMenu();
	hMenuFile = CreateMenu();
	hMenuEdit = CreateMenu();

	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hMenuFile, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_EXIT, L"&Exit");

	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_COPY, L"&Copy");
	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_PASTE, L"&Paste");
	CheckMenuItem(hMenuEdit, IDM_EDIT_PASTE, MF_CHECKED);
	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_CUT, L"&Cut");


	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuFile, L"&File");
	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuEdit, L"&Edit");
	SetMenu(hWnd, hMenuMainBar);
}









void RightClickMenu(HWND hWnd, LPARAM lParam) {

	HMENU menuRightClick;
	POINT mousePoint;

	mousePoint.x = LOWORD(lParam);
	mousePoint.y = HIWORD(lParam);

	menuRightClick = CreatePopupMenu();
	ClientToScreen(hWnd, &mousePoint);

	AppendMenuW(menuRightClick, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenuW(menuRightClick, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(menuRightClick, MF_SEPARATOR, 0, NULL);
	AppendMenuW(menuRightClick, MF_STRING, IDM_FILE_EXIT, L"&Quit");

	TrackPopupMenu(menuRightClick, TPM_RIGHTBUTTON, mousePoint.x, mousePoint.y, 0, hWnd, NULL);
	DestroyMenu(menuRightClick);
	


}