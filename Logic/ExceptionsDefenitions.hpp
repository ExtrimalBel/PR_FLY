#pragma once
#include <string>
#include <iostream>
/*
����� ���� ���������� ������ ��� ���������� 
���� ������ ������ ���� ������ ����� �� �������� �� ������ ��������
�������� ����� catch � ����������� ������ ������ � ������� ��������� �� ����� � � ����
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

	class WrongMenuType : public BaseException	// ������������ ��� ������������ � ���� menuitem �� � ��������� � 1 �� 4. ��� ��������� �������������� menuitem � 1
	{
	public:
		WrongMenuType(std::string mes) : BaseException(mes) {}
	};

	class BossConfigReadError : public BaseException // ������������ ����� ��������� ������ ��� ���������� ������� �����
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

	class NextLevelRequested : public BaseException // �������������� ��� ������ �� ������ ��������
	{
	public:
		NextLevelRequested(string Message) : BaseException(Message) {}
	};

	class LevelEndEx : public BaseException // �������������� ��� ���������� ������
	{
	public:
		bool Pass;
		LevelEndEx(string Message, bool Pass) : BaseException(Message) { this->Pass = Pass; }
	};

	class LevelFailEx : public BaseException // �������������� ���� ����� ����
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