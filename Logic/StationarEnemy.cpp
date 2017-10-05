#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>


namespace Enemys
{
	StationarEnemy::StationarEnemy(double cx, double cy, int x, int y, int health, double gunspeed, double speed, double demage) : BaseEnemy(cx, cy, health, gunspeed, speed, demage)
	{
		X = x;
		Y = y;
		enemy.setPosition(x, y);
	}

	void StationarEnemy::Update(float time, sf::RenderWindow &window)
	{
		Move(time);
		Draw(window);
		if (life <= 0) for_delete = true;
	}

	void StationarEnemy::Move(float time)
	{
		enemy.move(-0.1 * time,0);
	}

	void StationarEnemy::Draw(sf::RenderWindow &window)
	{
		window.draw(enemy);
	}
}