#ifndef INTER_H
#define INTER_H
#include <SFML\Graphics.hpp>
#include "Bullet.h"
#include "Enemy.h"
#include "Player_Class.h"
#include "setofenemy.h"
#include "LevelBoss.h"


class PlayerO;
class Level_Boss;
class SetOfEnemy;

namespace InterSects
{
	bool IfSpritesInterSects(const sf::Sprite &spr1, const sf::Image &img1, const sf::Sprite &spr2, const sf::Image &img2); // ������� ��� ������������ �������� �� ����������� ���� ��������
	int CountDemageToPlayer(std::vector<Bullet> &SOB,const sf::Sprite &PlayerSprite,const sf::Image &PlayerImage); // ������� ���� ���������� ������ ���������� ������ � �������� "�������������� ����" ��� ��������
	int CountDemageToEnemy(std::vector<Bullet> &PSOB,std::vector<Enemy> &EnemySet); // ���� ��� � ���� ������ ������ ��� 

	class IntersectsMenager
	{
		friend class PlayerO;
		friend class SetOfEnemy;
		friend class Level_Boss;
	public:
		IntersectsMenager();
		void CountDemageBetweenPlayerAndBoss(Level_Boss &BOSS, PlayerO &P1);
		void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys);

	};
}
#endif