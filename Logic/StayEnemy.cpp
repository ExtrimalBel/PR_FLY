#include "stdafx.h"
#include "StayEnemy.h"

namespace Ships
{
	StayEnemy::StayEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : BaseEnemy(BasePath, cox, coy, EnemyState, SndControl)
	{
		IdexOfCurrentCoordinates = 1;
		float StartX = this->EnemyState.MovingCoordinates[0].first;
		float StartY = this->EnemyState.MovingCoordinates[0].second;
		EnemySprite.setPosition(sf::Vector2f(StartX * cox, StartY * coy));
		NextCoord.first = EnemyState.MovingCoordinates[1].first;
		NextCoord.second = EnemyState.MovingCoordinates[1].second;
		this->MovingFinish = false;
	}

	void StayEnemy::Move(float time)
	{
		if (MovingFinish) return; // Если корабль закончил перемещие то он стоит на месте
		int x2 = NextCoord.first * cox;
		int y2 = NextCoord.second * coy;
		sf::Vector2f TargetPoint(x2, y2);
		sf::Vector2f direction = TargetPoint - EnemySprite.getPosition();
		float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
		unitVector = unitVector * time * (float)EnemyState.Speed;
		unitVector.x *= cox;
		unitVector.y *= coy;
		sf::Vector2f playerpos = EnemySprite.getPosition();
		playerpos = playerpos + unitVector;
		EnemySprite.setPosition(playerpos.x, playerpos.y);
		if ((x2 - 4 < playerpos.x && x2 + 4 > playerpos.x) && (y2 - 4 < playerpos.y && y2 + 4 > playerpos.y))
		{
			IdexOfCurrentCoordinates++;
			if (IdexOfCurrentCoordinates >= EnemyState.MovingCoordinates.size())
			{
				MovingFinish = true;
				return;
			}
			
			NextCoord.first = EnemyState.MovingCoordinates[IdexOfCurrentCoordinates].first;
			NextCoord.second = EnemyState.MovingCoordinates[IdexOfCurrentCoordinates].second;
		}
	}

	void StayEnemy::Update(float time, RenderWindow &window)
	{
		
		BaseEnemy::Update(time,window);
		if(!DeathAnim)Move(time);
		Draw(window);
	}
}