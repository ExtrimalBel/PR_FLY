#include <SFML\Graphics.hpp>
#include <io.h>
//int level = 0;
void LoadVideoMode(int &x, int &y,sf::Uint32 &st);

// Only for debug
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
int main()
{
	try
	{
		MainGameClass::Game GameClass("."); // Создаем основной класс игры
		GameClass.StartDemnedGame();
	}
	catch (Exceptions::GameWantToExit &Ex) // Если требуеться выйти из игры то перехватываем исключение
	{
		Ex.ShowMessage();
		return 0;
	}
	return 0;
}


void LoadVideoMode(int &x,int &y,sf::Uint32 &st)
{
	if (_access("videomode.txt", 0) == -1)
	{
		x = 1280;
		y = 720; 
		return;
	}
	std::ifstream vidstream;
	vidstream.open("videomode.txt");
	int mode = 0;
	vidstream >> mode;
	if (mode == 2) st = sf::Style::Fullscreen;
	else  st = sf::Style::Default;
	vidstream >> x;
	vidstream >> y;
	vidstream.close();
}