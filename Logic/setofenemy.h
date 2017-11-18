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
Данный класс реализует "множество врагов на уровне"
Его основа это связный список который содержит время появления врага
и указатель на связный список координат по которым перемещается этот враг
Объект читает информацию из специального файла в котором содержится информация о времени появления врага пи его координатам
Ключевые слова этого файла:
-1000 - обязательно. Обозначает начало файла
-1001 - Заканчивает описание данного врага.
TODO вынести код который чиатет иформацию о врагах в отдельный класс
Поместить вражеские пули в данный класс 
Переписать код в соответствии с новыми классами врагов
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
	// Векторы хранят информацию о врагах и о пулях выпущенных данными врагами
	std::vector<Enemys::MovingEnemy> SetOfMovingEnemys;
	std::vector<Bullet> SetOFMovingEnemysBullets;
	std::vector<Bullet> SetOFStationarEnemysBullet;
	std::vector<Enemys::StationarEnemy> SetOfStationarEnemys;
	void DeleteEnemy(); // Удалет врагов помеченных на удаление
	void UpdateBullets(float time, sf::RenderWindow &window); // Обновляет пули выпущенные врагами
	void DeleteBullets(); // Удаляет пули помеченные на удаление
	void addSetOfEnemy(std::ifstream &inputfile); // Формирует список врагов если обнаружено множесто врагов
	void SortEnemyList();
	void SwapEnemyInList(EnemyI *First, EnemyI *Second, EnemyI *tmpEn);
public:

	SetOfEnemy(const char *enemyfilename,double cx,double cy);
	void Update(float time, sf::RenderWindow &window);



	int ReturnEnemyLeftCount() { return EnemyLeft; }
	void ResetClock() { timer.restart(); }
	friend void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys); // Считает урон для игрока и для врагов и отнимает его
	void AddBullets();
};
#endif