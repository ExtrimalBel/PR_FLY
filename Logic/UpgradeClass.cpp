#include "stdafx.h"
#include "UpgradeClass.h"
namespace LevelLogic
{
	UpgradeScreen::UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, int CurrentCash, LevelLogic::CurrentPlayerUpgrades *CurrentUpStates, LevelLogic::UpgradesConfig *Config)
	{
		cout << "Cash For Upgrade" << CurrentCash << endl;
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		this->SndControl = SndControl;
		this->CurrentCash = CurrentCash;
		this->CurrentUpStates = CurrentUpStates;
		this->Config = Config;
		InitialSprites();
		InitialText();
		CheckIfLastUpgradeInstalled();
		SndControl.Playsnd(Config->BackId,true);
		
	}
	UpgradeScreen::~UpgradeScreen()
	{
		SndControl.StopSound(Config->BackId);
	}

	void UpgradeScreen::InitialSprites()
	{
		// Loading textures
		BackGroundTex.loadFromFile(BasePath + "/UpgradeMenu/background.png");
		ButtonTex.loadFromFile(BasePath + "/UpgradeMenu/button.png");
		ButtonTex.setSmooth(true);
		UpButtonTex.loadFromFile(BasePath + "/UpgradeMenu/upbutton.png");
		// SetUp sprites
		BackGroundSpr.setTexture(BackGroundTex);
		BackGroundSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		//Button.setTexture(ButtonTex);
		//Button.setScale(static_cast<float>(cox), static_cast<float>(coy));
		SaveButton.setTexture(ButtonTex);
		SaveButton.setScale(static_cast<float>(cox), static_cast<float>(coy));
		ArmorUpButton.setTexture(UpButtonTex);
		ArmorUpButton.setScale(static_cast<float>(cox), static_cast<float>(coy));
		FirstGunSpeedButton.setTexture(UpButtonTex);
		FirstGunSpeedButton.setScale(cox, coy);
		SecondGunSpeedButton.setTexture(UpButtonTex);
		SecondGunSpeedButton.setScale(cox, coy);
		FirstGunDemageButton.setTexture(UpButtonTex);
		FirstGunDemageButton.setScale(cox, coy);
		SecondGunDemageButton.setTexture(UpButtonTex);
		SecondGunDemageButton.setScale(cox, coy);
		ArmorUpButton.setPosition(sf::Vector2f(250 * cox, 250 * coy));
		FirstGunSpeedButton.setPosition(sf::Vector2f(250 * cox, 350 * coy));
		FirstGunDemageButton.setPosition(sf::Vector2f(250 * cox, 450 * coy));
		SecondGunSpeedButton.setPosition(sf::Vector2f(250 * cox, 550 * coy));
		SecondGunDemageButton.setPosition(sf::Vector2f(250 * cox, 650 * coy));
		//SetUp NextLevelButton
		NextLevelButtonSpr.setTexture(ButtonTex);
		NextLevelButtonSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		NextLevelButtonSpr.setTextureRect(sf::IntRect(0, 0, 300, 50));
		NextLevelButtonSpr.setPosition(sf::Vector2f(static_cast<float>(cox * 1520), static_cast<float>(coy * 980)));
		// SetUpExitButton
		ExitButtonSpr.setTexture(ButtonTex);
		ExitButtonSpr.setScale(static_cast<float>(cox),static_cast<float>(coy));
		ExitButtonSpr.setTextureRect(IntRect(300, 0, 300, 50));
		ExitButtonSpr.setPosition(sf::Vector2f(static_cast<float>(80 * cox),static_cast<float>(980 * coy)));
		// SetUp Save Button
		SaveButton.setTexture(ButtonTex);
		SaveButton.setScale(static_cast<float>(cox), static_cast<float>(coy));
		SaveButton.setTextureRect(IntRect(600, 0, 300, 50));
		SaveButton.setPosition(Vector2f(static_cast<float>(810 * cox), static_cast<float>(980 * coy)));

	}

	void UpgradeScreen::Draw(RenderWindow &window)
	{
		window.draw(BackGroundSpr);
		window.draw(ArmorUpButton);
		window.draw(ArmorText);
		window.draw(FirstGunSpeedButton);
		window.draw(FirstGunSpeedText);
		window.draw(FirstGunDemageButton);
		window.draw(FirstGunDemageText);
		window.draw(SecondGunDemageButton);
		window.draw(SecondGunDemageText);
		window.draw(SecondGunSpeedButton);
		window.draw(SecondGunSpeedText);
		window.draw(CaptionText);
		window.draw(ExitButtonSpr);
		window.draw(SaveButton);
		window.draw(CashText);
		for (int i = 0; i < 5; i++)
		{
			window.draw(ValuesOfUps[i]);
		}
		window.draw(NextLevelButtonSpr);
	}

	void UpgradeScreen::InitialText()
	{
		// load game font and assign it for all text objtcts
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		CaptionText.setFont(GameFont);
		CaptionText.setString("Окно улутшений");
		CaptionText.setPosition(Vector2f(600 * cox,50 * coy));
		FirstGunSpeedText.setFont(GameFont);
		FirstGunSpeedText.setString("Скорость основного орудия");
		SecondGunSpeedText.setFont(GameFont);
		SecondGunSpeedText.setString("Скорость вторичного орудия");
		FirstGunDemageText.setFont(GameFont);
		FirstGunDemageText.setString("Урон основного орудия");
		SecondGunDemageText.setFont(GameFont);
		SecondGunDemageText.setString("Урон вторичного орудия");
		ArmorText.setFont(GameFont);
		ArmorText.setString("Броня");
		FirstGunSpeedText.setScale(cox, coy);
		FirstGunDemageText.setScale(cox, coy);
		SecondGunDemageText.setScale(cox, coy);
		SecondGunSpeedText.setScale(cox, coy);
		ArmorText.setScale(cox, coy);
		ArmorText.setPosition(sf::Vector2f(600 * cox, 250 * coy));
		FirstGunSpeedText.setPosition(sf::Vector2f(600 * cox, 350 * coy));
		FirstGunDemageText.setPosition(sf::Vector2f(600 * cox, 450 * coy));
		SecondGunSpeedText.setPosition(sf::Vector2f(600 * cox, 550 * coy));
		SecondGunDemageText.setPosition(sf::Vector2f(600 * cox, 650 * coy));
		ArmorText.setFillColor(Color(255, 102, 0));
		FirstGunSpeedText.setFillColor(Color(255, 102, 0));
		FirstGunDemageText.setFillColor(Color(255,102,0));
		SecondGunSpeedText.setFillColor(Color(255, 102, 0));
		SecondGunDemageText.setFillColor(Color(255,102,0));
		int TempY = 255;
		for (int i = 0; i < 5; i++,TempY+= 100)
		{
			ValuesOfUps[i].setFont(GameFont);
			ValuesOfUps[i].setPosition(sf::Vector2f(350 * cox,TempY * coy));
			ValuesOfUps[i].setScale(cox, coy);
			ValuesOfUps[i].setFillColor(Color(51,51,255));
		}
		CashText.setFillColor(Color::Yellow);
		CashText.setFont(GameFont);
		stringstream ss;
		ss << "Деньги " << CurrentCash;
		CashText.setString(ss.str());
		CashText.setCharacterSize(52U);
		CashText.setScale(cox, coy);
		CashText.setPosition(300 * cox, 800 * coy);
		//TODO set coordinates for text objects
	}

	void UpgradeScreen::UpdateCash()
	{
		stringstream ss;
		ss << "Деньги " << CurrentCash;
		CashText.setString(ss.str());
	}

	void UpgradeScreen::UpdateText()
	{
		string TempString = "";
		stringstream ss;
		if(!FinishiedUp[0])ss << "Цена " <<  Config->ArmorUpgrades[CurrentUpStates->Armorid + 1].second;
		else
		{
			ValuesOfUps[0].setPosition(sf::Vector2f(340 * cox, 255 * coy));
			ss << "Улутшено";
		}
		TempString = ss.str();
		ValuesOfUps[0].setString(TempString);
		ss.str(string());
		if (!FinishiedUp[1]) ss << "Цена " << Config->FirstGunSpeedUpgrades[CurrentUpStates->FirstGunSpeedId + 1].second;
		else
		{
			ValuesOfUps[1].setPosition(sf::Vector2f(340 * cox, 355 * coy));
			ss << "Улутшено";
		}
		TempString = ss.str();
		ValuesOfUps[1].setString(TempString);
		ss.str(string());
		if (!FinishiedUp[2]) ss << "Цена " << Config->FirstGunDemageUpgrades[CurrentUpStates->FirstGunDemageId + 1].second;
		else
		{
			ValuesOfUps[2].setPosition(sf::Vector2f(340 * cox, 455 * coy));
			ss << "Улутшено";
		}
		TempString = ss.str();
		ValuesOfUps[2].setString(TempString);
		ss.str(string());
		if (!FinishiedUp[3]) ss << "Цена " << Config->SecondGunSpeedUpgrades[CurrentUpStates->SecondGunSpeedId + 1].second;
		else
		{
			ValuesOfUps[3].setPosition(sf::Vector2f(340 * cox, 555 * coy));
			ss << "Улутшено";
		}
		TempString = ss.str();
		ValuesOfUps[3].setString(TempString);
		ss.str(string());
		if (!FinishiedUp[4]) ss << "Цена " << Config->SecondGunDemageUpgrades[CurrentUpStates->SecondGunDemageId + 1].second;
		else
		{
			ValuesOfUps[4].setPosition(sf::Vector2f(340 * cox, 655 * coy));
			ss << "Улутшено";
		}
		TempString = ss.str();
		ValuesOfUps[4].setString(TempString);
		ss.str(string());
	}

	void UpgradeScreen::Update(float time, RenderWindow &window)
	{
		CheckIfLastUpgradeInstalled();
		UpdateText();
		CheckIfExit(window);
		CheckIfSave(window);
		CheckIfNextLevel(window);
		UpdateCash();
		ProcessUpgrades(window);
		Draw(window);
		
	}


	void UpgradeScreen::CheckIfLastUpgradeInstalled()
	{
		if (CurrentUpStates->Armorid + 1 >= Config->ArmorUpgrades.size()) FinishiedUp[0] = true; else FinishiedUp[0] = false;
		if (CurrentUpStates->FirstGunDemageId + 1 >= Config->FirstGunDemageUpgrades.size()) FinishiedUp[2] = true; else FinishiedUp[2] = false;
		if (CurrentUpStates->FirstGunSpeedId + 1 >= Config->FirstGunSpeedUpgrades.size()) FinishiedUp[1] = true; else FinishiedUp[1] = false;
		if (CurrentUpStates->SecondGunSpeedId + 1 >= Config->SecondGunSpeedUpgrades.size()) FinishiedUp[3] = true; else FinishiedUp[3] = false;
		if (CurrentUpStates->SecondGunDemageId + 1 >= Config->SecondGunDemageUpgrades.size()) FinishiedUp[4] = true; else FinishiedUp[4] = false;
	}
	void UpgradeScreen::ProcessUpgrades(RenderWindow &window)
	{
		Vector2f Mpos(Mouse::getPosition(window));
		FloatRect ArmorButtonRect(ArmorUpButton.getGlobalBounds());
		FloatRect FirstGunSpeedRect(FirstGunSpeedButton.getGlobalBounds());
		FloatRect FirstGunDemageRect(FirstGunDemageButton.getGlobalBounds());
		FloatRect SecondGunSpeedRect(SecondGunSpeedButton.getGlobalBounds());
		FloatRect SecondGunDemageRect(SecondGunDemageButton.getGlobalBounds());
		if (ArmorButtonRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left) )
		{
			int NextUpId = CurrentUpStates->Armorid;
			if (FinishiedUp[0])
			{
				SndControl.Playsnd(Config->BadUpId, false);
				cout << "Armor Not Up" << endl;
				Sleep(200);
				return;
			}
			pair<double,int> NextUpData = Config->ArmorUpgrades[NextUpId + 1];
			if (CurrentCash < NextUpData.second)
			{
				cout << "Armor Not Up" << endl;
				SndControl.Playsnd(Config->BadUpId, false);
			}
			else
			{
				cout << "Armor Up" << endl;
				CurrentUpStates->Armorid++;
				StatsForUpgrade.Armor = NextUpData.first;
				SndControl.Playsnd(Config->UpId++,false);
				CurrentCash -= NextUpData.second;
			}
			Sleep(200);
		}
		if (FirstGunSpeedRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left) && !FinishiedUp[1])
		{
			int NextUpId = CurrentUpStates->FirstGunSpeedId;
			if (FinishiedUp[1])
			{
				SndControl.Playsnd(Config->BadUpId, false);
				Sleep(200);
				return;
			}
			pair<double, int> NextUpData = Config->FirstGunSpeedUpgrades[NextUpId + 1];
			if (CurrentCash < NextUpData.second)
			{
				
				SndControl.Playsnd(Config->BadUpId, false);
			}
			else
			{
				CurrentCash -= NextUpData.second;
				CurrentUpStates->FirstGunSpeedId++;
				StatsForUpgrade.FirstGunSpeed = NextUpData.first;
				SndControl.Playsnd(Config->UpId, false);
			}
			Sleep(200);
		}
		if (FirstGunDemageRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left) && !FinishiedUp[2])
		{
			int NextUpId = CurrentUpStates->FirstGunDemageId;
			if (FinishiedUp[2])
			{
				SndControl.Playsnd(Config->BadUpId, false);
				Sleep(200);
				return;
			}
			pair<double, int> NextUpData = Config->FirstGunDemageUpgrades[NextUpId + 1];
			if (CurrentCash < NextUpData.second) SndControl.Playsnd(Config->BadUpId, false);
			else
			{
				CurrentCash -= NextUpData.second;
				CurrentUpStates->FirstGunDemageId++;
				StatsForUpgrade.FirstGunDemage = NextUpData.first;
				SndControl.Playsnd(Config->UpId, false);
			}
			Sleep(200);
		}
		if (SecondGunSpeedRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left) && !FinishiedUp[3])
		{
			int NextUpId = CurrentUpStates->SecondGunSpeedId;
			if (FinishiedUp[3])
			{
				SndControl.Playsnd(Config->BadUpId, false);
				Sleep(200);
				return;
			}
			pair<double, int> NextUpData = Config->SecondGunSpeedUpgrades[NextUpId + 1];
			if (CurrentCash < NextUpData.second) SndControl.Playsnd(Config->BadUpId, false);
			else
			{
				CurrentCash -= NextUpData.second;
				CurrentUpStates->SecondGunSpeedId++;
				StatsForUpgrade.SecondGunSpeed = NextUpData.first;
				SndControl.Playsnd(Config->UpId, false);
			}
			Sleep(200);
		}
		if (SecondGunDemageRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left) && !FinishiedUp[4]) 
		{
			int NextUpId = CurrentUpStates->SecondGunDemageId;
			if (FinishiedUp[4])
			{
				SndControl.Playsnd(Config->BadUpId, false);
				Sleep(200);
				return;
			}
			pair<double, int> NextUpData = Config->SecondGunDemageUpgrades[NextUpId + 1];
			if (CurrentCash < NextUpData.second) SndControl.Playsnd(Config->BadUpId, false);
			else
			{
				CurrentCash -= NextUpData.second;
				CurrentUpStates->SecondGunDemageId++;
				StatsForUpgrade.SecondGunDemage = NextUpData.first;
				SndControl.Playsnd(Config->UpId, false);
			}
			Sleep(200);
		}
	}

	void UpgradeScreen::CheckIfExit(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		sf::FloatRect ExitButtonRect = ExitButtonSpr.getGlobalBounds();
		if (ExitButtonRect.contains(Mpos))
		{
			ExitButtonSpr.setTextureRect(IntRect(300, 50, 300, 50));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.setMouseCursorVisible(false);
				SndControl.Playsnd(Config->ClickId, false);
				throw Exceptions::GameWantToSwitchToMenu("Выход в главное меню");
			}
		}
		else
		{
			ExitButtonSpr.setTextureRect(IntRect(300,0,300,50));
		}
	}

	void UpgradeScreen::CheckIfSave(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		sf::FloatRect SaveButtonRect = SaveButton.getGlobalBounds();
		if (SaveButtonRect.contains(Mpos))
		{
			SaveButton.setTextureRect(IntRect(600, 50, 300, 50));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				SndControl.Playsnd(Config->ClickId, false);
				throw Exceptions::GameWantToSave("Игра запросила сохранение");
			}
		}
		else
		{
			SaveButton.setTextureRect(IntRect(600, 0, 300, 50));
		}
	}

	void UpgradeScreen::CheckIfNextLevel(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		sf::FloatRect NextLevelButtonRect = NextLevelButtonSpr.getGlobalBounds();
		if (NextLevelButtonRect.contains(Mpos))
		{
			NextLevelButtonSpr.setTextureRect(IntRect(0, 50, 300, 50));
			if(Mouse::isButtonPressed(Mouse::Left))
			{
				SndControl.Playsnd(Config->ClickId, false);
				throw Exceptions::NextLevelRequested("Переход на следующий уровень");
			}
		}
		else
		{
			NextLevelButtonSpr.setTextureRect(IntRect(0, 0, 300, 50));
		}
	}
}