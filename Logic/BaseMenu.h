#ifndef BASEMENU_I
#define BASEMENU_I
#include <SFML/Graphics.hpp>
#include <SoundSystem.h>
#include "Background_Class.h"
#include <iostream>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API BaseMenu
{
protected:
	//Base Mode Path
	std::string BasePath;
	//SoundPayerPointer
	SoundSystem::SoundPlayer *SPlayer;
	// Menu logo
	sf::Texture menulogotex;
	sf::RectangleShape menulogo;
	// Logo
	sf::Image logoimg;
	sf::Texture logotex;
	sf::RectangleShape logo;
	// Фон
	Back_Menu *BMenu;
	// Фон для кнопок
	sf::Texture ButtonBack;
	// Кнопка новая игра
	sf::RectangleShape firstitem;
	// Кнопка загрузить игру
	sf::RectangleShape seconditem;
	// Кнопка настроек
	sf::RectangleShape thirditem;
	// Кнопка выход
	sf::RectangleShape fourthitem;
	// переменная для выбора пункта меню
	sf::Event ev; // Событие для закрытия окна
	int menuitem = 0;
	double cox, coy;
	// Текст для кнопок
	sf::Font textfont;
	sf::Text firstitemtext;
	sf::Text seconditemtext;
	sf::Text thirditemtext;
	sf::Text fouritemtext;
	// Курсор мыши
	sf::Texture mousecurtex;
	sf::Sprite mousecursorspr;
	void SetUpText();


	int MenuNum = 0;
	BaseMenu(double cox, double coy, SoundSystem::SoundPlayer &SPlayer,std::string BaseGamePath);
	virtual void Update(float time, sf::RenderWindow &window);
	virtual void Draw(sf::RenderWindow &window);
	virtual void IfMenuItemSelected(sf::RenderWindow &window);
};


#endif