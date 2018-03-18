#include "stdafx.h"
#include "Hud.h"

namespace LevelLogic
{
	GameHud::GameHud(string BasePath, double cox, double coy, string LevelName)
	{
		this->cox = cox;
		this->coy = coy;
		this->BasePath = BasePath;
		// SetUpText
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		LevelText.setFont(GameFont);
		LevelText.setCharacterSize(32U);
		LevelText.setScale(cox, coy);
		LevelText.setPosition(sf::Vector2f(1600 * cox, 0 * coy));
		LevelText.setString("Уровень" + LevelName);
		RocketsText.setFont(GameFont);
		RocketsText.setCharacterSize(32U);
		RocketsText.setScale(cox, coy);
		RocketsText.setPosition(sf::Vector2f(1300 * cox, 0 * coy));
		RocketsText.setString("Рокеты");
		RocketsText.setColor(Color::Red);
		LevelText.setColor(Color::Red);
		BackImage.loadFromFile(BasePath + "\\Images\\BackImages\\BackHud.png");
		BackImage.createMaskFromColor(Color::White);
		BackTex.loadFromImage(BackImage);
		BackTex.setSmooth(true);
		BackSpr.setTexture(BackTex);
		BackSpr.setScale(cox, coy);
		BackLifeTex.loadFromFile(BasePath + "/Images/Hud/backlife.png");
		FrontLifeTex.loadFromFile(BasePath + "/Images/Hud/frontlife.png");
		BackLifeSpr.setTexture(BackLifeTex);
		FrontLifeSpr.setTexture(FrontLifeTex);
		BackLifeSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		FrontLifeSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		BackLifeSpr.setPosition(sf::Vector2f(10 * cox,10 * coy));
		FrontLifeSpr.setPosition(sf::Vector2f(10 * cox, 10 * coy));
		HealthText.setFont(GameFont);
		HealthText.setString("Здоровье");
		HealthText.setScale(static_cast<float>(cox), static_cast<float>(coy));
		HealthText.setPosition(sf::Vector2f(420 * cox, 15 * coy));
		HealthText.setFillColor(Color::Red);
		CashText.setFont(GameFont);
		CashText.setString("Деньги");
		CashText.setScale(static_cast<float>(cox), static_cast<float>(coy));
		CashText.setFillColor(Color::Red);
		CashText.setPosition(Vector2f(1000 * cox, 0 * coy));
		CashText.setCharacterSize(32U);
	}

	void GameHud::Draw(RenderWindow &window)
	{
		window.draw(BackSpr);
		window.draw(RocketsText);
		window.draw(LevelText);
		window.draw(BackLifeSpr);
		window.draw(FrontLifeSpr);
		window.draw(HealthText);
		window.draw(CashText);
	}

	void GameHud::Update(RenderWindow &window)
	{
		Draw(window);
		UpdateText();
		UpdateHealthBar();
	}

	void GameHud::UpdateText()
	{
		stringstream ss;
		ss << "Ракеты "<< Rockets;
		RocketsText.setString(ss.str());
		ss.str(string());
		ss << "Деньги " << Cash;
		CashText.setString(ss.str());

	}

	void GameHud::SetParams(int Health, int Rockets,int Cash)
	{
		this->Cash = Cash;
		this->Health = Health;
		this->Rockets = Rockets;
	}

	void GameHud::UpdateHealthBar()
	{
		int posx = Health * 400 / 100;
		//FrontLifeSpr.setPosition(sf::Vector2f(posx, 0));
		FrontLifeSpr.setTextureRect(sf::IntRect(0,0,posx, 50));
		//cout << posx << endl;
	}
}
