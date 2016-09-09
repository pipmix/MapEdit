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

	MENUINFO menuInfo;
	menuInfo.cbSize = sizeof(MENUINFO);
	menuInfo.fMask = MIM_BACKGROUND | MIM_STYLE;
	menuInfo.dwStyle = MNS_AUTODISMISS;
	menuInfo.cyMax = 0;
	menuInfo.hbrBack = (HBRUSH)(COLOR_GRAYTEXT);
	menuInfo.dwContextHelpID = NULL;
	menuInfo.dwMenuData = NULL;
	SetMenuInfo(hMenuEdit, &menuInfo);

	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_COPY, L"&Copy");
	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_PASTE, L"&Paste");
	CheckMenuItem(hMenuEdit, IDM_EDIT_PASTE, MF_CHECKED);
	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_CUT, L"&Cut");


	AppendMenuW(hMenuEdit, MF_STRING, IDM_EDIT_ONTOP, L"&Always on top");
	CheckMenuItem(hMenuEdit, IDM_EDIT_ONTOP, MF_UNCHECKED);

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


void AddTextBox(HWND hWnd) {
	/*
	HFONT hfDefault;
	HWND hEdit;

	hEdit = CreateWindowEx(WS_EX_CLIENTEDGE, "EDIT", "",
		WS_CHILD | WS_VISIBLE | WS_VSCROLL | WS_HSCROLL | ES_MULTILINE | ES_AUTOVSCROLL | ES_AUTOHSCROLL,
		0, 0, 100, 100, hWnd, 0, GetModuleHandle(NULL), NULL);
	if (hEdit == NULL)
		MessageBox(hWnd, "Could not create edit box.", "Error", MB_OK | MB_ICONERROR);

	hfDefault = GetStockObject(DEFAULT_GUI_FONT);
	SendMessage(hEdit, WM_SETFONT, (WPARAM)hfDefault, MAKELPARAM(FALSE, 0));
	*/



}