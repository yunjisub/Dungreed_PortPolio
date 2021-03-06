#include "stdafx.h"
#include "image.h"
image::image() : _imageInfo(NULL), _fileName(NULL), _blendImage(NULL)
{
}
image::~image()
{
}

//빈 비트맵 초기화
HRESULT image::init(int width, int height)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_EMPTY;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, width, height);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;
	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//파일이름
	_fileName = NULL;
	//투명키 컬러 세팅
	_isTrans = false;
	_transColor = RGB(0, 0, 0);

	//이미지 정보를 얻는데 실패했을 시
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//이미지 파일로 초기화
HRESULT image::init(const char* fileName, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//이미지 정보를 얻는데 실패했을 시
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, float x, float y, int width, int height, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->frameWidth = width;
	_imageInfo->frameHeight = height;
	_imageInfo->maxFrameX = 0;
	_imageInfo->maxFrameY = 0;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//이미지 정보를 얻는데 실패했을 시
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
HRESULT image::init(const char* fileName, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//이미지 정보를 얻는데 실패했을 시
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::init(const char* fileName, float x, float y, int width, int height, int frameX, int frameY, bool isTrans, COLORREF transColor)
{
	//재초기화 방지용, 이미지 정보의 값이 들어 있다면 릴리즈해서 깨끗하게 초기화 하자
	if (_imageInfo != NULL) this->release();

	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//이미지 정보 구조체 새로 생성후 초기화 하기
	_imageInfo = new IMAGE_INFO;
	_imageInfo->loadType = LOAD_FILE;
	_imageInfo->hMemDC = CreateCompatibleDC(hdc);
	_imageInfo->hBit = (HBITMAP)LoadImage(_hInstance, fileName, IMAGE_BITMAP, width, height, LR_LOADFROMFILE);
	_imageInfo->hOBit = (HBITMAP)SelectObject(_imageInfo->hMemDC, _imageInfo->hBit);
	_imageInfo->x = x;
	_imageInfo->y = y;
	_imageInfo->width = width;
	_imageInfo->height = height;
	_imageInfo->maxFrameX = frameX - 1;
	_imageInfo->maxFrameY = frameY - 1;
	_imageInfo->frameWidth = width / frameX;
	_imageInfo->frameHeight = height / frameY;

	//파일이름
	int len = strlen(fileName);
	_fileName = new char[len + 1];
	strcpy(_fileName, fileName);

	_stretchImage = nullptr;
	_blendImage = nullptr;
	_rotateImage = nullptr;

	//투명키 컬러 세팅
	_isTrans = isTrans;
	_transColor = transColor;

	//이미지 정보를 얻는데 실패했을 시
	if (_imageInfo->hBit == NULL)
	{
		this->release();
		return E_FAIL;
	}

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}
//알파블렌드 초기화
HRESULT image::initForAlphaBlend()
{
	//DC 가져오기
	HDC hdc = GetDC(_hWnd);

	//알파블렌드 옵션 초기화
	//BlendOp => 현재는 AC_SRC_OVER만 사용가능
	//BlendFlags => 그냥 0대입, 나도 잘 모름, 예전 OS에서 사용했다고 함
	//AlphaFormat => 24bit사용시 0, 32bit사용시 AC_SRC_ALPHA 사용하면 되지만 별차이가 없어서 우린 그냥 0 
	_blendFunc.BlendOp = AC_SRC_OVER;
	_blendFunc.BlendFlags = 0;
	_blendFunc.AlphaFormat = 0;
	//0 ~ 255 => 255일때 원본색상
	//_blendFunc.SourceConstantAlpha = 255;

	//알파블렌드 이미지 정보 구조체 새로 생성후 초기화 하기
	_blendImage = new IMAGE_INFO;
	_blendImage->loadType = LOAD_FILE;
	_blendImage->hMemDC = CreateCompatibleDC(hdc);
	_blendImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * 10, _imageInfo->height * 10);
	_blendImage->hOBit = (HBITMAP)SelectObject(_blendImage->hMemDC, _blendImage->hBit);
	_blendImage->width = WINSIZEX;
	_blendImage->height = WINSIZEY;

	//DC 해제하기
	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForStretchBlend()
{
	HDC hdc = GetDC(_hWnd);

	_stretchImage = new IMAGE_INFO;
	_stretchImage->loadType = LOAD_FILE;
	_stretchImage->hMemDC = CreateCompatibleDC(hdc);
	_stretchImage->hBit = (HBITMAP)CreateCompatibleBitmap(hdc, _imageInfo->width * 10, _imageInfo->height * 10);
	_stretchImage->hOBit = (HBITMAP)SelectObject(_stretchImage->hMemDC, _stretchImage->hBit);
	_stretchImage->width = WINSIZEX * 10;
	_stretchImage->height = WINSIZEY * 10;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

HRESULT image::initForRotateBlend()
{
	HDC hdc = GetDC(_hWnd);

	_rotateImage = new IMAGE_INFO;
	_rotateImage->loadType = LOAD_FILE;
	_rotateImage->hMemDC = CreateCompatibleDC(hdc);
	_rotateImage->hBit = (HBITMAP)LoadImage(_hInstance, _fileName, IMAGE_BITMAP, _imageInfo->width, _imageInfo->height, LR_LOADFROMFILE);
	_rotateImage->hOBit = (HBITMAP)SelectObject(_rotateImage->hMemDC, _rotateImage->hBit);
	_rotateImage->width = _imageInfo->width;
	_rotateImage->height = _imageInfo->height;

	ReleaseDC(_hWnd, hdc);

	return S_OK;
}

//해제
void image::release()
{
	//이미지 정보가 남아 있다면 해제 시켜라
	if (_imageInfo != nullptr)
	{
		//이미지 삭제
		SelectObject(_imageInfo->hMemDC, _imageInfo->hOBit);
		DeleteObject(_imageInfo->hBit);
		DeleteDC(_imageInfo->hMemDC);
	
		//포인터 삭제
		SAFE_DELETE(_imageInfo);
		SAFE_DELETE_ARRAY(_fileName);

		//투명 컬러키 초기화
		_isTrans = false;
		_transColor = RGB(0, 0, 0);
	}

	//알파블렌드 이미지 정보가 남아 있다면 해제 시켜라
	if (_blendImage != nullptr)
	{
		//이미지 삭제
		SelectObject(_blendImage->hMemDC, _blendImage->hOBit);
		DeleteObject(_blendImage->hBit);
		DeleteDC(_blendImage->hMemDC);

		//포인터 삭제
		SAFE_DELETE(_blendImage);
	}

	if (_stretchImage != nullptr)
	{
		SelectObject(_stretchImage->hMemDC, _stretchImage->hOBit);
		DeleteObject(_stretchImage->hBit);
		DeleteDC(_stretchImage->hMemDC);

		SAFE_DELETE(_stretchImage);
	}

	if (_rotateImage != nullptr)
	{
		SelectObject(_rotateImage->hMemDC, _rotateImage->hOBit);
		DeleteObject(_rotateImage->hBit);
		DeleteDC(_rotateImage->hMemDC);

		SAFE_DELETE(_rotateImage);
	}
}

//렌더(내가 원하는 좌표에 출력해라, 일반적으로 우리는 RECT의 LT좌표에 이미지를 붙인다)
void image::render(HDC hdc, int destX, int destY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사할 좌표 시작X
			destY,				//복사할 좌표 시작Y
			_imageInfo->width,	//복사할 이미지 가로크기
			_imageInfo->height,	//복사할 이미지 세로크기
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,				//복사될 대상의 시작지점
			_imageInfo->width,	//복사 영역 가로크기
			_imageInfo->height,	//복사 영역 세로크기
			_transColor);		//복사할때 제외할 색상 (일반적으로 마젠타 색상을 사용함)
	}
	else//원본 이미지 그대로 출력
	{
		BitBlt(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, SRCCOPY);
	}
}

void image::render(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		GdiTransparentBlt(
			hdc,				//복사할 장소의 DC
			destX,				//복사할 좌표 시작X
			destY,				//복사할 좌표 시작Y
			sourWidth,			//복사할 이미지 가로크기
			sourHeight,			//복사할 이미지 세로크기
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,	//복사될 대상 DC
			sourX, sourY,		//복사될 대상의 시작지점
			sourWidth,			//복사 영역 가로크기
			sourHeight,			//복사 영역 세로크기
			_transColor);		//복사할때 제외할 색상 (일반적으로 마젠타 색상을 사용함)
	}
	else//원본 이미지 그대로 출력
	{
		//BitBlt : DC간의 영역끼리 고속복사 해주는 함수
		//메모리DC => 화면DC로 복사한다
		BitBlt(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, SRCCOPY);
	}
}

void image::stretchRender(HDC hdc, int destX, int destY, float scaleX, float scaleY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (!_stretchImage) this->initForStretchBlend();

	if (_isTrans) //배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);

		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_stretchImage->hMemDC,
			0, 0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			_transColor);
	}

	else//원본 이미지 그대로 출력
	{
		StretchBlt(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::stretchAlphaRender(HDC hdc, int destX, int destY, float scaleX, float scaleY, BYTE alpha, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (!_stretchImage) this->initForStretchBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans) //배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		
		      BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
         hdc, destX, destY, SRCCOPY);

      BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
         hdc, destX, destY, SRCCOPY);

      StretchBlt(
         _stretchImage->hMemDC,
         0,
         0,
         _imageInfo->width * scaleX,
         _imageInfo->height * scaleY,
         angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
         0, 0,
         _imageInfo->width,
         _imageInfo->height,
         SRCCOPY
      );

      GdiTransparentBlt(
         _blendImage->hMemDC,
         0,
         0,
         _imageInfo->width * scaleX,
         _imageInfo->height * scaleY,
         _stretchImage->hMemDC,
         0, 0,
         _imageInfo->width * scaleX,
         _imageInfo->height * scaleY,
         _transColor);

      GdiAlphaBlend(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
         _blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY, _blendFunc);

	}
	else//원본 이미지 그대로 출력
	{
		StretchBlt(hdc, destX, destY, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, SRCCOPY);
	}
}

void image::alphaRender(HDC hdc, BYTE alpha, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, 0, 0, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		//3
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, 0, 0, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, BYTE alpha, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->width,
			_imageInfo->height,
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}

	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->width, _imageInfo->height,
			_imageInfo->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height, _blendFunc);
	}
}

void image::alphaRender(HDC hdc, int destX, int destY, int sourX, int sourY, int sourWidth, int sourHeight, BYTE alpha, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle);
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width, _imageInfo->height,
			hdc, destX, destY, SRCCOPY);

		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			sourWidth,
			sourHeight,
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			sourX, sourY,
			sourWidth,
			sourHeight,
			_transColor);

		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_blendImage->hMemDC, 0, 0, sourWidth, sourHeight, _blendFunc);
	}
	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, sourWidth, sourHeight,
			_imageInfo->hMemDC, sourX, sourY, sourWidth, sourHeight, _blendFunc);
	}
}

void image::frameAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, BYTE alpha , float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;

	if (_isTrans)//배경색 없애고 출력
	{
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->frameWidth,  _imageInfo->frameHeight,
			hdc, destX, destY, SRCCOPY);


		if (angle != 0) RotateHDC(hdc, angle, currentFrameX, currentFrameY);
		GdiTransparentBlt(
			_blendImage->hMemDC,	//복사할 장소의 DC
			0,						//복사할 좌표 시작X
			0,						//복사할 좌표 시작Y
			_imageInfo->frameWidth,		//복사할 이미지 가로크기
			_imageInfo->frameHeight,		//복사할 이미지 세로크기
			angle == 0? _imageInfo->hMemDC:_rotateImage->hMemDC,		//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사될 대상의 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 대상의 시작지점			
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);			//복사할때 제외할 색상 (일반적으로 마젠타 색상을 사용함)

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, 0, 0,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}

	else//원본 이미지 그대로 출력
	{
		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_blendImage->hMemDC, _imageInfo->currentFrameX * _imageInfo->frameWidth, _imageInfo->currentFrameY * _imageInfo->frameHeight,
			_imageInfo->frameWidth, _imageInfo->frameHeight, _blendFunc);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	
	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0)RotateHDC(hdc, angle);
		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC
			destX,						//복사할 좌표 시작X
			destY,						//복사할 좌표 시작Y
			_imageInfo->frameWidth,		//복사할 이미지 가로크기
			_imageInfo->frameHeight,	//복사할 이미지 세로크기
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,			//복사될 대상 DC
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사될 대상의 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 대상의 시작지점			
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);				//복사할때 제외할 색상 (일반적으로 마젠타 색상을 사용함)
	}
	else//원본 이미지 그대로 출력
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	
	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (_isTrans)//배경색 없애고 출력
	{
		if (angle != 0) RotateHDC(hdc, angle, currentFrameX, currentFrameY);

		GdiTransparentBlt(
			hdc,						//복사할 장소의 DC
			destX,						//복사할 좌표 시작X
			destY,						//복사할 좌표 시작Y
			_imageInfo->frameWidth,		//복사할 이미지 가로크기
			_imageInfo->frameHeight,	//복사할 이미지 세로크기
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,		//복사될 대상의 시작지점
			_imageInfo->currentFrameY * _imageInfo->frameHeight,	//복사될 대상의 시작지점			
			_imageInfo->frameWidth,		//복사 영역 가로크기
			_imageInfo->frameHeight,	//복사 영역 세로크기
			_transColor);				//복사할때 제외할 색상 (일반적으로 마젠타 색상을 사용함)
	}
	else//원본 이미지 그대로 출력
	{
		BitBlt(hdc, destX, destY, _imageInfo->frameWidth, _imageInfo->frameHeight,
			_imageInfo->hMemDC,
			_imageInfo->currentFrameX * _imageInfo->frameWidth,
			_imageInfo->currentFrameY * _imageInfo->frameHeight, SRCCOPY);
	}
}

void image::frameStretchRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, float angle)
{
	if (_rotateImage == nullptr) initForRotateBlend();
	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_stretchImage) this->initForStretchBlend();

	if (_isTrans) //배경색 없애고 출력
	{
		if (angle != 0) RotateHDC(hdc, angle, currentFrameX, currentFrameY);
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, 0, 0, SRCCOPY);

		// 먼저 늘이거나 줄이고
		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->width * scaleX,
			_imageInfo->height * scaleY,
			angle == 0 ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			0, 0,
			_imageInfo->width,
			_imageInfo->height,
			SRCCOPY
		);

		// 그 뒤에 투명화한다
		GdiTransparentBlt(
			hdc,
			destX,
			destY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_stretchImage->hMemDC,
			_imageInfo->frameWidth * currentFrameX * scaleX,
			_imageInfo->frameHeight * currentFrameY * scaleY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_transColor);
	}
	else//원본 이미지 그대로 출력
	{
		StretchBlt(hdc, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth, currentFrameY * _imageInfo->frameHeight, _imageInfo->frameWidth, _imageInfo->frameHeight, SRCCOPY);
	}
}
//수정
void image::frameStretchAlphaRender(HDC hdc, int destX, int destY, int currentFrameX, int currentFrameY, float scaleX, float scaleY, BYTE alpha, float angle )
{
	if (_rotateImage == nullptr) initForRotateBlend();
	
	//이미지 예외처리
	_imageInfo->currentFrameX = currentFrameX;
	_imageInfo->currentFrameY = currentFrameY;
	if (currentFrameX > _imageInfo->maxFrameX)
	{
		_imageInfo->currentFrameX = _imageInfo->maxFrameX;
	}
	if (currentFrameY > _imageInfo->maxFrameY)
	{
		_imageInfo->currentFrameY = _imageInfo->maxFrameX;
	}

	if (!_stretchImage) this->initForStretchBlend();
	if (!_blendImage) this->initForAlphaBlend();
	_blendFunc.SourceConstantAlpha = alpha;
	if (_rotateImage == nullptr) initForRotateBlend();

	if (_isTrans) //배경색 없애고 출력
	{
		if (angle != 0.f) RotateHDC(hdc, angle, currentFrameX, currentFrameY);
		
		BitBlt(_stretchImage->hMemDC, 0, 0, _imageInfo->width * scaleX , _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);
		BitBlt(_blendImage->hMemDC, 0, 0, _imageInfo->width * scaleX, _imageInfo->height * scaleY,
			hdc, destX, destY, SRCCOPY);


		// 먼저 늘이거나 줄이고
		StretchBlt(
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			angle == 0.f ? _imageInfo->hMemDC : _rotateImage->hMemDC,
			_imageInfo->frameWidth * currentFrameX,
			_imageInfo->frameHeight * currentFrameY,
			_imageInfo->frameWidth,
			_imageInfo->frameHeight,
			SRCCOPY
		);
		GdiTransparentBlt(
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_stretchImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_transColor);

		GdiAlphaBlend(hdc,
			destX,
			destY,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_blendImage->hMemDC,
			0,
			0,
			_imageInfo->frameWidth * scaleX,
			_imageInfo->frameHeight * scaleY,
			_blendFunc);
		
	}
	else // 확대와 알파를 먹인 것 (투명화는 안함)
	{
		StretchBlt(_blendImage->hMemDC, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_imageInfo->hMemDC, currentFrameX * _imageInfo->frameWidth * scaleX, currentFrameY * _imageInfo->frameHeight * scaleY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY, SRCCOPY);

		GdiAlphaBlend(hdc, destX, destY, _imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY,
			_blendImage->hMemDC, destX + (currentFrameX * _imageInfo->frameWidth * scaleX), destY + (currentFrameY * _imageInfo->frameHeight * scaleY),
			_imageInfo->frameWidth * scaleX, _imageInfo->frameHeight * scaleY, _blendFunc);
	}


}

//루프렌더
void image::loopRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY)
{
	//오프셋(offset)은 일반적으로 동일 오브젝트 안에서 오브젝트 처음부터 주어진 요소나 특정 지점까지의 변위차
		//offset은 어떤 특정한 값에서 약간 차이가 나는 값 또는 그 차이 자체를 의미(차이에 따른 보정값)

		//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(일반렌더-이미지잘라서붙이기)
			render(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight);
		}
	}
}

void image::loopAlphaRender(HDC hdc, const LPRECT drawArea, int offsetX, int offsetY, BYTE alpha)
{
	//offset 값이 음수인 경우 보정하기
	if (offsetX < 0) offsetX = _imageInfo->width + (offsetX % _imageInfo->width);
	if (offsetY < 0) offsetY = _imageInfo->height + (offsetY % _imageInfo->height);

	//그려지는 영역 세팅
	RECT rcSour;
	int sourWidth;
	int sourHeight;

	//그려지는 DC 영역 (화면크기)
	RECT rcDest;

	//그려야 할 전체 영역
	int drawAreaX = drawArea->left;
	int drawAreaY = drawArea->top;
	int drawAreaW = drawArea->right - drawArea->left;
	int drawAreaH = drawArea->bottom - drawArea->top;

	//세로 루프영역
	for (int y = 0; y < drawAreaH; y += sourHeight)
	{
		//소스 영역의 높이 계산
		rcSour.top = (y + offsetY) % _imageInfo->height;
		rcSour.bottom = _imageInfo->height;
		sourHeight = rcSour.bottom - rcSour.top;

		//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
		if (y + sourHeight > drawAreaH)
		{
			//넘어간 그림의 값만큼 바텀값을 올려준다
			rcSour.bottom -= (y + sourHeight) - drawAreaH;
			sourHeight = rcSour.bottom - rcSour.top;
		}

		//그려지는 영역
		rcDest.top = y + drawAreaY;
		rcDest.bottom = rcDest.top + sourHeight;

		//가로 루프영역
		for (int x = 0; x < drawAreaW; x += sourWidth)
		{
			//소스 영역의 높이 계산
			rcSour.left = (x + offsetX) % _imageInfo->width;
			rcSour.right = _imageInfo->width;
			sourWidth = rcSour.right - rcSour.left;

			//소스 영역이 그리는 화면을 넘어갔다면(화면밖으로 나갔을때)
			if (x + sourWidth > drawAreaW)
			{
				//넘어간 그림의 값만큼 바텀값을 올려준다
				rcSour.right -= (x + sourWidth) - drawAreaW;
				sourWidth = rcSour.right - rcSour.left;
			}

			//그려지는 영역
			rcDest.left = x + drawAreaX;
			rcDest.right = rcDest.left + sourWidth;

			//그려주자(알파렌더-이미지잘라서붙이기)
			alphaRender(hdc, rcDest.left, rcDest.top, rcSour.left, rcSour.top, sourWidth, sourHeight, alpha);
		}
	}
}

void image::RotateHDC(HDC hdc, float angle, int xFrame, int yFrame)
{
	HBITMAP hTempBitmap;

	if (_rotateImage == nullptr) initForRotateBlend();

	hTempBitmap = GetRotatedBitmap(hdc, angle, xFrame, yFrame);

	(HBITMAP)SelectObject(_rotateImage->hMemDC, hTempBitmap);
	
	DeleteObject(hTempBitmap);
}


HBITMAP image::GetRotatedBitmap(HDC hdc, float angle, int xFrame, int yFrame)
{
	HDC destDC = CreateCompatibleDC(hdc);											// 회전할 비트맵을 출력받을 DC   
	HBITMAP hbmResult = CreateCompatibleBitmap(hdc, getWidth(), getHeight());		// 회전할 비트맵을 출력받을 메모리비트맵 핸들   

	HBITMAP hbmOldDest = (HBITMAP)SelectObject(destDC, hbmResult);                  // 회전할 비트맵을 출력받을 DC에, 회전할 비트맵을 출력받을 메모리비트맵 선택   

	HBRUSH hbrBack = CreateSolidBrush(RGB(255, 0, 255));                            // 회전으로 인한, 공백영역을 칠할 브러시핸들 생성   
	HBRUSH hbrOld = (HBRUSH)SelectObject(destDC, hbrBack);							// 브러시핸들 선택   
	PatBlt(destDC, 0, 0, getWidth(), getHeight(), PATCOPY);							// 선택된 브러시로, 회전할 비트맵을 출력받을 DC에, 미리 색상을 채워 지움   
	DeleteObject(SelectObject(destDC, hbrOld));                                     // 브러시 해제   

	float cosine = (float)cos(angle);												// 회전이동변환 행렬에 들어갈 cos세타 값을 구함          
	float sine = -(float)sin(angle);												// 회전이동변환 행렬에 들어갈 sin세타 값을 구함   

	SetGraphicsMode(destDC, GM_ADVANCED);                                           // 윈도우 좌표계의 회전을 위하여, 그래픽모드를 확장모드로 변경합니다.(요구사항:윈98,NT이상)   

	XFORM xform;                                                                    // 방정식을 표현하는 3행3열의 행렬 선언   
	xform.eM11 = cosine;                                                            // 1행 1열 성분 설정 (회전성분)   
	xform.eM12 = sine;                                                              // 1행 2열 성분 설정 (회전성분)   
	xform.eM21 = -sine;                                                             // 2행 1열 성분 설정 (회전성분)   
	xform.eM22 = cosine;                                                            // 2행 2열 성분 설정 (회전성분)   
	xform.eDx = (FLOAT)getFrameWidth() / 2.0f + xFrame * getFrameWidth();           // 3행 1열 성분 설정 (X축 이동 성분)   
	xform.eDy = (FLOAT)getFrameHeight() / 2.0f + yFrame * getFrameHeight();         // 3행 2열 성분 설정 (Y축 이동 성분)   

	SetWorldTransform(destDC, &xform);

	// 회전된 메모리DC에, 회전할 이미지를 출력   

	BitBlt(destDC,
		-(getFrameWidth() / 2.0f), 
		-(getFrameHeight() / 2.0f), 
		getFrameWidth(), getFrameHeight(),
		getMemDC(), xFrame * getFrameWidth(), 
		yFrame * getFrameHeight(), SRCCOPY);

	SelectObject(destDC, hbmOldDest);
	DeleteObject(destDC);

	return hbmResult;
}