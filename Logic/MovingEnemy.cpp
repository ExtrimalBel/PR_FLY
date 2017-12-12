#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>

namespace Enemys
{
	MovingEnemy::MovingEnemy(double cx, double cy, EnemyEventDef::EnemyData &DataStruct) : BaseEnemy(cx, cy,DataStruct)
	{
		std::copy(DataStruct.Coordinates.begin(), DataStruct.Coordinates.end(), Coordinates.begin()); //  опирует координаты перемещени€
		LoadEnemyImage();
	}

	void MovingEnemy::Update(float time, sf::RenderWindow &window)
	{
		if (EnemyDeath) // ≈сли враг "умер" то исполн€ем код ответственный за анимацию смерти и выходим
		{
			DeathAnimUpdate();
			window.draw(Enemy);
			return;
		}
		EnemyAnimUpdate();
		Move(time);
		Draw(window);
		if (life <= 0)
		{
			EnemyDeath = true;
			LoadEnemyDeathImage();
		}
	}

	void MovingEnemy::Draw(sf::RenderWindow &window)
	{
		window.draw(Enemy);
	}


	void MovingEnemy::Move(float time)
	{
		if (Coordinates.empty()) // ≈сли уже завершили все перемещени€ то помечаем врага дл€ удалени€ и выходим
		{
			for_delete = true;
			return;
		}
		int MovingType = Coordinates.front().Type;
		switch (MovingType)
		{
		case EnemyEventDef::LineMove:
			MoveLine(time);
			break;
		case EnemyEventDef::CircleMove:
			MoveCircle(time);
			break;
		deafult:
			throw Exceptions::UnknownMoveType("Ќеизвестный тип перемещени€");
			break;
		}
	}


	void MovingEnemy::MoveLine(float time)
	{
		int x2 = Coordinates.front().x;
		int y2 = Coordinates.front().y;
		int xn, yn;
		float speed = Coordinates.front().Speed;
		sf::Vector2f direction = sf::Vector2f(x2, y2) - Enemy.getPosition();
		float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
		unitVector = unitVector * time * (float)speed;
		unitVector.x *= cox;
		unitVector.y *= coy;
		sf::Vector2f playerpos = Enemy.getPosition();
		playerpos = playerpos + unitVector;
		Enemy.setPosition(playerpos.x, playerpos.y);
		if ((x2 - 4 < playerpos.x && x2 + 4 > playerpos.x) && (y2 - 4 < playerpos.y && y2 + 4 > playerpos.y))
		{
			Coordinates.pop_front();
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