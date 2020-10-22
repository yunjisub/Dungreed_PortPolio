#include "stdafx.h"
#include "BasicShortSword.h"

HRESULT BasicShortSword::init(int id, ITEMTYPE itemType, WEAPONTYPE weaponType, Skill * skill, string name, string description, ITEMCLASS itemClass,
	float minAtk, float maxAtk, float atkSpeed, int defence, bool useAtkSpeed, int numOfBullet, float reloadTime, Bullet * bullet,
	float accuracy, int buyPrice, bool isBulletInfinite, vector<string> imageNames, string invenImage, string dropImage)
{
	Item::init(id, itemType, weaponType, skill, name, description, itemClass, minAtk, maxAtk, atkSpeed,
		defence, useAtkSpeed, numOfBullet, reloadTime, bullet, accuracy, buyPrice, isBulletInfinite, imageNames, invenImage, dropImage);

	_isRenderFirst = true;
	_baseAngle = -(PI / 6);
	_slashImage = IMAGEMANAGER->findImage("BasicShortSwordEffect");
	return S_OK;
}

void BasicShortSword::update()
{
	Item::update();
	SlashUpdater();
}

void BasicShortSword::render(HDC hdc)
{
	CAMERAMANAGER->Render(hdc, _vImages[0], _renderPosX, _renderPosY, _angle + _baseAngle);
	for (int i = 0; i < _vSlashes.size(); i++) _vSlashes[i]->render(hdc);
}

void BasicShortSword::Activate()
{
	SOUNDMANAGER->play("휘두르기_무척가벼움2 (5)");
	_renderAngle = 0;

	ShortSwordEffect* slash = new ShortSwordEffect();

	slash->init(GetAngleCheckPosX() - _slashImage->getFrameWidth(), GetAngleCheckPosY() - _slashImage->getFrameHeight(), _slashImage->getKey(), (_angle));
	slash->_parent = this;

	_baseAngle = (_baseAngle < 0  ? (PI / 3) : -(PI / 3));
	_vSlashes.push_back(slash);
}

void BasicShortSword::SlashUpdater()
{
	for (int i = 0; i < _vSlashes.size(); i++)
	{
		_vSlashes[i]->update();
		if (_vSlashes[i]->GetEffect()->GetIsDead())
		{
			_vSlashes.erase(_vSlashes.begin() + i);
			i--;
		}
	}
}

void BasicShortSword::SetBaseRenderPos()
{
	bool playerIsLeft = ENTITYMANAGER->getPlayer()->GetIsLeft();	//플레이어 왼쪽인지
	_yFrame = playerIsLeft ? 0 : 1;

	_angleCheckPosX = ENTITYMANAGER->getPlayer()->GetX() + (playerIsLeft ? 20: 55);	//아이템 타입이 한손일때,각도체크용 중점에 플레이어의 x좌표+ 왼쪽인지 여부에따라 맞으면 +20,아니면 +40
	_angleCheckPosY = ENTITYMANAGER->getPlayer()->GetY() + 50;	//각도 체크용 중점에 플레이어의 Y좌표를 받아와서  +45만큼
	_renderPosX = _angleCheckPosX - _vImages[_currentImage]->getFrameWidth() / 2;
	_renderPosY = _angleCheckPosY - _vImages[_currentImage]->getFrameHeight() / 2;
	if (!_isAttacking)	//공격중이 아니면
	{
		_angle = getAngle(_angleCheckPosX, _angleCheckPosY, CAMERAMANAGER->GetAbsoluteX(_ptMouse.x), CAMERAMANAGER->GetAbsoluteY(_ptMouse.y));
		if (_angle > PI * 2) _angle -= PI * 2;
		if (_angle < 0) _angle += PI * 2;
	}
}

void BasicShortSword::ChangeMap()
{
	_vSlashes.clear();
}


void ShortSwordEffect::init(float x, float y, string imgName, float angle)
{
	_x = x;
	_y = y;
	_angle = SetAngleInBoundary(angle);

	_radius = 90;

	_effect = EFFECTMANAGER->AddEffect(_x, _y, imgName, 6, 0, 0, false, 255, _angle, 2,2);
}

void ShortSwordEffect::update()
{
	SetCollide();
}

void ShortSwordEffect::render(HDC hdc)
{
}

void ShortSwordEffect::SetCollide()
{
	if (_effect->GetFrameX() == 0 && _effect->GetAnimTimer() == 0)
	{
		vector<Object*> _vObjs = MAPMANAGER->GetPlayMap()->GetObjects();
		for (int i = 0; i < _vObjs.size(); i++)
		{
			if (_vObjs[i]->GetType() == OBJECTTYPE::OT_MONSTER || _vObjs[i]->GetType() == OBJECTTYPE::OT_BREAKABLE)
			{
				if (UTIL::interactRectArc(_vObjs[i]->GetBody(), POINT{ (LONG)_parent->GetAngleCheckPosX(), (LONG)_parent->GetAngleCheckPosY() }, _radius, _angle - PI * 0.2f, _angle + PI * 0.2f, _radius / 2))
				{
					_vObjs[i]->GetDamage();
				}
			}
		}
	}
}
