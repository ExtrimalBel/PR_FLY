#include <SFML\Graphics.hpp>
#include <io.h>
//int level = 0;
void LoadVideoMode(int &x, int &y,sf::Uint32 &st);

// Only for debug
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
#include <iostream>
int main()
{
	try
	{
		MainGameClass::Game GameClass("."); // Создаем основной класс игры
		GameClass.StartDemnedGame(); // Запускает игру цикл обработки событий внутри игры
	}
	catch (Exceptions::GameWantToExit &Ex) // Если требуеться выйти из игры то перехватываем исключение
	{
		Ex.ShowMessage();
		ExitProcess(0); // Корректное завершение игры
		return 0;
	}
	
	return 0;
}