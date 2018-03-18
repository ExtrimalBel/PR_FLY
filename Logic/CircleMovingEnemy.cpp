#include "stdafx.h"
#include "CircleMoveEnemy.h"

namespace Ships
{
	CircleMovingEnemy::CircleMovingEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : BaseEnemy(BasePath, cox, coy, EnemyState, SndControl)
	{
		//Selecting Random Pair Of Coord;
		IdOfNextCoord = 0;
		NextCoord = EnemyState.MovingCoordinates[IdOfNextCoord];
		EnemySprite.setPosition(Vector2f(NextCoord.first, NextCoord.second));
		//Selecting First Target Point
		IdOfNextCoord = 1;
		NextCoord = EnemyState.MovingCoordinates[IdOfNextCoord];
	}

	void CircleMovingEnemy::Move(float time)
	{
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
			IdOfNextCoord++;
			if (IdOfNextCoord >= EnemyState.MovingCoordinates.size()) IdOfNextCoord = 1;

			NextCoord.first = EnemyState.MovingCoordinates[IdOfNextCoord].first;
			NextCoord.second = EnemyState.MovingCoordinates[IdOfNextCoord].second;
		}
	}

	void CircleMovingEnemy::Update(float time, RenderWindow &window)
	{
		BaseEnemy::Update(time, window);
		if (!DeathAnim)Move(time);
		Draw(window);
	}
}