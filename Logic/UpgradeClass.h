#pragma once
#include <SFML\Graphics.hpp>
#include "ExceptionsDefenitions.hpp"
#include <iostream>
#include <SoundControl.h>
#include <string>
#include "Player.h"
using namespace std;
using namespace sf;

namespace LevelLogic
{
	class UpgradeScreen
	{
		// Определение тестур и спрайтов
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		Texture ButtonTex;
		Texture UpgradeButtonTex;
		Sprite Button;
		Sprite UpgradeButton;
		double cox, coy;
		string BasePath;
		SoundControl::SoundControlStruct SndControl;
		void ProcessUpgrade(); // Обрабатываются 
		// Определение текста
		Font GameFont;
		Text CaptionText;
		Text ArmorText;
		Text ArmorValue;
		Text FirstGunSpeedText;
		Text FirstGunSpeedValue;
		Text SecondGunSpeedText;
		Text SecondGunSpeedValue;
		void InitialText(); // Вызываеться из конструктора и инициализирует текст
		void CheckIfSave();
		void CheckIfExit();
		void UpdateTextStatesValue(); // Обновляет значения в текстовых объектах
		void InitialSprites(); // Вызывается из конструкктора и инициализиует спрайтыe
		Ships::PlayerStats StatsForUpgrade; // Структура содержит данные об апгредах 
		
		int CurrentCash; // Текущие "деньги"
	public:
		void SetStats(Ships::PlayerStats StatsForUpgrade);
		Ships::PlayerStats GetUpgradedStats();
		int GetCashRemain(); // Возвращает кол-во "денег" после апгрейда
		UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl,int CurrentCash);
		void Update(float time, RenderWindow &window); //Обновляет игровое поле
	};
}