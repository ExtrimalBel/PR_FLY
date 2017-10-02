#ifndef PLAYER_H
#define PLAYER_H
#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include "PlayerS.h"
#include <fstream>
#include "stdafx.h"

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API player_object{
	friend class SetOfEnemy;
	friend class SetOfBullets;
	friend class Level_Boss;
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
	PStatements State; // Структура с параметрами карабля
	int x, y; // Координаты коробля игрока
	int defx = 1920; // Высота всего поля по умолчанию
	int defy = 1080;
	int defsizex = 80;
	int defsizey = 64;
	double shapecox;
	double shapecoy;
public:
	friend void CountDemageBetweenPlayerAndBoss(SetOfBullets &SetOfB, Level_Boss &BOSS, player_object &P1);
	friend void RemoveDemageFromPlayers(player_object &Player, SetOfBullets &SetOFB, SetOfEnemy &ENM);
	bool ShieldActive = false;
	player_object(int x, int y, double shapecox,double shapecoy,bool Isnew);
	void Move(sf::RenderWindow &window);
	void Update(sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void IfShot(int inter, int remh);
	void RemoveHealth(int remh);
	void AddHealth(int addh);
	bool LoadFile(bool Isnew, char *filename);
	void SetCoord(int x, int y);
	void IfApocalypse(bool inter, int remh);
	int Fire();
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
	sf::IntRect ReturnRect();
	int GetHealth();
	bool ifShot();
	int GetDemage() { return State.gun; }
	int GetGunSpeed() { return State.gunspeed; }
	sf::Vector2f GetBulletPosition(int &y);
	sf::Image& GetImage() { return this->bodyimg; }
	sf::Sprite& GetSprite() { return Body; }
	player_object& operator-(int value); // Отнимает здоровье игроку использование player_object - int
	player_object& operator+(int value);
};
#endif