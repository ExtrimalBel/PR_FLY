#pragma once
#include <SFML\Graphics.hpp>
#include "ExceptionsDefenitions.hpp"
#include <iostream>
#include <SoundControl.h>
#include <string>
#include "Player.h"
#include "UpgradesMenager.h"
#include <sstream>
using namespace std;
using namespace sf;

namespace LevelLogic
{
	class UpgradeScreen
	{
		// Определение тестур и спрайтов
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		Texture ButtonTex; // Текстура одна для всех спрайтов. Нужная часть выбираеться через метод setTextureRect
		Texture UpButtonTex; // Текстура для кнопок апгредов
		Sprite Button;
		Sprite SaveButton;
		Sprite ArmorUpButton;
		Sprite FirstGunSpeedButton;
		Sprite FirstGunDemageButton;
		Sprite SecondGunSpeedButton;
		Sprite SecondGunDemageButton;
		Sprite ExitButtonSpr;
		Sprite NextLevelButtonSpr;
		double cox, coy;
		string BasePath;
		SoundControl::SoundControlStruct SndControl;
		void ProcessUpgrade(); // Обрабатываются 
		// Определение текста
		Font GameFont;
		Text CaptionText;
		// Следующие Text содержат кол-во апгредов установленных на компонент корабля
		Text FirstGunSpeedText;
		Text SecondGunSpeedText;
		Text FirstGunDemageText;
		Text SecondGunDemageText;
		Text ArmorText;
		Text ValuesOfUps[5];
		Text CashText;
		void InitialText(); // Вызываеться из конструктора и инициализирует текст
		void CheckIfSave(RenderWindow &window); // Проверяет запросил ли пользователь сохранение игры
		void CheckIfExit(RenderWindow &window); 
		void CheckIfNextLevel(RenderWindow &window);
		void UpdateTextStatesValue(); // Обновляет значения в текстовых объектах
		void InitialSprites(); // Вызывается из конструкктора и инициализиует спрайтыe
		void ProcessUpgrades(RenderWindow &window);
		void UpdateText();
		Ships::PlayerStats StatsForUpgrade; // Структура содержит данные об апгредах 
		LevelLogic::CurrentPlayerUpgrades *CurrentUpStates; // данные о том какие апгреды установлены
		LevelLogic::UpgradesConfig *Config; // Данные о том какие вообще есть апгрейды
		void Draw(RenderWindow &window);
		pair<double,int> ProcessUpDeFacto(vector<pair<int, double>> &vec, int Id);
		void CheckIfLastUpgradeInstalled();
		bool FinishiedUp[5];
		void UpdateCash();
	public:
		int CurrentCash; // Текущие "деньги"
		void SetStats(Ships::PlayerStats &StatsForUpgrade) { this->StatsForUpgrade = StatsForUpgrade; }
		Ships::PlayerStats GetUpgradedStats() { return this->StatsForUpgrade; }
		int GetCashRemain(); // Возвращает кол-во "денег" после апгрейда
		UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl,int CurrentCash,LevelLogic::CurrentPlayerUpgrades *CurrentUpStates,LevelLogic::UpgradesConfig *Config);
		void Update(float time, RenderWindow &window); //Обновляет игровое поле
		~UpgradeScreen();
	};
}