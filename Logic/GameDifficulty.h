#pragma once
#include "BaseMenu.h"
using namespace std;
using namespace sf;
namespace Menus
{
	class LOGIC_API GameDifficulty : public BaseMenu
	{
		void SetUpText();
	public:
		GameDifficulty(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct SndControl, IdOfSounds SndId);
		void Update(RenderWindow &window);
	};
}