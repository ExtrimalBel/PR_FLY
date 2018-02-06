#include "stdafx.h"
#include "BaseMenu.h"

namespace Menus
{
	BaseMenu::BaseMenu(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct SndControl, IdOfSounds SndId)
	{
		this->cox = cox;
		this->coy = coy;
		this->BaseGamePath = BaseGamePath;
		this->SndControl = SndControl;
		this->SndId = SndId;
		MenuTex.loadFromFile(BaseGamePath + "/menu/item.png");
		BackGroundTex.loadFromFile(BaseGamePath + "/menu/background.png");
		FirstMenuSpr.setTexture(MenuTex);
		SecondMenuSpr.setTexture(MenuTex);
		ThirdMenuSpr.setTexture(MenuTex);
		FourMenuSpr.setTexture(MenuTex);
		BackGroundSpr.setTexture(BackGroundTex);
		FirstMenuSpr.setPosition(660 * cox, 200 * coy);
		SecondMenuSpr.setPosition(660 * cox, 350 * coy);
		ThirdMenuSpr.setPosition(660 * cox, 500 * coy);
		FourMenuSpr.setPosition(660 * cox, 650 * coy);
		FirstMenuSpr.setScale(cox, coy);
		SecondMenuSpr.setScale(cox, coy);
		ThirdMenuSpr.setScale(cox, coy);
		FourMenuSpr.setScale(cox, coy);
		BackGroundSpr.setScale(cox, coy);
		SelectedMenuItem = 0;
		FirstMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
		SecondMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
		ThirdMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
		FourMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
	}

	void BaseMenu::Update(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		if (FirstMenuSpr.getGlobalBounds().contains(Mpos))
		{
			if (SelectedMenuItem != 1)
			{
				
				FirstMenuSpr.setTextureRect(sf::IntRect(600, 0, 600, 100));
				SndControl.Playsnd(SndId.SelectId, false);
				SecondMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				ThirdMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				FourMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			}
			SelectedMenuItem = 1;
		}
		else if (SecondMenuSpr.getGlobalBounds().contains(Mpos))
		{
			if (SelectedMenuItem != 2)
			{
				SecondMenuSpr.setTextureRect(sf::IntRect(600, 0, 600, 100));
				SndControl.Playsnd(SndId.SelectId, false);
				FirstMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				ThirdMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				FourMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			}
			SelectedMenuItem = 2;
		}
		else if (ThirdMenuSpr.getGlobalBounds().contains(Mpos))
		{
			if (SelectedMenuItem != 3)
			{
				ThirdMenuSpr.setTextureRect(sf::IntRect(600, 0, 600, 100));
				SndControl.Playsnd(SndId.SelectId, false);
				FirstMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				SecondMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				FourMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			}
			SelectedMenuItem = 3;
		}
		else if (FourMenuSpr.getGlobalBounds().contains(Mpos))
		{
			
			if (SelectedMenuItem != 4)
			{
				FourMenuSpr.setTextureRect(sf::IntRect(600, 0, 600, 100));
				SndControl.Playsnd(SndId.SelectId, false);
				FirstMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				SecondMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
				ThirdMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			}
			SelectedMenuItem = 4;
		}
		else

		{
			FirstMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			SecondMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			ThirdMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			FourMenuSpr.setTextureRect(IntRect(0, 0, 600, 100));
			SelectedMenuItem = 0;
		}
		Draw(window);
	}

	void BaseMenu::Draw(RenderWindow &window)
	{
		window.draw(BackGroundSpr);
		window.draw(FirstMenuSpr);
		window.draw(SecondMenuSpr);
		window.draw(ThirdMenuSpr);
		window.draw(FourMenuSpr);
		window.draw(FirstMenuItemText);
		window.draw(SecondMenuItemText);
		window.draw(ThirdMenuItemText);
		window.draw(FourMenuItemText);
	}

	int BaseMenu::ReturnSelectedCode()
	{
		if (Mouse::isButtonPressed(Mouse::Left) && SelectedMenuItem != 0)
		{
			SndControl.Playsnd(SndId.ClickId, false);
			Sleep(300);
			return SelectedMenuItem;
		}
	
		else return 0;
	}
}
