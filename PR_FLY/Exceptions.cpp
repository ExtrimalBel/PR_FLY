#include "Exceptions.h"

namespace Exceptions
{
	//ћетоды дл€ базового класса
	BasicException::BasicException(std::string Message) { this->Message = Message; }
	std::string BasicException::GetMessage() { return Message; }
	void BasicException::SetMessage(std::string Message) { this->Message = Message; }
	// ƒальше идкт определение конструкторов дл€ производных классов
	FileReadError::FileReadError(std::string Message) : BasicException(Message) {}

	FileNotFoundException::FileNotFoundException(std::string Message) : BasicException(Message) {}
}