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
#include "Enemy.h"
#include "coords.h"
#include "stdafx.h"
/*
Данный класс реализует "множество врагов на уровне"
Его основа это связный список который содержит время появления врага
и указатель на связный список координат по которым перемещается этот враг
Объект читает информацию из специального файла в котором содержится информация о времени появления врага пи его координатам
Ключевые слова этого файла:
-1000 - обязательно. Обозначает начало файла
-1001 - Заканчивает описание данного врага.

*/


class LOGIC_API SetOfEnemy
{
	friend class SetOfBullets;
	friend class player_object;
	double cox, coy;
	int EnemyCount;
	int EnemyLeft;
	sf::Clock timer;
	EnemyI *BeginofEnemy;
	EnemyI *CurrentEnemy;
	sf::IntRect GetIntersectRect(sf::IntRect first, sf::IntRect second);
public:
	std::vector<Enemy> SOE;
	SetOfEnemy(const char *enemyfilename,double cx,double cy);
	void Update(float time, sf::RenderWindow &window);
	void DeleteEnemy();
	void addSetOfEnemy(std::ifstream &inputfile);
	void SortEnemyList();
	void SwapEnemyInList(EnemyI *First, EnemyI *Second,EnemyI *tmpEn);
	int ReturnEnemyLeftCount() { return EnemyLeft; }
	void ResetClock() { timer.restart(); }
	std::vector<Enemy> * ReturnEnemysVector();
	friend void RemoveDemageFromPlayers(player_object &Player, SetOfBullets &SetOFB, SetOfEnemy &ENM);
	friend void AddEnemyBullets(SetOfEnemy &SOE, SetOfBullets &SOB);
};
#endif