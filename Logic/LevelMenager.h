#ifndef LEVELM_H
#define LEVELM_H
#include "SFML/Graphics.hpp"
#include <vector>
#include "Bullet.h"
#include "Enemy.h"
#include <fstream>
#include <stack>
#include <string>
#include "Level.h"
#include "transitscreen.h"
#include <thread>
enum LevelState {InGame,TranScr,Pause,EndLevelSet,UpgradeScreen};
class LevelMenager
{
	char pathtoenemy[100];
	bool LevelLoaded;
	LevelState State;
	int count;
	int CurLevel;
	bool LevelsEnd;
	double cox, coy;
	Screens::TransitScreen *TRSCR; // Указатель на объект экрана переключения уровней
	bool IsScreen;
	std::ifstream levelfile;
	std::ifstream levelnames;
	std::string basepath; // Путь до пака с уровнями
	Level *CurrentLevel;
	std::string *LevelNames;
	int LoadLevel(); // Загрузка уровня если уровней больше нет то победа -1 Ошибка
	int LoadNextLevel();
public:
	LevelMenager(char *path, double cox, double coy,bool Is_new,char *SaveFile);
	void Update(float time, sf::RenderWindow &window);
	void ReadLevelNames();
	bool IsLevelSetIsEnd();
	double GetHealth();
};


#endif

