#include "stdafx.h"
#include "BaseEnemy.h"

namespace Ships
{
	BaseEnemy::BaseEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl) : Health(EnemyState.Health) // ¬ дополнение инициализируем ссылку на Health
	{
		this->EnemyState = EnemyState;
		this->cox = cox;
		this->coy = coy;
		this->BasePath = BasePath;
		this->ForDelete = false;
		this->GunClock.restart();
		this->SndControl = SndControl;
	}

	bool BaseEnemy::IfEnemyShot()
	{
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
		sf::Vector2f CenterPos(EnemyText.getSize());
		CenterPos.x /= 2;
		CenterPos.y /= 2;
		EnemySprite.setOrigin(CenterPos);
		EnemySprite.setScale(cox, coy);
	}

	void BaseEnemy::Draw(RenderWindow &window)
	{
		window.draw(EnemySprite);
	}


	void BaseEnemyState::InitStats(int Health,double GunSpeed, double GunDemage, double Speed, vector<pair<int, int>> &VectorWithCoord, string EnemyImgPath)
	{
		this->GunDemage = GunDemage;
		this->GunSpeed = GunSpeed;
		this->Speed = Speed;
		copy(VectorWithCoord.begin(), VectorWithCoord.end(), this->MovingCoordinates.begin());
		this->EnemyImgPath = EnemyImgPath;
		this->Health = Health;
	}
}