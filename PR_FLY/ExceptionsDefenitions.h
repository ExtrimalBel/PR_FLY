#pragma once
#include <string>
#include <iostream>
#include <sstream>
using namespace std;
namespace Exceptions
{
	class BaseForExceptions{
		
		int ErrorCode;
	public:
		std::string Message;
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

	class GameWantToExit : public BaseForExceptions
	{
	public:
		GameWantToExit(std::string mes) : BaseForExceptions(mes) {}
	};

	class GameWantToLoad : public BaseForExceptions
	{
	public:
		int slot;
		GameWantToLoad(int slot) : BaseForExceptions("loading game from slot")
		{
			this->slot = slot;
			ostringstream oss;
			oss << " ";
			oss << slot;
			Message += oss.str();
		}
	};

	class GameWantToStartNew : public BaseForExceptions
	{
	public:
		int diflevel;
		GameWantToStartNew(int diflevel) : BaseForExceptions("Starting new game with level ")
		{
			this->diflevel = diflevel;
			ostringstream oss;
			oss << " ";
			oss << diflevel;
			Message += oss.str();
		}
	};
}