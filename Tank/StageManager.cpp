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
	cout << "���ΰ� �����: " << playerCount;
	Utility::gotoxy(50, 4);
	cout << "�� ��ũ ��: " << enemyCount;
	Utility::gotoxy(50, 6);
	cout << "�ı��� ��ũ ��:" << killCount;
	Utility::gotoxy(50, 8);
	cout << "����:" << score;
}

void StageManager::ShowResult()
{
	Utility::gotoxy(39, 7);
	cout << "������ �������� : " << (stageLevel - 1);
}

void StageManager::ShowIntro()
{
	Utility::gotoxy(25, 9);
	cout << stageLevel << "  ��������";
	Sleep(3000);
}

void StageManager::ShowSucess()
{
	Utility::gotoxy(0, 0);
	cout << "������������������������������������������������������������" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                     ////����                           ��" << endl;
	cout << "��                    q ��. �� p (^)@                     ��" << endl;
	cout << "��                    (��������) //                       ��" << endl;
	cout << "��                   �� �̼� ���� ��                      ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "������������������������������������������������������������"<< endl;
	Sleep(2000);
	system("cls");
}

void StageManager::ShowFail()
{
	Utility::gotoxy(0, 0);
	cout << "������������������������������������������������������������" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                    �̼� ���� !!!!                      ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                               �ܦ�����                 ��" << endl;
	cout << "��                                 ��  ��                 ��" << endl;
	cout << "��                                �����                ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                ��� �Ͻðڽ��ϱ�? (y/n)                ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "������������������������������������������������������������"<< endl;
}