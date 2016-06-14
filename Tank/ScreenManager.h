#pragma once

class ScreenManager
{
private:
	ScreenManager();
	~ScreenManager();
public:
	static void StartScreen();
	static void PrimeScreen();
	static void ResultScreen();
};