#include <SFML/Graphics.hpp>
#include <Logic.h>
#include <MainMenu.h>
#include <Settings.h>
#include <Game.h>
//int level = 0;
int main()
{
	sf::Clock clock;
	sf::RenderWindow window(sf::VideoMode(1280, 720), "SFML works!",sf::Style::Fullscreen);
	window.setFramerateLimit(30);
	MainMenu *Menu = new MainMenu;
	GameField *Field = NULL;
	GameSettings *Set = NULL;

	enum State {Game,Settings,MMenu,Records};
	State Statements = MMenu;
	while (window.isOpen())
	{
		float time = clock.getElapsedTime().asMicroseconds();
		clock.restart();
		time /= 800;
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
		window.clear();
		switch (Statements)
		{
		case MMenu:
			Menu->DrawMenu(window);
			Menu->updateMenu(window);
			if (Menu->IsSelected(window) == 2)
			{
				Statements = Settings;
				Set = new GameSettings;
				delete Menu;
			}
			if (Menu->IsSelected(window) == 3)
			{
				Statements = Game;
				Field = new GameField;
				delete Menu;
			}
			break;
		case Game:
			Field->updatePlayer(time, window);
			if (Field->IfExit() == 1)
			{
				Menu = new MainMenu;
				delete Field;
				Statements = MMenu;
			}

				break;
		case Settings:
			Set->DrawSettings(window);
			Set->update(window);
			if (Set->IfExitSet(window) == 2)
			{
				Statements = MMenu;
				Menu = new MainMenu;
				delete Set;
			}
			break;
		}
		
		window.display();
	}

	return 0;
}