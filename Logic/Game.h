#include <SFML\Graphics.hpp>

#include <vector>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#ifndef GAME_I // Стандартная  процедура для предотвращения повторного включения заголовка
#define GAME_I
#include "Bullets.h"
#include "ShipsClasses.h"
#include "Background_Class.h"
#include "Player_Class.h"
// This class is the game Field class
// Объявляю текстуры объектов

class LOGIC_API GameField
{
	sf::Texture PlayerTexture;
	sf::Texture BulletTexture;
	sf::Texture EnemyTexture;
	std::vector<Bullet> Bullets;
	std::vector<Enemy_Ship> Enemys;
	std::vector<Enemy_Bullet> En_Bullets; // Вектор котрый содержит вражеские пули
	sf::Texture BackText;
	sf::Sprite SprBack;
	sf::Texture DHudText;
	sf::Texture UHudText;
	sf::Sprite UHudSpr;
	sf::Clock Enemy_Clock;
	sf::Text Score;
	sf::Text HealthText;
	sf::Font fontforScore;
	int sc = 0;
	sf::Clock Bul_Clock;
	sf::Clock En_Bul;
	int statement;
	sf::Text Dead_Message;
	Player *p1;
	player_object *p2;
	int exit = 0;
	Back_Menu BMenu;
protected:

	void AddBullet(); // Добавление выпущенного снаряда
	void IFDELETEBULLET(); // Вышел ли снаряд за пределы поля
	void Addenemy();
	void IfEnemyKill();
	void MoveEnemys(float time);
	void AddEnemyBullet();
	void UpdateEnBullets(sf::RenderWindow &window, float time);
	void IfEnemyBulletOut();
	void IfShotInPlayer();
	void DrawDeath(sf::RenderWindow &window);
	void IfEnemyOut();
	void updatePlayer(float time, sf::RenderWindow &window);
	void UpdateEnemy(float time, sf::RenderWindow &window);
	void UpdateBullets(float time, sf::RenderWindow &window);

public:
	
	int IfExit();
	int GetExit() { return exit; }
	GameField();
	void UpdateAll(float time, sf::RenderWindow &window);
};
#endif