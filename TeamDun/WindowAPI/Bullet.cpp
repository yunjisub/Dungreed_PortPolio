#include "stdafx.h"
#include "Bullet.h"

HRESULT Bullet::init()
{
	return S_OK;
}

void Bullet::update()
{
	
	moveBullet();
	Animation();
	_distance = getDistance(_startX, _startY, _x, _y);
}

void Bullet::release()
{
}

void Bullet::render(HDC hdc)
{
	if (_isFrame)
	{
		CAMERAMANAGER->FrameRender(hdc, _ig, _x, _y, _frameX, _frameY);

	}
	else
	{
		CAMERAMANAGER->Render(hdc, _ig, _x, _y);
	}

}

void Bullet::makeBullet(const char * imageName, BULLETTYPE type, float x, float y, float angle, float speed, float maxDis, bool isFrame)
{
	_ig = IMAGEMANAGER->findImage(imageName);
	_type = type;
	_x = _startX = x;
	_y = _startY = y;
	_angle = angle;
	_speed = speed;
	_isFrame = isFrame;
	_frameX = 0;
	_frameY = 0; 
	_frameTimer = 0;
	_distance = getDistance(_startX, _startY, _x, _y);
	_maxDistance = maxDis;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::moveBullet()
{
	_x += cosf(_angle)*_speed;
	_y += -sinf(_angle)*_speed;
	if (_isFrame)
	{
		_rc = RectMake(_x, _y, _ig->getFrameWidth(), _ig->getFrameHeight());

	}
	else
	{
		_rc = RectMake(_x, _y, _ig->getWidth(), _ig->getHeight());
	}
}

void Bullet::Animation()
{

	_frameTimer++;
	_frameY = 0;
	
	if (_frameTimer > 5)
	{
		_frameTimer = 0;
		_frameX++;

		if (_frameX > _ig->getMaxFrameX())
		{
			_frameX = 0;  //�����
		}
	}
}


