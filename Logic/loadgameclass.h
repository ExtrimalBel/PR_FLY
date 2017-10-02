#ifndef LOADSCREEN_H
#define LOADSCREEN_H
#include "BaseMenu.h"
#include <SoundSystem.h>
#include "PlayerS.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API LoadM : public BaseMenu
{
	char *SaveFile;

public:
	class OverFlow {};
	LoadM(double cox, double coy, SoundSystem::SoundPlayer &SPlayer);
	void Update(float time, sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void IfMenuItemSelected(sf::RenderWindow &window);
	sf::Event GetEvent() { return ev; }
	int MenuSelect();
	void SetUpText();
	char *ReturnSaveFile();
};
#endif