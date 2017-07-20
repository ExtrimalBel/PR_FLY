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
	int dir; // ����������� ���� ����� ���� 1 -���� 2 - ����� 0 - ���� �� �����
public:
	Bullet(int direction,int x1,int y1);
	void Move(float time, sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	int Getx() { return this->x; }
	int Gety() { return this->y; }

};

#endif