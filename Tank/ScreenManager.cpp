#include <iostream>
#include "ScreenManager.h"
#include "Utility.h"

using namespace std;

void ScreenManager::StartScreen()
{
	Utility::gotoxy(0, 0);
	cout <<"旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬" << endl;
	cout << "早                                                        早" << endl;
	cout << "早         -----                                          早" << endl;
	cout << "早        /    |                                       /  早" << endl;
	cout << "早       /       |    戀觼 啪歜                       /   早" << endl;
	cout << "早      /          |                            /-----/   早" << endl;
	cout << "早     /            |---------------|         /           早" << endl;
	cout << "早    /                               |      /            早" << endl;
	cout << "早   /              旨收收收收收旬      |   /             早" << endl;
	cout << "早  /               早          早       |/               早" << endl;
	cout << "早/                 早    ≡    早                        早" << endl;
	cout << "早     ( (    旨收收收收收收收收收收收旬     ) )          早" << endl;
	cout << "早            早                      早                  早" << endl;
	cout << "早           〥 〥                   〥 〥                早" << endl;
	cout << "早           〥 〥 收收收收收收收收收〥 〥                早" << endl;
	cout << "早           〥 〥                   〥 〥                早" << endl;
	cout << "早  ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ ~ $ ~    ~早" << endl;
	cout << "早                                                        早" << endl;
	cout << "早                  Press Space Key !!                    早" << endl;
	cout << "早                                                        早" << endl;
	cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭" << endl;
}
void ScreenManager::PrimeScreen()
{
	Utility::gotoxy(0, 0);
	cout << "旨收收收收收收收收收收收收收收收收收收收收收收收收收收收收旬";
	for (int i = 1; i <= 19; i++)
	{
		Utility::gotoxy(0, i); 
		cout << "早                                                        早";
	}
	Utility::gotoxy(0, 20);
	cout << "曲收收收收收收收收收收收收收收收收收收收收收收收收收收收收旭";
}

void ScreenManager::ResultScreen()
{
	Utility::gotoxy(0, 0);
	cout << "                     戀觼 啪歜 部" << endl;
	cout << endl;
	cout << endl;
	cout << "                    旨收收收收收旬" << endl;
	cout << "               ~~   早          早"  << endl;
	cout << "        ~~          早    ≡    早"  << endl;
	cout << "    ≒         旨收收收收收收收收收收收旬" << endl;
	cout << "  曲早旭       早                      早"  << endl;
	cout << "   旨旬      〥 〥                   〥 〥"  << endl;
	cout << "             〥 〥 收收收收收收收收收〥 〥"  << endl;
	cout << "             〥 〥                   〥 〥"  << endl;
	cout << "~ ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ /~ $ ~~" << endl;

}