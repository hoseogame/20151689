#pragma once
#include "Object.h"

enum BULLET_TYPE
{
	ENEMY_BULLET, PLAYER_BULLET
};

class Bullet : public Object
{
private:
	DIRECTION dir;
	BULLET_TYPE bt;
public:
	explicit Bullet(int x, int y, Shape form, DIRECTION _dir, BULLET_TYPE _bt);
	virtual ~Bullet();

	bool CollisionCheck(Object* obj) override;
	void DoAction(KEY key) override;
};