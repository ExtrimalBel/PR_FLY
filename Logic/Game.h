#include <SFML\Graphics.hpp>
#include "ShipsClasses.h"
#include <vector>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#ifndef GAME_I // Стандартная  процедура для предотвращения повторного включения заголовка
#define GAME_I

#include "Bullets.h"
// This class is the game Field class
class __declspec(dllexport) GameField{
	std::vector<Bullet> Bullets;
	sf::Texture BackText;
	sf::Sprite SprBack;
	sf::Texture DHudText;
	sf::Texture UHudText;
	sf::Sprite UHudSpr;
public:
	Player p1;
	GameField()
	{
		UHudText.loadFromFile("./img/game/uhud.png");
		UHudSpr.setTexture(UHudText);
		UHudSpr.setPosition(0, 0);
	}
	void updatePlayer(float time,sf::RenderWindow &window)
	{
		window.draw(UHudSpr);
		p1.Move(time);
		p1.Draw(window);
		AddBullet();
		IFDELETEBULLET();
		for (std::vector<Bullet>::iterator it = Bullets.begin(); it != Bullets.end(); it++)
		{
			it->Move(time, window);
			it->Draw(window);
		}
	}
	int IfExit()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 1;
		else
			return 0;
	}
	void AddBullet()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			Bullet B(2,p1.getx() + 70,p1.gety() + 35);
			Bullets.push_back(B);
		}
	}
	void IFDELETEBULLET()
	{
		for (std::vector<Bullet>::iterator it = Bullets.begin(); it != Bullets.end(); it++)
		{
			if (Bullets.size() == 0) return;
			if (it->Getx() > 1280)
			{
				Bullets.erase(it);
				IFDELETEBULLET();
				break;
			}
		}
	}
};
#endif