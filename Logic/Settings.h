#pragma once
#include "ExceptionsDefenitions.hpp"
#include <SFML\Graphics.hpp>
#include <string>
#include <iostream>
#include <SoundControl.h>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif

using namespace sf;
using namespace std;

namespace Menus
{

	struct ResolutionItem
	{
		int x;
		int y;
		Text ResolutionText;
		Sprite ResolutionBackSpr;
	};
	class LOGIC_API SettingsClass
	{
		// Определение текстур и спрайтов
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		Image SoundVolumeBackImg;
		Texture SoundVolumeBackTex;
		Sprite SoundVolumeBackSpr;
		Image SoundVolumeCursorImg;
		Texture SoundVolumeCursorTex;
		Sprite SoundVolumeCursorSpr;
		Image SoundMuteImage;
		Texture SoundMuteTexture;
		Sprite SoundMuteSprite;
		Sprite FullScreenSprite;
		Texture ResolutionBackTex;
		// Определение текста
		Font GameFont;
		Text SoundVolumeText;
		Text MuteText;
		Text ResolutionText;
		Text FullScreenText;
		vector<ResolutionItem> Rezolutions;
		ResolutionItem CurrentResolution;
		SoundControl::SoundControlStruct SndControl;
		string BasePath;
		void SelectResolution();
		void SelectSoundParams();
		void SetUpText();
		void SetUpSprites();
		void SetUpResSprites();
		void DrawAll(RenderWindow &window);
		void UpdateVolume(RenderWindow &window);
		void ChangeMuteState(RenderWindow &window);
		void ChangeFullScreenState(RenderWindow &window);
		double cox, coy;
		Texture ButtonTex;
		Sprite AcceptButtonSpr;
		Texture CancelButtonSpr;
		int Volume;
		bool MuteState = false;
		bool FullScreen;
	public:
		SettingsClass(string BasePath, double &cox, double &coy, SoundControl::SoundControlStruct &SndControl);
		void Update(RenderWindow &window);
	};
}