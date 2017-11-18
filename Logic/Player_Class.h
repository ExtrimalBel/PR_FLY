#ifndef PLAYER_H
#define PLAYER_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "PlayerS.h"
#include <fstream>
#include "stdafx.h"
#include "Bullet.h"
#include "Intersectsmenager.h"
#include "setofenemy.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class Level_Boss;
class SetOfEnemy;
namespace InterSects
{
	class IntersectsMenager;
}

class LOGIC_API PlayerO{
	friend class InterSects::IntersectsMenager;
	sf::Clock timerclock;
	sf::Image bodyimg;
		sf::Sprite Body;
		sf::RectangleShape Gun;
		sf::RectangleShape Engine;
		sf::CircleShape Shield;
		sf::Texture BodyTex;
			sf::Texture GunTex;
			sf::Texture EngineTex;
			sf::Texture ShieldTex;
			sf::Clock fireclock;
			sf::Clock energytime;
	PStatements State; // —труктура с параметрами карабл€
	int x, y; //  оординаты коробл€ игрока
	int defx = 1920; // ¬ысота всего пол€ по умолчанию
	int defy = 1080;
	int defsizex = 80;
	int defsizey = 64;
	double shapecox;
	double shapecoy;
	std::vector<Bullet> SetOfPlayerBullets;
public:
	friend void CountDemageBetweenPlayerAndBoss(Level_Boss &BOSS, PlayerO &P1); // ћетод рассчитывает и отнимает урон боссу и игроку
	friend void CountDemageBeetwinPlayerAndEnemys(PlayerO &Player, SetOfEnemy &SetOFEnemys);
	bool ShieldActive = false;
	PlayerO(int x, int y, double shapecox,double shapecoy,bool Isnew);
	void Move(sf::RenderWindow &window);
	void Update(sf::RenderWindow &window,float time);
	void Draw(sf::RenderWindow &window);
	void RemoveHealth(int remh);
	void AddHealth(int addh);
	bool LoadFile(bool Isnew, char *filename);
	void SetCoord(int x, int y);
	void IfApocalypse(bool inter, int remh);
	void RemovePBullets();
	void SetGunSpeed();
	void SetEnergy();
	void ActiveDeactiveS();
	PStatements GetPlayerStatements();
	void SaveState(char *filename);
	void LoadEngineTexture();
	void LoadBodyTexture();
	void LoadGunTexture();
	int getx() { return x; }
	int gety() { return y; }
	int GetHealth();
	bool ifShot();
	int GetDemage() { return State.gun; }
	int GetGunSpeed() { return State.gunspeed; }
	sf::Vector2f GetBulletPosition(int &y);
	sf::Image& GetImage() { return this->bodyimg; }
	sf::Sprite& GetSprite() { return Body; }
	PlayerO& operator-(int value); // ќтнимает здоровье игроку использование player_object - int
	PlayerO& operator+(int value);
};
#endif