#pragma once
#include <GameField.h>
#include <GameMenu.h>
#include <fstream>
#include <SoundSystem.h>
#include <loadgameclass.h>
#include <SFML/Graphics.hpp>
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
	// Methods fopr create classes

	bool CreateGameField(sf::RenderWindow &window, float time);
	bool CreateLoadGameScreen(sf::RenderWindow &window, float time);
	bool CreateSettingsScreen(sf::RenderWindow &window, float time);
	bool CreateMainMenuScreen(sf::RenderWindow &wndow, float time);
	bool CreateSoundSystem();
	//Private Data
	MainM *Menu; // Главное меню
	GameField *Field; // Игровое поле
	LoadM *LM; // Экран загрузки
	SoundSystem::SoundPlayer *SPlayer; // Звуковая система
	double cox, coy; // Коэффициенты масщтабирования
	int VideoX, VideoY; // Разрешение экрана
	int Volume; // Общая громкость
};