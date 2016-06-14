#include <iostream>
#include "Player.h"
#include "Bullet.h"
#include <vector>
#include <memory>
using namespace std;

Player::Player(int x, int y) : Object(x, y, "Ⅹ", PLAYER), isShoot(false)
{};

Player::~Player()
{}

bool Player::CollisionCheck(Object* obj)
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

		case WALL:
		case BOX:
			SetPotion(GetBeforePos().x, GetBeforePos().y);
			break;

		case BOSS:
			break;

		case ENEMY:
		default:
			break;
		}
	}
	return true;
}

void Player::DoAction(KEY key)
{
	SetBeforPos(GetPotion());
	switch (key)
	{
	case KEYUP:
		dir = UP;
		this->SetPotion(GetPotion().x, GetPotion().y - 1);
		break;
	case KEYDOWN:
		dir = DOWN;
		this->SetPotion(GetPotion().x, GetPotion().y + 1);
		break;
	case KEYLEFT:
		dir = LEFT;
		this->SetPotion(GetPotion().x - 2, GetPotion().y);
		break;
	case KEYRIGHT:
		dir = RIGHT;
		this->SetPotion(GetPotion().x + 2, GetPotion().y);
		break;
	case S:
		isShoot = true;
		break;
	default:
		break;
	}
}

tr1::shared_ptr<Bullet> Player::MakeBullet()
{
	isShoot = false;
	switch (dir)
	{
	case UP:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "早", dir, PLAYER_BULLET));
	case DOWN:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "早", dir, PLAYER_BULLET));
	case LEFT:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "收", dir, PLAYER_BULLET));
	case RIGHT:
		return tr1::shared_ptr<Bullet>(new Bullet(GetPotion().x, GetPotion().y, "收", dir, PLAYER_BULLET));
	default:
		return nullptr;
	}
}