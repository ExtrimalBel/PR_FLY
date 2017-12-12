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
	void Update(); // ��������� ��� ����. ��� �� ��������� �������� ���� ����������
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
	MainM *Menu; // ������� ����
	GameField *Field; // ������� ����
	LoadM *LM; // ����� ��������
	SoundSystem::SoundPlayer *SPlayer; // �������� �������
	Screens::ErrorScreen *ErrScr; // ����� ������� ������
	double cox, coy; // ������������ ���������������
	int VideoX, VideoY; // ���������� ������
	int Volume; // ����� ���������
	sf::RenderWindow *window;
	sf::Uint32 VideoMode; // ���������� ������ ����
	std::string BaseGamePath; // Base game mode path
	EnemyEventDef::GameOptions Options; // Game Options
	GameState State;
};