#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
#include <SFML\Audio.hpp>
struct MainMSound
{
	// ���� ������ �������� ����
	sf::SoundBuffer selectbuf;
	bool selectplay = false; // ��� �������������� ���������� ������������ �����
	sf::Sound select;
	// ���� ������� �� ������� ����
	sf::SoundBuffer clickbuf;
	sf::Sound click;
	bool onelement;
	// Background_Sound
	sf::Music back_music;
};