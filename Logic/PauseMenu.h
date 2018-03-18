#pragma once
#include <SFML/Graphics.hpp>
#include "ExceptionsDefenitions.hpp"
#include <string>
#include <SoundControl.h>
using namespace std;
using namespace sf;
namespace LevelLogic
{
	class PauseMenu
	{
		Image BackImage;
		Sprite BackImageSpr;
		Texture BackImageTex;
		Texture ContinueTex;
		Sprite ContinueSpr;
		Texture MainMenuTex;
		Sprite MainMenuSpr;
		Text MainMenuText;
		Font GameFont;
		Text CaptionText;
		void CheckIfContinue(sf::Vector2f Mpos);
		void CheckIfExit(sf::Vector2f Mpos);
		double cox,coy;
		string BasePath;
		SoundControl::SoundControlStruct SndControl;
		void InitText();
		void InitSprites();
		void Draw(RenderWindow &window);
		int ReturnCode = 0;
		void UpdateMenuCursor(RenderWindow &window);
		Texture CursorTex;
		Sprite CursorSpr;
	public:
		PauseMenu(string BasePath, double cox, double coy, RenderWindow &window,SoundControl::SoundControlStruct &SndControl); // Сдесь передаем объект окна для извлечения картинки из текущего буфера
		int ReturnSelectedCode();
		void Update(RenderWindow &window);
	};
}