#pragma once
#include <string>
#include <iostream>
/*
Сдесь буду определять классы для исключений 
Сами классы должны быть разных типов но работать по одному принципу
Перехват через catch и исправление ошибки вместе с выводом сообщения на экран и в файл
*/
using namespace std;
namespace Exceptions{
	
	class BaseException{
		
		int ErrorCode;
	public:
		std::string Message;
		BaseException(std::string mes)
		{
			Message = mes;
		}
		void ShowMessage()
		{
			std::cout << Message << endl;
		}
		void SetMessage(string mess)
		{
			Message = mess;
		}
	};

	class LevelReadError : public BaseException
	{
	public:
		LevelReadError(std::string mes) : BaseException(mes) {}
	};

	class WrongMenuType : public BaseException	// Генерируется при установлении в меню menuitem не в диапазоне о 1 до 4. При перехвате устанавлівается menuitem в 1
	{
	public:
		WrongMenuType(std::string mes) : BaseException(mes) {}
	};

	class BossConfigReadError : public BaseException // Генерируется когда возникает ошибка при считывании конфига босса
	{
	public:
		BossConfigReadError(std::string mes) : BaseException(mes) {}
	};

	class LOGIC_API SettingsCloseWithoutSave : public BaseException
	{
	public:
		int x;
		int y;
		SettingsCloseWithoutSave(string mes, int x, int y) : BaseException(mes)
		{
			this->x = x;
			this->y = y;
		}
	};
}
