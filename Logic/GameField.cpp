#include "stdafx.h"
#include "GameField.h"

namespace Fields
{
	GameField::GameField(string BasePath, double cox, double coy, LoadAndSave::SaveSlot &CurrentSave, SoundControl::SoundControlStruct &SndControl) : CurrentSave(CurrentSave)
	{
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		this->SndControl = SndControl;
		Fpointers.LevelMenager = new LevelLogic::LevelMenager(BasePath, CurrentSave.NextLevel);
		Fpointers.UpgradeMenager = new LevelLogic::UpgradesMenager(BasePath);
		CurrentSave.NextLevel == 1 ? StartNewGame() : ContinueGame();
	}

	void GameField::StartNewGame()
	{

		Fpointers.CurrentLevel = new LevelLogic::Level(BasePath, cox, coy, SndControl, Fpointers.LevelMenager->ReturnCurrentLevelConfig(),CurrentSave);
		GameFieldState = Level;
	}

	void GameField::ContinueGame()
	{
		Fpointers.UpgradeScreen = new LevelLogic::UpgradeScreen(BasePath, cox, coy, SndControl, CurrentSave.Cash, &CurrentSave.PlayerUpInfo, Fpointers.UpgradeMenager->ReturnConfig()); 
		GameFieldState = UpgradeScreen;
	}

	void GameField::ProcessLevel(float time, RenderWindow &window)
	{
		try
		{
			Fpointers.CurrentLevel->Update(time, window);
		}
		catch (Exceptions::LevelEndEx &Ex)
		{
			SndControl.StopSound(Fpointers.LevelMenager->ReturnCurrentLevelConfig()->BackGroundSoundId);
			//window.setMouseCursorVisible(true);
			delete Fpointers.CurrentLevel;
			Fpointers.LevelMenager->NextLevel();
			if (Fpointers.LevelMenager->CheckIfLastLevel())
			{
				GameFieldState = Win; // ≈сли пройден последний уровень то показываем 
				return;
			}
			else GameFieldState = UpgradeScreen;
			CurrentSave.NextLevel++;
			Fpointers.UpgradeScreen = new LevelLogic::UpgradeScreen(BasePath, cox, coy, SndControl, CurrentSave.Cash,&CurrentSave.PlayerUpInfo,Fpointers.UpgradeMenager->ReturnConfig());
			Fpointers.UpgradeScreen->SetStats(CurrentSave.PStates);
			Fpointers.UpgradeScreen->SetStats(CurrentSave.PStates);
		}
		catch (Exceptions::LevelFailEx &Ex)
		{
			//window.setMouseCursorVisible(true);
			SndControl.StopSound(Fpointers.LevelMenager->ReturnCurrentLevelConfig()->BackGroundSoundId);
			delete Fpointers.CurrentLevel;
			if (Fpointers.LevelMenager->ReturnCurrentLevelConfig()->LevelNumber == 1)
			{
				Fpointers.CurrentLevel = new LevelLogic::Level(BasePath, cox, coy, SndControl, Fpointers.LevelMenager->ReturnCurrentLevelConfig(), CurrentSave);
				GameFieldState = Level;
			}
			else
			{
				GameFieldState = UpgradeScreen;
				Fpointers.UpgradeScreen = new LevelLogic::UpgradeScreen(BasePath, cox, coy, SndControl, CurrentSave.Cash, &CurrentSave.PlayerUpInfo, Fpointers.UpgradeMenager->ReturnConfig());
				Fpointers.UpgradeScreen->SetStats(CurrentSave.PStates);
			}
		
		}
		catch (Exceptions::GameWantToSwitchToMenu &Ex)
		{
			window.setMouseCursorVisible(false);
			SndControl.StopSound(Fpointers.LevelMenager->ReturnCurrentLevelConfig()->BackGroundSoundId);
			throw Exceptions::GameWantToSwitchToMenu("");
		}
	}

	void GameField::ProcessUpgradeScreen(float time, RenderWindow &window)
	{
		try
		{
			Fpointers.UpgradeScreen->Update(time, window);
		}
		catch (Exceptions::NextLevelRequested &Ex)
		{
			window.setMouseCursorVisible(false);
			// ¬озвращаем обновленные данные о корабле игрока
			CurrentSave.PStates = Fpointers.UpgradeScreen->GetUpgradedStats();
			CurrentSave.Cash = Fpointers.UpgradeScreen->CurrentCash;
			CurrentSave.PStates = Fpointers.UpgradeScreen->GetUpgradedStats();
			delete Fpointers.UpgradeScreen;
			Fpointers.CurrentLevel = new LevelLogic::Level(BasePath, cox, coy, SndControl, Fpointers.LevelMenager->ReturnCurrentLevelConfig(), CurrentSave);
			GameFieldState = Level;
			//LoadAndSave::SaveToFile(CurrentSave, BasePath, 1);
		}
	}

	void GameField::Upgrade(float time, RenderWindow &window)
	{
		switch (GameFieldState)
		{
		case Level:
			window.setMouseCursorVisible(false);
			ProcessLevel(time,window);
			break;
		case UpgradeScreen:
			try
			{
				ProcessUpgradeScreen(time, window);
			}
			catch (Exceptions::GameWantToSave &Ex)
			{
				CurrentSave.Cash = Fpointers.UpgradeScreen->CurrentCash;
				CurrentSave.PStates = Fpointers.UpgradeScreen->GetUpgradedStats();
				Menus::IdOfSounds SndMenuId;
				SndMenuId.ClickId = 0;
				SndMenuId.SelectId = 1;
				Fpointers.SaveMenu = new Menus::SaveGameMenu(BasePath, cox, coy, &CurrentSave, SndControl, SndMenuId);
				GameFieldState = SaveState;
			}
			break;
		case Win:
			break;
		case SaveState:
			try
			{
				Fpointers.SaveMenu->Update(window);
				if (Fpointers.SaveMenu->ReturnSelectedCode() == 4)
				{
					delete Fpointers.SaveMenu;
					GameFieldState = UpgradeScreen;
				}
			}
			catch (Exceptions::GameSaved &ex)
			{
				delete Fpointers.SaveMenu;
				GameFieldState = UpgradeScreen;
			}
			break;
		}
	}

	GameField::~GameField()
	{
		if (GameFieldState == UpgradeScreen)
		{
			delete Fpointers.UpgradeScreen;
		}
		if (GameFieldState == Level)
		{
			delete Fpointers.CurrentLevel;
		}
		if (GameFieldState == SaveState)
		{
			delete Fpointers.UpgradeScreen;
			delete Fpointers.SaveMenu;
		}
		delete Fpointers.UpgradeMenager;
		delete Fpointers.LevelMenager;
	}
}