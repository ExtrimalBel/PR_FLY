#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "PlayerClass.h"
using namespace std;
using namespace sf;

namespace Fields
{
	class GameField
	{
		struct FieldPointers//В структуре храняться указатели на класс уровня и на класс меню абгрейда
		{

		} Fpointers;
		vector<pair<int, string>> LevelMas; // Содержит в себе уровни игры
		vector<vector<pair<int,int>>> UpgradeStateMas; // Сдесь содержаться данные о возможных абгредах
		int Money; // Деньги
	public:
		GameField();
		void Upgrade()
	};
}