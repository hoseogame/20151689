#pragma once

enum KEY
{
	KEYLEFT = 75, KEYRIGHT = 77, KEYUP = 72, KEYDOWN = 80, S = 1, KEYSPACE = 32,KEYDEFAULT = 0
};

class Input
{
private:
	static char inkey;
	 Input();
	~Input();
public:
	static KEY KeyInput();
};