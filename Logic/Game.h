#include <SFML\Graphics.hpp>
#include "ShipsClasses.h"
#include <vector>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#ifndef GAME_I // Стандартная  процедура для предотвращения повторного включения заголовка
#define GAME_I

#include "Bullets.h"
// This class is the game Field class
class LOGIC_API GameField
{
	std::vector<Bullet> Bullets;
	std::vector<Enemy_Ship> Enemys;
	sf::Texture BackText;
	sf::Sprite SprBack;
	sf::Texture DHudText;
	sf::Texture UHudText;
	sf::Sprite UHudSpr;
	sf::Clock Enemy_Clock;
public:
	Player p1;
	GameField();
	void updatePlayer(float time, sf::RenderWindow &window);
	int IfExit();
	void AddBullet(); // Добавление выпущенного снаряда
	void IFDELETEBULLET(); // Вышел ли снаряд за пределы поля
	void Addenemy();
	void IfEnemyKill();
	void MoveEnemys(float time);
};
#endif