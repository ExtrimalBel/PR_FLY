#include "stdafx.h"
#include "Game.h"

namespace MainGameClass
{
	Game::Game(string BasePath)
	{
		this->BasePath = BasePath;
		SndControl = SoundControl::InitSoundSystemStruct(BasePath, "sound.xml");
	}


	void Game::StartDemnedGame()
	{
		//SndControl.Mute();
		LoadVideoMode(st);
		Menus::IdOfSounds SndMenuId;
		SndMenuId.ClickId = 0;
		SndMenuId.SelectId = 1;
		GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl, SndMenuId);
		State = Menu;
		SndControl.Playsnd(2, true);
		MainLoop();
	}

	void Game::UpdateMainMenu(RenderWindow &window)
	{
		GamePointers.MMenu->Update(window);
		int ReturnMenuItem = GamePointers.MMenu->ReturnSelectedCode();
		Menus::IdOfSounds SndMenuId;
		SndMenuId.ClickId = 0;
		SndMenuId.SelectId = 1;
		switch (ReturnMenuItem)
		{
		case 4:
			SndControl.StopSound(2);
			throw Exceptions::GameWantToExit("Exit Game");
			break;
		case 2:
			delete GamePointers.MMenu;
			GamePointers.LoadM = new Menus::LoadGameMenu(BasePath, cox, coy, SndControl, SndMenuId);
			State = Load;
			break;
		case 1:
			delete GamePointers.MMenu;
			GamePointers.DifClass = new Menus::GameDifficulty(BasePath, cox, coy, SndControl, SndMenuId);
			State = SelectDifficulty;
			break;
		case 3:
			delete GamePointers.MMenu;
			GamePointers.Set = new Menus::SettingsClass(BasePath, cox, coy, SndControl);
			State = Settings;
		}
	}

	void Game::MainLoop()
	{
		sf::Clock clock;
		sf::RenderWindow window(sf::VideoMode(vidx, vidy), "PR_FLY", this->st);
		window.setFramerateLimit(60);
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
			switch (State)
			{
			case Menu:
				UpdateMainMenu(window);
				break;
			case Load:
				try
				{
					UpdateLoadMenu(window);
				}
				catch (Exceptions::GameWantToLoad &Ex)
				{
					SndControl.StopSound(2); // останавливаем фоновую музыку меню
					Ex.ShowMessage();
				}
				break;
			case SelectDifficulty:
				try
				{
					UpdateGameDifficultyClass(window);
				}
				catch (Exceptions::GameWantToStartNew &Ex)
				{
					SndControl.StopSound(2); // останавливаем фоновую музыку меню
					Ex.ShowMessage();
				}
				break;
			case Settings:
				GamePointers.Set->Update(window);
				break;
			default:
				break;
			}
			

			window.display();
		}
	}
	void Game::LoadVideoMode(sf::Uint32 &st)
	{
		double x = 0, y = 0;
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
		this->cox = x / 1920;
		this->coy = y / 1080;
		this->vidx = x;
		this->vidy = y;
	}

	void Game::UpdateLoadMenu(RenderWindow &window)
	{

		GamePointers.LoadM->Update(window);
		int ReturnMenuItem = GamePointers.LoadM->ReturnSelectedCode();
		Menus::IdOfSounds SndMenuId;
		SndMenuId.ClickId = 0;
		SndMenuId.SelectId = 1;
		switch (ReturnMenuItem)
		{
		case 1:
		case 2:
		case 3:
		
			throw Exceptions::GameWantToLoad(ReturnMenuItem);
			break;
		case 4:
			delete GamePointers.LoadM;
			GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl, SndMenuId);
			State = Menu;
		}
	}

	void Game::UpdateGameDifficultyClass(RenderWindow &window)
	{
		Menus::IdOfSounds SndMenuId;
		SndMenuId.ClickId = 0;
		SndMenuId.SelectId = 1;
		GamePointers.DifClass->Update(window);
		int ReturnMenuItem = GamePointers.DifClass->ReturnSelectedCode();
		switch (ReturnMenuItem)
		{
		case 1:
		case 2:
		case 3:
			throw Exceptions::GameWantToStartNew(ReturnMenuItem);
			break;
		case 4:
			delete GamePointers.DifClass;
			GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl, SndMenuId);
			State = Menu;
			break;
		}
	}
}