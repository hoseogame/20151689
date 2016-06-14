#include <iostream>
#include "TankGame.h"
#include "Utility.h"

using namespace std;

int main(void)
{
	TankGame EX;
	EX.Init();
	while (1)
	{
		EX.Update();
		EX.Render();
	}
	EX.Release();

	return 0;
}