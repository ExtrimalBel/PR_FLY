#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>

namespace Enemys
{
	MovingEnemy::MovingEnemy(double cx, double cy, int health, double gunspeed, coord *beginofcoord, double speed, double demage) : BaseEnemy(cx, cy, health, gunspeed, speed, demage)
	{
		coordinates = beginofcoord;
		enemy.setPosition(coordinates->x, coordinates->y);
		coordinates = coordinates->next;
		x2 = coordinates->x;
		y2 = coordinates->y;
		coord *currentcoord = coordinates;
		while (currentcoord->x != -2000)
		{
			std::cout << "x" << currentcoord->x << " y " << currentcoord->y << std::endl;
			currentcoord = currentcoord->next;
		}
		enemyimg.loadFromFile("./img/game/sprite.png");
		enemytex.loadFromImage(enemyimg);
		enemytex.setSmooth(true);


		enemy.setTexture(enemytex);
		//enemy.setSize(sf::Vector2f(enemyimg.getSize().x, enemyimg.getSize().y));
		enemy.setScale(cox, coy);
		//enemy.setFillColor(sf::Color::Red);
	}

	void MovingEnemy::Update(float time, sf::RenderWindow &window)
	{
		Move(time);
		Draw(window);
		if (life <= 0) for_delete = true;
	}

	void MovingEnemy::Draw(sf::RenderWindow &window)
	{
		window.draw(enemy);
	}


	void MovingEnemy::Move(float time)
	{
		if (x2 == -2000)
		{
			return;
		}
		int xn, yn;
		int x1 = enemy.getPosition().x;
		int y1 = enemy.getPosition().y;
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
}