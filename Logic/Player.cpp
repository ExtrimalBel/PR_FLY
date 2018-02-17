#include "stdafx.h"
#include "Player.h"

namespace Ships
{
	Player::Player(string BasePath, double cox, double coy, SoundControl::SoundControlStruct &SndControl, PlayerStats &Stats, pair<int, int> SndIds)
	{
		this->SndControl = SndControl;
		this->Stats = Stats;
		this->cox = cox;
		this->coy = coy;
		this->FirstShotSoundId = SndIds.first;
		this->SecondShotSoundId = SndIds.second;
		this->BasePath = BasePath;
		PlayerImage.loadFromFile(BasePath + "/player/image.png");
		PlayerTexture.loadFromImage(PlayerImage);
		PlayerTexture.setSmooth(true);
		PlayerSprite.setTexture(PlayerTexture);
		PlayerSprite.setScale(cox, coy);
		PlayerSprite.setPosition(250, 1080 / 2 - PlayerTexture.getSize().y);
		FirstGunClock.restart();
		SecondGunClock.restart();
	}

	void Player::ChangeAnim()
	{

	}

	void Player::Draw(RenderWindow &window)
	{
		window.draw(PlayerSprite);
	}

	void Player::Move(RenderWindow &window) // ѕросто ѕеремещает корабль игрока в соответствии с координатами мышки
	{
		Vector2f Mpos(Mouse::getPosition(window));
		PlayerSprite.setPosition(Mpos.x, Mpos.y);
	}
	// ¬ этом и следующем методе сбрасываем таймеры и возвращаем "истину" если врем€ прошедшее с последненго выстрела превышает скорость между выстрелами
	bool Player::IfFirstGunShot()
	{
		float TimeFromLastShot = FirstGunClock.getElapsedTime().asSeconds();
		if (TimeFromLastShot > Stats.FirstGunSpeed)
		{
			SndControl.Playsnd(FirstShotSoundId, false);
			FirstGunClock.restart();
			return true;
		} return false;
	}

	bool Player::IFSecondGunShot()
	{
		float TimeFromlastShot = SecondGunClock.getElapsedTime().asSeconds();
		if (TimeFromlastShot > Stats.SecondGunSpeed)
		{
			SndControl.Playsnd(SecondShotSoundId, false);
			SecondGunClock.restart();
			Rockets--;
			return true;
		} return false;
	}

	PlayerStats Player::ReturnPlayerStats()
	{
		return Stats;
	}

	void Player::Update(float time, RenderWindow &window)
	{
		Move(window);
		Draw(window);
	}
}