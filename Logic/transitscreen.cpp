#include "stdafx.h"
#include "transitscreen.h"

namespace Screens
{
	BaseScreen::BaseScreen(double cox, double coy,std::string BasePath)
	{
		this->BasePath = BasePath;
		BackgroundText.loadFromFile(BasePath + "/img/trscreen.png");
		Background.setTexture(BackgroundText);
		BackgroundText.setSmooth(true);
		Background.setPosition(0, 0);
		Background.setScale(cox, coy);
		TextFont.loadFromFile(BasePath + "/fonts/CyrilicOld.TTF");
		Message.setFont(TextFont);
		Message.setFillColor(sf::Color::Red);
		Message.setPosition(300 * cox, 300 * coy);
		Message.setScale(cox, coy);
		this->cox = cox;
		this->coy = coy;
	}


	void BaseScreen::Update(sf::RenderWindow &window)
	{
		window.draw(Background);
		window.draw(Message);
	}

	void BaseScreen::SetTextString(sf::String str)
	{
		Message.setString(str);
	}
	int BaseScreen::IfExit()
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			return 1;
		}
		else
		{
			return 0;
		}
	}

	TransitScreen::TransitScreen(double cox, double coy, const char *levelname,std::string BasePath) : BaseScreen(cox, coy, BasePath)
	{

		loaded = false;
		sf::String str = "level ";
		str += levelname;
		str += " loading...";
		//Message.setString(str); // deprecated
		BaseScreen::SetTextString(str);

		this->levelname = levelname;
		this->ToExit = false;
	}
	void TransitScreen::Update(sf::RenderWindow &window)
	{
		BaseScreen::Update(window);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && loaded) this->ToExit = true;
	}
	int TransitScreen::IfExit()
	{
		if (this->ToExit) return 1;
		else return 0;
	}
	void TransitScreen::SetStateOfScreen(int state)
	{
		if (state == 1)
		{
			sf::String str = "level ";
			str += levelname;
			str += " loaded Pres Mouse button to strart";
			Message.setString(str);
			loaded = true;
		}

	}




	// Методы класса bosecomming

	BossComingScreen::BossComingScreen(double cox, double coy, double time, std::string BasePath) : BaseScreen(cox, coy,BasePath)
	{
		Tick.restart();
		this->time = time;
		sf::String boss = "Warning comming boss!";
		BaseScreen::SetTextString(boss);
	}

	int BossComingScreen::IfExit()
	{
		if (Tick.getElapsedTime().asSeconds() > time) return 1;
		else return 0;
	}

	ErrorScreen::ErrorScreen(double cox, double coy, std::string BasePath, std::string Message) : BaseScreen(cox, coy, BasePath)
	{
		SetTextString(Message);
	}

	int ErrorScreen::IfExit()
	{
		if (ToExit) return 1;
		else return 0;
	}

	void ErrorScreen::Update(sf::RenderWindow &window)
	{
		BaseScreen::Update(window);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return))
		{
			ToExit = true;
		}
	}
}