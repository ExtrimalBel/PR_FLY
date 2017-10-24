#ifndef EXH
#define EXH
/*
� ������ ������ ���������� ���� ���������� ������ ����� ��������� ��� ������ ���������
��� ���� ����������� �� ������ BasicException
��� ����������� ���������� ������ �������� ����� ������� �������� ������������ �� ��������� � ���������� ����������� ������������ ������

*/
#include <fstream>
#include <string>
#include <iostream>
namespace Exceptions
{
	class BasicException
	{
		std::string Message;
	public:
		BasicException(std::string Message);
		std::string GetMessage();
		void SetMessage(std::string Message);
		void PrintMessage();
	};

	class FileNotFoundException : public BasicException
	{
	public:
		FileNotFoundException(std::string Message);
	};

	class FileReadError : public BasicException
	{
	public:
		FileReadError(std::string Message);
	};

	class SoundSystemError : public BasicException
	{
	public:
		SoundSystemError(std::string Message);
	};

	class WrongMenuItem : public BasicException
	{
	public:
		WrongMenuItem(std::string Message);
	};
}
#endif