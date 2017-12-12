#ifndef EX_H
#define EX_H
#include <string>
#include <iostream>
/*
����� ���� ���������� ������ ��� ���������� 
���� ������ ������ ���� ������ ����� �� �������� �� ������ ��������
�������� ����� catch � ����������� ������ ������ � ������� ��������� �� ����� � � ����
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

	class WrongMenuType : public BaseForExceptions	// ������������ ��� ������������ � ���� menuitem �� � ��������� � 1 �� 4. ��� ��������� �������������� menuitem � 1
	{
	public:
		WrongMenuType(std::string mes) : BaseForExceptions(mes) {}
	};

	class BossConfigReadError : public BaseForExceptions // ������������ ����� ��������� ������ ��� ���������� ������� �����
	{
	public:
		BossConfigReadError(std::string mes) : BaseForExceptions(mes) {}
	};
	class SoundSystemError : public BaseForExceptions  // ����� �������������� � ������� �������� ����������. ������ ����� ��� ��������� ��������� ���� �����������
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