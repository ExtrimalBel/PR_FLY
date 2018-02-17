#pragma once 
#include <SFML\Graphics.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <SoundControl.h>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif

using namespace std;
using namespace sf;
namespace Ships
{

	struct PlayerStats
	{
		int Armor;
		double FirstGunSpeed;
		double SecondGunSpeed;
		int FirstGunDemage;
		int SecondGunDemage;
	};
	class Player
	{
		Clock FirstGunClock;
		Clock SecondGunClock;
		PlayerStats Stats;
		double cox, coy;
		Image PlayerImage;
		Texture PlayerTexture;
		Sprite PlayerSprite;
		SoundControl::SoundControlStruct SndControl;
		void ChangeAnim(); // �� �������� ��� ���������� �������� ����������� �������
		void Draw(RenderWindow &window);
		void Move(RenderWindow &window);
		Image* GetImage() { return &PlayerImage; }
		Sprite* GetSprite() { return &PlayerSprite; }
		bool IfFirstGunShot();
		bool IFSecondGunShot();
		PlayerStats ReturnPlayerStats();
		string BasePath;
		int FirstShotSoundId; // ������������� ����� ��������
		int SecondShotSoundId;
	public:
		int Rockets; // ��� � ��������� ���� ��������� ��� public ��� ����� �������� �������
		int Health;
		Player(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, PlayerStats &Stats, pair<int,int> SndIds);
		void Update(float time, RenderWindow &window);
	};
}