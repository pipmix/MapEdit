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




	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuFile, L"&File");
	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuEdit, L"&Edit");
	AppendMenuW(hMenuMainBar, MF_POPUP, (UINT_PTR)hMenuWindow, L"&Window");

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

HTREEITEM ListViewAddItem(HWND hWnd, HTREEITEM hItem, LPSTR lpstr) {

	TVINSERTSTRUCT insert;
	insert = { 0 };

	insert.hParent = hItem;
	insert.hInsertAfter = TVI_LAST;
	insert.item.mask = TVIF_TEXT;
	insert.item.pszText = lpstr;
	insert.item.cchTextMax = 10;

	//HTREEITEM test = TVM_INSERTITEM(0, &insert);
	return TreeView_InsertItem(hWnd, &insert);

}


HWND CreateSidePanel(HWND hWnd) {

	RECT rect;
	GetWindowRect(hWnd, &rect);
	HWND hSidePanel = 
	CreateWindowEx(0, WC_TREEVIEW, NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP |
		//TVS_HASLINES | TVS_LINESATROOT |
		TVS_HASBUTTONS  | WS_BORDER | TVS_FULLROWSELECT
		, 0, 0, 120, rect.right - rect.left,
		hWnd, 0, NULL, NULL);
	//TVS_CHECKBOXES   TVS_FULLROWSELECT   TVS_EDITLABELS   TVS_INFOTIP  TVS_SHOWSELALWAYS



	HTREEITEM hRoot;


	TV_INSERTSTRUCT tvins;

	tvins = { 0 };

	tvins.hInsertAfter = TVI_ROOT;
	tvins.item.mask = TVIF_TEXT;
	tvins.item.pszText = "Root";
	tvins.item.cchTextMax = 10;

	hRoot = TreeView_InsertItem(hSidePanel, &tvins);

	//tvins.hInsertAfter = TVI_LAST;
	//tvins.item.pszText = "Child";
	//hChild = TreeView_InsertItem(hSidePanel, &tvins);


	ListViewAddItem(hSidePanel, hRoot, "test");
	ListViewAddItem(hSidePanel, hRoot, "cat");
	ListViewAddItem(hSidePanel,  ListViewAddItem(hSidePanel, hRoot, "murder"), "more");

	tvins.hInsertAfter = TVI_ROOT;
	tvins.item.mask = TVIF_TEXT;
	tvins.item.pszText = "Root2";
	tvins.item.cchTextMax = 10;

	hRoot = TreeView_InsertItem(hSidePanel, &tvins);


	return hSidePanel;

}

int CreateColumn(HWND hWnd, int iCol, char * text, int iBreite)
{
	LVCOLUMN lvc;

	lvc.mask = LVCF_FMT | LVCF_WIDTH | LVCF_TEXT | LVCF_SUBITEM;
	lvc.fmt = LVCFMT_LEFT;
	lvc.cx = iBreite;
	lvc.pszText = text;
	lvc.iSubItem = iCol;
	return ListView_InsertColumn(hWnd, iCol, &lvc);
}


HWND CreateTablePanel(HWND hWnd) {

	HWND hTable;
	hTable = CreateWindowEx(0, WC_LISTVIEW, NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP | LVS_REPORT | WS_BORDER
		, 0, 0, 0, 0,
		hWnd, 0, 0, NULL);

	SendMessage(hTable, LVM_SETEXTENDEDLISTVIEWSTYLE,0, LVS_EX_FULLROWSELECT); 


	int col = 0;
	LVCOLUMN lvc;
	lvc = { 0 };
	lvc.mask = LVCF_TEXT;
	lvc.cx = 20;
	lvc.cchTextMax = 10;
	//lvc.iSubItem = 8;

	
	lvc.pszText = "Name";
	ListView_InsertColumn(hTable, col, &lvc);
	ListView_SetColumnWidth(hTable, col, 150);

	lvc.pszText = "Type";
	col++;
	ListView_InsertColumn(hTable, col, &lvc);
	ListView_SetColumnWidth(hTable, col, 100);

	lvc.pszText = "Size";
	col++;
	ListView_InsertColumn(hTable, col, &lvc);
	ListView_SetColumnWidth(hTable, col, 100);


	lvc.pszText = "Modified";
	col++;
	ListView_InsertColumn(hTable, col, &lvc);
	ListView_SetColumnWidth(hTable, col, 100);


	CHAR fileName[FILENAME_MAX];
	WIN32_FIND_DATA findData = { 0 };
	HANDLE hFind = ::FindFirstFile("c:/files/aab/*", &findData);
	int row = 0;
	col = 0;
	LVITEM lvi;
	lvi.mask = LVIF_TEXT;

	while (hFind != INVALID_HANDLE_VALUE) {

		lvi.iItem = row;
		lvi.iSubItem = 0;
		lvi.pszText = findData.cFileName;
		SendMessage(hTable, LVM_INSERTITEM, 0, (LPARAM)&lvi);

		col++;
		lvi.iSubItem = col;

		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)lvi.pszText = "Folder";
		else lvi.pszText = "File";
		SendMessage(hTable, LVM_SETITEM, 0, (LPARAM)&lvi);

		col++;
		lvi.iSubItem = col;
		

		if (!(findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
			char szTest[10];
			sprintf_s(szTest, "%d", findData.nFileSizeLow);
			lvi.pszText = szTest;

			SendMessage(hTable, LVM_SETITEM, 0, (LPARAM)&lvi);





		}

		col++;
		lvi.iSubItem = col;

		char szTest[100];
		sprintf_s(szTest, "%d", findData.ftLastWriteTime.dwLowDateTime);
		lvi.pszText = szTest;


		SendMessage(hTable, LVM_SETITEM, 0, (LPARAM)&lvi);



		col = 0;
		if (FindNextFile(hFind, &findData) == FALSE) break;
	}

	FindClose(hFind);


	//lvi.iItem = 1;
	//lvi.iSubItem = 1; 
	//lvi.pszText = "testx2";
	//SendMessage(hTable, LVM_SETITEM, 0, (LPARAM)&lvi);

	
	/*
	CHAR fileName[FILENAME_MAX];
	WIN32_FIND_DATA findData = { 0 };
	HANDLE hFind = ::FindFirstFile("c:/files/aab/*", &findData);
	//HANDLE handle = FindFirstFile(fileName, &findData);
	
	while (hFind != INVALID_HANDLE_VALUE) {


		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			lvc.pszText = findData.cFileName;

			ListView_InsertColumn(hTable, col, &lvc);
			ListView_SetColumnWidth(hTable, col, 100);
			col++;
		}

		if (FindNextFile(hFind, &findData) == FALSE) break;
	}

	FindClose(hFind);

	*/



	return hTable;



}

HWND CreateConsoleWindow(HWND parentHandle) {

	return CreateWindowEx(0, WC_TREEVIEW, NULL,
		WS_CHILD | WS_VISIBLE | WS_TABSTOP |
		TVS_HASBUTTONS  | TVS_FULLROWSELECT | WS_BORDER
		, 0, 0, 0, 0,
		parentHandle, 0, NULL, NULL);


}

POINT GetCenterCoord(int windowW, int windowH){
	int screenW = GetSystemMetrics(SM_CXSCREEN);
	int screenH = GetSystemMetrics(SM_CYSCREEN);

	return POINT{ (screenW - windowW) / 2 , (screenH - windowH) / 2 };


}