#include "stdafx.h"
#include "GameField.h"
#include <iostream>
GameField::GameField(double xsc, double ysc, int slot, sf::RenderWindow &window,bool Is_new, char *SaveFile)
{
#define DEBUG
	BackM = new Back_Menu(xsc, ysc);
	xscale = xsc;
	yscale = ysc;
	
	HD = new Hud(xsc, ysc);
	fuel = 100;
	sf::Mouse::setPosition(sf::Vector2i(window.getPosition().x + 200, window.getPosition().y + 200));

	// Debug
	Men = new LevelMenager("vanilla/", xscale, yscale,Is_new,SaveFile);
	WriteLogFile("GameField created");

}

void GameField::UpdateAll(float time, sf::RenderWindow &window)
{
	
	BackM->Update(time, window);
	fuel -= 0.01;
	std::cout << Men->GetHealth() << std::endl;
	HD->UpdateHud(Men->GetHealth(),fuel,50,20);

	Men->Update(time, window);
	Draw(window);


}

void GameField::Draw(sf::RenderWindow &window)
{
	HD->Draw(window);
}

int GameField::IfExit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
		return 1;
	else
		return 0;
}


GameField::~GameField()
{
	Back_Theme.stop();
}