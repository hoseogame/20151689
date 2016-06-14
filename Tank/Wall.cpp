#include <iostream>
#include "Wall.h"

using namespace std;

Wall::Wall(int x, int y) : Object(x, y, "▤", WALL)
{}

Wall::~Wall()
{}

bool Wall::CollisionCheck(Object* obj)
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

void Wall::DoAction(KEY key)
{
	//아무행동안함
}