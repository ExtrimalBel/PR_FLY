#include "stdafx.h"
#include "ShipsClasses.h"
#include <SFML/Graphics.hpp>
#define LOGIC_API __declspec(dllexport)
#define NOMINMAX
Player::Player() : Ship("./img/ships/player.png", 100, 100)
{
	speed = 0;
	if (level == 1) life = 3;
	if (level == 2) life = 2;
	if (level == 3) life = 1;
}

void Player::Move(float time)
{
	// pos 1 - Up 2 - Down 3 - Left 4 - Right
	int pos = 0;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		speed = 0.1;
		pos = 1;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		speed = 0.1;
		pos = 2;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		speed = 0.1;
		pos = 3;
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		speed = 0.2;
		pos = 4;
	}
	float dx = 0, dy = 0;
	switch (pos)
	{
	case 1:
		dx = 0; dy = -speed;
		break;
	case 2:
		dx = 0; dy = speed;
		break;
	case 3:
		dx = -speed; dy = 0;
		break;
	case 4:
		dx = speed; dy = 0;
		break;
	}
	x += time * dx;
	y += time * dy;
	if (x > 1200) x = 1200;
	if (y > 640) y = 640;
	if (x < 0) x = 0;
	if (y < 70) y = 70;
	spr.setPosition(x, y);
	speed = 0;
}

void Player::Draw(sf::RenderWindow &window) // Отрисовка спрайта гг
{
	window.draw(spr);
}

// Далее реализации методов класса "противник"

Enemy_Ship::Enemy_Ship() : Ship("./img/ships/enemy.png", 100, 100)
{
	speed = -0.1;
	health = 100;
}

void Enemy_Ship::Move(float time)
{
	double dx = 0;
	dx = speed* time;
	x += dx;
	this->SetPosition(x, y);
}

bool Enemy_Ship::InterSects(int bulx,int buly)
{
	/*int count = 0;
	if (x > bulx + 20) count++;
	if (x + 40 < bulx) count++;
	if (y > buly + 20) count++;
	if (y + 40 < buly) count++;
	if ((x > bulx + 20) && (x + 40 < bulx) && (y > buly + 20) && )
	*/
	std::cout << "ship_x is" << x << std::endl;
	if ((bulx + 20 < x) || (bulx > x + 40)) return false;
	else return true;
	
}