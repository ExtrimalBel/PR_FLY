#include "stdafx.h"
#include "Thingsh.h"

void RemoveDemageFromPlayers(player_object &Player, SetOfBullets &SetOFB, SetOfEnemy &ENM)
{
	std::vector<Bullet>::iterator it = SetOFB.SOB.begin();
	for (; it != SetOFB.SOB.end(); it++)
	{
		if (InterSects::IfSpritesInterSects(Player.GetSprite(), Player.GetImage(), it->GetSprite(), it->GetImage()))
		{
			//Player.RemoveHealth(it->GetDemage());
			Player - it->GetDemage();
			it->SetDelete(true);
		}
	}
	std::vector<Enemy>::iterator EnemyIt;// Сдесь объявляю итераторы на пули и врагов
	std::vector<Bullet>::iterator BulletIt;
	for (EnemyIt = ENM.SOE.begin(); EnemyIt != ENM.SOE.end(); EnemyIt++) // Проверяю каждого врага и пулю на пересечение и если оно произошло то отнимаю у врага жизни и устанавливаю пулю на удаление
	for (BulletIt = SetOFB.PSOB.begin(); BulletIt != SetOFB.PSOB.end(); BulletIt++)
	{
		if (InterSects::IfSpritesInterSects(EnemyIt->GetSprite(), EnemyIt->GetImage(), BulletIt->GetSprite(), BulletIt->GetImage()))
		{
			EnemyIt->RemoveHealth(BulletIt->GetDemage());
			BulletIt->SetDelete(true);
		}
	}
	SetOFB.DeleteBullets();
}

void AddEnemyBullets(SetOfEnemy &SOE, SetOfBullets &SOB)
{
	for (std::vector<Enemy>::iterator it = SOE.SOE.begin(); it != SOE.SOE.end(); it++)
	{
		if (it->IsShot())
		{
			it->ResetClock();
			SOB.AddBullet(it->GetPostion(), SOE.cox, SOE.coy, 2, 0.1, it->GetDemage());
		}
	}
}


void CountDemageBetweenPlayerAndBoss(SetOfBullets &SetOfB, Level_Boss &BOSS, player_object &P1) // Проверяет попадание пль игрока в босса и наоброт и если попадание есть отнимает здоровь
{
	std::vector<Bullet>::iterator it = SetOfB.PSOB.begin();
	for (; it != SetOfB.PSOB.end(); it++) // В этом цикле проверяем все пули выпущенные игроком на попадание в босса и если оно случилось то отнимаем у босса хп
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
			P1 - it->GetDemage();
		}
	}
	for (it = BOSS.SetofSBullet.begin(); it != BOSS.SetofSBullet.end(); it++)
	{
		if (InterSects::IfSpritesInterSects(it->GetSprite(), it->GetImage(), P1.GetSprite(), P1.GetImage()))
		{
			it->SetDelete(true);
			P1 - it->GetDemage();
		}
	}
	BOSS.DeleteBullets();
	SetOfB.DeleteBullets();
}