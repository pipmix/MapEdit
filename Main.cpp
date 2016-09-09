#include "Headers.h"
#include "Tools.h"

ATOM MyRegisterClass(HINSTANCE hInstance);
BOOL InitInstance(HINSTANCE, int);


static TCHAR szWindowClass[] = _T("MapEditWndClass");
static TCHAR szTitle[] = _T("MapEdit");

int gWidth = 768;
int gHeight = 768;
HINSTANCE hInst;
HWND hWnd;
HWND hTest;

LRESULT CALLBACK WndProc(HWND, UINT, WPARAM, LPARAM);


int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {

	MyRegisterClass(hInstance);
	if (!InitInstance(hInstance, nCmdShow)) return FALSE;
	
	ShowWindow(hWnd,nCmdShow);
	UpdateWindow(hWnd);

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

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {

	UINT check;
	HMENU hTmp = GetMenu(hWnd);

	switch (message) {

	case WM_COMMAND:

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
			case IDM_EDIT_COPY:
				MessageBoxW(NULL, L"Copied", L"Copy", MB_OK);


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
		break;

	case WM_SIZE:
		SendMessage(hTest, WM_SIZE, wParam, lParam);
		break;

	case WM_RBUTTONUP:
		RightClickMenu(hWnd, lParam);
		break;
	case WM_CREATE:
		AddMenus(hWnd);
		AddTextBox(hWnd);

		hTest = CreateWindowExW(0, STATUSCLASSNAMEW, NULL,
			WS_CHILD | WS_VISIBLE, 0, 0, 0, 0, hWnd,
			(HMENU)1, GetModuleHandle(NULL), NULL);

		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}
	return 0;
}


ATOM MyRegisterClass(HINSTANCE hInstance)
{
	WNDCLASSEX wcex;

	wcex.cbSize = sizeof(WNDCLASSEX);

	wcex.style = CS_HREDRAW | CS_VREDRAW;
	wcex.lpfnWndProc = WndProc;
	wcex.cbClsExtra = 0;
	wcex.cbWndExtra = 0;
	wcex.hInstance = hInstance;
	//wcex.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wcex.hIcon = (HICON)LoadImage(NULL, "largeicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);
	wcex.hCursor = LoadCursor(nullptr, IDC_ARROW);
	wcex.hbrBackground = (HBRUSH)(COLOR_GRAYTEXT);
	wcex.lpszMenuName = NULL;
	wcex.lpszClassName = szWindowClass;
	wcex.hIconSm = (HICON)LoadImage(NULL, "smallicon.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE | LR_DEFAULTSIZE | LR_SHARED);

	return RegisterClassEx(&wcex);
}

BOOL InitInstance(HINSTANCE hInstance, int nCmdShow) {

	hInst = hInstance;
	HWND hWnd = CreateWindow(szWindowClass, szTitle,  WS_OVERLAPPEDWINDOW | SS_OWNERDRAW | WS_EX_TOPMOST,
		CW_USEDEFAULT, 0, CW_USEDEFAULT, 0, nullptr, nullptr, hInstance, nullptr);

	if (!hWnd) return FALSE;

	

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);

	return TRUE;
}


