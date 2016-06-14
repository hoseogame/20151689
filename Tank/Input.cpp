#include <Windows.h>
#include <conio.h>
#include "Input.h"

char Input::inkey = NULL;

KEY Input::KeyInput()
{
	if (_kbhit())
	{
		inkey = _getch();

		switch (inkey)
		{
		case KEYLEFT:
			return KEYLEFT;
		case KEYRIGHT:
			return KEYRIGHT;
		case KEYUP:
			return KEYUP;
		case KEYDOWN:
			return KEYDOWN;
		case KEYSPACE:
			return KEYSPACE;
		case 'S':
		case 's':
			return S;
		default:
			return KEYDEFAULT;
		}
	}

	return KEYDEFAULT;
}