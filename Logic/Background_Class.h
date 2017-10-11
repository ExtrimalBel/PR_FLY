#include <SFML\Graphics.hpp>
#include <ctime>
#include <vector>
#ifndef BACK_I
#define BACK_I
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
// —десь определил класс отвечающий за фон в игре
// ƒанный класс отрисовывает рандомное колличество линий на экране которые "перемещаютс€" по экрану
class LOGIC_API Back_Menu
{
	int PosLines[12];
	std::vector<sf::Sprite> Lines;
	sf::RectangleShape lin;
	sf::RectangleShape Back_Rec;
	sf::Texture Backtex;
	sf::Clock Up_Clock;
	sf::Texture StarTexture;
	double cox, coy;
protected:
	void Draw(float time, sf::RenderWindow &window);
	void AddLine();
	void MoveLines(float time);
	void DelLines();
public:
	Back_Menu(double cox,double coy);
	void Update(float time,sf::RenderWindow &window);
	
};
#endif