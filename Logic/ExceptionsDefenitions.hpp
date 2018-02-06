#pragma once
#include <string>
#include <iostream>
/*
����� ���� ���������� ������ ��� ���������� 
���� ������ ������ ���� ������ ����� �� �������� �� ������ ��������
�������� ����� catch � ����������� ������ ������ � ������� ��������� �� ����� � � ����
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
