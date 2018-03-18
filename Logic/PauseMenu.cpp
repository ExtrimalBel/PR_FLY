#include "stdafx.h"
#include "PauseMenu.h"

namespace LevelLogic
{
	PauseMenu::PauseMenu(string BasePath, double cox, double coy, RenderWindow &window,SoundControl::SoundControlStruct &SndControl)
	{
		//window.setMouseCursorVisible(true);
		this->BackImage = window.capture();
		this->cox = cox;
		this->coy = coy;
		this->BasePath = BasePath;
		this->SndControl = SndControl;
		InitText();
		InitSprites();
		ReturnCode = 0;
		CursorTex.loadFromFile(BasePath + "/Images/cur.png");
		CursorSpr.setTexture(CursorTex);
		CursorSpr.setScale(cox, coy);
		CursorSpr.setOrigin(CursorSpr.getLocalBounds().width, 0);
	}

	void PauseMenu::UpdateMenuCursor(RenderWindow &window)
	{
		Vector2f Mpos(Mouse::getPosition(window));
		CursorSpr.setPosition(Mpos);
		window.draw(CursorSpr);
	}

	void PauseMenu::InitText()
	{
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		CaptionText.setFont(GameFont);
		CaptionText.setPosition(sf::Vector2f(static_cast<float>(900 * cox),static_cast<float>(250 * coy)));
		CaptionText.setString("Пауза");

	}

	void PauseMenu::InitSprites()
	{
		BackImageTex.loadFromImage(BackImage);
		BackImageSpr.setTexture(BackImageTex);
		ContinueTex.loadFromFile(BasePath + "/Images/buttons/pausecon.png");
		ContinueTex.setSmooth(true);
		ContinueSpr.setTexture(ContinueTex);
		ContinueSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		ContinueSpr.setPosition(sf::Vector2f((float)(660 * cox), (float)400 * coy));
		MainMenuTex.loadFromFile(BasePath + "/Images/buttons/pauseexit.png");
		MainMenuTex.setSmooth(true);
		MainMenuSpr.setTexture(MainMenuTex);
		MainMenuSpr.setScale(static_cast<float>(cox), static_cast<float>(coy));
		MainMenuSpr.setPosition(sf::Vector2f(static_cast<float>(660 * cox), static_cast<float>(600 * coy)));
		MainMenuSpr.setTextureRect(IntRect(0,0,600,100));
		ContinueSpr.setTextureRect(IntRect(0,0,600,100));

	}

	void PauseMenu::Draw(RenderWindow &window)
	{
		window.draw(BackImageSpr);
		window.draw(CaptionText);
		window.draw(ContinueSpr);
		window.draw(MainMenuSpr);
	}

	void PauseMenu::CheckIfContinue(sf::Vector2f Mpos)
	{
		if (ContinueSpr.getGlobalBounds().contains(Mpos))
		{
			ContinueSpr.setTextureRect(IntRect(600, 0, 600, 100));
			if (ReturnCode != 1)SndControl.Playsnd(1, false);
			ReturnCode = 1;
		}
		else
		{
			if (ReturnCode != 2)ReturnCode = 0;
			ContinueSpr.setTextureRect(IntRect(0, 0, 600, 100));
		}
	}

	void PauseMenu::CheckIfExit(sf::Vector2f Mpos)
	{
		if (MainMenuSpr.getGlobalBounds().contains(Mpos))
		{
			MainMenuSpr.setTextureRect(IntRect(600, 0, 600, 100));
			if (ReturnCode != 2)SndControl.Playsnd(1, false);
			ReturnCode = 2;
		}
		else
		{
			if(ReturnCode != 1)ReturnCode = 0;
			MainMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
		}
	}

	void PauseMenu::Update(RenderWindow &window)
	{
		Vector2f Mpos(Mouse::getPosition(window));
		CheckIfExit(Mpos);
		CheckIfContinue(Mpos);
		Draw(window);
		UpdateMenuCursor(window);
	}

	int PauseMenu::ReturnSelectedCode()
	{
		if (Mouse::isButtonPressed(Mouse::Left) && ReturnCode != 0)
		{
			SndControl.Playsnd(0, false);
			return ReturnCode;
		}
		else return 0;
	}
}