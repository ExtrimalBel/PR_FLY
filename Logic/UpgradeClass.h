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
		// ����������� ������ � ��������
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		Texture ButtonTex;
		Texture UpgradeButtonTex;
		Sprite Button;
		Sprite UpgradeButton;
		double cox, coy;
		string BasePath;
		SoundControl::SoundControlStruct SndControl;
		void ProcessUpgrade(); // �������������� 
		// ����������� ������
		Font GameFont;
		Text CaptionText;
		Text ArmorText;
		Text ArmorValue;
		Text FirstGunSpeedText;
		Text FirstGunSpeedValue;
		Text SecondGunSpeedText;
		Text SecondGunSpeedValue;
		void InitialText(); // ����������� �� ������������ � �������������� �����
		void CheckIfSave();
		void CheckIfExit();
		void UpdateTextStatesValue(); // ��������� �������� � ��������� ��������
		void InitialSprites(); // ���������� �� ������������� � ������������� �������e
		Ships::PlayerStats StatsForUpgrade; // ��������� �������� ������ �� �������� 
		
		int CurrentCash; // ������� "������"
	public:
		void SetStats(Ships::PlayerStats StatsForUpgrade);
		Ships::PlayerStats GetUpgradedStats();
		int GetCashRemain(); // ���������� ���-�� "�����" ����� ��������
		UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl,int CurrentCash);
		void Update(float time, RenderWindow &window); //��������� ������� ����
	};
}