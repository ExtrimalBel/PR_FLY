#ifndef GAMEF_H
#define GAMEF_H

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "Background_Class.h"

#include "Hud.h"
#include <vector>
#include "LevelMenager.h"
#include "phfsint.hpp"
class LOGIC_API GameField
{
	// Player object

	PStatements StateP;
	// BackGround
	Back_Menu *BackM;

	Hud *HD;
	double xscale;
	double yscale;
	double fuel;
	std::vector<sf::Vector2f> coordsxy;
	LevelMenager *Men;
	PhysControl Control;
	PhysFsStream FileStream;
	sf::Music Back_Theme;
public:
	GameField(double xsc, double ysc,int slot,sf::RenderWindow &window,bool Is_new,char *SaveFile);
	void UpdateAll(float time, sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	int IfExit();
	~GameField();

};


#endif