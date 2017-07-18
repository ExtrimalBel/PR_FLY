#include <SFML/Graphics.hpp>
#define LOGIC_API __declspec(dllexport)

class LOGIC_API MainMenu
{
	sf::Image imgHud;
	sf::Texture TextHud;
	sf::Sprite SprHud;
	sf::Texture TextBackground;
	sf::Sprite SprBackGround;
	sf::Texture menu1;
	sf::Sprite menus1;
	sf::Texture menu2;
	sf::Sprite menus2;
	bool IsStartGame = false;
	int MenuNum = 0;
public:
	MainMenu()
	{
		imgHud.loadFromFile("./img/menu/menuhud.png");
		TextHud.loadFromImage(imgHud);
		SprHud.setTexture(TextHud);
		TextBackground.loadFromFile("./img/menu/menuback.png");
		SprBackGround.setTexture(TextBackground);
		menu1.loadFromFile("./img/menu/startgame.png");
		menus1.setTexture(menu1);
		menus1.setTextureRect(sf::IntRect(0, 0, 300, 50));
		menus1.setPosition(490, 100);
		menu2.loadFromFile("./img/menu/settings.png");
		menus2.setTexture(menu2);
		menus2.setPosition(490, 160);
	}
	void DrawMenu(sf::RenderWindow &Window)
	{
		SprBackGround.setPosition(0, 0);
		SprHud.setPosition(0, 0);
		Window.draw(SprBackGround);
		Window.draw(SprHud);
		Window.draw(menus1);

	}
	void updateMenu(sf::RenderWindow &Window)
	{
		if (sf::IntRect(490, 100, 300, 50).contains(sf::Mouse::getPosition(Window)))
		{
			menus1.setTextureRect(sf::IntRect(300, 0, 300, 50));
			MenuNum = 1;
		}
		else if (sf::IntRect(490, 160, 300, 50).contains(sf::Mouse::getPosition(Window)))
		{
			MenuNum = 2;
		}
		else
		{
			menus1.setTextureRect(sf::IntRect(0, 0, 300, 50));
			MenuNum = 0;
		}
	}
	int IsSelected(sf::RenderWindow &Window)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			if (MenuNum == 1) return 3;
			else if (MenuNum == 2) return 2;
			else return 1;
		}
	}
};