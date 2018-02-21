#include "stdafx.h"
#include "Player.h"

namespace Ships
{
	Player::Player(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, PlayerStats &Stats, pair<int, int> SndIds,int Cash)
	{
		TaranClock.restart();
		this->Cash = Cash;
		this->SndControl = SndControl;
		this->Stats = Stats;
		this->cox = cox;
		this->coy = coy;
		this->FirstShotSoundId = SndIds.first;
		this->SecondShotSoundId = SndIds.second;
		this->BasePath = BasePath;
		ReadPlayerParams();
		PlayerImage.loadFromFile((BasePath + "/" + this->Stats.ImgPath));
		PlayerTexture.loadFromImage(PlayerImage);
		PlayerTexture.setSmooth(true);
		PlayerSprite.setTexture(PlayerTexture);
		PlayerSprite.setTextureRect(sf::IntRect(0, 0, Stats.Width, Stats.Height));
		PlayerSprite.setScale(cox, coy);
		PlayerSprite.setPosition(250, 1080 / 2 - PlayerTexture.getSize().y);
		FirstGunClock.restart();
		SecondGunClock.restart();
		this->AnimFrame = 0;
		this->DeathAnim = false;
		Health = 100;
		cout << "Roctes" << Rockets;
	}

	void Player::SetDeathAnim(bool value)
	{
		if (DeathAnim) return;
		PlayerTexture.loadFromFile(BasePath + "/" + this->Stats.DeathAnim);
		PlayerSprite.setTexture(PlayerTexture);
		PlayerSprite.setTextureRect(IntRect(0, 0, PlayerTexture.getSize().x / this->Stats.DeathAnimFrameCount, PlayerTexture.getSize().y));
		CurrentFramesInAnim = 0;
		this->DeathAnim = value;
	}

	void Player::ChangeAnim()
	{

	}

	void Player::Draw(RenderWindow &window)
	{
		window.draw(PlayerSprite);
	}

	void Player::Move(RenderWindow &window) // Просто Перемещает корабль игрока в соответствии с координатами мышки
	{
		Vector2f Mpos(Mouse::getPosition(window));
		sf::Vector2i pos = sf::Mouse::getPosition(window);
		int xt, yt;
		xt = pos.x;
		yt = pos.y;
		// Ïðîëâåðÿþ âûøåë ëè êîðàáëü èãðîêà çà ïðåäåëû äèàïàçîíà
		if (pos.x < 100 * cox) xt = 60 * cox;
		if (pos.x > 1780 * cox) xt = 1780 * cox;
		if (pos.y > 980 * coy) yt = 980 * coy;
		if (pos.y < 140 * coy) yt = 140 * coy;
		PlayerSprite.setPosition(sf::Vector2f(xt, yt));
		//sf::Mouse::setPosition(sf::Vector2i(xt,yt));
	}
	// В этом и следующем методе сбрасываем таймеры и возвращаем "истину" если время прошедшее с последненго выстрела превышает скорость между выстрелами
	bool Player::IfFirstGunShot()
	{
		float TimeFromLastShot = FirstGunClock.getElapsedTime().asSeconds();
		if (TimeFromLastShot > Stats.FirstGunSpeed)
		{
			
			FirstGunClock.restart();
			return true;
		} return false;
	}

	bool Player::IFSecondGunShot()
	{
		if (Rockets <= 0) return false; 
		float TimeFromlastShot = SecondGunClock.getElapsedTime().asSeconds();
		if (TimeFromlastShot > Stats.SecondGunSpeed)
		{
			
			SecondGunClock.restart();
			
			return true;
		} return false;
	}

	PlayerStats Player::ReturnPlayerStats()
	{
		return Stats;
	}


	void Player::ProcessAnim(int MaxFrameCount)
	{
		if (AnimClockTimer.getElapsedTime().asSeconds() > Stats.DAnimTime)
		{
			if (DeathAnim && AnimFrame >= MaxFrameCount) return;
			if (AnimFrame >= MaxFrameCount) AnimFrame = 0;
			PlayerSprite.setTextureRect(sf::IntRect(Stats.Width * AnimFrame, 0, Stats.Width, Stats.Height));		
			AnimFrame++;
			AnimClockTimer.restart();
		}
	}

	void Player::ReadPlayerParams()
	{
		string ErrorMessage = "Невозможно прочитать информацию о игроке";
		tinyxml2::XMLDocument xmldoc;
		xmldoc.LoadFile((BasePath + "/playerconfig.xml").c_str());
		tinyxml2::XMLElement *Root = xmldoc.FirstChildElement("Player");
		if (Root == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		tinyxml2::XMLElement *TmpElement = Root->FirstChildElement("PlayerImgPath");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.ImgPath = TmpElement->GetText();
		TmpElement = Root->FirstChildElement("DeathImagePath");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.DeathAnim = TmpElement->GetText();
		TmpElement = Root->FirstChildElement("AnimFrameCount");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.AnimFrameCount = atoi(TmpElement->GetText());
		TmpElement = Root->FirstChildElement("DeathAnimFrameCount");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.DeathAnimFrameCount = atoi(TmpElement->GetText());
		TmpElement = Root->FirstChildElement("AnimDelay");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.DAnimTime = atof(TmpElement->GetText());
		TmpElement = Root->FirstChildElement("Width");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.Width = atoi(TmpElement->GetText());
		TmpElement = Root->FirstChildElement("Height");
		if (TmpElement == NULL) throw Exceptions::XmlReadError(ErrorMessage);
		Stats.Height = atoi(TmpElement->GetText());
	}

	void Player::Update(float time, RenderWindow &window)
	{
		if (DeathAnim)
		{

			ProcessAnim(Stats.DeathAnimFrameCount);
			window.draw(PlayerSprite);
			return;
		}
		ProcessAnim(Stats.AnimFrameCount);
		Move(window);
		Draw(window);
		SpawnPlayerBullet();
		UpdatePlayerBullet(time,window);
		//DeletePlayerBullet();
	}

	void Player::SpawnPlayerBullet()
	{
		sf::Vector2f PlayerPos = PlayerSprite.getPosition();
		sf::FloatRect PlayerParams = PlayerSprite.getGlobalBounds();
		sf::Vector2f BulletPos = PlayerPos;
		BulletPos.x += PlayerParams.width;
		BulletPos.y += PlayerParams.height / 2;
		if (IfFirstGunShot() && sf::Mouse::isButtonPressed(Mouse::Left))
		{
			SndControl.Playsnd(FirstShotSoundId, false);
			PlayerBullets.push_back(new Bullet(BulletPos, cox, coy, (BasePath + "/Images/bullet.png").c_str(), 1, 0.5, Stats.FirstGunDemage));
		}
		if (IFSecondGunShot() && sf::Mouse::isButtonPressed(Mouse::Right) && Rockets > 0)
		{
			cout << "Rockets " << Rockets << endl;
			Rockets--;
			SndControl.Playsnd(SecondShotSoundId, false);
			PlayerBullets.push_back(new Bullet(BulletPos, cox, coy, (BasePath + "/Images/secondbullet.png").c_str(), 1, 1, Stats.SecondGunDemage));
		}
	}

	void Player::DeletePlayerBullet()
	{
		for (unsigned int i = 0; i < PlayerBullets.size(); i++)
		{
			sf::Vector2f BulletPos = PlayerBullets[i]->GetSprite().getPosition();
			if (PlayerBullets[i]->IsForDelete() || BulletPos.x > 1920 * cox)
			{
				PlayerBullets.erase(PlayerBullets.begin() + i);
				if (i != 0) i--;
			}

		}
	}

	void Player::UpdatePlayerBullet(float time, RenderWindow &window)
	{
		//DeletePlayerBullet();
		PlayerBullets.erase(remove_if(PlayerBullets.begin(), PlayerBullets.end(), [](Bullet *B){ return B->IsForDelete(); }), PlayerBullets.end());
		for each(Bullet* b in PlayerBullets)
		{
			
			b->Move(time);
			b->Draw(window);
		}
		
	}
}