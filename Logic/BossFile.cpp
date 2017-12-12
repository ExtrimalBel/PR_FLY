#include "stdafx.h"
#include "BaseForEnemys.h"

namespace Enemys
{
	LevelBoss::LevelBoss(double cx, double cy, EnemyEventDef::EnemyData &DataStruct) : BaseEnemy(cx, cy, DataStruct)
	{
		std::copy(DataStruct.Coordinates.begin(), DataStruct.Coordinates.end(), Coordinates.begin());
		LoadEnemyImage();
		CurItemIndex = 0;
	}

	void LevelBoss::Update(float time, sf::RenderWindow &window)
	{
		if (life <= 0)
		{
			EnemyDeath = true;
			DeathAnimUpdate();
			Draw(window);
			return;
		}
		if (EnemyDeath)
		{
			DeathAnimUpdate();
			return;
		}
		EnemyAnimUpdate();

		Move(time);
		Draw(window);
		if (life <= 0) EnemyDeath = true;
	}

	void LevelBoss::Move(float time)
	{
		EnemyEventDef::MoveType MoveType = Coordinates.front().Type;
		switch (MoveType)
		{
		case EnemyEventDef::MoveCircle:
			MoveCircle(time);
			break;
		case EnemyEventDef::MoveRandom:
			MoveRandom(time);
			break;
		default:
			throw Exceptions::UnknownMoveType("Неизвестный тип перемещения");
			break;
		}
	}

	void LevelBoss::MoveCircle(float time)
	{
		int ListSize = Coordinates.size();
		CountNextPoint(CurItemIndex, time); // Само передвижение между точками
		if (IfPointReached()) CurItemIndex++; // Если достигли конечной точки то идем к следующей
		if (CurItemIndex >= ListSize) CurItemIndex = 0; // Если уже прошли все точки то возвращаемся к первой

	}

	sf::Vector2f LevelBoss::CountNextPoint(int CurItemIndex,float time)
	{
		int xn, yn;
		int x1 = Enemy.getPosition().x;
		int y1 = Enemy.getPosition().y;
		int nextx = Coordinates[CurItemIndex].x;
		int nexty = Coordinates[CurItemIndex].y;
		float speed = Coordinates[CurItemIndex].Speed;
		sf::Vector2f direction = sf::Vector2f(nextx, nexty) - Enemy.getPosition();
		float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
		sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
		unitVector = unitVector * time * (float)speed;
		sf::Vector2f playerpos = Enemy.getPosition();
		playerpos = playerpos + unitVector;
		return playerpos;
	}

	int LevelBoss::FindNewPoint(int PrevNumber)
	{
		int NewPoint = 0;
		int Size = Coordinates.size();
		do{
			NewPoint = rand() % Size;
		} while (NewPoint == PrevNumber);
		return Size;
	}

	bool LevelBoss::IfPointReached()
	{
		int x2 = Coordinates[CurItemIndex].x;
		int y2 = Coordinates[CurItemIndex].y;
		int x = Enemy.getPosition().x;
		int y = Enemy.getPosition().y;
		if (x2 - 4 < x && x2 + 4 > x && y2 - 4 < y && y2 + 4 > y)
			return true;
		else
			return false;
	}

	void LevelBoss::MoveRandom(float time)
	{
		int VectorSize = Coordinates.size();
		CountNextPoint(CurItemIndex, time);	  // Двигаемся до точки
		if (IfPointReached())	// Если дошли до точки то выбираем любую которая не равна текущей
		{
			int RandomPoint = 0;
			do{
				RandomPoint = rand() % VectorSize;
			} while (RandomPoint == CurItemIndex);
			CurItemIndex = RandomPoint;
		}
	}

	void LevelBoss::Draw(sf::RenderWindow &window)
	{
		window.draw(Enemy);
	}
}