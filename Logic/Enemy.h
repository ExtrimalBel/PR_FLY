#ifndef ENEMYC_H
#define ENEMYC_H

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#include <SFML\Graphics.hpp>
#include <vector>
#include "coords.h"
class LOGIC_API Enemy
{
	double demage;
	double life;
	double speed;
	sf::Clock lasshot;
	sf::Image enemyimg;
	sf::Texture enemytex;
	sf::Sprite enemy;
	std::vector<sf::Vector2f> coordst;
	double cox, coy;
	double gunspeed;
	bool ref = false;
	coord *coordinates;
	int x2, y2;
	bool for_delete;
public:
	Enemy(double cx, double cy, int health, double gunspeed,coord *beginofcoord, double speed, double demage);
	virtual void Update(float time, sf::RenderWindow &window);
	virtual void Move(float time);
	virtual void Draw(sf::RenderWindow &window);
	bool IsForDelete();
	float GetTimeFromLastShot();
	bool IsShot();
	void ResetClock();
	virtual void RemoveHealth(int health);
	sf::Vector2f GetPostion();
	sf::IntRect GetEnemyRect();
	double GetDemage() { return demage; }
	sf::Image& GetImage() { return enemyimg; }
	sf::Sprite& GetSprite() { return enemy; }
};


class StationarEnemy
{

};


#endif