#include "stdafx.h"
#include "Settings.h"

namespace Menus
{
	SettingsClass::SettingsClass(string BasePath, double &cox, double &coy, SoundControl::SoundControlStruct &SndControl, int SoundVolume, bool FullScreen)
	{
		this->FullScreen = FullScreen;
		this->BasePath = BasePath;
		this->SndControl = SndControl;
		this->cox = cox;
		this->coy = coy;
		Volume = SoundVolume;
		SetUpSprites();
		SetUpText();
		SetUpResSprites();
		SetUpResolution();
		
		FullScreen = false;
		GameFont.loadFromFile(BasePath + "/menu/font.ttf");
	}

	void SettingsClass::SetUpSprites()
	{
		BackGroundTex.loadFromFile(BasePath + "/menu/settingsback.png");
		BackGroundTex.setSmooth(true);
		BackGroundSpr.setTexture(BackGroundTex);
		BackGroundSpr.setScale(cox, coy);
		SoundVolumeBackImg.loadFromFile(BasePath + "/menu/volumeback.png");
		SoundVolumeBackImg.createMaskFromColor(sf::Color::White);
		SoundVolumeBackTex.loadFromImage(SoundVolumeBackImg);
		SoundVolumeBackTex.setSmooth(true);
		SoundVolumeBackSpr.setTexture(SoundVolumeBackTex);
		SoundVolumeBackSpr.setScale(cox, coy);

		SoundVolumeBackSpr.setPosition(cox * 320,coy * 300);
		SoundVolumeCursorImg.loadFromFile(BasePath + "/menu/volcur.png");
		SoundVolumeCursorImg.createMaskFromColor(Color::White);
		SoundVolumeCursorTex.loadFromImage(SoundVolumeCursorImg);
		SoundVolumeCursorTex.setSmooth(true);
		SoundVolumeCursorSpr.setTexture(SoundVolumeCursorTex);
		SoundVolumeCursorSpr.setOrigin(sf::Vector2f(25, 25));
		SoundVolumeCursorSpr.setScale(cox, coy);
		SoundMuteImage.loadFromFile(BasePath + "/menu/mute.png");
		SoundMuteImage.createMaskFromColor(sf::Color::White);
		
		SoundMuteTexture.loadFromImage(SoundMuteImage);
		SoundMuteTexture.setSmooth(true);
		SoundMuteSprite.setTexture(SoundMuteTexture);
		SoundMuteSprite.setTextureRect(sf::IntRect(0,0,50,50));
		if (SndControl.GetMuteState())
		{
			MuteState = true;
			SoundMuteSprite.setTextureRect(sf::IntRect(50, 0, 50, 50));
		}
		else MuteState = false;
		SoundMuteSprite.setScale(cox, coy);
		SoundMuteSprite.setPosition(410 * cox, 350 * coy);
		LeaveSettingsTex.loadFromFile(BasePath + "/menu/item.png");
		LeaveSettingsTex.setSmooth(true);
		LeaveSettingsSpr.setTexture(LeaveSettingsTex);
		LeaveSettingsSpr.setTextureRect(sf::IntRect(0,0,600,100));
		LeaveSettingsSpr.setPosition(1300 * cox, 810 * coy);
		LeaveSettingsSpr.setScale(cox / 2, coy / 2);
		double newvolumex = 600 * Volume;
		newvolumex /= 100;
		newvolumex += 300;
		SoundVolumeCursorSpr.setPosition( cox * newvolumex, coy * 325);
		FullScreenSprite.setTexture(SoundMuteTexture);
		FullScreenSprite.setPosition(cox * 560, coy * 400);
		if (!FullScreen)
		{
			FullScreenSprite.setTextureRect(sf::IntRect(0, 0, 50, 50));
		}
		else FullScreenSprite.setTextureRect(IntRect(50,0,50,50));
		
		
		FullScreenSprite.setScale(cox, coy);
		SoundVolumeBackTex.setSmooth(true);
		SoundVolumeCursorTex.setSmooth(true);
		SoundMuteTexture.setSmooth(true);
	}

	void SettingsClass::ChangeMuteState(RenderWindow &window)
	{
		sf::Vector2f Mpos(sf::Mouse::getPosition(window));
		if (SoundMuteSprite.getGlobalBounds().contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
		{
			Sleep(300);
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
				window.setMouseCursorVisible(false);
			}
			else
			{
				window.create(sf::VideoMode(vidx, vidy), "PR_FLY", sf::Style::Close);
				window.setMouseCursorVisible(false);
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
		window.draw(FullScreenText);
		window.draw(LeaveSettingsSpr);
		window.draw(LeaveSettingsText);
		for (unsigned int i = 0; i < Rezolutions.size(); i++)
		{
			window.draw(Rezolutions[i].ResolutionBackSpr);
			window.draw(Rezolutions[i].ResolutionText);
		}
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
		SoundVolumeText.setPosition(cox * 270, coy *  250);
		SoundVolumeText.setString("Громкость звуков");
		MuteText.setPosition(cox * 270, coy * 350);
		ResolutionText.setPosition(cox * 270, coy * 450);
		SoundVolumeText.setScale(cox, coy);
		ResolutionText.setScale(cox, coy);
		MuteText.setScale(cox, coy);
		FullScreenText.setFont(GameFont);
		FullScreenText.setScale(cox, coy);
		FullScreenText.setPosition(cox * 270, coy * 400);
		FullScreenText.setString("Полноэкранный режим");
		SoundVolumeText.setFillColor(sf::Color::Green);
		SoundVolumeText.setStyle(Text::Bold);
		MuteText.setFillColor(Color::Green);
		ResolutionText.setFillColor(Color::Green);
		FullScreenText.setFillColor(Color::Green);
		LeaveSettingsText.setFont(GameFont);
		LeaveSettingsText.setScale(cox, coy);
		LeaveSettingsText.setFillColor(sf::Color::Yellow);
		LeaveSettingsText.setPosition(1400 * cox, 815 * coy);
		LeaveSettingsText.setCharacterSize(28);
		LeaveSettingsText.setString("Выход");
	}

	void SettingsClass::SetUpResolution()
	{
		ResolutionBackTex.loadFromFile(BasePath + "/menu/resolution.png");
		//Create Resolution
		int i = 0;
		int ResolutionCollection[8][8] = 
		{
			{800,600},
			{1024,768},
			{1280,1024},
			{1280,720},
			{1366,768},
			{1440,900},
			{1600,900},
			{1920,1080}
		};
		int Startx = 270, Starty = 500;
		while (i < 8)
		{
			Rezolutions.push_back(ResolutionItem());
			auto CurResIt = Rezolutions.end() - 1;
			string ResStr = "";
			char *tmpstr = new char[5];
			itoa(ResolutionCollection[i][0],tmpstr,10);
			ResStr += strcat(tmpstr, "x");
			itoa(ResolutionCollection[i][1], tmpstr, 10);
			ResStr += tmpstr;
			//cout << ResStr << endl;
			CurResIt->ResolutionText.setString(ResStr);
			CurResIt->ResolutionText.setFont(GameFont);
			CurResIt->ResolutionText.setPosition((Startx + 60) * cox,(Starty + 5) * coy);
			CurResIt->ResolutionText.setScale(cox, coy);
			CurResIt->ResolutionBackSpr.setTexture(ResolutionBackTex);
			CurResIt->ResolutionBackSpr.setPosition(Startx * cox, Starty * coy);
			CurResIt->ResolutionBackSpr.setScale(cox, coy);
			CurResIt->x = ResolutionCollection[i][0];
			CurResIt->y = ResolutionCollection[i][1];
			Startx += 300;
			if (i == 3)
			{
				Startx = 270;
				Starty = 600;
			}
			i++;
		}

	}

	void SettingsClass::ProcessResolution(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		for (unsigned int i = 0; i < Rezolutions.size(); i++)
		{
			if (Rezolutions[i].ResolutionBackSpr.getGlobalBounds().contains(Mpos) && Mouse::isButtonPressed(Mouse::Left))
			{
				Sleep(200);
				window.clear();
				
				window.create(sf::VideoMode(Rezolutions[i].x, Rezolutions[i].y), "PR_FLY", FullScreen ? Style::Fullscreen : Style::Close);
				window.setMouseCursorVisible(false);
				cox = (double) Rezolutions[i].x / 1920;
				coy = (double)Rezolutions[i].y / 1080;
				Rezolutions.clear();
				SetUpSprites();
				SetUpText();
				SetUpResolution();

			}
		}
	}

	void SettingsClass::Update(RenderWindow &window)
	{
		CheckIfExit(window);
		UpdateVolume(window);
		ChangeMuteState(window);
		ChangeFullScreenState(window);
		ProcessResolution(window);
		DrawAll(window);
	}
	
	void SettingsClass::CheckIfExit(RenderWindow &window)
	{
		sf::Vector2f Mpos(Mouse::getPosition(window));
		if (LeaveSettingsSpr.getGlobalBounds().contains(Mpos))
		{
			LeaveSettingsSpr.setTextureRect(sf::IntRect(600, 0, 600, 100));
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				int vidx = window.getSize().x;
				int vidy = window.getSize().y;
				throw new Exceptions::SettingsClose("Setitngs Close",vidx,vidy,Volume,MuteState,FullScreen);
			}
		}
		else LeaveSettingsSpr.setTextureRect(sf::IntRect(0, 0, 600, 100));
	}
}