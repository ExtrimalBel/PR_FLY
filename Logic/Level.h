#pragma once
#include <iostream>
#include <string>
#include <SFML\Graphics.hpp>
#include "Player.h"
#include "LevelMenager.h"
#include <SoundControl.h>
#include "UpgradeClass.h"
#include "PlayerSaveSlotDef.h"
#include "SetOfEnemy.h"
#include "Hud.h"
#include "InterSects.h"
#include "PauseMenu.h"
using namespace sf;
using namespace std;

namespace LevelLogic
{
	class Level
	{
		Clock SplashClock;
		enum {InSplashScreen,Game,EndSplashScreen,LoseGameSreen,LevelPause}LevelState;
		struct
		{
			// —десь должны быть указатели на hud класс врагов, класс игрока
			Ships::Player *PlayerClass;
			LevelLogic::SetOfEnemy *SetOfEnemy;
			LevelLogic::GameHud *Hud;
			LevelLogic::PauseMenu *PMenu;
		}PartOfLevel;
		vector<Bullet> PlayerBullets;
		LevelLogic::LevelConfigStruct *CurrentLevelConfig; //  онфиг уровн€
		Texture BackGroundTex; // текстура и спрайт фона уровн€
		LoadAndSave::SaveSlot &CurrentSave;
		Sprite BackGroundSpr;
		string BasePath;
		Texture SplashTex;
		Sprite SplashBack;
		Texture EndSlpashTexture;
		Sprite EndSplashTexture;
		Font GameFont;
		Text SplashText;
		Text ButtomText;
		Text EndLevelMessage; // —ообщение выводитьс€ тогда, когда корабль игрока уничтожен
		double cox, coy;
		SoundControl::SoundControlStruct SndControl; // —туктура с указател€ми дл€ работы со звуком
		void UpdateSetOfEnemy(float time,RenderWindow &window);
		void UpdatePlayer(float time, RenderWindow &window);
		void CheckInterSects(RenderWindow &window);
		void DrawBaseLevel(RenderWindow &window);
		void UpdatePlayerBullets(float time,RenderWindow &window);
	public:
		void Update(float time, RenderWindow &window);
		Level(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, LevelLogic::LevelConfigStruct *CurrentLevelConfig,LoadAndSave::SaveSlot &CurrentSave);
	};
}