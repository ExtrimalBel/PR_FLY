#pragma once 
#include <SFML\Graphics.hpp>
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <SoundControl.h>
#include "Bullet.h"
#include "tinyxml2.h"
#include "ExceptionsDefenitions.hpp"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif

using namespace std;
using namespace sf;
namespace InterSects
{
	class InterSectsMenager;
}
namespace Ships
{
	struct PlayerStats
	{
		int Armor;
		double FirstGunSpeed;
		double SecondGunSpeed;
		int FirstGunDemage;
		int SecondGunDemage;
		int FrameCount;
		int Width; // ������ ������� ������
		int Height; // ������ ������� ������
		string ImgPath;
		string DeathAnim;
		double DAnimTime; // ����� ����� ������� ������ ��������
		int DeathAnimFrameCount;
		int AnimFrameCount;
		double LevelCoo;
	};

	class Player
	{
		int CurrentFramesInAnim; // ����� ����������� ������ � �������
		string PlayerPath;
		bool DeathAnim; // ���������� ����������� �� �������� ������
		friend class InterSects::InterSectsMenager;
		Clock FirstGunClock; 
		Clock SecondGunClock;
		Clock AnimClockTimer; // ����� ��� ����������� ������ ��������
		int AnimFrame; // ������� ���� ��������
	
		PlayerStats Stats;
		double cox, coy;
		Image PlayerImage;
		Texture PlayerTexture;
		Sprite PlayerSprite;
		SoundControl::SoundControlStruct SndControl;
		void ChangeAnim(); // �� �������� ��� ���������� �������� ����������� �������
		void Draw(RenderWindow &window);
		void Move(RenderWindow &window);
		vector<Bullet*> PlayerBullets;
		bool IfFirstGunShot();
		bool IFSecondGunShot();
		Image& GetImage() { return PlayerImage; }
		Sprite& GetSprite() { return PlayerSprite; }
		PlayerStats ReturnPlayerStats();
		string BasePath;
		int FirstShotSoundId; // ������������� ����� ��������
		int SecondShotSoundId;
		// ������ ��� ��������� ���� ������
		void SpawnPlayerBullet();
		void DeletePlayerBullet();
		void UpdatePlayerBullet(float time,RenderWindow &window);
		void ProcessAnim(int MaxFrameCount); // ��������� ��������
		void ReadPlayerParams();
	public:
		Clock TaranClock;
		void SetDeathAnim(bool value);
		int Rockets; // ��� � ��������� ���� ��������� ��� public ��� ����� �������� �������
		int Health;
		int Cash;
		Player(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, PlayerStats &Stats, pair<int,int> SndIds,int Cash);
		void Update(float time, RenderWindow &window);
		
	};
}