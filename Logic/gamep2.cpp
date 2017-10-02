#include "stdafx.h"
#include "Game.h"

void GameField::AddEnemyBullet()
{
	bool is_add = false;
	for (std::vector<Enemy_Ship>::iterator it = Enemys.begin(); it != Enemys.end(); it++)
	{
		if (En_Bul.getElapsedTime().asSeconds() > 3.5)
		{
			int tmpx = it->getx();
			int tmpy = it->gety();
			Enemy_Bullet tmp(2, tmpx, tmpy + 10,BulletTexture);
			tmp.Setx(tmpx);
			tmp.Sety(tmpy + 10);
			En_Bullets.push_back(tmp);
			is_add = true;

		}
	
	}
	if(is_add)En_Bul.restart();
}
void GameField::IfEnemyBulletOut()
{
	for (std::vector<Enemy_Bullet>::iterator it = En_Bullets.begin(); it != En_Bullets.end(); it++)
	{
		if (it->Getx() < 0)
		{
			En_Bullets.erase(it);
			IfEnemyBulletOut();
			return;
		}
	}
}

void GameField::IfShotInPlayer()
{
	for (std::vector<Enemy_Bullet>::iterator it = En_Bullets.begin(); it != En_Bullets.end(); it++)
	{
		int bulx = it->Getx();
		int buly = it->Gety();
		if (p1->InterSects(bulx, buly))
		{
			p1->DelHealth(10);
			En_Bullets.erase(it);
			IfShotInPlayer();
			return;
		}
	}
}



void GameField::UpdateEnBullets(sf::RenderWindow &window,float time)
{
	AddEnemyBullet();
	IfEnemyBulletOut();
	for (std::vector<Enemy_Bullet>::iterator it = En_Bullets.begin(); it != En_Bullets.end(); it++)
	{
		it->Update(window,time);
	}
}

void GameField::DrawDeath(sf::RenderWindow &window)
{

	window.clear();
	window.draw(UHudSpr);
	window.draw(Dead_Message);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	exit = 1;
}

void GameField::IfEnemyOut()
{
	for (std::vector<Enemy_Ship>::iterator it = Enemys.begin(); it != Enemys.end(); it++)
	{
		int tmpx = it->getx();
		if (tmpx < 0)
		{
			Enemys.erase(it);
			IfEnemyOut();
			sc -= 5;
			return;
		}
	}
}

void GameField::UpdateAll(float time, sf::RenderWindow &window)
{
	updatePlayer(time, window);
	UpdateBullets(time, window);
	UpdateEnBullets(window, time);
	UpdateEnemy(time, window);
	char bufstr[10];
	itoa(p1->GetHealth(), bufstr, 10);
	sf::String Str = sf::String(bufstr);
	Score.setString(Str);
	itoa(sc, bufstr, 10);
	char buf2[15] = "Очки ";
	sf::String HT = strcat(buf2, bufstr);
	HealthText.setString(HT);
	p2->Draw(window);
	window.draw(Score);
	window.draw(HealthText);
}

void GameField::UpdateBullets(float time,sf::RenderWindow &window)
{
	AddBullet();
	IFDELETEBULLET();
	for (std::vector<Bullet>::iterator it = Bullets.begin(); it != Bullets.end(); it++)
	{
		it->Move(time, window);
		it->Draw(window);
	}
	
}

void GameField::UpdateEnemy(float time, sf::RenderWindow &window)
{

	Addenemy();
	MoveEnemys(time);
	IfEnemyOut();
	IfEnemyKill();
	for (std::vector<Enemy_Ship>::iterator it = Enemys.begin(); it != Enemys.end(); it++)
	{
		it->Draw(window);
	}
}