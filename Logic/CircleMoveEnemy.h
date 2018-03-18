#include <string>
#include <iostream>
#include <SFML/Graphics.hpp>
#include "BaseEnemy.h"

namespace Ships
{
	class CircleMovingEnemy : public BaseEnemy
	{
		void Move(float time);
		pair <int, int> NextCoord;
		int IdOfNextCoord;
	public:
		CircleMovingEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
		void Update(float time, RenderWindow &window);
	};
}