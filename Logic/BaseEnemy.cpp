#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>
namespace Enemys
{
	BaseEnemy::BaseEnemy(double cx, double cy, int health, double gunspeed, double speed, double demage)
	{
		this->demage = demage; // Just for debug
		this->speed = speed;
		this->life = health;
		this->gunspeed = gunspeed;
		lasshot.restart();
		for_delete = false;
		cox = cx;
		coy = cy;
		//copy(st.begin(), st.end() - 1, coordst.begin());
	
	}

	float BaseEnemy::GetTimeFromLastShot()
	{
		return lasshot.getElapsedTime().asSeconds();

	}

	void BaseEnemy::ResetClock()
	{
		lasshot.restart();
	}

	sf::Vector2f BaseEnemy::GetPostion()
	{
		sf::Vector2f pos = enemy.getPosition();
		//	pos.y -= enemy.getSize().y / 2;
		return pos;
	}

	void BaseEnemy::RemoveHealth(int health)
	{
		life -= health;
	}
	bool BaseEnemy::IsShot()
	{
		if (gunspeed == 0) return false;
		if (lasshot.getElapsedTime().asSeconds() > gunspeed)
		{
			lasshot.restart();
			return true;
		}
		else
		{
			return false;
		}
	}
	
	bool BaseEnemy::IsForDelete()
	{
		if (life <= 0)
		{
			for_delete = true;
		}
		return for_delete;
	}
}