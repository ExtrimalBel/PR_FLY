#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>

namespace Enemys
{
	MovingEnemy::MovingEnemy(double cx, double cy, EnemyEventDef::EnemyData &DataStruct) : BaseEnemy(cx, cy,DataStruct)
	{

	}

	void MovingEnemy::Update(float time, sf::RenderWindow &window)
	{
		Move(time);
		Draw(window);
		if (life <= 0) for_delete = true;
	}

	void MovingEnemy::Draw(sf::RenderWindow &window)
	{
		window.draw(Enemy);
	}


	void MovingEnemy::Move(float time)
	{
		switch (MovingType)
		{
		case 1:
			MoveLine(time);
			break;
		case 2:
			MoveCircle(time);
			break;
		}
	}

	void MovingEnemy::MoveLine(float time)
	{
		if (x2 == -2000)
		{
			return;
		}
		int xn, yn;
		//x1 = enemy.getPosition().x;
		//y1 = enemy.getPosition().y;
		//x1 = Coordinates.
		sf::Vector2f direction = sf::Vector2f(x2, y2) - enemy.getPosition();
		float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
		unitVector = unitVector * time * (float)speed;
		unitVector.x *= cox;
		unitVector.y *= coy;
		sf::Vector2f playerpos = enemy.getPosition();
		playerpos = playerpos + unitVector;
		enemy.setPosition(playerpos.x, playerpos.y);
		if ((x2 - 4 < playerpos.x && x2 + 4 > playerpos.x) && (y2 - 4 < playerpos.y && y2 + 4 > playerpos.y))
		{
			coordinates = coordinates->next;
			x2 = coordinates->x;
			y2 = coordinates->y;
			if (x2 == -2000)
			{
				for_delete = true;
				return;
			}
		}
	}

	void MovingEnemy::MoveCircle(float time)
	{

	}
}