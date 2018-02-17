#include "stdafx.h"
#include "UpgradeClass.h"
namespace LevelLogic
{
	UpgradeScreen::UpgradeScreen(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, int CurrentCash)
	{
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		this->SndControl = SndControl;
		this->CurrentCash = CurrentCash;
		InitialSprites();
		InitialText();
	}

	void UpgradeScreen::InitialSprites()
	{
		// Loading textures
		BackGroundTex.loadFromFile(BasePath + "/upgrade/background.png");
		UpgradeButtonTex.loadFromFile(BasePath + "/upgrade/upbutton.png");
		ButtonTex.loadFromFile(BasePath + "/upgrade/button.png");
		// SetUp sprites
		BackGroundSpr.setTexture(BackGroundTex);
		BackGroundSpr.setScale(cox,coy);
		Button.setTexture(ButtonTex);
		Button.setScale(cox,coy);
		UpgradeButton.setTexture(UpgradeButtonTex);
		UpgradeButton.setScale(cox,coy);

	}

	void UpgradeScreen::InitialText()
	{
		// load game font and assign it for all text objtcts
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		FirstGunSpeedText.setFont(GameFont);
		SecondGunSpeedText.setFont(GameFont);
		FirstGunSpeedValue.setFont(GameFont);
		SecondGunSpeedValue.setFont(GameFont);
		CaptionText.setFont(GameFont);
		ArmorText.setFont(GameFont);
		ArmorValue.setFont(GameFont);
		//Settings string to all text
		FirstGunSpeedText.setString("Скорость основного орудия");
		SecondGunSpeedText.setString("Скорость дополнительного орудия");
		CaptionText.setString("Окно улутшений");
		//TODO set coordinates for text objects
	}

	void UpgradeScreen::Update(float time, RenderWindow &window)
	{

	}

	void UpgradeScreen::CheckIfExit()
	{
		
	}
}