#include "baseitem.h"
#include <SFML/Graphics.hpp>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#ifndef BULLETS_I
#define BULLETS_I
#define NOMINMAX
class LOGIC_API Bullet :public Item
{
	int dir; // Направление куда летит пуля 1 -лево 2 - право 0 - Пуля на месте
public:
	Bullet(int direction,int x1,int y1,sf::Texture &txt);
	void Move(float time, sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	int Getx() { return this->x; }
	int Gety() { return this->y; }

};

class LOGIC_API Enemy_Bullet : public Item
{
	int dir;

protected:
	void Move(float time); // Перемещение
	void Draw(sf::RenderWindow &window); // Отрисовка на экране
public:
	Enemy_Bullet(int direction, int x1, int y1,sf::Texture &txt);
	void Update(sf::RenderWindow &window,float time); // Для обновления состояния вражеской пули
	int Getx() { return x; }
	int Gety() { return y; }
	void Setx(int x1) { x = x1; }
	void Sety(int y1) { y = y1; }

};

#endif