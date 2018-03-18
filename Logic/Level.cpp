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
		// ������� ������ ������
		pair<int, int>SndIds;
		SndIds.first = 6;
		SndIds.second = 6;
		PartOfLevel.PlayerClass = new Ships::Player(BasePath, cox, coy, SndControl, CurrentSave.PStates, SndIds,CurrentSave.Cash);
		PartOfLevel.PlayerClass->Health = 100;
		PartOfLevel.PlayerClass->Rockets = CurrentLevelConfig->StartRocketsCount;
	
		BackGroundTex.loadFromFile(BasePath + "/" + CurrentLevelConfig->BackGroundPath);
		BackGroundTex.setSmooth(true);
		BackGroundSpr.setTexture(BackGroundTex);	
		BackGroundSpr.setScale(cox, coy);
		BackGroundSpr.setPosition(0, 0);
		SndControl.Playsnd(CurrentLevelConfig->BackGroundSoundId,true);
		SplashTex.loadFromFile(BasePath + "/" + CurrentLevelConfig->SlpashPath);
		SplashBack.setTexture(SplashTex);
		SplashBack.setScale(cox, coy);
		SplashBack.setColor(sf::Color(64, 128,0));
		SplashClock.restart();
		LevelState = InSplashScreen;
		// ����� ������������ �� splashscreen��
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		SplashText.setFont(GameFont);
		SplashText.setColor(Color::Yellow);
		SplashText.setCharacterSize(48U);
		SplashText.setPosition(sf::Vector2f(20 * cox,20 * coy));
		SplashText.setString("������� " + CurrentLevelConfig->LevelName);
		SplashText.setScale(cox, coy);
		ButtomText.setFont(GameFont);
		ButtomText.setCharacterSize(48U);
		ButtomText.setString("������ ������");
		ButtomText.setPosition(sf::Vector2f(20 * cox,950 * coy));
		ButtomText.setScale(cox, coy);
		//SetUpHud
		PartOfLevel.Hud = new LevelLogic::GameHud(BasePath, cox, coy, CurrentLevelConfig->LevelName);
		EndLevelMessage.setFont(GameFont);
		EndLevelMessage.setCharacterSize(48U);
		EndLevelMessage.setFillColor(sf::Color::Yellow);

		EndLevelMessage.setPosition(Vector2f(static_cast<float>(700 * cox), static_cast<float>(520 * coy)));
		
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
			InterSects::InterSectsMenager::CountDemageToPlayer(*PartOfLevel.PlayerClass, *PartOfLevel.SetOfEnemy); // ����������� �� ���������� 
			UpdateSetOfEnemy(time, window);
			PartOfLevel.Hud->Update(window);
			if (PartOfLevel.SetOfEnemy->IFLevelEnd()) // ���� ������� ��������� �� ������������� �� ���� ��������� � ���������� ������
			{
				EndLevelMessage.setString("������� �������");
				SndControl.StopSound(CurrentLevelConfig->BackGroundSoundId);
				SndControl.Playsnd(9, false);
				delete PartOfLevel.SetOfEnemy;
				LevelState = EndSplashScreen;
				CurrentSave.Cash = PartOfLevel.PlayerClass->Cash;
				SplashClock.restart(); // ����� ���� ������ �������� �� ����� ������ ������ ����� ������
			}
			if (PartOfLevel.PlayerClass->Health < 0) // ������������ ������ ������
			{
				EndLevelMessage.setString("�� ����������");
				SndControl.StopSound(CurrentLevelConfig->BackGroundSoundId);
				SndControl.Playsnd(8, false);
				LevelState = LoseGameSreen;
				PartOfLevel.PlayerClass->SetDeathAnim(true);
				SplashClock.restart(); // ���������� � ������� if-��
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
			if (SplashClock.getElapsedTime().asSeconds() > 8)
			{
				delete PartOfLevel.Hud;
				throw Exceptions::LevelEndEx("�������" + CurrentLevelConfig->LevelName + " �������� �������",true);
			}
			window.draw(BackGroundSpr);
			PartOfLevel.Hud->Update(window);
			PartOfLevel.PlayerClass->Update(time, window);
			window.draw(EndLevelMessage);
			
			break;
		case LoseGameSreen:
			if (SplashClock.getElapsedTime().asSeconds() > 5)
			{
				delete PartOfLevel.Hud;
				delete PartOfLevel.PlayerClass;
				delete PartOfLevel.SetOfEnemy;
				throw Exceptions::LevelFailEx("������� " + CurrentLevelConfig->LevelName + " - ���������");
			}
			window.draw(BackGroundSpr);
	
			PartOfLevel.PlayerClass->Update(time, window);
			PartOfLevel.SetOfEnemy->Update(time, window);
			PartOfLevel.Hud->Update(window);
			window.draw(EndLevelMessage);

			break;
		case LevelPause:
			PartOfLevel.PMenu->Update(window);
			int ReturnCode = PartOfLevel.PMenu->ReturnSelectedCode();
			if (ReturnCode == 2)
			{
				cout << "GameWantToExit" << endl;
				throw Exceptions::GameWantToSwitchToMenu("����� � ������� ����");
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