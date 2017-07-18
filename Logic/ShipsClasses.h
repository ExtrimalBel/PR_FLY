#include "baseitem.h"
#include <iostream>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
int level = 0;
class LOGIC_API Ship : public Item
{
protected:
	int speedbost; // Модификатор ускорения скорости
	int health;
	Ship(char *imagename,int x, int y) : Item(imagename,x,y)
	{
		health = 100;
		speedbost = 0;
	}
	//virtual void Shot() = 0;
};

class LOGIC_API Player : public Ship
{
	
	int life;
public:
	double speed;
	Player();
	void Move(float time)
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
		std::cout << x << std::endl;
		std::cout << y << std::endl;
	}
	void Draw(sf::RenderWindow &window)
	{
		window.draw(spr);
	}
};