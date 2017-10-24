#include "stdafx.h"
#include "BaseMenu.h"
#include <SoundSystem.h>
#include "Exceptions.h"
BaseMenu::BaseMenu(double cox, double coy, SoundSystem::SoundPlayer &SPlayer)
{
	sf::Mouse::setPosition(sf::Vector2i(300, 300));
	BMenu = new Back_Menu(cox, coy);
	this->cox = cox;
	this->coy = coy;
	this->SPlayer = &SPlayer;
	//SPlayer.Inicialize();
	ButtonBack.loadFromFile("./img/menu/newgame.png");
	ButtonBack.setSmooth(true);

	logotex.loadFromFile("./img/menu/logo.png");
	logo.setTexture(&logotex);
	logo.setScale(cox, coy);
	logo.setPosition(sf::Vector2f(1200 * cox, 200 * coy));
	sf::Vector2u logosize = logotex.getSize();
	logo.setSize(sf::Vector2f(logosize.x, logosize.y));


	menulogotex.loadFromFile("./img/menu/menulogo.png");
	menulogo.setTexture(&menulogotex);
	menulogo.setScale(cox, coy);
	menulogo.setPosition(sf::Vector2f(50 * cox, 50 * coy));
	sf::Vector2u menulogosize = menulogotex.getSize();
	menulogo.setSize(sf::Vector2f(menulogosize.x, menulogosize.y));


	firstitem.setTexture(&ButtonBack);
	firstitem.setSize(sf::Vector2f(600, 100));
	firstitem.setScale(sf::Vector2f(cox, coy));
	firstitem.setPosition(660 * cox, 200 * coy);
	firstitem.setTextureRect(sf::IntRect(0, 0, 600, 100));


	seconditem.setTexture(&ButtonBack);
	seconditem.setSize(sf::Vector2f(600, 100));
	seconditem.setScale(sf::Vector2f(cox, coy));
	seconditem.setPosition(660 * cox, 350 * coy);
	seconditem.setTextureRect(sf::IntRect(0, 0, 600, 100));



	thirditem.setTexture(&ButtonBack);
	thirditem.setSize(sf::Vector2f(600, 100));
	thirditem.setScale(sf::Vector2f(cox, coy));
	thirditem.setPosition(660 * cox, 500 * coy);
	thirditem.setTextureRect(sf::IntRect(0, 0, 600, 100));

	fourthitem.setTexture(&ButtonBack);
	fourthitem.setSize(sf::Vector2f(600, 100));
	fourthitem.setScale(sf::Vector2f(cox, coy));
	fourthitem.setPosition(660 * cox, 650 * coy);
	fourthitem.setTextureRect(sf::IntRect(0, 0, 600, 100));



	mousecurtex.loadFromFile("./img/cursor.png");
	mousecursorspr.setTexture(mousecurtex);
	mousecursorspr.setScale(cox, cox);
	mousecursorspr.setPosition(0, 0);

	this->SPlayer->PlaySound(3);
}

void BaseMenu::Update(float time, sf::RenderWindow &window)
{

	try
	{
		if (menuitem < 0 || menuitem > 4) throw Exceptions::FileNotFoundException("Ќепраильный пункт меню, устанавливаю в 1");
	}
	catch (Exceptions::FileNotFoundException &Ex)
	{
		Ex.PrintMessage();
	}
	
	sf::Vector2i  m = sf::Mouse::getPosition(window);
	mousecursorspr.setPosition(sf::Vector2f(m.x,m.y));
	BMenu->Update(time, window);
	IfMenuItemSelected(window);
	Draw(window);
}


void BaseMenu::Draw(sf::RenderWindow &window)
{
	window.draw(firstitem);
	window.draw(seconditem);
	window.draw(thirditem);
	window.draw(fourthitem);
	window.draw(logo);
	window.draw(menulogo);
	window.draw(firstitemtext);
	window.draw(seconditemtext);
	window.draw(thirditemtext);
	window.draw(fouritemtext);
	window.draw(mousecursorspr);
}

void BaseMenu::IfMenuItemSelected(sf::RenderWindow &window)
{
	sf::IntRect NewGamerect(firstitem.getPosition().x, firstitem.getPosition().y, firstitem.getGlobalBounds().width, firstitem.getGlobalBounds().height);
	sf::IntRect LoadGameerect(seconditem.getPosition().x, seconditem.getPosition().y, seconditem.getGlobalBounds().width, seconditem.getGlobalBounds().height);
	sf::IntRect setrect(thirditem.getPosition().x, thirditem.getPosition().y, thirditem.getGlobalBounds().width, thirditem.getGlobalBounds().height);
	sf::IntRect exitrect(fourthitem.getPosition().x, fourthitem.getPosition().y, fourthitem.getGlobalBounds().width, fourthitem.getGlobalBounds().height);
	if (NewGamerect.contains(sf::Mouse::getPosition(window)))
	{
		SPlayer->PlaySound(1);
		SPlayer->SetOnElement(true);
		//firstitemtext.setFillColor(sf::Color::Cyan);
		std::cout << 660 * cox << std::endl << 200 * cox << std::endl;
		firstitem.setTextureRect(sf::IntRect(600, 0, 600, 100));
		menuitem = 1;
	}
	else if (LoadGameerect.contains(sf::Mouse::getPosition(window)))
	{
		SPlayer->PlaySound(1);
		SPlayer->SetOnElement(true);
		//seconditemtext.setFillColor(sf::Color::Cyan);
		seconditem.setTextureRect(sf::IntRect(600, 0, 600, 100));
		menuitem = 2;
	}
	else if (setrect.contains(sf::Mouse::getPosition(window)))
	{
		SPlayer->PlaySound(1);
		SPlayer->SetOnElement(true);
		//thirditemtext.setFillColor(sf::Color::Cyan);
		thirditem.setTextureRect(sf::IntRect(600, 0, 600, 100));
		menuitem = 3;
	}
	else if (exitrect.contains(sf::Mouse::getPosition(window)))
	{
		SPlayer->PlaySound(1);
		SPlayer->SetOnElement(true);
		//fouritemtext.setFillColor(sf::Color::Cyan);
		fourthitem.setTextureRect(sf::IntRect(600, 0, 600, 100));
		menuitem = 4;
	}
	else
	{
		SPlayer->SetOnElement(false);
		//firstitemtext.setFillColor(sf::Color(178, 34, 34));
		//seconditemtext.setFillColor(sf::Color(178, 34, 34));
		//thirditemtext.setFillColor(sf::Color(178, 34, 34));
		//fouritemtext.setFillColor(sf::Color(178, 34, 34));
		menuitem = 0;
		firstitem.setTextureRect(sf::IntRect(0, 0, 600, 100));
		seconditem.setTextureRect(sf::IntRect(0, 0, 600, 100));
		thirditem.setTextureRect(sf::IntRect(0, 0, 600, 100));
		fourthitem.setTextureRect(sf::IntRect(0, 0, 600, 100));
	}
}