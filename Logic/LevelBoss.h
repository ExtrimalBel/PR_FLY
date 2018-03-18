#ifndef BOSSH
#define BOSSH
#include <SFML/Graphics.hpp>
#include "coords.h"
#include <fstream>
#include "Bullet.h"
#include "Intersectsmenager.h"

namespace InterSects
{
	class IntersectsMenager;
}


class Level_Boss
{
	friend class InterSects::IntersectsMenager;
	bool for_delete;
	// Data
	sf::Texture bllettext;
	sf::Image bossimg;

	sf::Clock FirstBulletClock;
	sf::Clock SecondBulletClock;
	int currentnumber; // Текущая позиция босса
	int maxnumber; // Максималшьный номер позиции босса
	int nextx, nexty; // Следующие координаты
	int currentx, currenty; // Текущие координаты
	bool Is_Moving; // Буль показывает двигаеться ли босс. Нужен для смены координат движения
	double demage; // Урон босса
	double fgunspeed; // Скорость стельбы основног оруия босса
	double sgunspeed; // Скрорость вторичного оружия босса
	double fguninterval;
	double sguninterval;
	float speed; // Скорость самого босса
	double cox, coy; // Коэффициенты масштабирования
	int health; // Здоровье босса
	char *pathtofile; // Путь к файлу описания босса
	boss_coord *Coordinates; // Указатель на список коодинат перемещения босса
	std::ifstream inputfile; // Объект файла с описание босса
	// Sprite of boss
	sf::Texture bosstex;
	sf::Sprite bossprite;
	// Weapon of boss
	sf::Texture firstbossbullet;
	sf::Sprite firstbullet;
	sf::Texture secondbossbullet;
	sf::Sprite secondbullet;
	int TypeOfMoving; // 1 - random 2 -circle 0 - undefined

	// Vectors of boss bullet
	std::vector<Bullet> SetofFBullet;
	std::vector<Bullet> SetofSBullet;


	// Private methods
	int Move(float  time); 
	void Draw(sf::RenderWindow &window);
	void MoveRandom(float time);
	void MoveCircle(float time);
	int MakeCoordList();

	sf::Vector2f CountNextPoint(float time);
	bool IfPointReached(sf::Vector2f playerpos);
	boss_coord * FindNumberInList(int number);
	// Функции стрельбы босса
	int Shot();
	int FirstGunShot();
	int SecondGunShot();
	void MoveBullets(float time);
	void DrawBullets(sf::RenderWindow &window);
	friend void CountDemageBetweenPlayerAndBoss(Level_Boss &BOSS, PlayerO &P1);  // Проверяет попадание пль игрока в босса и наоброт и если попадание есть отнимает здоровье
	void DeleteBullets();
public:
	bool IsForDelete() { return for_delete; }
	void RemoveHealth(int demage) { health -= demage; }
	void Update(float time, sf::RenderWindow &window);
	Level_Boss(char *pathtofile, double cox, double coy);
	sf::Sprite& GetSprite() { return bossprite;}
	sf::Image& GetImage() { return bossimg; }
};

#endif