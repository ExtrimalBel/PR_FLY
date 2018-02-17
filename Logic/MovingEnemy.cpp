#include "stdafx.h"
#include "MovingEnemy.h"

namespace Ships
{
	MovingEnemy::MovingEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : BaseEnemy(BasePath, cox, coy, EnemyState,SndControl)
	{
		NextCoord.first = EnemyState.MovingCoordinates[0].first;
		NextCoord.second = EnemyState.MovingCoordinates[0].second;
		IdOfNextCoord = 0; // ѕо сути при первом вызове Move будут установлены следующа€ пара координат
		
	}

	void MovingEnemy::Move(float time)
	{
		int x2 = NextCoord.first;
		int y2 = NextCoord.second;
		sf::Vector2f TargetPoint(x2, y2);
		sf::Vector2f direction = TargetPoint - EnemySprite.getPosition();
		float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
		unitVector = unitVector * time * (float)EnemyState.Speed;
		sf::Vector2f playerpos = EnemySprite.getPosition();
		playerpos = playerpos + unitVector;
		EnemySprite.setPosition(playerpos.x, playerpos.y);
		if ((x2 - 4 < playerpos.x && x2 + 4 > playerpos.x) && (y2 - 4 < playerpos.y && y2 + 4 > playerpos.y))
		{
			IdOfNextCoord++;
			if (IdOfNextCoord >= EnemyState.MovingCoordinates.size())
			{
				ForDelete = true;
				return;
			}

			NextCoord.first = EnemyState.MovingCoordinates[IdOfNextCoord].first;
			NextCoord.second = EnemyState.MovingCoordinates[IdOfNextCoord].second;
		}
	}
	void MovingEnemy::Update(float time,RenderWindow &window)
	{
		Move(time);
		Draw(window);
	}
	
}