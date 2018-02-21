#pragma once
#include <string>
#include <iostream>
/*
Сдесь буду определять классы для исключений 
Сами классы должны быть разных типов но работать по одному принципу
Перехват через catch и исправление ошибки вместе с выводом сообщения на экран и в файл
*/
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
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
	

	class XmlReadError : public BaseException
	{
	public:
		XmlReadError(string Message) : BaseException(Message) {}
	};
	class LOGIC_API SettingsClose : public BaseException
	{
	public:
		pair<int, int> Resolution;
		int Volume;
		bool Mute;
		bool Fullsreen;
		SettingsClose(string Message,int vidx,int vidy,int Volume,bool Mute,bool Fullscreen) : BaseException(Message) 
		{
			//Settings Resolution
			this->Resolution.first = vidx;
			this->Resolution.second = vidy;
			this->Volume = Volume;
			this->Mute = Mute;
			this->Fullsreen = Fullscreen;
		}
	};

	class LOGIC_API ProcessingEnemyCriticalError : public BaseException
	{
	public:
		ProcessingEnemyCriticalError(string Message) : BaseException(Message) {}
	};

	class ThisIsALastLevel : public BaseException
	{
	public:
		ThisIsALastLevel(string Message) : BaseException(Message) {}
	};

	class LevelMenagerCreateError : public BaseException
	{
	public:
		LevelMenagerCreateError(string Message) : BaseException(Message) {}
	};

	class LevelMenagerReadError : public BaseException
	{
	public:
		LevelMenagerReadError(string Message) : BaseException(Message) { }
	};

	class GameWantToSave : public BaseException
	{
	public:
		GameWantToSave(string Message) : BaseException(Message) {}
	};

	class GameLoadError : public BaseException
	{
	public:
		GameLoadError(string Message) : BaseException(Message) {}
	};

	class GameSaveError : public BaseException
	{
	public:
		GameSaveError(string Message) : BaseException(Message) {}
	};

	class NextLevelRequested : public BaseException // Выбрасываеться при выходе из экрана апгрейда
	{
	public:
		NextLevelRequested(string Message) : BaseException(Message) {}
	};

	class LevelEndEx : public BaseException // Выбрасываеться при завершении уровня
	{
	public:
		bool Pass;
		LevelEndEx(string Message, bool Pass) : BaseException(Message) { this->Pass = Pass; }
	};

	class LevelFailEx : public BaseException // Выбрасываеться если игрок умер
	{
	public:
		LevelFailEx(string Message) : BaseException(Message) {}
	};

	class GameSavedCorrect : public BaseException
	{
	public:
		GameSavedCorrect(string Message) : BaseException(Message) {}
	};

	class SaveCompleteCorrect : public BaseException
	{
	public:
		SaveCompleteCorrect(string Message) : BaseException(Message) {}
	};

	class LOGIC_API GameWantToSwitchToMenu : public BaseException
	{
	public:
		GameWantToSwitchToMenu(string Message) : BaseException(Message) {}
	};

	class GameSaved : public BaseException
	{
	public:
		GameSaved(string Message) : BaseException(Message) {}
	};
}