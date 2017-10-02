#include "stdafx.h"
#include "Settings.h"
#include <iostream>
GameSettings::GameSettings(sf::RenderWindow &window)
{
	BMenu = new Back_Menu(0.7, 0.7);
	// Подгрузим тестуры и укажем их поизцию в окне
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
	currentmode = sf::VideoMode::getDesktopMode();
	xco = currentmode.height;
	yco = currentmode.width;
	Vid_Modes = sf::VideoMode::getFullscreenModes();
	videomodefont.loadFromFile("./CyrilicOld.TTF");
	videomodetext.setFont(videomodefont);


	videomodetext.setPosition(20, 20);
	for (std::size_t i = 0; i < Vid_Modes.size(); ++i)
	{
		sf::VideoMode mode = Vid_Modes[i];
		std::cout << "Mode #" << i << ": " << mode.width << "x" << mode.height << " - "
			<< mode.bitsPerPixel << " bpp" << std::endl;
	}
	for (std::vector<sf::VideoMode>::iterator it = Vid_Modes.begin(); it != Vid_Modes.end(); it++)
	{
		if (it->width == 1280 && it->height == 720)
		{
			currentmode = *it;
			break;
		}
	}
	char buf1[10];
	char buf2[10];
	itoa(currentmode.height, buf1, 10);
	itoa(currentmode.width, buf2, 10);
	sf::String str = buf2;
	str += " x ";
	str += buf1;
	modeit = Vid_Modes.begin();
	videomodetext.setString(str);
	cl.restart();
}


void GameSettings::ChangeModes()
{
	
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) && (cl.getElapsedTime().asSeconds() > 1))
	{
		modeit++;
		if (modeit == Vid_Modes.end()) modeit == Vid_Modes.begin();
		char buf1[10];
		char buf2[10];
		itoa(modeit->height, buf1, 10);
		itoa(modeit->width, buf2, 10);
		sf::String str = buf2;
		str += " x ";
		str += buf1;
		videomodetext.setString(str);
		videomodetext.setPosition(20, 20);
		std::cout << modeit->height << std::endl << modeit->width << std::endl;
		std::cout << Vid_Modes.size();
	}
	
}

void GameSettings::DrawSettings(sf::RenderWindow &Window)
{
	
	Window.draw(levels1);
	Window.draw(levels2);
	Window.draw(levels3);
	Window.draw(ExitSpr);
	Window.draw(FullScreenspr);
	Window.draw(videomodetext);
}

void GameSettings::update(float time,sf::RenderWindow &Window, sf::Clock &mainclock)
{
	
	BMenu->Update(time, Window);
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
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) IFScreenChanged(Window,mainclock);
	}
	else
	{
		selected_level = 0;
		levels1.setTextureRect(sf::IntRect(0, 0, 300, 50));
		levels2.setTextureRect(sf::IntRect(0, 0, 300, 50));
		levels3.setTextureRect(sf::IntRect(0, 0, 300, 50));
		ExitSpr.setTextureRect(sf::IntRect(0, 0, 300, 50));
		FullScreenspr.setTextureRect(sf::IntRect(0, 0, 300, 50));
		ChangeModes();
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


void GameSettings::IFScreenChanged(sf::RenderWindow &window, sf::Clock &mainclock)
{
	fullscreen = !fullscreen;
	if (fullscreen)
	{
		window.close();
		window.create(sf::VideoMode(1920, 1080), "Work", sf::Style::Fullscreen);
		window.setFramerateLimit(60);
		mainclock.restart();
	}
	else
	{
		window.close();
		window.create(sf::VideoMode(1280, 720), "Work");
		window.setFramerateLimit(60);
		mainclock.restart();
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