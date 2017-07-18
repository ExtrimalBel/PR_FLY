#include <SFML\Graphics.hpp>
#include "ShipsClasses.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class GameField{
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
	}
	int IfExit()
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
			return 1;
		else
			return 0;
	}
};