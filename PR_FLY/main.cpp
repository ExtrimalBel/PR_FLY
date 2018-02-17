#include <SFML\Graphics.hpp>
#include <io.h>
//int level = 0;
void LoadVideoMode(int &x, int &y,sf::Uint32 &st);

// Only for debug
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
#include <iostream>
int main()
{
	try
	{
		MainGameClass::Game GameClass("."); // ������� �������� ����� ����
		GameClass.StartDemnedGame(); // ��������� ���� ���� ��������� ������� ������ ����
	}
	catch (Exceptions::GameWantToExit &Ex) // ���� ���������� ����� �� ���� �� ������������� ����������
	{
		Ex.ShowMessage();
		ExitProcess(0); // ���������� ���������� ����
		return 0;
	}
	
	return 0;
}