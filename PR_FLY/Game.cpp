#include "stdafx.h"
#include "Game.h"

namespace MainGameClass
{
	Game::Game(string BasePath)
	{
		this->BasePath = BasePath;
		SndControl = SoundControl::InitSoundSystemStruct(BasePath, "/sound/sound.xml");
		CursorTex.loadFromFile(BasePath + "/Images/cur.png");
		CursorSpr.setTexture(CursorTex);

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
		//Settings Up MenuCursor;
		CursorSpr.setScale(cox, coy);
		CursorSpr.setOrigin(CursorSpr.getLocalBounds().width, 0);
		MainLoop(); // Вход в главный цикл

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
			throw Exceptions::GameWantToExit("Exit Game");
			break;
		case 2:
			delete GamePointers.MMenu;
			GamePointers.MMenu = NULL;
			GamePointers.LoadM = new Menus::LoadGameMenu(BasePath, cox, coy, SndControl, SndMenuId);
			State = Load;
			break;
		case 1:
			delete GamePointers.MMenu;
			GamePointers.MMenu = NULL;
			GamePointers.DifClass = new Menus::GameDifficulty(BasePath, cox, coy, SndControl, SndMenuId);
			State = SelectDifficulty;
			break;
		case 3:
			delete GamePointers.MMenu;
			GamePointers.Set = new Menus::SettingsClass(BasePath, cox, coy, SndControl,this->Settings.Volume,this->Settings.Fullscreen);
			State = GameState::Settings;
		}
	}

	void Game::UpdateMenuCursor(RenderWindow &window)
	{
		Vector2f Mpos(Mouse::getPosition(window));
		CursorSpr.setPosition(Mpos);
		window.draw(CursorSpr);
	}

	void Game::MainLoop()
	{
		sf::Clock clock;
		sf::RenderWindow window(sf::VideoMode(vidx, vidy), "PR_FLY", this->st);
		window.setFramerateLimit(60);
		window.setMouseCursorVisible(false);
		while (window.isOpen())
		{
			window.clear();
			// time задает время между каждой итерацией цикла. На эту величину корректируются все величины
			float time = clock.getElapsedTime().asMicroseconds();
			clock.restart();
			time /= 800;
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
				{
					window.close();
					throw Exceptions::GameWantToExit("Выход из игр");
				}
			}
			window.setMouseCursorGrabbed(true);
			Menus::IdOfSounds SndMenuId;
			SndMenuId.ClickId = 0;
			SndMenuId.SelectId = 1;
			switch (State)
			{
			case GameS:
				try
				{
					GamePointers.Gf->Upgrade(time, window);
				}
				catch (Exceptions::GameWantToSwitchToMenu &Ex) // Обрабатывем выход в главное меню из игры
				{
					delete GamePointers.Gf;
					GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl, SndMenuId);
					SndControl.Playsnd(2, true);
					State = Menu;
				}
				break;
			case Menu:
				UpdateMainMenu(window);
				UpdateMenuCursor(window);
				break;
			case Load:
				try
				{
					UpdateLoadMenu(window);
				}
				catch (Exceptions::GameWantToLoad &Ex)
				{
					try
					{
						LoadAndSave::SaveSlot *tmpslot = &LoadAndSave::LoadFromFile(BasePath, Ex.slot);
						GamePointers.Gf = new Fields::GameField(BasePath, cox, coy, *tmpslot, SndControl);
						SndControl.StopSound(2); // останавливаем фоновую музыку меню
						Ex.ShowMessage();
						State = GameS;
					}
					catch (Exceptions::GameLoadError &Ex)
					{
						SndControl.Playsnd(8, false);
					}
					
				}
				UpdateMenuCursor(window);
				break;
			case SelectDifficulty:
				try
				{
					UpdateGameDifficultyClass(window);
				}
				catch (Exceptions::GameWantToStartNew &Ex)
				{
					delete GamePointers.DifClass;
					GamePointers.DifClass = NULL;
					LoadAndSave::SaveSlot *SS = new LoadAndSave::SaveSlot();
					SS->Cash = 10;
					SS->PStates.LevelCoo = Ex.diflevel;
					SS->LevelCoefficient = Ex.diflevel;
					SS->NextLevel = 1;
					SS->PStates.Armor = 60;
					SS->PStates.FirstGunDemage = 5;
					SS->PStates.FirstGunSpeed = 0.5;
					SS->PStates.SecondGunDemage = 10;
					SS->PStates.SecondGunSpeed = 1;
					/*LevelLogic::CurrentPlayerUpgrades *up = LevelLogic::UpgradesMenager::MakeClearPlayerUpgrades();
					SS->PlayerUpInfo.Armorid = up->Armorid;
					SS->PlayerUpInfo.FirstGunDemageId = up->FirstGunDemageId;
					SS->PlayerUpInfo.FirstGunSpeedId = up->FirstGunSpeedId;
					SS->PlayerUpInfo.SecondGunDemageId = up->SecondGunDemageId;
					SS->PlayerUpInfo.SecondGunSpeedId = up->SecondGunSpeedId;*/
					SS->PlayerUpInfo.Armorid = 0;
					SS->PlayerUpInfo.FirstGunDemageId = 0;
					SS->PlayerUpInfo.SecondGunSpeedId = 0;
					SS->PlayerUpInfo.FirstGunSpeedId = 0;
					SS->PlayerUpInfo.SecondGunDemageId = 0;
					SS->Cash = 0;
					GamePointers.Gf = new Fields::GameField(BasePath, cox, coy, *SS, SndControl);
					SndControl.StopSound(2); // останавливаем фоновую музыку меню
					Ex.ShowMessage();
					State = GameS;
				}
				UpdateMenuCursor(window);
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
					GamePointers.Set = 0; // Зануляю указатель что-бы в деструкторе можно было проверить существование объекта сравнением с 0
					GamePointers.MMenu = new Menus::MainMenu(BasePath,cox,coy,SndControl,SndMenuId);
					State = Menu;
				}
				UpdateMenuCursor(window);
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
			x = 1024;
			y = 768;
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
		SndControl.SetVolume(this->Settings.Volume);
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
			GamePointers.LoadM = 0;
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
			GamePointers.DifClass = 0;
			GamePointers.MMenu = new Menus::MainMenu(BasePath, cox, coy, SndControl, SndMenuId);
			State = Menu;
			break;
		}
	}

	Game::~Game()
	{
		SoundControl::DeleteSoundSystem();
		if (GamePointers.DifClass != 0) delete GamePointers.DifClass;
		if (GamePointers.LoadM != 0) delete  GamePointers.LoadM;
		if (GamePointers.MMenu != 0) delete GamePointers.MMenu;
		if (GamePointers.Set != 0) delete GamePointers.Set;
	}
}