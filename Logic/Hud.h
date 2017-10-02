#ifndef HUD_H
#define HUD_H


#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#include <SFML\Graphics.hpp>
class LOGIC_API Hud
{
	int score;
	double fuel;
	int life;
	double energy;
	int rockets;
	double cox;
	double coy;
	// Задний фон
	sf::RectangleShape BackHud;
	sf::Image BackHudimg;
	sf::Texture BackHudtex;
	// Заглушки для полос
	sf::RectangleShape lifedel;
	sf::RectangleShape fuelddel;
	sf::RectangleShape energydel;
	// Картинка для жизней
	sf::Image lifeimg;
	sf::Texture lifetex;
	sf::RectangleShape lifer;
	// Картинка для топлива
	sf::Image fuelimg;
	sf::Texture fueltex;
	sf::RectangleShape fuelr;
	// Шрифт для отображения текста
	sf::Font textfont;
	// Объект для отображения результатов
	sf::Text ScoreText;
	// Объект для отображение ракет
	sf::Text RocketsCount;
public:
	Hud(double xco, double yco);
	void UpdateHud(int lifecor, int fuelcor, int scorecor,int corrockets);
	void Draw(sf::RenderWindow &window);
};

#endif