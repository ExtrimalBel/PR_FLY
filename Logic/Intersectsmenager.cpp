#include "stdafx.h"
#include "Intersectsmenager.h"

namespace InterSects
{
	bool IfSpritesInterSects(const sf::Sprite &spr1, const sf::Image &img1, const sf::Sprite &spr2, const sf::Image &img2)
	{
		return PixelPerfectCollision(spr1, spr2, img1, img2);
	}

	int CountDemageToPlayer(std::vector<Bullet> &SOB, const sf::Sprite &PlayerSprite, const sf::Image &PlayerImage)
	{
		int demage = 0; // �������� ���� ������
		std::vector<Bullet>::iterator BulletIt;
		for (BulletIt = SOB.begin(); BulletIt != SOB.end(); BulletIt++) // ���� ��������� ���� ������ �� ����� �� �������� � ����� ���� ���� ���� � ������� ��� ���� �� ��������
		{
			if (IfSpritesInterSects(BulletIt->GetSprite(), BulletIt->GetImage(), PlayerSprite, PlayerImage))
			{
				demage += BulletIt->GetDemage();
				BulletIt->SetDelete(true);
			}
		}
		return demage;
	}


	int CountDemageToEnemy(std::vector<Bullet> &PSOB, std::vector<Enemy> &EnemySet)
	{
		std::vector<Enemy>::iterator EnemyIt;// ����� �������� ��������� �� ���� � ������
		std::vector<Bullet>::iterator BulletIt;
		for (EnemyIt = EnemySet.begin(); EnemyIt != EnemySet.end();EnemyIt++) // �������� ������� ����� � ���� �� ����������� � ���� ��� ��������� �� ������� � ����� ����� � ������������ ���� �� ��������
		for (BulletIt = PSOB.begin(); BulletIt != PSOB.end(); BulletIt++)
		{
			if (IfSpritesInterSects(EnemyIt->GetSprite(), EnemyIt->GetImage(), BulletIt->GetSprite(), BulletIt->GetImage()))
			{
				EnemyIt->RemoveHealth(BulletIt->GetDemage());
				BulletIt->SetDelete(true);
			}
		}
		return 0;
	}


}