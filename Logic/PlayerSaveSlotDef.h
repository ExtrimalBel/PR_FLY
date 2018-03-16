#pragma once
#include "Player.h"
#include <string>
#include <fstream>
#include "ExceptionsDefenitions.hpp"
#include "UpgradesMenager.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
using namespace std;
using namespace sf;
/*
����� ���������� ��������� ����������� "���� ����������"
� ����� ������ �������� � ����������
*/
namespace LoadAndSave
{
	struct LOGIC_API SaveSlot
	{
		LevelLogic::CurrentPlayerUpgrades PlayerUpInfo; // ������ id ��������
		Ships::PlayerStats PStates; // ������ � ������� ������
		int Cash;
		int NextLevel;
		double LevelCoefficient;
	};

	//����� ���������� ������� ���������� � ��������

	SaveSlot LOGIC_API LoadFromFile(string BasePath,int SaveSlot);

	void LOGIC_API SaveToFile(SaveSlot DataToSave,string BasePath,int SaveSlot);
}