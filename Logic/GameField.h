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
		struct FieldPointers//� ��������� ��������� ��������� �� ����� ������ � �� ����� ���� ��������
		{

		} Fpointers;
		vector<pair<int, string>> LevelMas; // �������� � ���� ������ ����
		vector<vector<pair<int,int>>> UpgradeStateMas; // ����� ����������� ������ � ��������� ��������
		int Money; // ������
	public:
		GameField();
		void Upgrade()
	};
}