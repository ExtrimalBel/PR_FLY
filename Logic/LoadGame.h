#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "BaseMenu.h"
namespace Menus
{
	class LOGIC_API LoadGameMenu : public BaseMenu
	{
		void SetUpText();
	public:
		LoadGameMenu(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct SndControl, IdOfSounds SndId);
		void Update(RenderWindow &window);
	};
}