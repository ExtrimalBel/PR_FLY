#pragma once
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include "MovingEnemy.h"
#include "StayEnemy.h"
#include "Bullet.h"
#include "ExceptionsDefenitions.hpp"
#include <SoundControl.h>
#include "RandomMovingEnemy.h"
#include "Chronometer.hpp"
#include "CircleMoveEnemy.h"
namespace InterSects
{
	class InterSectsMenager;
}
using namespace sf;
using namespace std;
using namespace sftools;
namespace LevelLogic
{
	
	
	typedef vector<pair<Ships::BaseEnemyState, int>>::iterator EnemyConfigIt;
	
	
	class SetOfEnemy
	{
		friend class InterSects::InterSectsMenager;
		string BasePath;
		double cox, coy;
		int EnemyTotalCount;
		int DeletedEnemy;
		vector<Ships::EnemyNode> Enemys; // Корабли на уровне
		vector<Bullet*> Bullets; // Выпущенные врагами пули
		vector<pair<Ships::BaseEnemyState, int>> EnemySVector; // Конфиги врагов
		SoundControl::SoundControlStruct &SndControl;
		EnemyConfigIt ConfigIt;
		void UpdateEnemys(float time, RenderWindow &window);
		void ProcessEnemysShots(); // Обрабатывает выстрелы врагов
		void SpawnNewEnemy();
		void DeleteEnemys();
		void DeleteBullets();
		void UpdateBullets(float time, RenderWindow &window);
		bool EndOfEnemys;
		Chronometer SetClock;
		
	public:
		void PauseInClock() { SetClock.pause(); cout << SetClock.getElapsedTime().asSeconds() << endl; }
		void ResumeInClock() { SetClock.resume(); cout << SetClock.getElapsedTime().asSeconds() << endl; }
		bool IFLevelEnd() { return (EnemyTotalCount == DeletedEnemy ? true : false); }
		SetOfEnemy(string BasePath, double cox, double coy, vector<pair<Ships::BaseEnemyState, int>> &EnemysConfigs,SoundControl::SoundControlStruct &SndControl);
		void Update(float time,RenderWindow &window);
	};
}