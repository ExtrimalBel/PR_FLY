#include <SFML/Graphics.hpp>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API Item
{
protected:
	/*
	Сдесь объявлен абстрактный класс который будет основой для всех остальных классов
	Данный класс условно представляет собой "вещь" на игровом поле
	*/
	sf::Image img;
	sf::Texture Texture;
	sf::Sprite spr;
	int x, y; // Позиция объекта
	Item(char *imgname,int x = 0,int y = 0)
	{
		if (x != 0) x = 0;
		if (y != 0) y = 0;
		img.loadFromFile(imgname);
		Texture.loadFromImage(img);
		spr.setTexture(Texture);
		//time.restart();
	}
	void SetPosition(int x1, int y1)
	{
		x = x1;
		y = y1;
	}
};