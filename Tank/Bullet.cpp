#include <iostream>
#include "Bullet.h"
#include "Utility.h"
#include "StageManager.h"
using namespace std;

Bullet::Bullet(int x, int y, Shape form, DIRECTION _dir, BULLET_TYPE _bt) : Object(x, y, form, BULLET), dir(_dir), bt(_bt)
{};

Bullet::~Bullet()
{}

bool Bullet::CollisionCheck(Object* obj)
{
	if (obj->GetPotion().x == GetPotion().x && obj->GetPotion().y == GetPotion().y)
	{
		switch (obj->GetType())
		{
		case PLAYER:
			if (bt == ENEMY_BULLET)	{
				StageManager::GetInstance()->LostLife();
				SetPotion(50, 0);
				dir = NONE;
			}
			break;
		case ENEMY:
			if (bt == PLAYER_BULLET){
				SetPotion(50, 0);
				dir = NONE;
			}
			break;
		case BULLET:
		case WALL:
		case BOX:
		case BOSS:
			SetPotion(GetBeforePos().x, GetBeforePos().y);
			SetPotion(50, 0);
			dir = NONE;
		default:
			break;
		}
	}
	return false;
}

void Bullet::DoAction(KEY key)
{
	SetBeforPos(GetPotion());
	switch (dir)
	{
	case UP:
		this->SetPotion(GetPotion().x, GetPotion().y - 1);
		break;
	case DOWN:
		this->SetPotion(GetPotion().x, GetPotion().y + 1);
		break;
	case LEFT:
		this->SetPotion(GetPotion().x - 2, GetPotion().y);
		break;
	case RIGHT:
		this->SetPotion(GetPotion().x + 2, GetPotion().y);
		break;
	default:
		break;
	}
}