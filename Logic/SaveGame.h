#pragma once
#include "BaseMenu.h"
#include <SoundControl.h>
#include <SFML\Graphics.hpp>
#include "ExceptionsDefenitions.hpp"
#include "PlayerSaveSlotDef.h"
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
using namespace std;
using namespace sf;

namespace Menus
{
	class LOGIC_API SaveGameMenu : public BaseMenu
	{
		enum{SelectSlot,WarningMsgState} MenuState;
		void SetUpText();
		void ProcessSaveWarningMessage();
		void DrawWarningMessage(RenderWindow &window);
		//Sprites Images and Text for save warning messsage
		Image BackWarningImg;	
		Texture BackWarningTex;
		Sprite BackWarningSpr;
		Texture WarningButton;
		Sprite AcceptButton;
		Sprite CancelButton;
		Text WarningMessage;
		Text OkMessage;
		Text CancelMessage;
		void SetUpWarningMessage();
		void ProcessWarningMessage(RenderWindow &window);
		LoadAndSave::SaveSlot *CurrentSave;
	public:
		SaveGameMenu(string BaseGamePath, double cox, double coy,LoadAndSave::SaveSlot *CurrentSave, SoundControl::SoundControlStruct &SndControl, IdOfSounds SndId);
		void Update(RenderWindow &window);
		
	};
}