#include "stdafx.h"
#include "BaseEnemy.h"

namespace Ships
{
	BaseEnemy::BaseEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : Health(EnemyState.Health) // Â äîïîëíåíèå èíèöèàëèçèðóåì ññûëêó íà Health
	{
		this->EnemyState = EnemyState;
		this->Health = EnemyState.Health;
		this->cox = cox;
		this->coy = coy;
		this->BasePath = BasePath;
		this->ForDelete = false;
		this->GunClock.restart();
		this->SndControl = SndControl;
		this->AnimClock.restart();
		this->CurrentFrame = 0;
		CurrentFrame = 0;
		LoadEnemyImg();
	}

	bool BaseEnemy::IfEnemyShot()
	{
		if (EnemyState.GunSpeed <= 0) return false;
		if (DeathAnim) return false;
		if (GunClock.getElapsedTime().asSeconds() > EnemyState.GunSpeed)
		{
			//SndControl.Playsnd(0, false);
			GunClock.restart();
			return true;
		}
		else return false;
	}

	void BaseEnemy::LoadEnemyImg()
	{
		EnemyImg.loadFromFile(BasePath + "/" + EnemyState.EnemyImgPath);
		EnemyText.loadFromImage(EnemyImg);
		EnemyText.setSmooth(true);
		EnemySprite.setTexture(EnemyText);
		FloatRect SpriteParams = EnemySprite.getGlobalBounds();
		EnemySprite.setScale(cox, coy);
		sf::Vector2f CenterPos(EnemyText.getSize() );
		CenterPos.x /= 2 * this->EnemyState.FrameCount;
		CenterPos.y /= 2;
		EnemySprite.setOrigin(CenterPos);
		int W = SpriteParams.width / EnemyState.FrameCount;
		EnemySprite.setTextureRect(IntRect(0,0,W,SpriteParams.height));
		DeathAnim = false;
		
		
	}

	void BaseEnemy::Draw(RenderWindow &window)
	{
		window.draw(EnemySprite);
	}


	void BaseEnemyState::InitStats(int Health, double GunSpeed, double GunDemage, double Speed, vector<pair<int, int>> &VectorWithCoord, string EnemyImgPath)
	{
		this->GunDemage = GunDemage;
		this->GunSpeed = GunSpeed;
		this->Speed = Speed;
		copy(VectorWithCoord.begin(), VectorWithCoord.end(), this->MovingCoordinates.begin());
		this->EnemyImgPath = EnemyImgPath;
		this->Health = Health;
	}

	void BaseEnemy::ProcessEnemyAnim()
	{
		int TotalFrameCount = 0;
		double FrameTime = 0;
		if (DeathAnim)
		{
			TotalFrameCount = EnemyState.DeathFrameCount;
			FrameTime = EnemyState.DeathFrameTime;
		}
		else
		{
			TotalFrameCount = EnemyState.FrameCount;
			FrameTime = EnemyState.DeathFrameTime;
		}
		FloatRect ShipParams = EnemySprite.getLocalBounds();
		if (AnimClock.getElapsedTime().asSeconds() > FrameTime)
		{
			CurrentFrame++;
			if (CurrentFrame >= TotalFrameCount && DeathAnim) ForDelete = true;
			if (CurrentFrame >= TotalFrameCount) CurrentFrame = 0;
			EnemySprite.setTextureRect(IntRect(ShipParams.width * CurrentFrame, 0, ShipParams.width, ShipParams.height));
			AnimClock.restart();
		}
	}

	void BaseEnemy::Update(float time, RenderWindow &window)
	{
		if (!DeathAnim && this->Health <= 0)
		{
			Vector2f PrevEnemyPosition = EnemySprite.getPosition();
			EnemyText.loadFromFile(BasePath + "/" + EnemyState.DeathSprPath);
			EnemySprite.setTexture(EnemyText);
			EnemySprite.setScale(cox, coy);
			EnemySprite.setTextureRect(IntRect(0,0,EnemyText.getSize().x / EnemyState.DeathFrameCount,EnemyText.getSize().y));
			float NewCenterX = EnemyText.getSize().x / (EnemyState.DeathFrameCount * 2);
			float NewCenterY = EnemyText.getSize().y / 2;
			EnemySprite.setOrigin(NewCenterX, NewCenterY);
			EnemySprite.setPosition(PrevEnemyPosition);
			DeathAnim = true;
			CurrentFrame = 0;
		}
		ProcessEnemyAnim();
	}
}