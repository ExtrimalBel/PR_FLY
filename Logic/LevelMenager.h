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
	����� ����� ������������ ��� ������ ���������� �� �������
	����� ��� ���� � �������� � ����� ������, ������� ������ ������� ������������ �� ������, ������� � �������� ������� ����� �������� �� ������. ���� ����� ����������� 
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
		void ReadShipsData(vector<pair<Ships::BaseEnemyState,int>> &ShipsVector); // ������ ���������� � ������ �� ������
		// TODO �������� ���������� � ������� � ������
	public:
		LevelConfigStruct* ReturnCurrentLevelConfig();
		
		void NextLevel();
		void PrevLevel();
		bool CheckIfLastLevel(); // ����� ��������� �� ����� �� 
		LevelMenager(string BasePath,int StartLevel);
		LevelMenager(string BasePath);
	};
}