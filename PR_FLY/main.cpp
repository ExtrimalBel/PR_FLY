#include <SFML/Graphics.hpp>
#include <Logic.h>

#include <GameField.h>
#include <GameMenu.h>
#include <fstream>
#include <windows.h>
#include <SoundSystem.h>
#include <loadgameclass.h>
#include <../Logic/stdafx.h>
#include "Game.h"
//#include "SoundSystem.h"
#include <io.h>
//int level = 0;
void LoadVideoMode(int &x, int &y,sf::Uint32 &st);
sf::Event ev;
// Only for debug
void Save()
{
	std::ofstream out;
	out.open("save.txt");
	PStatements State;
	State.energy = 1;
	State.energyco = 1.1;
	State.engine = 1;
	State.fuel = 100;
	State.fuelco = 0.9;
	State.gun = 5;
	State.gunspeed = 0.1;
	State.health = 100;
	State.life = 1;
	out.write((char*)&State, sizeof(PStatements));

	out.close();
}

int main()
{
	try
	{
		Game G;
		G.Update();

	}
	catch (Exceptions::AbnormalException &Ex)
	{
		std::cout << Ex.Message;
		ExitProcess(-1);
	}
	ExitProcess(0);
	return 0;
}

