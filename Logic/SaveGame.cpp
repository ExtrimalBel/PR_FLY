#include "stdafx.h"
#include "SaveGame.h"

namespace Menus
{
	SaveGameMenu::SaveGameMenu(string BaseGamePath, double cox, double coy, LoadAndSave::SaveSlot *CurrentSave, SoundControl::SoundControlStruct &SndControl, IdOfSounds SndId) : BaseMenu(BaseGamePath, cox, coy, SndControl, SndId)
	{
		SetUpText();
		MenuState = SelectSlot;
		this->CurrentSave = CurrentSave;
	}

	void SaveGameMenu::SetUpText()
	{
		MenuFont.loadFromFile(BaseGamePath + "/menu/font.TTF");
		FirstMenuItemText.setFont(MenuFont);
		FirstMenuItemText.setCharacterSize(48);
		FirstMenuItemText.setScale(cox, coy);
		//FirstMenuItemText.setFillColor(sf::Color::Yellow);
		FirstMenuItemText.setFillColor(sf::Color::Yellow);
		sf::String str = " Слот 1";
		FirstMenuItemText.setString(str);
		FirstMenuItemText.setPosition(840 * cox, 220 * coy);


		SecondMenuItemText.setFont(MenuFont);
		SecondMenuItemText.setCharacterSize(48);
		SecondMenuItemText.setScale(cox, coy);
		SecondMenuItemText.setFillColor(sf::Color::Yellow);
		sf::String loadstr = "Слот 2";
		SecondMenuItemText.setString(loadstr);
		SecondMenuItemText.setPosition(810 * cox, 370 * coy);

		ThirdMenuItemText.setFont(MenuFont);
		ThirdMenuItemText.setCharacterSize(48);
		ThirdMenuItemText.setScale(cox, coy);
		ThirdMenuItemText.setFillColor(sf::Color::Yellow);
		sf::String settingstr = "Слот 3";
		ThirdMenuItemText.setString(settingstr);
		ThirdMenuItemText.setPosition(830 * cox, 520 * coy);

		FourMenuItemText.setFont(MenuFont);
		FourMenuItemText.setCharacterSize(48);
		FourMenuItemText.setScale(cox, coy);
		FourMenuItemText.setFillColor(sf::Color::Yellow);
		sf::String exitstr = "Выход";
		FourMenuItemText.setString(exitstr);
		FourMenuItemText.setPosition(850 * cox, 670 * coy);

		WarningMessage.setFont(MenuFont);
		WarningMessage.setCharacterSize(48);
		WarningMessage.setScale(cox, coy);
		WarningMessage.setFillColor(sf::Color::Yellow);
		// Строка устанавливаеться при выводе сообщения
		OkMessage.setFont(MenuFont);
		OkMessage.setCharacterSize(40);
		OkMessage.setScale(cox, coy);
		OkMessage.setFillColor(sf::Color::Yellow);
		OkMessage.setString("Да");
		OkMessage.setPosition(sf::Vector2f(840,630));
		CancelMessage.setFont(MenuFont);
		CancelMessage.setCharacterSize(40);
		CancelMessage.setScale(cox, coy);
		CancelMessage.setFillColor(Color::Yellow);

	}

	void SaveGameMenu::ProcessWarningMessage(RenderWindow &window)
	{
		sf::FloatRect AcceptButtonRect = AcceptButton.getGlobalBounds();
		sf::FloatRect CancelButtonRect = CancelButton.getGlobalBounds();
		sf::Vector2f Mpos(Mouse::getPosition(window));
		if (AcceptButtonRect.contains(Mpos)  && Mouse::isButtonPressed(Mouse::Left))
		{
			SndControl.Playsnd(SndId.ClickId, false);
			throw Exceptions::SaveCompleteCorrect("Выбран слот сохранения " + SelectedMenuItem);
		}
		if (CancelButtonRect.contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
		{
			SndControl.Playsnd(SndId.ClickId,false);
			MenuState = SelectSlot;
		}
	}

	void SaveGameMenu::Update(RenderWindow &window)
	{
		Draw(window);
		//BaseMenu::Update(window);
		int ClickedMenuItem = BaseMenu::ReturnSelectedCode();
		switch (MenuState)
		{
		case SelectSlot:
			BaseMenu::Update(window);
			
			if (ClickedMenuItem >= 1 && ClickedMenuItem < 4)
			{
				LoadAndSave::SaveToFile(*CurrentSave, BaseGamePath, SelectedMenuItem);
				//MenuState = WarningMsgState;
				throw Exceptions::GameSaved("");
			}
			
			break;
		case WarningMsgState:
			BaseMenu::Draw(window);
			ProcessWarningMessage(window);
			break;
		default:
			break;
		}
		
	}

	void SaveGameMenu::DrawWarningMessage(RenderWindow &window)
	{
		
	}

	void SaveGameMenu::SetUpWarningMessage()
	{
		BackWarningImg.loadFromFile(BaseGamePath + "/menu/warningback.png");
		BackWarningImg.createMaskFromColor(Color::White);
		BackWarningTex.loadFromImage(BackWarningImg);
		BackWarningTex.setSmooth(true);
		BackWarningSpr.setTexture(BackGroundTex);
		BackWarningSpr.setScale(cox, coy);
		WarningButton.loadFromFile(BaseGamePath + "/menu/warningbutton.png");
		AcceptButton.setTexture(WarningButton);
		AcceptButton.setScale(cox, coy);
		AcceptButton.setTextureRect(sf::IntRect(0, 0, 100, 50));
		AcceptButton.setPosition(sf::Vector2f(800 * cox, 620 * cox));
		CancelButton.setTexture(WarningButton);
		CancelButton.setScale(cox, coy);
		CancelButton.setTextureRect(sf::IntRect(0, 0, 100, 50));
		CancelButton.setPosition(sf::Vector2f(1100 * cox, 620 * coy));
	}

}