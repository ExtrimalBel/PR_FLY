#include "stdafx.h"
#include "GameDifficulty.h"

namespace Menus
{
	GameDifficulty::GameDifficulty(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct SndControl, IdOfSounds SndId) : BaseMenu(BaseGamePath, cox, coy, SndControl, SndId)
	{
		SetUpText();
	}

	void GameDifficulty::SetUpText()
	{
		MenuFont.loadFromFile(BaseGamePath + "/menu/font.TTF");
		FirstMenuItemText.setFont(MenuFont);
		FirstMenuItemText.setCharacterSize(48);
		FirstMenuItemText.setScale(cox, coy);
		FirstMenuItemText.setFillColor(sf::Color(178, 34, 34));
		sf::String str = "Низкий";
		FirstMenuItemText.setString(str);
		FirstMenuItemText.setPosition(840 * cox, 220 * coy);


		SecondMenuItemText.setFont(MenuFont);
		SecondMenuItemText.setCharacterSize(48);
		SecondMenuItemText.setScale(cox, coy);
		SecondMenuItemText.setFillColor(sf::Color(178, 34, 34));
		sf::String loadstr = "Средний";
		SecondMenuItemText.setString(loadstr);
		SecondMenuItemText.setPosition(810 * cox, 370 * coy);

		ThirdMenuItemText.setFont(MenuFont);
		ThirdMenuItemText.setCharacterSize(48);
		ThirdMenuItemText.setScale(cox, coy);
		ThirdMenuItemText.setFillColor(sf::Color(178, 34, 34));
		sf::String settingstr = "Сложный";
		ThirdMenuItemText.setString(settingstr);
		ThirdMenuItemText.setPosition(830 * cox, 520 * coy);

		FourMenuItemText.setFont(MenuFont);
		FourMenuItemText.setCharacterSize(48);
		FourMenuItemText.setScale(cox, coy);
		FourMenuItemText.setFillColor(sf::Color(178, 34, 34));
		sf::String exitstr = "Назад";
		FourMenuItemText.setString(exitstr);
		FourMenuItemText.setPosition(850 * cox, 670 * coy);
	}

	void GameDifficulty::Update(RenderWindow &window)
	{
		BaseMenu::Update(window);
	}
}