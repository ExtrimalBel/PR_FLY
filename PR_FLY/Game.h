#pragma once
#include <string>
#include <iostream>
#include <fstream>
#include <SFML\Graphics.hpp>
#include <Windows.h>
#include <io.h>
#include <MainMenu.h>
#include <SoundControl.h>
#include "ExceptionsDefenitions.h"
#include <ExceptionsDefenitions.hpp>
#include "LoadGame.h"
#include "GameDifficulty.h"
#include <Settings.h>
#include "PlayerSaveSlotDef.h"
#include "GameField.h"
#include "UpgradesMenager.h"
using namespace std;
using namespace sf;


namespace MainGameClass
{

	typedef enum{GameS,Settings,Menu,Load,SelectDifficulty}GameState;
	class Game
	{
		struct GameSettings
		{
			pair<int, int>Resolution;
			int Volume;
			bool MuteState;
			bool Fullscreen;
		}Settings;
		struct mainItemPointers
		{
			Menus::SettingsClass *Set;
			Menus::LoadGameMenu *LoadM;
			Menus::MainMenu *MMenu;
			Menus::GameDifficulty *DifClass;
			Fields::GameField *Gf;
		} GamePointers;
		sf::Uint32 st;
		GameState State;
		string BasePath;
		double cox, coy;
		double vidx, vidy;
		SoundControl::SoundControlStruct SndControl;
		RenderWindow *Window; // Окно в котором отрисовываеться игра
		void MainLoop(); // Главная функция игры
		void LoadGameSettings(sf::Uint32 &st);
		void SaveGameSettings(Exceptions::SettingsClose *Ex);
		void UpdateMainMenu(RenderWindow &window);
		void UpdateLoadMenu(RenderWindow &window);
		void UpdateGameDifficultyClass(RenderWindow &window);
		void UpdateMenuCursor(RenderWindow &window);
		Texture CursorTex;
		Sprite CursorSpr;
	public:
		Game(string BasePath);
		~Game();
		void StartDemnedGame(); // Запускает игру
	};
}