#include "stdafx.h"
#include "Level.h"

namespace LevelLogic
{
	Level::Level(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, LevelLogic::LevelConfigStruct *CurrentLevelConfig, LoadAndSave::SaveSlot &CurrentSave) : CurrentSave(CurrentSave)
	{
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		this->SndControl = SndControl;
		this->CurrentLevelConfig = CurrentLevelConfig;
		// Создаем объект игрока
		pair<int, int>SndIds;
		SndIds.first = 6;
		SndIds.second = 6;
		PartOfLevel.PlayerClass = new Ships::Player(BasePath, cox, coy, SndControl, CurrentSave.PStates, SndIds,CurrentSave.Cash);
		PartOfLevel.PlayerClass->Health = 100;
		PartOfLevel.PlayerClass->Rockets = CurrentLevelConfig->StartRocketsCount;
	
		BackGroundTex.loadFromFile(BasePath + "/" + CurrentLevelConfig->BackGroundPath);
		BackGroundSpr.setTexture(BackGroundTex);
		BackGroundSpr.setScale(cox, coy);
		SndControl.Playsnd(CurrentLevelConfig->BackGroundSoundId,true);
		SplashTex.loadFromFile(BasePath + "/" + CurrentLevelConfig->SlpashPath);
		SplashBack.setTexture(SplashTex);
		SplashBack.setScale(cox, coy);
		SplashBack.setColor(sf::Color(64, 128,0));
		SplashClock.restart();
		LevelState = InSplashScreen;
		// Текст появляющийся на splashscreenах
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		SplashText.setFont(GameFont);
		SplashText.setColor(Color::Yellow);
		SplashText.setCharacterSize(48U);
		SplashText.setPosition(sf::Vector2f(20 * cox,20 * coy));
		SplashText.setString("Уровень " + CurrentLevelConfig->LevelName);
		SplashText.setScale(cox, coy);
		ButtomText.setFont(GameFont);
		ButtomText.setCharacterSize(48U);
		ButtomText.setString("Запуск уровня");
		ButtomText.setPosition(sf::Vector2f(20 * cox,950 * coy));
		ButtomText.setScale(cox, coy);
		//SetUpHud
		PartOfLevel.Hud = new LevelLogic::GameHud(BasePath, cox, coy, CurrentLevelConfig->LevelName);
		FailMessage.setFont(GameFont);
		FailMessage.setCharacterSize(48U);
		FailMessage.setFillColor(sf::Color::Yellow);
		FailMessage.setString("Вы уничтожены");
		FailMessage.setPosition(Vector2f(static_cast<float>(700 * cox), static_cast<float>(520 * coy)));
		
	}


	void Level::Update(float time, RenderWindow &window)
	{
		switch (LevelState)
		{
			
		case InSplashScreen:

			if (SplashClock.getElapsedTime().asSeconds() > 3)
			{
				LevelState = Game;
				SplashClock.restart();
				return;
			}
			window.draw(SplashBack);
			window.draw(SplashText);
			window.draw(ButtomText);
			break;
		case Game:
			
			window.draw(BackGroundSpr);
			
			UpdatePlayer(time, window);
			PartOfLevel.Hud->SetParams(PartOfLevel.PlayerClass->Health, PartOfLevel.PlayerClass->Rockets,PartOfLevel.PlayerClass->Cash);
			PartOfLevel.Hud->Update(window);
			if (SplashClock.getElapsedTime().asSeconds() < 2)
			{
				PartOfLevel.SetOfEnemy = new LevelLogic::SetOfEnemy(BasePath, cox, coy, CurrentLevelConfig->EnemySVector, SndControl);
				return;
			}
			InterSects::InterSectsMenager::CountDemageToEnemy(*PartOfLevel.PlayerClass, *PartOfLevel.SetOfEnemy);
			InterSects::InterSectsMenager::CountDemageToPlayer(*PartOfLevel.PlayerClass, *PartOfLevel.SetOfEnemy); // Вызываеться до обновления 
			UpdateSetOfEnemy(time, window);
			PartOfLevel.Hud->Update(window);
			if (PartOfLevel.SetOfEnemy->IFLevelEnd()) // Если уровень законнчен то переключиться на пока сообщения о завершении уровня
			{
				delete PartOfLevel.SetOfEnemy;
				LevelState = EndSplashScreen;
				CurrentSave.Cash = PartOfLevel.PlayerClass->Cash;
				SplashClock.restart(); // Далее этот таймер отвечает за время показа экрана конца уровня
			}
			if (PartOfLevel.PlayerClass->Health < 0) // Обрабатываем смерть игрока
			{
				LevelState = LoseGameSreen;
				PartOfLevel.PlayerClass->SetDeathAnim(true);
				SplashClock.restart(); // Аналогично с прошлым if-ом
				PartOfLevel.PlayerClass->SetDeathAnim(true);
			}
			if (Keyboard::isKeyPressed(Keyboard::Escape))
			{
				PartOfLevel.PMenu = new LevelLogic::PauseMenu(BasePath, cox, coy, window, SndControl);
				PartOfLevel.SetOfEnemy->PauseInClock();
				LevelState = LevelPause;
				break;
				//window.setMouseCursorVisible(true);
			}
			break;
		case EndSplashScreen:
			if (SplashClock.getElapsedTime().asSeconds() > 3)
			{
				delete PartOfLevel.Hud;
				throw Exceptions::LevelEndEx("Уровень" + CurrentLevelConfig->LevelName + " Завершен успешно",true);
			}
			window.draw(BackGroundSpr);
			PartOfLevel.Hud->Update(window);
			PartOfLevel.PlayerClass->Update(time, window);
			
			break;
		case LoseGameSreen:
			if (SplashClock.getElapsedTime().asSeconds() > 5)
			{
				delete PartOfLevel.Hud;
				delete PartOfLevel.PlayerClass;
				delete PartOfLevel.SetOfEnemy;
				throw Exceptions::LevelFailEx("Уровень " + CurrentLevelConfig->LevelName + " - Поражение");
			}
			window.draw(BackGroundSpr);
	
			PartOfLevel.PlayerClass->Update(time, window);
			PartOfLevel.SetOfEnemy->Update(time, window);
			PartOfLevel.Hud->Update(window);
			window.draw(FailMessage);

			break;
		case LevelPause:
			PartOfLevel.PMenu->Update(window);
			int ReturnCode = PartOfLevel.PMenu->ReturnSelectedCode();
			if (ReturnCode == 2)
			{
				cout << "GameWantToExit" << endl;
				throw Exceptions::GameWantToSwitchToMenu("Выход в главное меню");
			}
			if (ReturnCode == 1)
			{
				PartOfLevel.SetOfEnemy->ResumeInClock();
				delete PartOfLevel.PMenu;
				LevelState = Game;
			}
			break;
		}
		
	}

	void Level::UpdateSetOfEnemy(float time, RenderWindow &window)
	{
		PartOfLevel.SetOfEnemy->Update(time, window);
	}

	void Level::UpdatePlayer(float time, RenderWindow &window)
	{
		PartOfLevel.PlayerClass->Update(time, window);
	}

	void Level::UpdatePlayerBullets(float time, RenderWindow &window)
	{
		for each(Bullet var in PlayerBullets)
		{
			var.Move(time);
			var.Draw(window);
		}
	}
}