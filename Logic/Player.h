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
		int Width; // Ширина спрайта игрока
		int Height; // Высота спрайта игрока
		string ImgPath;
		string DeathAnim;
		double DAnimTime; // Время между сменами кадров анимации
		int DeathAnimFrameCount;
		int AnimFrameCount;
		double LevelCoo;
	};

	class Player
	{
		int CurrentFramesInAnim; // Общее колличество кадров в анимаии
		string PlayerPath;
		bool DeathAnim; // Определяет обрабатыват ли анимацию смерти
		friend class InterSects::InterSectsMenager;
		Clock FirstGunClock; 
		Clock SecondGunClock;
		Clock AnimClockTimer; // Нужен для корректного показа анимации
		int AnimFrame; // Текущий кадр анимации
	
		PlayerStats Stats;
		double cox, coy;
		Image PlayerImage;
		Texture PlayerTexture;
		Sprite PlayerSprite;
		SoundControl::SoundControlStruct SndControl;
		void ChangeAnim(); // На будующее для реализации анимации перемещения корабля
		void Draw(RenderWindow &window);
		void Move(RenderWindow &window);
		vector<Bullet*> PlayerBullets;
		bool IfFirstGunShot();
		bool IFSecondGunShot();
		Image& GetImage() { return PlayerImage; }
		Sprite& GetSprite() { return PlayerSprite; }
		PlayerStats ReturnPlayerStats();
		string BasePath;
		int FirstShotSoundId; // Идентификатор звука выстрела
		int SecondShotSoundId;
		// Методы для обработки пуль игрока
		void SpawnPlayerBullet();
		void DeletePlayerBullet();
		void UpdatePlayerBullet(float time,RenderWindow &window);
		void ProcessAnim(int MaxFrameCount); // Обработка анимацию
		void ReadPlayerParams();
	public:
		Clock TaranClock;
		void SetDeathAnim(bool value);
		int Rockets; // Это и следующие поля объявлены как public для более простого доступа
		int Health;
		int Cash;
		Player(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, PlayerStats &Stats, pair<int,int> SndIds,int Cash);
		void Update(float time, RenderWindow &window);
		
	};
}