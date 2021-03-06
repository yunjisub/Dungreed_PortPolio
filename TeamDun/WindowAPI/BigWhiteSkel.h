#pragma once
#include "enemy.h"

class BigWhiteSkel : public Enemy
{
private:
	float		_probeBottom;
	float		_gravity;
	float		_jumpPower;
	bool		_isJump;
	bool		_downJump;
	bool		_isAttack;
	bool		_leftBack;
	bool		_rightBack;
	int			_jumpCount;
	int			_downJmpTimer;
	int			_jumpTimer;
	int			_idleTimer;
	vector<int>	_attackAnimFrame;
	int			_randomXPosTimer;
	int			_randomXPos;

public:
	virtual HRESULT init(int id, string name, OBJECTTYPE type, vector<string> imgNames);
	virtual void	update();
	virtual	void	release();
	virtual void	render(HDC hdc);	

	virtual void	Move();
	virtual void	Attack();
	virtual void	Animation();
	virtual void	pixelCollision();
};