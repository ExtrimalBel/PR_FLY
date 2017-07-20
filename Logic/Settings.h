#include <SFML/Graphics.hpp>
#include <iostream>
#define LOGIC_API __declspec(dllexport)
class LOGIC_API GameSettings
{
	int level = 0;
	sf::Texture BackText; // Текстура фона
	sf::Sprite Backspr; // Спрайт фона
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
	void DrawSettings(sf::RenderWindow &Window); // Отрисовка элементов настроек
	void update(sf::RenderWindow &Window); // Изменяем элементы в соответствии с выбранным пунктом настроек а также анимируем пункты меню настроек
	void SetLevelGlobal(sf::RenderWindow &window); // Установка уровня сложности глобально
	void IFScreenChanged(sf::RenderWindow &window); // Изменяем режим экрана если выбран соответсвующий пукт в настройках
	int IfExitSet(sf::RenderWindow &Window); // Если выбран пункт выхода в главное меню то выходим
};