#pragma once
#include <string>

using namespace std;
namespace Exceptions
{
	class AbnormalException
	{
	public:
		string Message;
		AbnormalException(string Message) { this->Message = Message; }
	};
}