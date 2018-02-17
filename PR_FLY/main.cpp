#include <SFML\Graphics.hpp>
#include <io.h>
//int level = 0;


// Only for debug
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
#include <iostream>
#include <Windows.h>
int main(int argv,char*argc[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		string BasePath;
		if (argv == 2) BasePath = argc[0];
		else BasePath = "./vanilla";

		MainGameClass::Game GameClass(BasePath); // ������� �������� ����� ����
		GameClass.StartDemnedGame(); // ��������� ���� ���� ��������� ������� ������ ����
	}
	catch (Exceptions::GameWantToExit &Ex) // ���� ���������� ����� �� ���� �� ������������� ����������
	{
		Ex.ShowMessage();
		ExitProcess(0); // ���������� ���������� ����
		return 0;
	}
	catch (Exceptions::SoundSystemError &Ex)
	{
		cout << "������ ��� ������ �� ������:" << Ex.Message << endl;
		ExitProcess(0); // ���������� ���������� ����
		return 0;
	}
	
	return 0;
}