#include "stdafx.h"
#include "Enemy.h"
#include <iostream>
Enemy::Enemy(double cx, double cy, int health, double gunspeed, coord *beginofcoord, double speed, double demage)
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
	enemyimg.loadFromFile("./img/game/sprite.png");
	enemytex.loadFromImage(enemyimg);
	enemytex.setSmooth(true);
	

	enemy.setTexture(enemytex);
	//enemy.setSize(sf::Vector2f(enemyimg.getSize().x, enemyimg.getSize().y));
	enemy.setScale(cox, coy);
	//enemy.setFillColor(sf::Color::Red);
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

}

void Enemy::Update(float time, sf::RenderWindow &window)
{
	Move(time);
	Draw(window);
	if (life <= 0) for_delete = true;
}

void Enemy::Draw(sf::RenderWindow &window)
{
	window.draw(enemy);
}

void Enemy::Move(float time)
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
	unitVector = unitVector * time * (float) speed;
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


float Enemy::GetTimeFromLastShot()
{
	return lasshot.getElapsedTime().asSeconds();

}

void Enemy::ResetClock()
{
	lasshot.restart();
}

sf::Vector2f Enemy::GetPostion()
{
	sf::Vector2f pos = enemy.getPosition();
//	pos.y -= enemy.getSize().y / 2;
	return pos;
}

void Enemy::RemoveHealth(int health)
{
	life -= health;
}


bool Enemy::IsShot()
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




sf::IntRect Enemy::GetEnemyRect()
{
	sf::IntRect Enemyrect(enemy.getPosition().x, enemy.getPosition().y, enemy.getGlobalBounds().width, enemy.getGlobalBounds().height);
	return Enemyrect;
}

bool Enemy::IsForDelete()
{
	if (life <= 0)
	{
		for_delete = true;
	}
	return for_delete;
}