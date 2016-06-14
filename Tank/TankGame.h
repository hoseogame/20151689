#pragma once
#include <Windows.h>
#include <vector>
#include <memory>
#include "Object.h"
class GameScene;

class Player;
class Wall;
class Enemy;
class Bullet;
class Box;
class Boss;

using namespace std;

class TankGame
{
private:
	bool isStart;
	bool isgameOver;
	bool isStageChange;
	bool isWallDraw;
	DWORD wallDrawTimeCheck, enemyMoveTimeCheck;
	DWORD enemyShootTimeCheck, bulletMoveTimeCheck;
	DWORD bulletDeleTimeCheck;
	tr1::shared_ptr<Player> player;
	tr1::shared_ptr<Boss> boss;
	vector<tr1::shared_ptr<Wall>> wall;
	vector<tr1::shared_ptr<Bullet>> bullet;
	vector<tr1::shared_ptr<Enemy>> enemy;
	vector<tr1::shared_ptr<Box>> box;

public:
	void Init();
	bool Update();
	void Render();
	void Release();

public:
	explicit TankGame();
	~TankGame();

	void SetObjects();
	bool CollisionCheck();
	void RenderObjects();
	void UpdateObjects();

};
