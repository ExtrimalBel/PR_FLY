#pragma once
#include "SFML\Graphics.hpp"
#include <string>
#include <vector>
#include "BaseEnemy.h"
#include "ExceptionsDefenitions.hpp"
#include "tinyxml2.h"
using namespace std;
using namespace sf;
namespace LevelLogic
{
	/*
	Даный класс предназначен для чтении информации об уровнях
	Такой как файл с имененим и фоном уровня, конфига врагов которые присутствуют на уровне, Конфига с бонусами которые могут выпадать на уровне. акже может осуществять 
	*/
	struct LevelConfigStruct
	{
		int LevelNumber;
		string BackGroundPath;
		vector<pair<Ships::BaseEnemyState,int>> EnemySVector;
		//ToDO Write Boss Data
	};

	class LevelMenager
	{
		string BasePath;
		vector<LevelConfigStruct> VectorOfLevelConfig;
		int CurrentLevel;
		void ReadLevelConfig();
		void ReadShipsData(vector<pair<Ships::BaseEnemyState,int>> &ShipsVector); // Читает информацию о врагах на уровне
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