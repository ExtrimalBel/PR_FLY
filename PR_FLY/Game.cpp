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
		LoadGameSettings(st);
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
			//SndControl.StopSound(2);
			SoundControl::DeleteSoundSystem(); // перед выбросом исключения удаляем звуковую подсистему
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
			State = GameState::Settings;
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
			Menus::IdOfSounds SndMenuId;
			SndMenuId.ClickId = 0;
			SndMenuId.SelectId = 1;
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
			case GameState::Settings:
				try
				{
					GamePointers.Set->Update(window);
				}
				catch (Exceptions::SettingsClose *Ex)
				{
					SaveGameSettings(Ex);
					delete Ex;
					delete GamePointers.Set;
					GamePointers.MMenu = new Menus::MainMenu(BasePath,cox,coy,SndControl,SndMenuId);
					State = Menu;
				}
				break;
			default:
				break;
			}
			

			window.display();
		}
	}
	void Game::LoadGameSettings(sf::Uint32 &st)
	{
		// Формат 
		double x = 0, y = 0;
		if (_access((BasePath + "/settings.txt").c_str(), 0) == -1)
		{
			x = 1280;
			y = 720;
			return;
		}
		std::ifstream vidstream;
		vidstream.open(BasePath + "/settings.txt");
		int mode = 0;
		vidstream >> mode;
		if (mode == 2)
		{
			st = sf::Style::Fullscreen;
			this->Settings.Fullscreen = true;
		}
		else
		{
			st = sf::Style::Default;
			this->Settings.Fullscreen = false;
		}
		vidstream >> x;
		vidstream >> y;
		vidstream >> this->Settings.Volume;
		vidstream >> this->Settings.MuteState;
		vidstream.close();
		this->cox = x / 1920;
		this->coy = y / 1080;
		this->vidx = x;
		this->vidy = y;
		this->Settings.Resolution.first = x;
		this->Settings.Resolution.second = y;
		this->Settings.MuteState ? SndControl.Mute() : SndControl.UnMute();
	}

	void Game::SaveGameSettings(Exceptions::SettingsClose *Ex)
	{
		this->Settings.Fullscreen = Ex->Fullsreen;
		this->Settings.MuteState = Ex->Mute;
		this->Settings.Volume = Ex->Volume;
		this->Settings.Resolution = Ex->Resolution;
		ofstream outfile;
		outfile.open(BasePath + "/settings.txt", std::ostream::out | std::ostream::trunc);
		this->Settings.Fullscreen ? outfile << 2 : outfile << 1;
		outfile << " ";
		outfile << this->Settings.Resolution.first;
		outfile << " ";
		outfile << this->Settings.Resolution.second;
		outfile << " ";
		outfile << this->Settings.Volume;
		outfile << " ";
		outfile << this->Settings.MuteState;
		outfile.close();
		this->cox = (double)Ex->Resolution.first / 1920;
		this->coy = (double)Ex->Resolution.second / 1080;
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
			GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl,SndMenuId);
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