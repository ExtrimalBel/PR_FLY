#ifndef EX_H
#define EX_H
#include <string>
#include <iostream>
/*
Сдесь буду определять классы для исключений 
Сами классы должны быть разных типов но работать по одному принципу
Перехват через catch и исправление ошибки вместе с выводом сообщения на экран и в файл
*/
using namespace std;
namespace Exceptions{
	
	class BaseForExceptions{
		std::string Message;
		int ErrorCode;
	public:
		BaseForExceptions(std::string mes)
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

	class LevelReadError : public BaseForExceptions
	{
	public:
		LevelReadError(std::string mes) : BaseForExceptions(mes) {}
	};

	class WrongMenuType : public BaseForExceptions	// Генерируется при установлении в меню menuitem не в диапазоне о 1 до 4. При перехвате устанавлівается menuitem в 1
	{
	public:
		WrongMenuType(std::string mes) : BaseForExceptions(mes) {}
	};

	class BossConfigReadError : public BaseForExceptions // Генерируется когда возникает ошибка при считывании конфига босса
	{
	public:
		BossConfigReadError(std::string mes) : BaseForExceptions(mes) {}
	};
	class SoundSystemError : public BaseForExceptions  // Будет генерироваться в классах звуковой подсистемы. Скорее всего при генерации программа буде завершатсья
	{
	public:
		SoundSystemError(std::string mes) : BaseForExceptions(mes) {}
	};

	class XMLDocumentReadError : public BaseForExceptions
	{
	public:
		XMLDocumentReadError(std::string mes) : BaseForExceptions(mes) {}
	};

	class ImageLoadError : public BaseForExceptions
	{
	public:
		ImageLoadError(std::string mes) : BaseForExceptions(mes) {}
	};

	class UnknownMoveType : public BaseForExceptions
	{
	public:
		UnknownMoveType(std::string mes) : BaseForExceptions(mes) {}
	};
}

#endif