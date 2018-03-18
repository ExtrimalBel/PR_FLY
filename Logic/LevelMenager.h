#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
#include "BaseEnemy.h"
#include "ExceptionsDefenitions.hpp"
#include "tinyxml2.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
using namespace std;
using namespace sf;
namespace LevelLogic
{
	/*
	Даный класс предназначен для чтении информации об уровнях
	Такой как файл с имененим и фоном уровня, конфига врагов которые присутствуют на уровне, Конфига с бонусами которые
	могут выпадать на уровне. акже может осуществять 
	*/
	struct LOGIC_API LevelConfigStruct
	{
		int LevelNumber;
		string LevelName;
		string SlpashPath;
		string EndSplashPath;
		string BackGroundPath;
		string PathToEnemyConfig;
		int StartRocketsCount;
		vector<pair<Ships::BaseEnemyState,int>> EnemySVector;
		int BackGroundSoundId;
		//ToDO Write Boss Data
	};

	class LOGIC_API LevelMenager
	{
		string BasePath;
		vector<LevelConfigStruct> VectorOfLevelConfig;
		int CurrentLevel;
		void ReadLevelConfig();
		void ReadShipsData(vector<pair<Ships::BaseEnemyState,int>> &ShipsVector,string pathToEnemyConfig); // Читает информацию о врагах на уровне
		void ReadSetOfShipsData(tinyxml2::XMLNode *MainNode, string EnemyName, int Id, vector<pair<Ships::BaseEnemyState, int>> &ShipsVector);
		void WriteDataOfEnemyType(tinyxml2::XMLNode *MainNode, string EnemyName, int Id, vector<pair<Ships::BaseEnemyState, int>> &ShipsVector);
		// TODO добавить информацию о бонусах и боссах
	public:
		LevelConfigStruct* ReturnCurrentLevelConfig();
		
		void NextLevel();
		void PrevLevel();
		bool CheckIfLastLevel(); // Также проверяет то может ли 
		LevelMenager(string BasePath,int StartLevel);
		LevelMenager(string BasePath);
	};
}