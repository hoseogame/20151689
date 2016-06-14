#include <iostream>
#include "Box.h"

using namespace std;

Box::Box(int x, int y) : Object(x, y, "■", BOX)
{};

Box::~Box()
{}

bool Box::CollisionCheck(Object* obj)
{
	if (obj->GetPotion().x == GetPotion().x && obj->GetPotion().y == GetPotion().y)
	{
		switch (obj->GetType())
		{
		case BULLET:
			delete this;
			break;
		case PLAYER:
		case ENEMY:
		case WALL:
		case BOX:
		case BOSS:

		default:
			break;
		}
	}
	return true;
}

void Box::DoAction(KEY key)
{
	//아무행동안함
}