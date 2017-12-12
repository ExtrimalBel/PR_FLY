#include <SFML\Graphics.hpp>

#include <SoundSystem.h>
#ifndef GameMenu
#define GameMenu
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
#include "BaseMenu.h"
class LOGIC_API MainM : public BaseMenu
{
	
public:
	MainM(double cox,double coy,SoundSystem::SoundPlayer &SPlayer,std::string BasePath);
	void Update(float time,sf::RenderWindow &window);
	void Draw(sf::RenderWindow &window);
	void IfMenuItemSelected(sf::RenderWindow &window);
	sf::Event GetEvent() { return ev; }
	int MenuSelect();
	void SetUpText();
};
#endif