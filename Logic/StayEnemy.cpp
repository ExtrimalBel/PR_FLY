#include "stdafx.h"
#include "StayEnemy.h"

namespace Ships
{
	StayEnemy::StayEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : BaseEnemy(BasePath, cox, coy, EnemyState, SndControl)
	{
		IdexOfCurrentCoordinates = 0;
		NextCoord.first = this->EnemyState.MovingCoordinates[0].first;
		NextCoord.second = this->EnemyState.MovingCoordinates[0].second;
	}

	void StayEnemy::Move(float time)
	{
		if (MovingFinish) return; // Если корабль закончил перемещие то он стоит на месте
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
			
			if (IdexOfCurrentCoordinates >= EnemyState.MovingCoordinates.size())
			{
				MovingFinish = true;
			}

			NextCoord.first = EnemyState.MovingCoordinates[IdexOfCurrentCoordinates].first;
			NextCoord.second = EnemyState.MovingCoordinates[IdexOfCurrentCoordinates].second;
		}
	}

	void StayEnemy::Update(float time, RenderWindow &window)
	{
		Move(time);
		Draw(window);
	}
}