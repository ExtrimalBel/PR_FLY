#ifndef BASEENEMY_H
#define BASEENEMY_H
#include <SFML/\Graphics.hpp>
#include <vector>
#include "coords.h"
namespace Enemys
{
	class BaseEnemy
	{
	protected:
		double demage;
		double life;
		double speed;
		sf::Clock lasshot;
		sf::Image enemyimg;
		sf::Texture enemytex;
		sf::Sprite enemy;
		std::vector<sf::Vector2f> coordst;
		double cox, coy;							    //
		double gunspeed;
		bool ref = false;

		int x2, y2;
		bool for_delete;
	public:
		BaseEnemy(double cx, double cy, int health, double gunspeed, double speed, double demage);
		virtual void Update(float time, sf::RenderWindow &window) = 0;
		virtual void Move(float time) = 0;
		virtual void Draw(sf::RenderWindow &window) = 0;
		bool IsForDelete();
		float GetTimeFromLastShot();
		bool IsShot();
		void ResetClock();
		virtual void RemoveHealth(int health);
		sf::Vector2f GetPostion();
		double GetDemage() { return demage; }
		sf::Image& GetImage() { return enemyimg; }
		sf::Sprite& GetSprite() { return enemy; }
	};


	class StationarEnemy : public BaseEnemy
	{
	private:
		int X, Y; // Текущие координаты
		void Move(float time);
		void Draw(sf::RenderWindow &window);
	public:
		StationarEnemy(double cx, double cy,int x,int y,int health, double gunspeed, double speed, double demage);
		void Update(float time, sf::RenderWindow &window);
		
	};


	class MovingEnemy : public BaseEnemy
	{
	private: 
		coord *coordinates;
		void Move(float time);
		void Draw(sf::RenderWindow &window);
	public:
		MovingEnemy(double cx, double cy, int health, double gunspeed, coord *beginofcoord, double speed, double demage);
		void Update(float time, sf::RenderWindow &window);
		
	};

}


#endif