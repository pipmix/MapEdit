#pragma once
#include "Headers.h"


class Sprite {

public:


	HBITMAP m_bitmap;
	long posX, posY;

	bool Initialise(int _iResourceID, int _iMaskResourceID);  
	void Draw();  
	void Process(float _fDeltaTick);  
	int GetWidth() const;  
	int GetHeight() const; 
	int GetX() const;  
	int GetY() const;  
	void SetX(int _i); 
	void SetY(int _i);  
	void TranslateRelative(int _iX, int _iY);  
	void TranslateAbsolute(int _iX, int _iY);   
	
	int centerX;  
	int centerY;  
	HBITMAP m_hSprite;  
	HBITMAP m_hMask;  
	BITMAP m_bitmapSprite;  
	BITMAP m_bitmapMask;  
	static HDC s_hSharedSpriteDC;  
	static int s_iRefCount;private:};

};

