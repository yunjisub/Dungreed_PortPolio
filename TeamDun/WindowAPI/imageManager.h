#pragma once
#include "singletonBase.h"
#include "image.h"
//=============================================================
//	## imageManager ##
//=============================================================

class imageManager : public singletonBase <imageManager>
{
private:
	typedef map<string, image*> mapImageList;			//맵으로 만든 이미지목록
	typedef map<string, image*>::iterator mapImageIter;	//맵으로 만든 이미지목록의 반복자

private:
	//map<string, image*> _mImageList;
	mapImageList _mImageList;	//실제 이미지클래스를 담을 STL맵

public:
	//이미지 매니져 초기화
	HRESULT init();
	//이미지 매니져 해제
	void release();

	//빈 비트맵 초기화
	image* addImage(string strKey, int width, int height);
	//이미지 파일로 초기화
	image* addImage(string strKey, const char* fileName, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	image* addImage(string strKey, const char* fileName, float x, float y, int width, int height, bool isTrans = false, COLORREF transColor = RGB(0, 0, 0));
	//프레임 이미지 파일로 초기화
	image* addFrameImage(string strKey, const char* fileName, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));
	image* addFrameImage(string strKey, const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans = true, COLORREF transColor = RGB(255, 0, 255));

	//이미지 키값으로 찾기
	image* findImage(string strKey);
	//이미지 키값으로 삭제
	BOOL deleteImage(string strKey);
	//이미지 전체삭제
	BOOL deleteAll();

//=============================================================
//	## 일반렌더 ##
//=============================================================
	void render(string strKey, HDC hdc, int destX = 0, int destY = 0, float angle = 0);
	void render(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float angle = 0);

//=============================================================
//	## 알파렌더 ##
//=============================================================
	void alphaRender(string strKey, HDC hdc, BYTE alpha, float angle = 0);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, BYTE alpha, float angle = 0);
	void alphaRender(string strKey, HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float angle = 0);

//=============================================================
//	## 프레임렌더 ##
//=============================================================
	void frameRender(string strKey, HDC hdc, int destX, int destY, float angle = 0);
	void frameRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle = 0);
	void frameAlphaRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, int alpha,float angle = 0);
	void frameStretchAlphaRender(string strKey ,HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle = 0);

//=============================================================
//	## 스트레치렌더##
//=============================================================
	void stretchRender(string strKey, HDC hdc, int destX, int destY, float scaleX, float scaleY, float angle = 0);

//=============================================================
//	## 루프렌더 ##
//=============================================================
	void loopRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY);
	void loopAlphaRender(string strKey, HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha);

	void frameStretchRender(string strKey, HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY);

//=============================================================
//  ## 회전 만들기 ##
//=============================================================
	void MakeRotateImage(string strKey);

	imageManager() {}
	~imageManager() {}
};