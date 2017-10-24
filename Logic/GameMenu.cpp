#include "stdafx.h"
#include "GameMenu.h"
#include <iostream>

MainM::MainM(double cox, double coy, SoundSystem::SoundPlayer &SPlayer) : BaseMenu(cox,coy,SPlayer)
{

	SetUpText();

}


void MainM::Update(float time,sf::RenderWindow &window)
{
	BaseMenu::Update(time, window);
	MenuSelect();
	//if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) window.close();
}

void MainM::Draw(sf::RenderWindow &window)
{
	BaseMenu::Draw(window);
}

void MainM::IfMenuItemSelected(sf::RenderWindow &window)
{
	BaseMenu::IfMenuItemSelected(window);
}

int MainM::MenuSelect()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (menuitem != 0 && menuitem != 4) SPlayer->PlaySound(2);
		if (menuitem == 1) return 3;
		if (menuitem == 2) return 2;
		else if (menuitem == 4) return 22;
		else return 1;
	}
}


void MainM::SetUpText()
{
	// Иницализирую текст "Новая игра"
	textfont.loadFromFile("./CyrilicOld.TTF");
	firstitemtext.setFont(textfont);
	firstitemtext.setCharacterSize(48);
	firstitemtext.setScale(cox, coy);
	//firstitemtext.setFillColor(sf::Color(178,34,34));
	firstitemtext.setFillColor(sf::Color::Black);
	sf::String str = "Новая игра";
	firstitemtext.setString(str);
	firstitemtext.setPosition(840 * cox, 220 * coy);

	// Инициализирую текст "Заггрузить игру"
	seconditemtext.setFont(textfont);
	seconditemtext.setCharacterSize(48);
	seconditemtext.setScale(cox, coy);
	//seconditemtext.setFillColor(sf::Color(178,34,34));
	firstitemtext.setFillColor(sf::Color::Black);
	sf::String loadstr = "Загрузить игру";
	seconditemtext.setString(loadstr);
	seconditemtext.setPosition(810 * cox, 370 * coy);
	// Инициализирую текст "настройки" 
	thirditemtext.setFont(textfont);
	thirditemtext.setCharacterSize(48);
	thirditemtext.setScale(cox, coy);
	//thirditemtext.setFillColor(sf::Color(178,34,34));
	thirditemtext.setFillColor(sf::Color::Black);
	sf::String settingstr = "Настройки";
	thirditemtext.setString(settingstr);
	thirditemtext.setPosition(830 * cox, 520 * coy);

	fouritemtext.setFont(textfont);
	fouritemtext.setCharacterSize(48);
	fouritemtext.setScale(cox, coy);
	//fouritemtext.setFillColor(sf::Color(178,34,34));
	fouritemtext.setFillColor(sf::Color::Black);
	sf::String exitstr = "Выход";
	fouritemtext.setString(exitstr);
	fouritemtext.setPosition(850 * cox, 670 * coy);

}


