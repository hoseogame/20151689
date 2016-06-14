#include <iostream>
#include <stdlib.h>
#include <memory>
#include <vector>
#include "Enemy.h"
#include "Bullet.h"
#include "Utility.h"

using namespace std;

Enemy::Enemy(int x, int y) : Object(x, y, "¡Ú", ENEMY), dir(LEFT)
{};

Enemy::~Enemy()
{}

bool Enemy::CollisionCheck(Object* obj)
{
	if (obj->GetPotion().x == GetPotion().x && obj->GetPotion().y == GetPotion().y)
	{
		int temp;
		switch (obj->GetType())
		{
		case PLAYER:
			break;
		case BULLET:

			break;

		case ENEMY:
		case WALL:
		case BOX:
			SetPotion(GetBeforePos().x, GetBeforePos().y);
			temp = rand() % 4;
			dir = (DIRECTION)temp;
			break;

		case BOSS:
			break;

		default:
			break;
		}
	}
	return true;
}

void Enemy::DoAction(KEY key)
{
	SetBeforPos(GetPotion());

	switch (dir)
	{
	case UP:
		SetPotion(GetPotion().x, GetPotion().y - 1);
		break;
	case DOWN:
		SetPotion(GetPotion().x, GetPotion().y + 1);
		break;
	case LEFT:
		SetPotion(GetPotion().x - 2, GetPotion().y);
		break;
	case RIGHT:
		SetPotion(GetPotion().x + 2, GetPotion().y);
		break;
	default:
		break;
	}
}

tr1::shared_ptr<Bullet> Enemy::MakeBullet()
{
	switch (dir)
	{
	case UP:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "¡è", dir, ENEMY_BULLET));
	case DOWN:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "¡é", dir, ENEMY_BULLET));
	case LEFT:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "¡ç", dir, ENEMY_BULLET));
	case RIGHT:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "¡æ", dir, ENEMY_BULLET));
	default:
		return nullptr;
	}
}