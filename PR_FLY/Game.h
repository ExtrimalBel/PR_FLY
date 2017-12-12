#pragma once
#include <GameField.h>
#include <GameMenu.h>
#include <fstream>
#include <SoundSystem.h>
#include <loadgameclass.h>
#include <SFML/Graphics.hpp>
#include <ConfigReader.h>
#include "ExternalExceptions.h"
#include <transitscreen.h>
typedef enum { GameF, Settings, MainMenu, LoadGame,ErrorMessage} GameState;
class Game
{
public:
	Game();
	~Game();
	void Update(); // Обновляет всю игру. Тут же находится глаывный цикл приложения
private:
	void UpdateLoadGameScreen(sf::RenderWindow &window, float time);
	void UpdateGameField(sf::RenderWindow &window, float time);
	void UpdateSettings(sf::RenderWindow &window, float time);
	void UpdateMainMenu(sf::RenderWindow &window,float time);
	void UpdateSplayer(sf::RenderWindow &window,float time);
	// Methods fopr create classes

	bool CreateGameField();
	bool CreateLoadGameScreen();
	bool CreateSettingsScreen();
	bool CreateMainMenuScreen();
	bool CreateSoundSystem();
	bool CreateErrorMessage();
	//Private Data
	sf::Clock clock; // Ingame Clock
	MainM *Menu; // Главное меню
	GameField *Field; // Игровое поле
	LoadM *LM; // Экран загрузки
	SoundSystem::SoundPlayer *SPlayer; // Звуковая система
	Screens::ErrorScreen *ErrScr; // Экран игровой ошибки
	double cox, coy; // Коэффициенты масщтабирования
	int VideoX, VideoY; // Разрешение экрана
	int Volume; // Общая громкость
	sf::RenderWindow *window;
	sf::Uint32 VideoMode; // Разрешение экрана игры
	std::string BaseGamePath; // Base game mode path
	EnemyEventDef::GameOptions Options; // Game Options
	GameState State;
};