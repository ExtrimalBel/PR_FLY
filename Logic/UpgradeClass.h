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
		// ����������� ������ � ��������
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		Texture ButtonTex; // �������� ���� ��� ���� ��������. ������ ����� ����������� ����� ����� setTextureRect
		Texture UpButtonTex; // �������� ��� ������ ��������
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
		void ProcessUpgrade(); // �������������� 
		// ����������� ������
		Font GameFont;
		Text CaptionText;
		// ��������� Text �������� ���-�� �������� ������������� �� ��������� �������
		Text FirstGunSpeedText;
		Text SecondGunSpeedText;
		Text FirstGunDemageText;
		Text SecondGunDemageText;
		Text ArmorText;
		Text ValuesOfUps[5];
		Text CashText;
		void InitialText(); // ����������� �� ������������ � �������������� �����
		void CheckIfSave(RenderWindow &window); // ��������� �������� �� ������������ ���������� ����
		void CheckIfExit(RenderWindow &window); 
		void CheckIfNextLevel(RenderWindow &window);
		void UpdateTextStatesValue(); // ��������� �������� � ��������� ��������
		void InitialSprites(); // ���������� �� ������������� � ������������� �������e
		void ProcessUpgrades(RenderWindow &window);
		void UpdateText();
		Ships::PlayerStats StatsForUpgrade; // ��������� �������� ������ �� �������� 
		LevelLogic::CurrentPlayerUpgrades *CurrentUpStates; // ������ � ��� ����� ������� �����������
		LevelLogic::UpgradesConfig *Config; // ������ � ��� ����� ������ ���� ��������
		void Draw(RenderWindow &window);
		pair<double,int> ProcessUpDeFacto(vector<pair<int, double>> &vec, int Id);
		void CheckIfLastUpgradeInstalled();
		bool FinishiedUp[5];
		void UpdateCash();
	public:
		int CurrentCash; // ������� "������"
		void SetStats(Ships::PlayerStats &StatsForUpgrade) { this->StatsForUpgrade = StatsForUpgrade; }
		Ships::PlayerStats GetUpgradedStats() { return this->StatsForUpgrade; }
		int GetCashRemain(); // ���������� ���-�� "�����" ����� ��������
		UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl,int CurrentCash,LevelLogic::CurrentPlayerUpgrades *CurrentUpStates,LevelLogic::UpgradesConfig *Config);
		void Update(float time, RenderWindow &window); //��������� ������� ����
		~UpgradeScreen();
	};
}