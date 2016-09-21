#include "Wind.h"

void Wind::SetHandle(HWND h){
	m_hWnd = h;
}

void Wind::SetParent(HWND p){
	m_parentHWnd = p;
}

void Wind::SetDim(long & x, long & y, long & w, long & h){

	m_posX = x;
	m_posY = y;
	m_width = w;
	m_height = h;
}

void Wind::Resize(){

	MoveWindow(m_hWnd, m_posX, m_posY, m_width, m_height, 1);
}
