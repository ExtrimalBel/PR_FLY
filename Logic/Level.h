#ifndef LEVEL_H
#define LEVEL_H
#include <SFML/Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
//#include "setofenemy.h"
//#include "SetOfBullets.h"
//#include "Player_Class.h"
#include "PlayerS.h"
#include "transitscreen.h"
#include "stdafx.h"
#include "Thingsh.h"
class Level
{
	SetOfBullets *SOB;
	SetOfEnemy *ENM;
	player_object *p1;
	double cox, coy;
	bool LevelEnd;
	bool Boss_fight;
	bool Boss_fight_screen; // Показывает рисовать ли "экран прихода босса"
	Level_Boss *Boss;
	Screens::BossComingScreen *bossscreen;
public:
	Level(const char *Enemyfile, double cox, double coy,bool Is_new,char *SaveFile);
	void UpdateLevel(float time, sf::RenderWindow &window);
	void UpdateBoss(float time, sf::RenderWindow &window);
	void RemoveDemageFromPlayer();
	double GetPlayerHealth();
	void CountDemageFromEnemy();
	void CountDemageBeetweenEnemsAndPlayer();
	void ResetClocks();
	bool ReturnLevelEnd() { return LevelEnd; }
};

#endif