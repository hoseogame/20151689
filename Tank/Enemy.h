#pragma once
#include "Object.h"
#include <memory>

class Bullet;

class Enemy : public Object
{
private:
	DIRECTION dir;
public:
	explicit Enemy(int x, int y);
	virtual ~Enemy();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
	std::tr1::shared_ptr<Bullet> MakeBullet();
};