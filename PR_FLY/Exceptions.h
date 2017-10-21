#ifndef EXH
#define EXH
/*
� ������ ������ ���������� ���� ���������� ������ ����� ��������� ��� ������ ���������
��� ���� ����������� �� ������ BasicException
��� ����������� ���������� ������ �������� ����� ������� �������� ������������ �� ��������� � ���������� ����������� ������������ ������

*/
#include <fstream>
#include <string>
namespace Exceptions
{
	class BasicException
	{
		std::string Message;
	public:
		BasicException(std::string Message);
		std::string GetMessage();
		void SetMessage(std::string Message);
	};

	class FileNotFoundException : public BasicException
	{
		FileNotFoundException(std::string Message);
	};

	class FileReadError : public BasicException
	{
		FileReadError(std::string Message);
	};

	class SoundSystemError : public BasicException
	{
		SoundSystemError(std::string Message);
	};
}
#endif