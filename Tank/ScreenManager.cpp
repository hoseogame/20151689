#include <iostream>
#include "ScreenManager.h"
#include "Utility.h"

using namespace std;

void ScreenManager::StartScreen()
{
	Utility::gotoxy(0, 0);
	cout <<"������������������������������������������������������������" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��         -----                                          ��" << endl;
	cout << "��        /    |                                       /  ��" << endl;
	cout << "��       /       |    ��ũ ����                       /   ��" << endl;
	cout << "��      /          |                            /-----/   ��" << endl;
	cout << "��     /            |---------------|         /           ��" << endl;
	cout << "��    /                               |      /            ��" << endl;
	cout << "��   /              ��������������      |   /             ��" << endl;
	cout << "��  /               ��          ��       |/               ��" << endl;
	cout << "��/                 ��    ��    ��                        ��" << endl;
	cout << "��     ( (    ��������������������������     ) )          ��" << endl;
	cout << "��            ��                      ��                  ��" << endl;
	cout << "��           �� ��                   �� ��                ��" << endl;
	cout << "��           �� �� �������������������� ��                ��" << endl;
	cout << "��           �� ��                   �� ��                ��" << endl;
	cout << "��  ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ ~ $ ~    ~��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "��                  Press Space Key !!                    ��" << endl;
	cout << "��                                                        ��" << endl;
	cout << "������������������������������������������������������������" << endl;
}
void ScreenManager::PrimeScreen()
{
	Utility::gotoxy(0, 0);
	cout << "������������������������������������������������������������";
	for (int i = 1; i <= 19; i++)
	{
		Utility::gotoxy(0, i); 
		cout << "��                                                        ��";
	}
	Utility::gotoxy(0, 20);
	cout << "������������������������������������������������������������";
}

void ScreenManager::ResultScreen()
{
	Utility::gotoxy(0, 0);
	cout << "                     ��ũ ���� ��" << endl;
	cout << endl;
	cout << endl;
	cout << "                    ��������������" << endl;
	cout << "               ~~   ��          ��"  << endl;
	cout << "        ~~          ��    ��    ��"  << endl;
	cout << "    ��         ��������������������������" << endl;
	cout << "  ������       ��                      ��"  << endl;
	cout << "   ����      �� ��                   �� ��"  << endl;
	cout << "             �� �� �������������������� ��"  << endl;
	cout << "             �� ��                   �� ��"  << endl;
	cout << "~ ~ ^ ~ $~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^ ~ ~ ~ ^~ ~ ~ ~ /~ $ ~~" << endl;

}