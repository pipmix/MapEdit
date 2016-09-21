#pragma once
#include "Headers.h"


class Wind {

	void SetHandle(HWND h);
	void SetParent(HWND p);

	void SetDim(long& x, long& y, long& w, long& h);
	void Resize();

	long& m_posX;
	long& m_posY;
	long& m_width;
	long& m_height;

	HWND m_hWnd;
	HWND m_parentHWnd;



};