#include "stdafx.h"
#include  "Old_Bullets.h"

Bullet::Bullet(int direction, int x1, int y1, sf::Texture &txt) : Item(txt, 0, 0)
{
	img.loadFromFile("./img/bullets/bullet.png");
	Texture.loadFromImage(img);
	spr.setTexture(Texture);
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
	x = x + (time * 0.1);
	spr.setPosition(x, y);
}

void Bullet::Draw(sf::RenderWindow &window)
{
	window.draw(spr);
}

Enemy_Bullet::Enemy_Bullet(int direction, int x1, int y1,sf::Texture &txt) : Item(txt, 0, 0)
{
	spr.setTextureRect(sf::IntRect(0, 0, 10, 10));
	SetPosition(x1, y1);
	dir = direction;
	x = x1;
	y = y1;
}

void Enemy_Bullet::Move(float time)
{
	x = x + (time * -0.3);
	spr.setPosition( x + (time * -0.3), y);
}

void Enemy_Bullet::Draw(sf::RenderWindow &window)
{
	window.draw(spr);
}

void Enemy_Bullet::Update(sf::RenderWindow &window, float time)
{
	Move(time);
	Draw(window);
}
