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
	void Update(); // ��������� ��� ����. ��� �� ��������� �������� ���� ����������
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
	MainM *Menu; // ������� ����
	GameField *Field; // ������� ����
	LoadM *LM; // ����� ��������
	SoundSystem::SoundPlayer *SPlayer; // �������� �������
	double cox, coy; // ������������ ���������������
	int VideoX, VideoY; // ���������� ������
	int Volume; // ����� ���������
};