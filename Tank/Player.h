#pragma once
#include "Object.h"
#include <memory>

class Bullet;

class Player : public Object
{
private:
	DIRECTION dir;
	bool isShoot;
public:
	explicit Player(int x, int y);
	virtual ~Player();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
	std::tr1::shared_ptr<Bullet> MakeBullet();

	inline bool GetIsShoot()
	{
		return isShoot;
	}
};