#include <SFML\Graphics.hpp>
#include <io.h>
//int level = 0;


// Only for debug
#include "Game.h"
#include "ExceptionsDefenitions.h"
#include <SoundControl.h>
#include <iostream>
#include <Windows.h>
int main(int argv,char*argc[])
{
	SetConsoleCP(1251);
	SetConsoleOutputCP(1251);
	try
	{
		string BasePath;
		if (argv == 2) BasePath = argc[0];
		else BasePath = "./vanilla";

		MainGameClass::Game GameClass(BasePath); // Создаем основной класс игры
		GameClass.StartDemnedGame(); // Запускает игру цикл обработки событий внутри игры
	}
	catch (Exceptions::GameWantToExit &Ex) // Если требуеться выйти из игры то перехватываем исключение
	{
		Ex.ShowMessage();
		ExitProcess(0); // Корректное завершение игры
		return 0;
	}
	catch (Exceptions::SoundSystemError &Ex)
	{
		cout << "Ошибка при работе со звукми:" << Ex.Message << endl;
		ExitProcess(0); // Корректное завершение игры
		return 0;
	}
	
	return 0;
}