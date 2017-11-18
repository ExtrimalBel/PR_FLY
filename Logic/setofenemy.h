#ifndef ENEM_H
#define ENEM_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "PlayerS.h"
#include <fstream>
#include <vector>

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#include "BaseForEnemys.h"
#include "coords.h"
#include "stdafx.h"
#include "Bullet.h"
#include "Intersectsmenager.h"
#include "Player_Class.h"
/*
������ ����� ��������� "��������� ������ �� ������"
��� ������ ��� ������� ������ ������� �������� ����� ��������� �����
� ��������� �� ������� ������ ��������� �� ������� ������������ ���� ����
������ ������ ���������� �� ������������ ����� � ������� ���������� ���������� � ������� ��������� ����� �� ��� �����������
�������� ����� ����� �����:
-1000 - �����������. ���������� ������ �����
-1001 - ����������� �������� ������� �����.
TODO ������� ��� ������� ������ ��������� � ������ � ��������� �����
��������� ��������� ���� � ������ ����� 
���������� ��� � ������������ � ������ �������� ������
*/

namespace InterSects
{
	class IntersectsMenager;
}

class PlayerO;
class LOGIC_API SetOfEnemy
{
	friend class InterSects::IntersectsMenager;
	double cox, coy;
	int EnemyCount;
	int EnemyLeft;
	sf::Clock timer;
	EnemyI *BeginofEnemy;
	EnemyI *CurrentEnemy;
	sf::IntRect GetIntersectRect(sf::IntRect first, sf::IntRect second);
	// ������� ������ ���������� � ������ � � ����� ���������� ������� �������
	std::vector<Enemys::MovingEnemy> SetOfMovingEnemys;
	std::vector<Bullet> SetOFMovingEnemysBullets;
	std::vector<Bullet> SetOFStationarEnemysBullet;
	std::vector<Enemys::StationarEnemy> SetOfStationarEnemys;
	void DeleteEnemy(); // ������ ������ ���������� �� ��������
	void UpdateBullets(float time, sf::RenderWindow &window); // ��������� ���� ���������� �������
	void DeleteBullets(); // ������� ���� ���������� �� ��������
	void addSetOfEnemy(std::ifstream &inputfile); // ��������� ������ ������ ���� ���������� �������� ������
	void SortEnemyList();
	void SwapEnemyInList(EnemyI *First, EnemyI *Second, EnemyI *tmpEn);
public:

	SetOfEnemy(const char *enemyfilename,double cx,double cy);
	void Update(float time, sf::RenderWindow &window);



	int ReturnEnemyLeftCount() { return EnemyLeft; }
	void ResetClock() { timer.restart(); }
	friend void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys); // ������� ���� ��� ������ � ��� ������ � �������� ���
	void AddBullets();
};
#endif