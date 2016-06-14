#include <iostream>
#include "DudogiGame.h"
#include "TankGame.h"
#include "Utility.h"

using namespace std;

int main(void)
{
	int Select = 0;

	cout << "					<<Select Game >>					 " << endl;
	cout << "\n\n\n\n\n\n\n\n\n\n";
	cout << "Press 1 : �δ��� ����	\n\nPress 2 : ��ũ ����    " << endl;
	
	cin >> Select;

	switch (Select)
	{
	case 1:		
		DudogiGame* game = new DudogiGame();
		game->Run();
		delete game;
		break;
	}
	switch (Select)
	{
	case 2:
		TankGame EX;
		EX.Init();
		while (1)
		{
			EX.Update();
			EX.Render();
		}
		EX.Release();
		break;
	}
	return 0;
}