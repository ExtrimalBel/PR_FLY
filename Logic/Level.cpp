#include "stdafx.h"
#include "Level.h"
#include "Intersectsmenager.h"




Level::Level(const char *Enemyfile, double cox, double coy, bool Is_new, char *SaveFile)
{
	LevelEnd = false;
	Boss_fight = false;
	Boss_fight_screen = false;
	this->cox = cox;
	this->coy = coy;
	ENM = new SetOfEnemy(Enemyfile, this->cox, this->coy);
	SOB = new SetOfBullets(cox, coy);
	p1 = new PlayerO(200, 200, cox, coy, Is_new);
	Boss = new Level_Boss("./data/vanilla/boss.txt", cox, coy);
}

void Level::UpdateLevel(float time, sf::RenderWindow &window)
{
	p1->Update(window, time);
	ENM->Update(time, window);
	if (p1->ifShot())
	{
		int y;
		sf::Vector2f tmp = p1->GetBulletPosition(y);
		tmp.y += y / 4;
	}
	if (Boss_fight_screen)
	{

		if (bossscreen->IfExit())
		{
			delete bossscreen;
			Boss_fight = true;
			Boss_fight_screen = false;
		}
		else
		{
			bossscreen->Update(window);
			return;
		}
	}
	else if (Boss_fight)
	{
		UpdateBoss(time, window);
		CountDemageBetweenPlayerAndBoss(*Boss, *p1);

	}
	else
	{
		ENM->Update(time, window);
		

		//AddEnemyBullets(*ENM, *SOB);
		CountDemageBeetwinPlayerAndEnemys(*p1, *ENM);
	}

	//RemoveDemageFromPlayer();

	if (ENM->ReturnEnemyLeftCount() <= 0 && !Boss_fight)
	{
		bossscreen = new Screens::BossComingScreen(cox, coy, 3);
		Boss_fight_screen = true;
	}
	if (Boss_fight_screen)
	{
	}
}

double Level::GetPlayerHealth()
{
	double h = p1->GetHealth();
	return h;
}

void Level::ResetClocks()
{
	ENM->ResetClock();
}


void Level::UpdateBoss(float time, sf::RenderWindow &window)
{
	Boss->Update(time, window);
	if (Boss->IsForDelete() == true) LevelEnd = true;
}


Level::~Level()
{
	if (p1 != NULL)
	{
		delete p1;
	}
	if (ENM != NULL)
	{
		delete ENM;
	}
	if (SOB != NULL)
	{
		delete SOB;
	}
	if (Boss != NULL)
	{
		delete Boss;
	}
}