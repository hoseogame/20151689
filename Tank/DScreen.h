#pragma once
#include <Windows.h>

class Screen
{
private:
	static int g_nScreenIndex;
	static HANDLE g_hScreen[2];
public:
	static void ScreenInit();
	static void ScreenFlipping();
	static void ScreenClear();
	static void ScreenRelease();
	static void ScreenPrint(int x, int y, char *string);
	static void SetColor(unsigned short color);
};