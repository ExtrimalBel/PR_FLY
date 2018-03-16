#pragma once
#include <string>
#include <iostream>
#include <vector>
#include "tinyxml2.h"
#include "ExceptionsDefenitions.hpp"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
/*
��� ������� ������ ����� ������������� ���� ���������� ��� � � ������ LevelMenager ���� �� ������� ������ ����������
*/
using namespace std;

namespace LevelLogic
{

	struct LOGIC_API CurrentPlayerUpgrades
	{
		// �������� �� ��� ������������� ��������
		int Armorid;
		int FirstGunSpeedId;
		int SecondGunSpeedId;
		int FirstGunDemageId;
		int SecondGunDemageId;
	};
	struct LOGIC_API UpgradesConfig
	{
		vector<pair<double, int>> ArmorUpgrades;
		vector<pair<double, int>> FirstGunSpeedUpgrades;
		vector<pair<double, int>> SecondGunSpeedUpgrades;
		vector<pair<double, int>> FirstGunDemageUpgrades;
		vector<pair<double, int>> SecondGunDemageUpgrades;
		// �� ������
		int ClickId;
		int UpId;
		int BadUpId;
		int BackId;
		int SelectId;
	};
	class LOGIC_API UpgradesMenager
	{
		string ErrorMessage = "��������� ��������� ���������� � ���������";
		UpgradesConfig Config;
		// ������ ��� ������ ������������ ������ �������
		void ReadArmorUpgrades(tinyxml2::XMLElement *Element);
		void ReadFirstGunSpeedUpgrades(tinyxml2::XMLElement *Element);
		void ReadSecondGunSpeedUpgrades(tinyxml2::XMLElement *Element);
		void ReadFirstGunDemageUpgrades(tinyxml2::XMLElement *Element);
		void ReadSecondGunDemageUpgrades(tinyxml2::XMLElement *Element);
		vector<pair<double, int>> TempUpgradeVector;
		void ReadOneUpgrade(tinyxml2::XMLElement *Element); // � � ��� ������ � �������� ����� ���������� ��������� �� ����� �������� ��� �������� ������ �� ��������� � ��������� �����
		void ReadConfig(); // ������� ����� ����������� ������ �������
		void ReadSoundIds(tinyxml2::XMLElement *Element); // ������ �� �������� ������. ���� �� ������� ��������� �� ��������� ������ � ������� �� ���������
		string BasePath;
	public:
		//static CurrentPlayerUpgrades * MakeClearPlayerUpgrades(); // ������ �� ��������� ���� ������� ����� �������������
		UpgradesConfig * ReturnConfig() { return &Config; }
		UpgradesMenager(string BasePath);
	};
}