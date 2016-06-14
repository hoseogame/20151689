#include <stdio.h>
#include <conio.h>
#include <windows.h>

class Utility
{
private:
	Utility();
	~Utility();

public:
	static void gotoxy(int x, int y)
	{
		COORD CursorPosition = { x, y };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), CursorPosition);
	}
};
