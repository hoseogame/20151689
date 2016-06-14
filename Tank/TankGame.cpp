#include "TankGame.h"
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <time.h>
#include <string>
#include <stdlib.h>
#include <memory>
#include "ScreenManager.h"
#include "StageManager.h"
#include "Input.h"
#include "Utility.h"
#include "Wall.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Box.h"
#include "Boss.h"

using namespace std;

TankGame::TankGame() : isgameOver(false), isStageChange(true), isWallDraw(false), isStart(true)
{}

TankGame::~TankGame()
{}

void TankGame::Init()
{
	SetObjects();
	wallDrawTimeCheck = GetTickCount() + 500;
	bulletMoveTimeCheck = GetTickCount() + 300;
	enemyMoveTimeCheck = GetTickCount() + 1000;
	enemyShootTimeCheck = GetTickCount() + 7000;
	bulletDeleTimeCheck = enemyShootTimeCheck + 20000;
}

bool TankGame::Update()
{
	if (isStart)
	{
		if (kbhit())
			isStart = false;
	}

	UpdateObjects();
	CollisionCheck();

	return true;
}

void TankGame::Render()
{
	if (isStart)
	{
		ScreenManager::StartScreen();
	}
	else if (isStageChange)
	{
		ScreenManager::PrimeScreen();
		StageManager::GetInstance()->ShowIntro();
		system("cls");
		isStageChange = false;
	}
	else if (isgameOver)
	{
		system("cls");
		ScreenManager::ResultScreen();
		StageManager::GetInstance()->ShowResult();
	}
	else
	{
		StageManager::GetInstance()->ShowUi();
		RenderObjects();
	}
	Sleep(70);
}

void TankGame::Release()
{

}

void TankGame::SetObjects()
{
	ifstream fp;
	fp.open("map1.txt");
	int x = 2, y = 0;
	string type;
	while (!fp.eof())
	{
		fp >> type;
		if (type == "1")
			box.push_back(tr1::shared_ptr<Box>(new Box(x, y)));
		if (type == "2")
			wall.push_back(tr1::shared_ptr<Wall>(new Wall(x, y)));
		if (type == "3")
			enemy.push_back(tr1::shared_ptr<Enemy>(new Enemy(x, y)));
		if (type == "4")
			boss.reset(new Boss(x, y));
		if (type == "5")
			player.reset(new Player(x, y));

		if (x == 46)
		{
			x = 2;
			++y;
		}
		else
			x += 2;

	}
	fp.close();
}

void TankGame::UpdateObjects()
{
	static KEY key = KEYDEFAULT;
	key = Input::KeyInput();

	player->DoAction(key);
	if (player->GetIsShoot())
		bullet.push_back(player->MakeBullet());

	if (GetTickCount() >= bulletMoveTimeCheck)
	{
		for (int i = 0; i < bullet.size(); i++)
			bullet[i]->DoAction(key);
		bulletMoveTimeCheck = GetTickCount() + 300;
	}

	if (GetTickCount() >= enemyMoveTimeCheck)
	{
		for (int i = 0; i < enemy.size(); i++)
			enemy[i]->DoAction(key);
		enemyMoveTimeCheck = GetTickCount() + 800;
	}

	if (GetTickCount() >= enemyShootTimeCheck)
	{
		for (int i = 0; i < enemy.size(); i++)
			bullet.push_back(enemy[i]->MakeBullet());
		enemyShootTimeCheck = GetTickCount() + 9000;
	}

	if (GetTickCount() >= bulletDeleTimeCheck)
	{
		bullet.clear();
		isWallDraw = false;
		bulletDeleTimeCheck = enemyShootTimeCheck + 20000;
	}
}

bool TankGame::CollisionCheck()
{
	//적이 벽 상자 총알
	for (int i = 0; i < enemy.size(); i++)
	{
		for (int j = 0; j < wall.size(); j++) {
			enemy[i]->CollisionCheck(wall[j].get());
		}

		for (int k = 0; k < box.size(); k++) {
			enemy[i]->CollisionCheck(box[k].get());
		}
	}

	// 플레이어가 벽
	for (int j = 0; j < wall.size(); j++) {
		player->CollisionCheck(wall[j].get());
	}
	//플레이어가 상자
	for (int k = 0; k < box.size(); k++) {
		player->CollisionCheck(box[k].get());
	}

	//총알이 상자 벽 적 캐릭터
	for (int i = 0; i < bullet.size(); i++) {
		for (int j = 0; j < wall.size(); j++) {
			bullet[i]->CollisionCheck(wall[j].get());
		}

		for (int k = 0; k < box.size(); k++) {
			bullet[i]->CollisionCheck(box[k].get());
		}
		for (int l = 0; l < enemy.size(); l++)
			bullet[i]->CollisionCheck(enemy[l].get());

		bullet[i]->CollisionCheck(player.get());
	}
	return true;
}

void TankGame::RenderObjects()
{
	if (!isWallDraw)
	{
		for (int i = 0; i < wall.size(); i++)
			wall[i]->DrawThis();
		isWallDraw = true;
	}

	if (GetTickCount() >= wallDrawTimeCheck)
	{
		for (int i = 0; i < box.size(); i++)
			box[i]->DrawThis();

		wallDrawTimeCheck = GetTickCount() + 500;
	}

	for (int i = 0; i < bullet.size(); i++)
		bullet[i]->DrawThis();

	Utility::gotoxy(50, 0);
	cout << " ";

	for (int i = 0; i < enemy.size(); i++)
		enemy[i]->DrawThis();

	boss->DrawThis();
	player->DrawThis();
}