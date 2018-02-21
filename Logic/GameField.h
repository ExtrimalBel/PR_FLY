#pragma once
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <vector>
#include "PlayerClass.h"
#include "Level.h"
#include "LevelMenager.h"
#include "UpgradeClass.h"
#include "PlayerSaveSlotDef.h"
#include <SoundControl.h>
#include "SaveGame.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
using namespace std;
using namespace sf;
namespace Fields
{
	class LOGIC_API GameField
	{
		enum{Level,UpgradeScreen,Win,SaveState} GameFieldState;
		struct FieldPointers//В структуре храняться указатели на класс уровня и на класс меню абгрейда
		{
			LevelLogic::Level *CurrentLevel;
			LevelLogic::LevelMenager *LevelMenager;
			LevelLogic::UpgradeScreen *UpgradeScreen;
			LevelLogic::UpgradesMenager *UpgradeMenager;
			Menus::SaveGameMenu *SaveMenu;
		} Fpointers;
		LoadAndSave::SaveSlot &CurrentSave;
		SoundControl::SoundControlStruct SndControl;
		double cox, coy;
		string BasePath;
		int Money; // Деньги
		void ProcessLevel(float time,RenderWindow &window);
		void ProcessUpgradeScreen(float time, RenderWindow &window);
		void ProcessWinScreen(float time,RenderWindow &window);
		void StartNewGame();
		void ContinueGame();
	public:
		GameField(string BasePath, double cox, double coy, LoadAndSave::SaveSlot &CurrentSave,SoundControl::SoundControlStruct &SndControl);
		void Upgrade(float time,RenderWindow &window);
		~GameField();
	};
}