#include "stdafx.h"
#include "Settings.h"

namespace Menus
{
	SettingsClass::SettingsClass(string BasePath, double &cox, double &coy, SoundControl::SoundControlStruct &SndControl)
	{
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		Volume = 50;
		SetUpSprites();
		SetUpText();
		SetUpResSprites();
		this->SndControl = SndControl;
		FullScreen = false;
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
		SetUpSprites();
		SetUpText();
		SetUpResSprites();
	}

	void SettingsClass::SetUpSprites()
	{
		BackGroundTex.loadFromFile(BasePath + "/menu/background.png");
		BackGroundSpr.setTexture(BackGroundTex);
		BackGroundSpr.setScale(cox, coy);
		SoundVolumeBackImg.loadFromFile(BasePath + "/menu/volumeback.png");
		SoundVolumeBackImg.createMaskFromColor(sf::Color::White);
		SoundVolumeBackTex.loadFromImage(SoundVolumeBackImg);
		SoundVolumeBackSpr.setTexture(SoundVolumeBackTex);
		SoundVolumeBackSpr.setScale(cox, coy);

		SoundVolumeBackSpr.setPosition(cox * 300,coy * 300);
		SoundVolumeCursorImg.loadFromFile(BasePath + "/menu/volcur.png");
		SoundVolumeCursorImg.createMaskFromColor(Color::White);
		SoundVolumeCursorTex.loadFromImage(SoundVolumeCursorImg);
		SoundVolumeCursorSpr.setTexture(SoundVolumeCursorTex);
		SoundVolumeCursorSpr.setOrigin(sf::Vector2f(25, 25));
		SoundVolumeCursorSpr.setScale(cox, coy);
		SoundMuteImage.loadFromFile(BasePath + "/menu/mute.png");
		SoundMuteImage.createMaskFromColor(sf::Color::White);
		SoundMuteTexture.loadFromImage(SoundMuteImage);
		SoundMuteTexture.setSmooth(true);
		SoundMuteSprite.setTexture(SoundMuteTexture);
		SoundMuteSprite.setTextureRect(sf::IntRect(0,0,50,50));
		
		SoundMuteSprite.setScale(cox, coy);
		SoundMuteSprite.setPosition(400 * cox, 350 * coy);
		double newvolumex = 600 * Volume;
		newvolumex /= 100;
		newvolumex += 300;
		SoundVolumeCursorSpr.setPosition( cox * newvolumex, coy * 325);
		FullScreenSprite.setTexture(SoundMuteTexture);
		FullScreenSprite.setPosition(cox * 500, coy * 400);
		FullScreenSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		FullScreenSprite.setScale(cox, coy);
	}

	void SettingsClass::ChangeMuteState(RenderWindow &window)
	{
		sf::Vector2f Mpos(sf::Mouse::getPosition(window));
		if (SoundMuteSprite.getGlobalBounds().contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
		{
			Sleep(200);
			MuteState = !MuteState;
			if (MuteState)
			{
				SndControl.Mute();
				SoundMuteSprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
			}
else
{
	SndControl.UnMute();
	SoundMuteSprite.setTextureRect(sf::IntRect(0,0,50,50));
}
		}

	}


	void SettingsClass::ChangeFullScreenState(RenderWindow &window)
	{
		int vidx, vidy;
		vidx = window.getSize().x;
		vidy = window.getSize().y;
		sf::Vector2f Mpos(sf::Mouse::getPosition(window));
		if (FullScreenSprite.getGlobalBounds().contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
		{
			Sleep(200);
			FullScreen = !FullScreen;
			if (FullScreen)
			{
				FullScreenSprite.setTextureRect(sf::IntRect(50,0, 50, 50));
				window.create(sf::VideoMode(vidx, vidy),"PR_FLY", sf::Style::Fullscreen);
			}
			else
			{
				window.create(sf::VideoMode(vidx, vidy), "PR_FLY", sf::Style::Close);
				FullScreenSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
			}
			SetUpSprites();
			SetUpText();
			SetUpResSprites();
		}
	}
	void SettingsClass::UpdateVolume(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		if (SoundVolumeBackSpr.getGlobalBounds().contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
		{
			SoundVolumeCursorSpr.setPosition(Mpos.x, coy * 325);
			Volume = (Mpos.x / cox - 300) * 100 / (600);
			SndControl.SetVolume(Volume);
		}
	}
	void SettingsClass::DrawAll(RenderWindow &window)
	{
		window.draw(BackGroundSpr);
		window.draw(SoundVolumeText);
		window.draw(SoundVolumeBackSpr);
		window.draw(SoundVolumeCursorSpr);
		window.draw(MuteText);
		window.draw(ResolutionText);
		window.draw(SoundMuteSprite);
		window.draw(FullScreenSprite);
	}

	void SettingsClass::SetUpResSprites()
	{

	}

	void SettingsClass::SetUpText()
	{
		
		SoundVolumeText.setFont(GameFont);
		MuteText.setFont(GameFont);
		ResolutionText.setFont(GameFont);
		ResolutionText.setString("Разрешение экрана");
		ResolutionText.setFillColor(Color::Green);
		MuteText.setString("Без звука");
		SoundVolumeText.setPosition(cox * 250, coy *  250);
		SoundVolumeText.setString("Громкость звуков");
		MuteText.setPosition(cox * 250, coy * 350);
		ResolutionText.setPosition(cox * 250, coy * 450);
		SoundVolumeText.setScale(cox, coy);
		ResolutionText.setScale(cox, coy);
		MuteText.setScale(cox, coy);
		FullScreenText.setFont(GameFont);
		FullScreenText.setString("Полноэкранный режим");
	}

	void SettingsClass::Update(RenderWindow &window)
	{
		UpdateVolume(window);
		ChangeMuteState(window);
		ChangeFullScreenState(window);
		DrawAll(window);
	}
}