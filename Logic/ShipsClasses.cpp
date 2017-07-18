#include "stdafx.h"
#include "ShipsClasses.h"
#include <SFML/Graphics.hpp>
#define LOGIC_API __declspec(dllexport)

Player::Player() : Ship("./img/ships/player.png", 100, 100)
{
	speed = 0;
	if (level == 1) life = 3;
	if (level == 2) life = 2;
	if (level == 3) life = 1;
}