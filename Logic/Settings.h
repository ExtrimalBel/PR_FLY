#include <SFML/Graphics.hpp>
#include <iostream>
#define LOGIC_API __declspec(dllexport)
class LOGIC_API GameSettings
{
	int level = 0;
	sf::Texture BackText; // �������� ����
	sf::Sprite Backspr; // ������ ����
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
	int selected_level = 0;
	bool fullscreen = false;
public:
	GameSettings();
	void DrawSettings(sf::RenderWindow &Window); // ��������� ��������� ��������
	void update(sf::RenderWindow &Window); // �������� �������� � ������������ � ��������� ������� �������� � ����� ��������� ������ ���� ��������
	void SetLevelGlobal(sf::RenderWindow &window); // ��������� ������ ��������� ���������
	void IFScreenChanged(sf::RenderWindow &window); // �������� ����� ������ ���� ������ �������������� ���� � ����������
	int IfExitSet(sf::RenderWindow &Window); // ���� ������ ����� ������ � ������� ���� �� �������
};