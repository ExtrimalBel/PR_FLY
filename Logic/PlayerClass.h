#pragma once
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;
using namespace sf;

namespace Player
{
	struct PlayerStatement
	{
		int Rockets;
		int Money;
		int Armor;
		int FirstGunDemage;
		int SecondGunDemage;
		int FirstGunSpeed;
		int SecondGunSpeed;
	};
}