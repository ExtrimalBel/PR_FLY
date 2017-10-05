#ifndef SetOfBullet_H
#define SetOfBullet_H
#include <vector>
#include "Bullet.h"
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "stdafx.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif

class LOGIC_API  SetOfBullets
{
	friend class SetOfEnemy;
	friend class PlayerO;
	friend class Level_Boss;
	std::vector<Bullet> SOB;
	std::vector<Bullet> PSOB;
	double cx, cy;
	void Move(float time); // Движение пуль
	void Draw(sf::RenderWindow &window); // Отрисовка пуль
public:
	void DeleteBullets();
	SetOfBullets(double cx,double cy);
	void Update(float time, sf::RenderWindow &window); // Обновляем все пули
	void AddBullet(sf::Vector2f position, double cx, double cy, int dir, float speed,double demage);
	void AddPlayerBullet(sf::Vector2f position, double cx, double cy, int dir, float speed, double demage);
	void CountDemageToPlayer(double &demage,sf::IntRect playerrect);
	friend void RemoveDemageFromPlayers(PlayerO &Player, SetOfBullets &SetOFB,SetOfEnemy &ENM);
	void RemoveDemageFromBoss(double &demage, const sf::Sprite& bosssprite, sf::Image& bossimg);
	friend void AddEnemyBullets(SetOfEnemy &SOE, SetOfBullets &SOB);
	friend void CountDemageBetweenPlayerAndBoss(SetOfBullets &SetOfB, Level_Boss &BOSS,PlayerO &P1); // Проверяет попадание пль игрока в босса и наоброт и если попадание есть отнимает здоровье
	
};

#endif