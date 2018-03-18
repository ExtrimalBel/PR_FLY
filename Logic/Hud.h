#pragma once
#include <SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <sstream>
using namespace std;
using namespace sf;


namespace LevelLogic
{
	class GameHud
	{
		int Health;
		int Rockets;
		int Cash;
		string BasePath;
		double cox, coy;
		Font GameFont;
		Text RocketsText;
		Text LevelText;
		Image BackImage;
		Texture BackTex;
		Sprite BackSpr;
		Texture BackLifeTex;
		Sprite BackLifeSpr;
		Texture FrontLifeTex;
		Sprite FrontLifeSpr;
		Text HealthText;
		Text CashText;
		void Draw(RenderWindow &window);
		void UpdateHealthBar();
		void UpdateText();
	public:
		GameHud(string BasePath, double cox, double coy, string LevelName);
		void Update(RenderWindow &window);
		void SetParams(int Health,int Rockets,int Cash);

	};
}