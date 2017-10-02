#ifndef SND
#define SND
#include <SFML/Audio.hpp>

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
namespace SOUNDSYSTEM
{


	class SoundPlayer
	{


	public:
		static sf::SoundBuffer buffer;
		static sf::Sound select;
		static bool IS_UP;
		static void PlaySound();
	};


}

#endif