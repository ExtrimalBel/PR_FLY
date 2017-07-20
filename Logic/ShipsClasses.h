#ifndef SHIPS_I
#define SHIPS_I

#include "baseitem.h"
#include <iostream>
#include "Bullets.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#define NOMINMAX
class LOGIC_API Ship : public Item
{
protected:
	int speedbost; // ћодификатор ускорени€ скорости
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
	int level = 1;
	int life;
public:
	double speed;
	Player();
	void Move(float time); // ѕередвежение с прив€зкой ко времени
	void Draw(sf::RenderWindow &window);
	int getx(){return x;} // Ёто дл€ предоставлени€ координат из приват области класса
	int gety(){return y;}

};

class LOGIC_API Enemy_Ship : public Ship
{
	
public:
	double speed;
	Enemy_Ship();
	void Move(float time);
	bool InterSects(int bulx, int buly);
	int getx() { return x; }
	int gety() { return y; }
	void setx(int x1) { x = x1; }
	void sety(int y1) { y = y1; }
	void Draw(sf::RenderWindow &window)
	{
		window.draw(spr);
	}
};

#endif