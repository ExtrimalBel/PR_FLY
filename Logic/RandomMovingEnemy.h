// Описан класс врага который двигаеться бесконечно по координатам  ну типа босса
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include "BaseEnemy.h"
using namespace std;
using namespace sf;

namespace Ships
{
	class RandomMovingEnemy : public BaseEnemy
	{
		void Move(float time);
		pair <int, int> NextCoord;
		int IdOfNextCoord;
	public:
		RandomMovingEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
		void Update(float time, RenderWindow &window);
	};
}