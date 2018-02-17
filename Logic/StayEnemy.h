#pragma once
#include "BaseEnemy.h"
#include <string>
#include <SFML\Graphics.hpp>
using namespace std;

namespace Ships
{
	class StayEnemy : public BaseEnemy
	{
		
		bool MovingFinish; // True ��������� �� �� ������� ������������ �� �������� ����������
		pair<int, int> NextCoord;
		int IdexOfCurrentCoordinates;
		void Move(float time);
	public:
		void Update(float time, RenderWindow &window);
		StayEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
	};
}