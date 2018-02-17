#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include "BaseEnemy.h"
#include <SoundControl.h>
namespace Ships
{
	class MovingEnemy : public BaseEnemy
	{
		void Move(float time);
		pair <int, int> NextCoord;
		int IdOfNextCoord;
	public:
		MovingEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
		void Update(float time, RenderWindow &window);
	};
}