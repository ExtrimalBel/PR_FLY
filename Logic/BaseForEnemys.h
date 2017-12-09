#ifndef BASEENEMY_H
#define BASEENEMY_H
#include <SFML/\Graphics.hpp>
#include <vector>
#include "coords.h"
#include <list>
#include "LevelEventDefenition.h"
#include "ExceptionsDefenitions.hpp"
namespace Enemys
{
	class BaseEnemy
	{
	protected:
		double FirstGunDemage;
		double SecondGunDemage;
		double life;
		double speed;
		int Heigth, Width; // ������ � ������ ��������
		//������� �������� � �������� ��������
		sf::Clock FirstGunLastShot;
		sf::Clock SecondGunLastShot;
		sf::Clock AnimSpeed;
		sf::Image EnemyImg;
		sf::Image EnemyDeathImg;
		sf::Texture EnemyTex;
		sf::Texture EnemyDeathTex;
		sf::Sprite Enemy;
		double cox, coy;							    //
		double FirstGunSpeed; // �������� ���������� ������
		double SecondGunSpeed; // �������� ���������� ������
		bool ref = false;
		EnemyEventDef::AnimationType AnimType; // ��� �������� �����
		EnemyEventDef::DeathAnimType DeathType; // ��� �������� ������ �����
		int x2, y2;
		bool for_delete;
		int AnimS;
		int DeathS;
		int AnimFrame; // ������� ���� �������� ������������ ��� �������� ������
		int DeathFrames; // ���-�� ������ �������� ������
		int AnimFrames; // ���-�� ������ �������� 
		// ���� � ���������
		std::string EnemyImgPath;
		std::string EnemyDeathPath;
	protected:
		void DeathAnimUpdate(float time, sf::RenderWindow &window);
		void EnemyAnimUpdate(float time, sf::RenderWindow &window);
		void LoadEnemyImage();
		void LoadEnemyDeathImage();
	public:

		BaseEnemy(double cx, double cy,EnemyEventDef::EnemyData &DataStruct);
		virtual void Update(float time, sf::RenderWindow &window) = 0;
		virtual void Move(float time) = 0;
		virtual void Draw(sf::RenderWindow &window) = 0;
		bool IsForDelete();
		float GetTimeFromLastFirstGunShot();
		float GetTimeFromLastSecondGunShot();
		virtual bool IFFirstGunShot() = 0;
		virtual bool IFSecondGunShot() = 0;
		void ResetClock();
		virtual void RemoveHealth(int health);
		sf::Vector2f GetPostion();
		double GetFirstGunDemage() { return FirstGunDemage; }
		double GetSecondGunDemage() { return SecondGunDemage; }
		sf::Image& GetImage() { return EnemyImg; }
		sf::Sprite& GetSprite() { return Enemy; }
	};


	class StationarEnemy : public BaseEnemy
	{
	private:
		int X, Y; // ������� ����������
		void Move(float time);
		void Draw(sf::RenderWindow &window);
	public:
		StationarEnemy(double cx, double cy,int x,int y,int health, double gunspeed, double speed, double demage);
		void Update(float time, sf::RenderWindow &window);
		
	};

	class AdvancedMovingEnemy : public BaseEnemy
	{

	};


	class MovingEnemy : public BaseEnemy
	{
	private: 
		int MovingType; // ��� ����������� 1 - ����� 2 - ����������
		std::list<EnemyEventDef::CoordDef> *Coordinates;
		//coord *coordinates;
		std::list<EnemyEventDef::CoordDef> ListOfCoord; // ������ ���������� � ����������� �����������
		void MoveLine(float time);
		void MoveCircle(float time);
		void Move(float time);
		void Draw(sf::RenderWindow &window);
	public:
		MovingEnemy(double cx, double cy,EnemyEventDef::EnemyData &DataStruct);
		void Update(float time, sf::RenderWindow &window);
		
	};

	class LevelBoss : public BaseEnemy
	{

	};

}


#endif