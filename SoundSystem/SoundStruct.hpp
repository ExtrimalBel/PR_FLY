#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
#include <SFML\Audio.hpp>
struct MainMSound
{
	// Звук выбора элемента меню
	sf::SoundBuffer selectbuf;
	bool selectplay = false; // Для предотвращения повторного проигрывания звука
	sf::Sound select;
	// Звук нажатия на элемент меню
	sf::SoundBuffer clickbuf;
	sf::Sound click;
	bool onelement;
	// Background_Sound
	sf::Music back_music;
};