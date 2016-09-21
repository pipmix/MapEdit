// Vision Explorer
// v0.01
// pipmix.com

#include "Headers.h"
#include "Tools.h"
#include "Console.h"

ATOM RegisterWindowClass(HINSTANCE hInstance);
BOOL CreateInstance(HINSTANCE, int);

bool windowHasFocus = false;


static TCHAR szWindowClass[] = _T("MapEditWndClass");
static TCHAR szTitle[] = _T("Vision");

int gWidth = 768;
int gHeight = 768;
HINSTANCE hInst;

HWND hTest;
HWND hText;
HWND hSidePanel;
HWND hTablePanel;
HWND hConsolePanel;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);
LRESULT CALLBACK ChildProc(HWND, UINT, WPARAM, LPARAM);
void CommandMsg(HWND hWnd, WPARAM wParam);

void RegisterChild1();
void RegisterChild2();
void GetDir();

//test var
int v_panelWidth = 200;
int v_panelHeight = 600;
int v_maxW = 0;
int v_maxH = 0;

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {


	RegisterWindowClass(hInstance);
	CreateInstance(hInstance, nCmdShow);

	

	

	INITCOMMONCONTROLSEX icc = { sizeof(INITCOMMONCONTROLSEX),
		ICC_BAR_CLASSES | ICC_DATE_CLASSES | ICC_LISTVIEW_CLASSES | ICC_STANDARD_CLASSES |
		ICC_TREEVIEW_CLASSES | ICC_USEREX_CLASSES | ICC_WIN95_CLASSES  };
	InitCommonControlsEx(&icc);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0)){
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	return (int)msg.wParam;
}




ATOM RegisterWindowClass(HINSTANCE hInstance) {

	WNDCLASSEX wcex = { 0 };

	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	wcex.hIcon = (HICON)LoadImage(NULL, "largeicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = GetSysColorBrush(COLOR_GRAYTEXT);//  (HBRUSH)(COLOR_GRAYTEXT);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = (HICON)LoadImage(NULL, "smallicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

	return RegisterClassEx(&wcex);
}

BOOL CreateInstance(HINSTANCE hInstance, int nCmdShow) {

	hInst = hInstance;
	//HWND hWnd = CreateWindow(szWindowClass, szTitle,  WS_OVERLAPPEDWINDOW | SS_OWNERDRAW | WS_EX_TOPMOST,
	//	CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	HWND hWnd = CreateWindowEx(
		WS_EX_CLIENTEDGE,
		szWindowClass,
		szTitle,
		WS_OVERLAPPEDWINDOW,
		CW_USEDEFAULT, CW_USEDEFAULT, gWidth, gWidth,
		NULL, NULL, hInstance, NULL);




	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}








LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	UINT check;
	HMENU hTmp = GetMenu(hWnd);
	const int BUF_LEN = 10;
	wchar_t buf[BUF_LEN];

	RECT clientRect;
	GetWindowRect(hWnd, &clientRect);
	RECT windowRect;
	GetWindowRect(hWnd, &windowRect);

	switch (message) {
		case WM_CREATE:
			RegisterHotKey(hWnd, IDHK_CENTER, MOD_CONTROL, 0x43);
			CenterWindow(hWnd);
			AddMenus(hWnd);
			AddTextBox(hWnd);

			hTest = CreateWindowExW(0, STATUSCLASSNAMEW, NULL,
				WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
				(HMENU)1, GetModuleHandle(NULL), NULL);
			/*
			RegisterChild1();
			CreateWindowW(L"RedPanelClass", NULL,
				WS_CHILD | WS_VISIBLE,
				20, 20, 80, 80,
				hWnd, (HMENU)1, NULL, NULL);


			RegisterChild2();
			CreateWindowEx(0,
				"EChild2Class", NULL,
				WS_CHILD | WS_VISIBLE,
				100, 100, 280, 280,
				hWnd, (HMENU)2, GetModuleHandle(NULL), NULL);


			CreateWindowW(L"static", L"x: Test ",
				WS_CHILD | WS_VISIBLE,
				10, 60, 100, 20,
				hWnd, 0, NULL, NULL);

			hText = CreateWindowW(L"static", L"0",
				WS_CHILD | WS_VISIBLE,
				60, 60, 100, 20,
				hWnd, 0, NULL, NULL);
				*/


			hSidePanel = CreateSidePanel(hWnd);
			hTablePanel = CreateTablePanel(hWnd);
			hConsolePanel = CreateConsole(hWnd);
			ShowWindow(hTest, SW_HIDE);

			break;



			return 0;
		case WM_MOVE:

			StringCbPrintfW(buf, BUF_LEN, L"%ld", clientRect.left);
			SetWindowTextW(hText, buf);

			break;

		case WM_KEYDOWN:
			if (wParam == VK_ESCAPE) {
				int tmp = MessageBoxW(hWnd, L"Quit?", L"Message", MB_OKCANCEL);
				if (tmp == IDOK)  SendMessage(hWnd, WM_CLOSE, 0, 0);
				
			}
			break;

		case WM_KILLFOCUS:
			windowHasFocus = 0;
			break;
		case WM_SETFOCUS:
			windowHasFocus = 1;
			break;

		case WM_COMMAND:
			CommandMsg(hWnd, wParam);
			break;

		case WM_HOTKEY: {
			//HWND temp = GetActiveWindow();
			HWND temp = GetForegroundWindow();
			if (temp != hWnd)break;

			
		}
			if ((wParam) == IDHK_CENTER) {
				CenterWindow(hWnd);
			}
			break;

		case WM_SIZE:
			SendMessage(hTest, WM_SIZE, wParam, lParam);


			MoveWindow(hSidePanel, 0, 0, v_panelWidth, v_panelHeight, 1);
			MoveWindow(hTablePanel, v_panelWidth, 0, clientRect.right, v_panelHeight, 1);
			MoveWindow(hConsolePanel, 0, v_panelHeight, clientRect.right, clientRect.bottom, 1);
	


			break;

		case WM_RBUTTONUP:
			RightClickMenu(hWnd, lParam);
			break;


		case WM_LBUTTONUP:
			ReleaseCapture();
			break;
		case WM_LBUTTONDOWN:
			SetCapture(hWnd);
			break;

		case WM_DESTROY:
			UnregisterHotKey(hWnd, IDHK_CENTER);
			PostQuitMessage(0);
			break;
		default:
			return DefWindowProc(hWnd, message, wParam, lParam);
			break;
	}
	return 0;
}





void CommandMsg(HWND hWnd, WPARAM wParam) {


	switch (LOWORD(wParam)) {
		case IDM_FILE_NEW:
			ShowWindow(hTest, SW_HIDE);
			break;
		case IDM_FILE_OPEN:
			ShowWindow(hTest, SW_SHOW);
			MessageBeep(MB_ICONINFORMATION);
			break;
		case IDM_FILE_EXIT:
			SendMessage(hWnd, WM_CLOSE, 0, 0);
			break;
		case IDM_EDIT_COPY: {
			int x = GetSystemMetrics(SM_CXSCREEN);
			int y = GetSystemMetrics(SM_CYSCREEN);



			MessageBoxW(NULL, IntToLPCWSTR(x), IntToLPCWSTR(y), MB_OK);
		}

			break;

		case IDM_SETTINGS_ONE:{
			CenterWindow(hWnd);

			RECT rc = { 0 };
			GetWindowRect(hWnd, &rc);
			int win_w = rc.right - rc.left;
			int win_h = rc.bottom - rc.top;

			MessageBoxW(NULL, IntToLPCWSTR(win_h), IntToLPCWSTR(win_w), MB_OK);
		}
			break;
		case IDM_EDIT_ONTOP:

			if (FlipCheckMenu(hWnd, IDM_EDIT_ONTOP))
				SetWindowPos(hWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			else
				SetWindowPos(hWnd, HWND_NOTOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
			// current pos, current size
			break;
		case IDM_EDIT_PASTE:
			FlipCheckMenu(hWnd, IDM_EDIT_PASTE);

			break;
		case IDM_WINDOW_WIREFRAME:
			SetRadioMenu(hWnd, IDM_WINDOW_WIREFRAME, IDM_WINDOW_TEXTURED, IDM_WINDOW_WIREFRAME);
			break;
		case IDM_WINDOW_SHADED:
			SetRadioMenu(hWnd, IDM_WINDOW_WIREFRAME, IDM_WINDOW_TEXTURED, IDM_WINDOW_SHADED);
			break;
		case IDM_WINDOW_TEXTURED:
			SetRadioMenu(hWnd, IDM_WINDOW_WIREFRAME, IDM_WINDOW_TEXTURED, IDM_WINDOW_TEXTURED);
			break;
	}

}


LRESULT CALLBACK ChildProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {


	switch (message) {
	case WM_LBUTTONUP:
		MessageBeep(MB_OK);
		CenterWindow(hWnd);
		break;
	}
	return DefWindowProcW(hWnd, message, wParam, lParam);

}

void RegisterChild1() {

	HBRUSH hbrush = CreateSolidBrush(RGB(0, 0, 255));
	WNDCLASSW rwc = { 0 };
	rwc.lpszClassName = L"RedPanelClass";
	rwc.hbrBackground = hbrush;
	rwc.lpfnWndProc = ChildProc;
	rwc.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassW(&rwc);


}


void RegisterChild2() {

	WNDCLASSEX wcex = { 0 };
	wcex.cbSize = sizeof(WNDCLASSEX);
	wcex.lpszClassName = "EChild2Class";
	wcex.hbrBackground = (HBRUSH)CreateSolidBrush(RGB(55, 55, 55));;
	wcex.lpfnWndProc = ChildProc;
	wcex.hCursor = LoadCursor(0, IDC_ARROW);
	RegisterClassEx(&wcex);

	
}




void GetDir() {


	CHAR fileName[FILENAME_MAX];
	WIN32_FIND_DATA findData = { 0 };
	HANDLE hFind = ::FindFirstFile("c:/files/aab/Levels/", &findData);
	//HANDLE handle = FindFirstFile(fileName, &findData);

	while (hFind != INVALID_HANDLE_VALUE){

		findData.cFileName;

		if (FindNextFile(hFind, &findData) == FALSE)
			break;
	}

	FindClose(hFind);


	/*
	wchar_t sp[128];
	wsprintf(sp, L"%s/*.*", folder.c_str());
	WIN32_FIND_DATA fd;
	HANDLE hFind = ::FindFirstFile(sp, &fd);
	if (hFind != INVALID_HANDLE_VALUE) {
		do {
			// read all (real) files in current folder
			// , delete '!' read other 2 default folder . and ..
			if (!(fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY)) {
				names.push_back(fd.cFileName);
			}
			else //Put folders into vector
			{
				folders.push_back(fd.cFileName);
			}

		} while (::FindNextFile(hFind, &fd));
		::FindClose(hFind);
	}

	if (!slim) {

		for (int i = 0; i < names.size(); i++) {
			wcout << names[i] << endl;

		}
		for (int i = 0; i < folders.size(); i++) {
			//wcout << folders[i] << endl;

		}

	

	}
	*/

}

