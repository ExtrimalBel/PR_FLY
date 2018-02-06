#pragma once
#include <string>
#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
using namespace std;

namespace Exceptions
{
	class SOUNDSYSTEM_API SoundSystemError
	{
	public:
		string Message;
		SoundSystemError(string Message)
		{
			this->Message = Message;
		}
	};
}