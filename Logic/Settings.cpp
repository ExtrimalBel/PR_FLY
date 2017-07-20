#include "stdafx.h"
#include "Settings.h"

GameSettings::GameSettings()
{
	// Подгрузим тестуры и укажем их поизцию в окне
	BackText.loadFromFile("./img/settings/background.png");
	Backspr.setTexture(BackText);
	level1.loadFromFile("./img/settings/level1.png");
	levels1.setTexture(level1);
	level2.loadFromFile("./img/settings/level2.png");
	levels2.setTexture(level1);
	level3.loadFromFile("./img/settings/level3.png");
	levels3.setTexture(level3);
	levels1.setPosition(490, 100);
	levels2.setPosition(490, 160);
	levels3.setPosition(490, 220);
	levels1.setTextureRect(sf::IntRect(0, 0, 300, 50));
	levels2.setTextureRect(sf::IntRect(0, 0, 300, 50));
	levels3.setTextureRect(sf::IntRect(0, 0, 300, 50));
	ExitText.loadFromFile("./img/settings/exit.png");
	ExitSpr.setTexture(ExitText);
	ExitSpr.setPosition(490, 280);
	ExitSpr.setTextureRect(sf::IntRect(0, 0, 300, 50));
	FullScreenText.loadFromFile("./img/settings/fs.png");
	FullScreenspr.setTexture(FullScreenText);
	FullScreenspr.setPosition(490, 340);
	FullScreenspr.setTextureRect(sf::IntRect(0, 0, 300, 50));
}


void GameSettings::DrawSettings(sf::RenderWindow &Window)
{
	Window.draw(Backspr);
	Window.draw(levels1);
	Window.draw(levels2);
	Window.draw(levels3);
	Window.draw(ExitSpr);
	Window.draw(FullScreenspr);
}

void GameSettings::update(sf::RenderWindow &Window)
{
	if (sf::IntRect(490, 100, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		levels1.setTextureRect(sf::IntRect(300, 0, 300, 50));
		selected_level = 1;
		SetLevelGlobal(Window);
	}
	else
	if (sf::IntRect(490, 160, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		levels2.setTextureRect(sf::IntRect(300, 0, 300, 50));
		selected_level = 2;
		SetLevelGlobal(Window);
	}
	else
	if (sf::IntRect(490, 220, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		levels3.setTextureRect(sf::IntRect(300, 0, 300, 50));
		selected_level = 3;
		SetLevelGlobal(Window);
	}
	else if (sf::IntRect(490, 280, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		ExitSpr.setTextureRect(sf::IntRect(300, 0, 300, 50));
		IfExitSet(Window);
	}
	else if (sf::IntRect(490, 340, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		FullScreenspr.setTextureRect(sf::IntRect(300, 0, 300, 50));
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IFScreenChanged(Window);
	}
	else
	{
		selected_level = 0;
		levels1.setTextureRect(sf::IntRect(0, 0, 300, 50));
		levels2.setTextureRect(sf::IntRect(0, 0, 300, 50));
		levels3.setTextureRect(sf::IntRect(0, 0, 300, 50));
		ExitSpr.setTextureRect(sf::IntRect(0, 0, 300, 50));
		FullScreenspr.setTextureRect(sf::IntRect(0, 0, 300, 50));
	}
}

void GameSettings::SetLevelGlobal(sf::RenderWindow &window) // Установка уровня сложности глобально
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (selected_level == 1)
		{
			level = 1;
		}
		if (selected_level == 2)
		{
			level = 2;
		}
		if (selected_level == 3)
		{

			level = 3;
		}
		std::cout << level;

	}

}


void GameSettings::IFScreenChanged(sf::RenderWindow &window)
{
	fullscreen = !fullscreen;
	if (fullscreen)
	{
		window.close();
		window.create(sf::VideoMode(1280, 720), "Work", sf::Style::Fullscreen);
	}
	else
	{
		window.close();
		window.create(sf::VideoMode(1280, 720), "Work");
	}
}
int GameSettings::IfExitSet(sf::RenderWindow &Window)
{
	if (sf::IntRect(490, 280, 300, 50).contains(sf::Mouse::getPosition(Window)))
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 2;
		}
		else
			return 1;
	}
}