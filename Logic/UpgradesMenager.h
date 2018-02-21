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
При ошибках чтения будут выбрасываться теже исключения что и в классе LevelMenager дабы не плодить классы исключений
*/
using namespace std;

namespace LevelLogic
{

	struct LOGIC_API CurrentPlayerUpgrades
	{
		// Содержит ид уже установленных объектов
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
		// Ид звуков
		int ClickId;
		int UpId;
		int BadUpId;
		int BackId;
		int SelectId;
	};
	class LOGIC_API UpgradesMenager
	{
		string ErrorMessage = "Невоможно прочитать информацию о апгрейдах";
		UpgradesConfig Config;
		// Методы для чтения определенных частей кнофига
		void ReadArmorUpgrades(tinyxml2::XMLElement *Element);
		void ReadFirstGunSpeedUpgrades(tinyxml2::XMLElement *Element);
		void ReadSecondGunSpeedUpgrades(tinyxml2::XMLElement *Element);
		void ReadFirstGunDemageUpgrades(tinyxml2::XMLElement *Element);
		void ReadSecondGunDemageUpgrades(tinyxml2::XMLElement *Element);
		vector<pair<double, int>> TempUpgradeVector;
		void ReadOneUpgrade(tinyxml2::XMLElement *Element); // Т к все записи о апгредах имеют одинаковую структуру то можно выделить код читающий записи об апгрейдах в отдельный метод
		void ReadConfig(); // Главный метод запускающий чтение конфига
		void ReadSoundIds(tinyxml2::XMLElement *Element); // Читает ид звуковых файлов. Дабы не плодить структуры ид храняться вместе с данными об апгрейдах
		string BasePath;
	public:
		//static CurrentPlayerUpgrades * MakeClearPlayerUpgrades(); // Объект по указателю надо удалить после использования
		UpgradesConfig * ReturnConfig() { return &Config; }
		UpgradesMenager(string BasePath);
	};
}