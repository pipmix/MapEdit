#pragma once
#include "Headers.h"

void AddMenus(HWND hWnd) {

	HMENU hMenuMainBar;
	HMENU hMenuFile;
	HMENU hMenuEdit;
	HMENU hMenuWindow;
	HMENU hMenuSettings;

	hMenuMainBar = CreateMenu();
	hMenuFile = CreateMenu();
	hMenuEdit = CreateMenu();
	hMenuWindow = CreateMenu();
	hMenuSettings = CreatePopupMenu();

	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_NEW, L"&New");
	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_OPEN, L"&Open");
	AppendMenuW(hMenuFile, MF_SEPARATOR, 0, NULL);
	AppendMenuW(hMenuFile, MF_STRING, IDM_FILE_EXIT, L"&Exit");
	AppendMenuW(hMenuFile, MF_STRING | MF_POPUP, (UINT_PTR)hMenuSettings, L"&Settings");

	AppendMenuW(hMenuSettings, MF_STRING, IDM_SETTINGS_ONE, L"&One");
	AppendMenuW(hMenuSettings, MF_STRING, IDM_SETTINGS_TWO, L"&Two");
	AppendMenuW(hMenuSettings, MF_STRING, IDM_SETTINGS_THREE, L"&Three");
	AppendMenuW(hMenuSettings, MF_STRING, IDM_SETTINGS_FOUR, L"&Four");


	
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

	AppendMenuW(hMenuWindow, MF_STRING, IDM_WINDOW_WIREFRAME, L"&Wireframe");
	AppendMenuW(hMenuWindow, MF_STRING, IDM_WINDOW_SHADED, L"&Shaded");
	AppendMenuW(hMenuWindow, MF_STRING, IDM_WINDOW_TEXTURED, L"&Textured");
	CheckMenuRadioItem(hMenuWindow, IDM_WINDOW_WIREFRAME, IDM_WINDOW_TEXTURED, IDM_WINDOW_WIREFRAME, MF_BYCOMMAND);

	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuFile, L"&File");
	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuEdit, L"&Edit");
	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuWindow, L"&Window");

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

bool FlipCheckMenu(HWND hWnd, UINT id) {

	UINT check;
	HMENU hTmp = GetMenu(hWnd);


	check = GetMenuState(hTmp, id, MF_BYCOMMAND);
	if (check == MF_CHECKED) {
		CheckMenuItem(hTmp, id, MF_UNCHECKED);
		return 0;
	}
	else {
		CheckMenuItem(hTmp, id, MF_CHECKED);
		return 1;
	}

}

void SetRadioMenu(HWND hWnd, UINT left, UINT right, UINT setValue) {

	HMENU hTmp = GetMenu(hWnd);
	CheckMenuRadioItem(hTmp, left, right, setValue, MF_BYCOMMAND);



}

WCHAR* IntToLPCWSTR(int i) {
	WCHAR buffer[256];
	wsprintfW(buffer, L"%d", i);
	return buffer;
}


void MiscWindowsFunctions() {
	LPCWSTR dir = L"blank";
	DWORD setDir = SetCurrentDirectoryW(dir);

	WCHAR buffer[BUFSIZE];
	DWORD getDir =  GetCurrentDirectoryW(BUFSIZE, buffer);
	// if dword == 0 then error

	WCHAR cName[MAX_COMPUTERNAME_LENGTH + 1];
	DWORD size = sizeof(cName) / sizeof(cName[0]);
	int getCompName = GetComputerNameW(cName, &size);

	MEMORYSTATUSEX mem = { 0 };
	mem.dwLength = sizeof(mem);
	int r = GlobalMemoryStatusEx(&mem);
	//mem.
}

void CenterWindow(HWND hWnd) {

	RECT rc = { 0 };
	GetWindowRect(hWnd, &rc);
	int windowWidth = rc.right - rc.left;
	int windowHeight = rc.bottom - rc.top;
	int screenWidth = GetSystemMetrics(SM_CXSCREEN);
	int screenHeight = GetSystemMetrics(SM_CYSCREEN);
	SetWindowPos(hWnd, HWND_TOP, (screenWidth - windowWidth) / 2,
		(screenHeight - windowHeight) / 2, 0, 0, SWP_NOSIZE);
}

void CreateText(HWND hWnd) {

	CreateWindowW(L"static", L"x: ",
		WS_CHILD | WS_VISIBLE,
		10, 10, 25, 25,
		hWnd, (HMENU)1, NULL, NULL);
	CreateWindowW(L"static", L"150",
		WS_CHILD | WS_VISIBLE,
		40, 10, 55, 25,
		hWnd, (HMENU)2, NULL, NULL);


}

void CreateSidePane(HWND hWnd) {




}