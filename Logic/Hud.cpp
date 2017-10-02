#include "stdafx.h"
#include "Hud.h"
#include <iostream>
Hud::Hud(double xco,double yco)
{
	life = 100;
	cox = xco;
	coy = yco;
	std::cout << cox << coy;
	BackHudimg.loadFromFile("./img/game/uhud.png");
	BackHudtex.loadFromImage(BackHudimg);
	BackHud.setTexture(&BackHudtex);
	//BackHud.setScale(sf::Vector2f(cox,coy));
	BackHud.setPosition(sf::Vector2f(0, 0));
	BackHud.setSize(sf::Vector2f(1920 * cox, 100 * coy));
	// Инициализирую каринку жизней
	lifeimg.loadFromFile("./img/game/lifeimg.png");
	lifetex.loadFromImage(lifeimg);
	lifer.setTexture(&lifetex);
	lifer.setSize(sf::Vector2f(720, 30));
	lifer.setScale(cox, coy);
	lifer.setPosition(0, 0);
	lifedel.setFillColor(sf::Color::Black);
	lifedel.setPosition(720 * cox, 0);
	lifedel.setSize(sf::Vector2f(0, 30));
	// Инициализирую картинку топлива
	fuelimg.loadFromFile("./img/game/fuelimg.png");
	fueltex.loadFromImage(fuelimg);
	fuelr.setTexture(&fueltex);
	fuelr.setSize(sf::Vector2f(640, 30));
	fuelr.setScale(cox, coy);
	fuelr.setPosition(0, 32 * coy);
	fuelddel.setFillColor(sf::Color::Black);
	fuelddel.setPosition(640 * cox, 32 * coy);
	fuelddel.setSize(sf::Vector2f(0, 30));
	// Инициализирую текст
	textfont.loadFromFile("./CyrilicOld.TTF");
	// Инициализация текста результата
	ScoreText.setFont(textfont);
	ScoreText.setCharacterSize(48);
	ScoreText.setScale(cox, coy);
	ScoreText.setPosition(1600 * cox, 10 * coy);
	ScoreText.setFillColor(sf::Color::Red);
	// Инициализирую счётчик ракет
	RocketsCount.setFont(textfont);
	RocketsCount.setCharacterSize(48);
	RocketsCount.setScale(cox, coy);
	RocketsCount.setPosition(1300 * cox, 10 * coy);
	RocketsCount.setFillColor(sf::Color::Red);
	// Загружаю строку в результат
	char buff[10];
	score = 0;
	itoa(score, buff, 10);
	sf::String str = "Очки";
	str += buff;
	ScoreText.setString(str);
	// Загружаю очки в рокетыный счётчик))
	rockets = 0;
	itoa(rockets, buff, 10);
	sf::String str2 = "Рокеты ";
	str += buff;
	RocketsCount.setString(str2);
}

void Hud::UpdateHud(int lifecor,int fuelcor,int scorecor,int corrockets)
{
	life = lifecor;
	int x = 100 - lifecor;
	int sizex = (x * 720) / 100;
	int posx = 720 - sizex;
	sizex *= cox;
	posx *= cox;
	lifedel.setPosition(sf::Vector2f(posx, 0));
	lifedel.setSize(sf::Vector2f(sizex, 30 * coy));
	fuel = fuelcor;
	x = 100 - fuelcor;
	sizex = (x * 640) / 100;
	posx = 640 - sizex;
	sizex *= cox;
	posx *= cox;
	fuelddel.setPosition(sf::Vector2f(posx, 32 * coy));
	fuelddel.setSize(sf::Vector2f(sizex, 30 * coy));
	score = scorecor;
	char buff[10];
	itoa(score, buff, 10);
	sf::String str = "Очки";
	str += buff;
	ScoreText.setString(str);
	rockets = corrockets;
	itoa(rockets, buff, 10);
	sf::String str2 = "Рокеты ";
	str2 += buff;
	RocketsCount.setString(str2);
}

void Hud::Draw(sf::RenderWindow &window)
{
	window.draw(BackHud);
	window.draw(lifer);
	window.draw(lifedel);
	window.draw(fuelr);
	window.draw(fuelddel);
	window.draw(ScoreText);
	window.draw(RocketsCount);
}