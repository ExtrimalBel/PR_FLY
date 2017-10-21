#include "Exceptions.h"

namespace Exceptions
{
	//������ ��� �������� ������
	BasicException::BasicException(std::string Message) { this->Message = Message; }
	std::string BasicException::GetMessage() { return Message; }
	void BasicException::SetMessage(std::string Message) { this->Message = Message; }
	// ������ ���� ����������� ������������� ��� ����������� �������
	FileReadError::FileReadError(std::string Message) : BasicException(Message) {}

	FileNotFoundException::FileNotFoundException(std::string Message) : BasicException(Message) {}
}