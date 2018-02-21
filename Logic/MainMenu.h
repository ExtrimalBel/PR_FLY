#pragma once
#include "BaseMenu.h"
using namespace std;
using namespace sf;
namespace Menus
{
	class LOGIC_API MainMenu : public BaseMenu
	{
		void SetUpText();
	public:
		MainMenu(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, IdOfSounds SndId);
		void Update(RenderWindow &window);
	};
}