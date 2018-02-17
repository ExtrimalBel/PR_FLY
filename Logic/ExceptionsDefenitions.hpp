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

	class UpgradeFinished : public BaseException
	{
	public:
		UpgradeFinished(string Message) : BaseException(Message) { }
	};

	class GameWantToSave : public BaseException
	{
	public:
		GameWantToSave(string Message) : BaseException(Message) {}
	};
}
 