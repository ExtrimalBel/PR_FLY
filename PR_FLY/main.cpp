#include <SFML\Graphics.hpp>
#include <io.h>
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
#include <iostream>
#include <Windows.h>
#include <LevelMenager.h>
#include <SaveGame.h>
#include "UpgradesMenager.h"

void TestUpgradeConfig()
{
	LevelLogic::UpgradesConfig *P;
	LevelLogic::UpgradesMenager UP("./Vanilla");
	P = UP.ReturnConfig(); // ����� ��������� ����� �������� � ��������� ����� ������� ������������ ���������� ������
}
int main(int argv,char*argc[])
{
	SetDllDirectoryA("./lib");
	int speed;
	SystemParametersInfo(SPI_GETMOUSESPEED, NULL, &speed, 0);
	
	SystemParametersInfo(SPI_SETMOUSESPEED, NULL, reinterpret_cast<void*>(10), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		string BasePath;
		if (argv == 2) BasePath = argc[0];
		else BasePath = "./vanilla";
		MainGameClass::Game GameClass(BasePath); // ������� �������� ����� ����
		GameClass.StartDemnedGame(); // ��������� ���� ���� ��������� ������� ������ ����
		TestUpgradeConfig();
		//LevelLogic::LevelMenager LM("./vanilla", 1);
	}
	catch (Exceptions::GameWantToExit &Ex) // ���� ���������� ����� �� ���� �� ������������� ����������
	{
		SystemParametersInfo(SPI_SETMOUSESPEED, NULL, reinterpret_cast<void*>(speed), SPIF_UPDATEINIFILE | SPIF_SENDWININICHANGE);
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
	catch (Exceptions::ProcessingEnemyCriticalError &Ex)
	{
		cout << Ex.Message << endl;
		ExitProcess(0);
		return 0;
	}
	catch (Exceptions::LevelMenagerReadError &Ex)
	{
		cout << Ex.Message << endl;
		ExitProcess(0);
		return 0;
	}
	catch (Exceptions::LevelMenagerCreateError &Ex)
	{
		cout << Ex.Message << endl;
		ExitProcess(0);
		return 0;
	}
	return 0;
}