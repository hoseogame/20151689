#include <iostream>
#include "Boss.h"

using namespace std;

Boss::Boss(int x, int y) : Object(x, y, "♨", BOSS)
{};

Boss::~Boss()
{}

bool Boss::CollisionCheck(Object* obj)
{
	if (obj->GetPotion().x == GetPotion().x && obj->GetPotion().y == GetPotion().y)
	{
		switch (obj->GetType())
		{
		case PLAYER:
			break;
		case BULLET:
			break;
		case ENEMY:
			break;
		case WALL:
			break;
		case BOX:
			break;
		case BOSS:
			break;
		default:
			break;
		}
	}
	return true;
}

void Boss::DoAction(KEY key)
{
	//아무행동안함
}