#include "stdafx.h"
#include  "Bullets.h"

Bullet::Bullet(int direction,int x1,int y1) : Item("./img/bullets/bullet.png",0,0)
{
	SetPosition(x1, y1);
	dir = direction;
}

void Bullet::Move(float time, sf::RenderWindow &window)
{
	/*int dx = 0;
	dir = 2;
	if (dir == 1) dx = -0.1;
	if (dir == 2) dx = 0.1;
	*/
	SetPosition(x + (time * 0.2), y);
}

void Bullet::Draw(sf::RenderWindow &window)
{
	window.draw(spr);
}

