#include <iostream>
#include <Windows.h>
#include "StageManager.h"
#include "Utility.h"

using namespace std;

StageManager* StageManager::instance = new StageManager();

StageManager::StageManager() : stageLevel(1), playerCount(3), enemyCount(9), killCount(3), score(0)
{
}
StageManager::~StageManager()
{}

StageManager* StageManager::GetInstance()
{
	if (!instance)
		instance = new StageManager();

	return instance;
}

void StageManager::Release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

void StageManager::ShowUi()
{
	Utility::gotoxy(50, 2);
	cout << "주인공 생명력: " << playerCount;
	Utility::gotoxy(50, 4);
	cout << "적 탱크 수: " << enemyCount;
	Utility::gotoxy(50, 6);
	cout << "파괴된 탱크 수:" << killCount;
	Utility::gotoxy(50, 8);
	cout << "점수:" << score;
}

void StageManager::ShowResult()
{
	Utility::gotoxy(39, 7);
	cout << "성공한 스테이지 : " << (stageLevel - 1);
}

void StageManager::ShowIntro()
{
	Utility::gotoxy(25, 9);
	cout << stageLevel << "  스테이지";
	Sleep(3000);
}

void StageManager::ShowSucess()
{
	Utility::gotoxy(0, 0);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                     ////＼＼                           ┃" << endl;
	cout << "┃                    q ∧. ∧ p (^)@                     ┃" << endl;
	cout << "┃                    (└──┘) //                       ┃" << endl;
	cout << "┃                   ♬ 미션 성공 ♪                      ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<< endl;
	Sleep(2000);
	system("cls");
}

void StageManager::ShowFail()
{
	Utility::gotoxy(0, 0);
	cout << "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━┓" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                    미션 실패 !!!!                      ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                               ●┳━┓                 ┃" << endl;
	cout << "┃                                 ┛  ┗                 ┃" << endl;
	cout << "┃                                ■■■■                ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                계속 하시겠습니까? (y/n)                ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┃                                                        ┃" << endl;
	cout << "┗━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛"<< endl;
}