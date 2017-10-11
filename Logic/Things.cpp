#include "stdafx.h"
#include "Thingsh.h"


void CountDemageBetweenPlayerAndBoss(Level_Boss &BOSS, PlayerO &P1) // Проверяет попадание пль игрока в босса и наоброт и если попадание есть отнимает здоровь
{
	std::vector<Bullet>::iterator it = P1.SetOfPlayerBullets.begin();
	for (; it != P1.SetOfPlayerBullets.end(); it++) // В этом цикле проверяем все пули выпущенные игроком на попадание в босса и если оно случилось то отнимаем у босса хп
	{
		if (InterSects::IfSpritesInterSects(it->GetSprite(), it->GetImage(), BOSS.GetSprite(), BOSS.GetImage()))
		{
			it->SetDelete(true);
			BOSS.RemoveHealth(it->GetDemage());
		}
	}
	if (BOSS.health <= 0) BOSS.for_delete = true; // Если после попадания здоровье босса меньше или равно 0 то пометить босса на удаление
	for (it = BOSS.SetofFBullet.begin(); it != BOSS.SetofFBullet.end(); it++)
	{
		if (InterSects::IfSpritesInterSects(it->GetSprite(), it->GetImage(), P1.GetSprite(), P1.GetImage()))
		{
			it->SetDelete(true);
			P1.RemoveHealth(it->GetDemage());
		}
	}
	for (it = BOSS.SetofSBullet.begin(); it != BOSS.SetofSBullet.end(); it++)
	{
		if (InterSects::IfSpritesInterSects(it->GetSprite(), it->GetImage(), P1.GetSprite(), P1.GetImage()))
		{
			it->SetDelete(true);
			P1.RemoveHealth(it->GetDemage());
		}
	}
	P1.RemovePBullets();
	BOSS.DeleteBullets();
}		  

void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys)
{
	std::vector<Bullet>::iterator EnemyBUlit; // Указывает на вражескую пулю
	// Просматриваем вражеские пули на пересечение с игроком и если пересечение обнаружено то пулю помечаем на удаление и отнимаем здоровье у игрока
	for (EnemyBUlit = SetOFEnemys.SetOFMovingEnemysBullets.begin(); EnemyBUlit != SetOFEnemys.SetOFMovingEnemysBullets.end(); EnemyBUlit++)
	{
		if (InterSects::IfSpritesInterSects(EnemyBUlit->GetSprite(), EnemyBUlit->GetImage(), Player.GetSprite(), Player.GetImage()))
		{
			Player - EnemyBUlit->GetDemage();
			EnemyBUlit->SetDelete(true);
		}
	}
	std::vector<Bullet>::iterator PBulletIt; // Указывает на пулю врага
	std::vector<Enemys::MovingEnemy>::iterator En; // Указывает на врага
	for (PBulletIt = Player.SetOfPlayerBullets.begin(); PBulletIt != Player.SetOfPlayerBullets.end(); PBulletIt++)
	{
		for (En = SetOFEnemys.SetOfMovingEnemys.begin(); En != SetOFEnemys.SetOfMovingEnemys.end(); En++)
		{
			if (InterSects::IfSpritesInterSects(PBulletIt->GetSprite(), PBulletIt->GetImage(), En->GetSprite(),En->GetImage()))
			{
				En->RemoveHealth(PBulletIt->GetDemage());
				PBulletIt->SetDelete(true);
			}
		}
	}
}