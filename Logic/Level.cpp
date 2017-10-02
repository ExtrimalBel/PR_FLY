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
	p1 = new player_object(200, 200, cox, coy, Is_new);
	Boss = new Level_Boss("./data/vanilla/boss.txt", cox, coy);
}

void Level::UpdateLevel(float time, sf::RenderWindow &window)
{
	p1->Move(window);
	p1->Draw(window);
	if (p1->ifShot())
	{
		int y;
		sf::Vector2f tmp = p1->GetBulletPosition(y);
		tmp.y += y / 4;

		SOB->AddPlayerBullet(tmp, cox, coy, 1, p1->GetGunSpeed(), p1->GetDemage());
		//tmp.y += y / 4;
		//SOB->AddPlayerBullet(tmp, cox, coy, 1, p1->GetGunSpeed(), p1->GetDemage());
	}
	SOB->Update(time, window);
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
		CountDemageBetweenPlayerAndBoss(*SOB, *Boss, *p1);

	}
	else
	{
		ENM->Update(time, window);
		

		AddEnemyBullets(*ENM, *SOB);
	
		RemoveDemageFromPlayers(*p1, *SOB, *ENM);
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


void Level::RemoveDemageFromPlayer()
{
	/*sf::IntRect playerrect = p1->ReturnRect();
	if (Boss_fight)
	{
		double demage = 0;
		sf::Sprite playerspr = p1->GetSprite();
		sf::Image playerimg = p1->GetImage();
		//Boss->CountDemageToPlayer(playerspr,playerimg,demage);
		p1->RemoveHealth(demage);
//		sf::IntRect Boss_rect = Boss->GetRect();
		demage = 0;
		SOB->RemoveDemageFromBoss(demage, Boss->GetSprite(), Boss->GetImage());
		Boss->RemoveHealth(demage);
	}
	/*else
	{
	
		double demage = 0;
		SOB->CountDemageToPlayer(demage, playerrect);
		p1->RemoveHealth(demage);
	}*/
	
}

double Level::GetPlayerHealth()
{
	double h = p1->GetHealth();
	return h;
}


void Level::CountDemageFromEnemy()
{
	//SOB->RemoveDemageFromEnemy(p1->GetDemage(),ENM);
}

void Level::ResetClocks()
{
	ENM->ResetClock();
}


void Level::UpdateBoss(float time, sf::RenderWindow &window)
{
	
	RemoveDemageFromPlayer();
	Boss->Update(time, window);
	if (Boss->IsForDelete() == true) LevelEnd = true;
}


void Level::CountDemageBeetweenEnemsAndPlayer()
{
}