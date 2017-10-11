#include <SFML/Graphics.hpp>
#include <Logic.h>
#include <Settings.h>
#include <GameField.h>
#include <GameMenu.h>
#include <fstream>
#include <windows.h>
#include <SoundSystem.h>
#include <loadgameclass.h>
#include <../Logic/stdafx.h>
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
		setlocale(LC_ALL, "Russian");
		Save();
		SoundSystem::SoundPlayer SPlayer;
		sf::Clock clock;
		int vidx;
		int vidy;

		SPlayer.SetVolume(0);
		sf::Uint32 st;
		LoadVideoMode(vidx, vidy, st);
		double cox = vidx;
		double coy = vidy;
		cox /= 1920;
		coy /= 1080;
		sf::RenderWindow window(sf::VideoMode(vidx, vidy), "SFML works!", st);
		window.setMouseCursorGrabbed(true);

		window.setFramerateLimit(60);
		MainM *Menu = new MainM(cox, coy, SPlayer);
		GameField *Field = NULL;
		GameSettings *Set = NULL;
		LoadM *LM = NULL;
		enum State { Game, Settings, MMenu, LoadGame }; // Перечесление отображающее состояние работы программы
		State Statements = MMenu; // Объект данного перечесления
		while (window.isOpen())
		{
			window.clear();
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time /= 800;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}
			switch (Statements) // В зависимости от состояния игры делаем нужные действия
			{
			case MMenu:
				window.setMouseCursorVisible(false);
				Menu->Update(time, window);
				if (Menu->MenuSelect() == 3)
				{
					window.setMouseCursorVisible(false);
					clock.restart();
					Statements = Game;
					Field = new GameField(cox, coy, 0, window,false,"");
					delete Menu;
				}
				if (Menu->MenuSelect() == 22)
				{
					SPlayer.~SoundPlayer();
					delete Menu;
					window.close();
				}
				if (Menu->MenuSelect() == 2)
				{
					delete Menu;
					LM = new LoadM(cox, coy, SPlayer);
					Statements = LoadGame;

				}
				break;
			case Game:
				Field->UpdateAll(time, window);
				if (Field->IfExit() == 1)
				{
					window.setMouseCursorVisible(true);
					Menu = new MainM(cox, coy, SPlayer);
					delete Field;
					Statements = MMenu;
				}

				break;
			case Settings:

				Set->update(time, window, clock);
				Set->DrawSettings(window);
				if (Set->IfExitSet(window) == 2)
				{
					Statements = MMenu;
					Menu = new MainM(cox, coy, SPlayer);
					delete Set;
				}
				break;
			case LoadGame:
				LM->Update(time, window);
				if (LM->MenuSelect() == 4)
				{
					delete LM;
					Menu = new MainM(cox, coy, SPlayer);
					Statements = MMenu;
				}
				break;
			}

			window.display();
		}
		ExitProcess(0);
		PostQuitMessage(0);
		return 0;
	}
	catch (char *str)
	{
		WriteLogFile(str);
		std::cout << str << std::endl;
	}
}


void LoadVideoMode(int &x,int &y,sf::Uint32 &st)
{
	if (_access("videomode.txt", 0) == -1)
	{
		x = 1280;
		y = 720; 
		return;
	}
	std::ifstream vidstream;
	vidstream.open("videomode.txt");
	int mode = 0;
	vidstream >> mode;
	if (mode == 2) st = sf::Style::Fullscreen;
	else  st = sf::Style::Default;
	vidstream >> x;
	vidstream >> y;
	vidstream.close();
}