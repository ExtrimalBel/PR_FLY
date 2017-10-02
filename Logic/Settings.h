#include <SFML/Graphics.hpp>
#include <iostream>
#include "Background_Class.h"
#define LOGIC_API __declspec(dllexport)
class LOGIC_API GameSettings
{
	int level = 0;
	Back_Menu *BMenu;
	sf::Texture level1;
	sf::Texture level2;
	sf::Texture level3;
	sf::Sprite levels1;
	sf::Sprite levels2;
	sf::Sprite levels3;
	sf::Texture ExitText;
	sf::Sprite ExitSpr;
	sf::Texture FullScreenText;
	sf::Sprite FullScreenspr;
	sf::Font videomodefont;
	sf::RectangleShape videomoderect;
	sf::Text videomodetext;
	sf::VideoMode currentmode;
	std::vector<sf::VideoMode> Vid_Modes;
	std::vector<sf::VideoMode>::iterator modeit;
	int xco;
	int yco;
	int selected_level = 0;
	bool fullscreen = false;
	sf::Clock cl;
	int modei = 0;
public:
	GameSettings(sf::RenderWindow &window);
	void ChangeModes();
	void DrawSettings(sf::RenderWindow &Window); // ��������� ��������� ��������
	void update(float time,sf::RenderWindow &Window,sf::Clock &mainclock); // �������� �������� � ������������ � ��������� ������� �������� � ����� ��������� ������ ���� ��������
	void SetLevelGlobal(sf::RenderWindow &window); // ��������� ������ ��������� ���������
	void IFScreenChanged(sf::RenderWindow &window, sf::Clock &mainclock); // �������� ����� ������ ���� ������ �������������� ���� � ����������
	int IfExitSet(sf::RenderWindow &Window); // ���� ������ ����� ������ � ������� ���� �� �������
};