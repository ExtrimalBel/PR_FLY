#include "stdafx.h"
#include "Thingsh.h"
/*
void RemoveDemageFromPlayers(PlayerO &Player, SetOfBullets &SetOFB, SetOfEnemy &ENM)
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
	std::vector<Enemy>::iterator EnemyIt;// ����� �������� ��������� �� ���� � ������
	std::vector<Bullet>::iterator BulletIt;
	for (EnemyIt = ENM.SetOfMovingEnemys.begin(); EnemyIt != ENM.SetOfMovingEnemys.end(); EnemyIt++) // �������� ������� ����� � ���� �� ����������� � ���� ��� ��������� �� ������� � ����� ����� � ������������ ���� �� ��������
	for (BulletIt = SetOFB.PSOB.begin(); BulletIt != SetOFB.PSOB.end(); BulletIt++)
	{
		if (InterSects::IfSpritesInterSects(EnemyIt->GetSprite(), EnemyIt->GetImage(), BulletIt->GetSprite(), BulletIt->GetImage()))
		{
			EnemyIt->RemoveHealth(BulletIt->GetDemage());
			BulletIt->SetDelete(true);
		}
	}
	SetOFB.DeleteBullets();
}  */


void CountDemageBetweenPlayerAndBoss(Level_Boss &BOSS, PlayerO &P1) // ��������� ��������� ��� ������ � ����� � ������� � ���� ��������� ���� �������� �������
{
	std::vector<Bullet>::iterator it = P1.SetOfPlayerBullets.begin();
	for (; it != P1.SetOfPlayerBullets.end(); it++) // � ���� ����� ��������� ��� ���� ���������� ������� �� ��������� � ����� � ���� ��� ��������� �� �������� � ����� ��
	{
		if (InterSects::IfSpritesInterSects(it->GetSprite(), it->GetImage(), BOSS.GetSprite(), BOSS.GetImage()))
		{
			it->SetDelete(true);
			BOSS.RemoveHealth(it->GetDemage());
		}
	}
	if (BOSS.health <= 0) BOSS.for_delete = true; // ���� ����� ��������� �������� ����� ������ ��� ����� 0 �� �������� ����� �� ��������
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
	P1.RemovePBullets();
	BOSS.DeleteBullets();
}		  

void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys)
{
	std::vector<Bullet>::iterator EnemyBUlit; // ��������� �� ��������� ����
	// ������������� ��������� ���� �� ����������� � ������� � ���� ����������� ���������� �� ���� �������� �� �������� � �������� �������� � ������
	for (EnemyBUlit = SetOFEnemys.SetOFMovingEnemysBullets.begin(); EnemyBUlit != SetOFEnemys.SetOFMovingEnemysBullets.end(); EnemyBUlit++)
	{
		if (InterSects::IfSpritesInterSects(EnemyBUlit->GetSprite(), EnemyBUlit->GetImage(), Player.GetSprite(), Player.GetImage()))
		{
			Player - EnemyBUlit->GetDemage();
			EnemyBUlit->SetDelete(true);
		}
	}
	std::vector<Bullet>::iterator PBulletIt; // ��������� �� ���� �����
	std::vector<Enemys::MovingEnemy>::iterator En; // ��������� �� �����
	for (PBulletIt = Player.SetOfPlayerBullets.begin(); PBulletIt != Player.SetOfPlayerBullets.end(); PBulletIt++)
	{
		for (En = SetOFEnemys.SetOfMovingEnemys.begin(); En != SetOFEnemys.SetOfMovingEnemys.end(); En++)
		{
			if (InterSects::IfSpritesInterSects(PBulletIt->GetSprite(), PBulletIt->GetImage(), En->GetSprite(),En->GetImage()))
			{
				En - PBulletIt->GetDemage();
				PBulletIt->SetDelete(true);
			}
		}
	}
}