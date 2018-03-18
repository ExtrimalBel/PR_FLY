#include "stdafx.h"
#include "SetOfEnemy.h"

namespace LevelLogic
{
	bool SortEnemyConfigs(pair<Ships::BaseEnemyState, int> &str1, pair<Ships::BaseEnemyState, int> &str2);
	SetOfEnemy::SetOfEnemy(string BasePath, double cox, double coy, vector<pair<Ships::BaseEnemyState, int>> &EnemysConfigs, SoundControl::SoundControlStruct &SndControl) : SndControl(SndControl)
	{
		this->BasePath = BasePath;
		this->cox = cox;
		this->coy = coy;
		this->EnemySVector.resize(EnemysConfigs.size());
		copy(EnemysConfigs.begin(), EnemysConfigs.end(), this->EnemySVector.begin()); // Копируем конфиги врагов
		sort(this->EnemySVector.begin(), this->EnemySVector.end(), SortEnemyConfigs);
		SetClock.reset();
		SetClock.resume();
		this->EndOfEnemys = false;
		ConfigIt = this->EnemySVector.begin();
		EnemyTotalCount = EnemySVector.size(); // Колво врагов это размер вектора с врагами
		DeletedEnemy = 0;
	}

	void SetOfEnemy::UpdateEnemys(float time, RenderWindow &window)
	{
		for each (Ships::EnemyNode var in Enemys)
		{
			Ships::BaseEnemy *PointerToEnemy = static_cast<Ships::BaseEnemy *>(var.EnemyClass);
			PointerToEnemy->Update(time, window);
		}


	}

	void SetOfEnemy::ProcessEnemysShots()
	{
		for each(Ships::EnemyNode var in Enemys)
		{
			Ships::BaseEnemy *TempEnemy = (Ships::BaseEnemy*)var.EnemyClass;
			if (TempEnemy->IfEnemyShot())
			{
				
				// Расситывем позицию пули
				Sprite *EnemySprite = &TempEnemy->GetSprite();
				const sf::Vector2f EnemyPosition = EnemySprite->getPosition();
				const sf::FloatRect EnemySize = EnemySprite->getGlobalBounds();
				sf::Vector2f BulletPosition;
				BulletPosition.x = EnemyPosition.x - (EnemySize.width / 2);
				BulletPosition.y = EnemyPosition.y;
				const Ships::BaseEnemyState EnemyState = TempEnemy->RetrurnEnemyState();
				string Path = BasePath + "/" + EnemyState.EnemyBulletPath;
				
				Bullets.push_back(new Bullet(BulletPosition, cox, coy, Path.c_str(), 2, EnemyState.BulletSpeed, EnemyState.GunDemage));
			}
		}
	}

	void SetOfEnemy::SpawnNewEnemy()
	{
		float SpendTime = SetClock.getElapsedTime().asSeconds(); // Время прошедшее с момента создания объекта
		if (ConfigIt == EnemySVector.end()) return;
 		if (ConfigIt->first.SpawnTime > SpendTime) return; // Выходим если не пришло время создания врагов))
		Ships::EnemyNode TmpNode;
		//SetClock.reset();
		//SetClock.resume();
		TmpNode.Type = ConfigIt->second;
		switch (ConfigIt->second)
		{
		case 1:
			TmpNode.EnemyClass = (void*)new Ships::MovingEnemy(BasePath, cox, coy, (Ships::BaseEnemyState)ConfigIt->first, SndControl);
			break;
		case 2:
			TmpNode.EnemyClass = (void*) new Ships::StayEnemy(BasePath, cox, coy, (Ships::BaseEnemyState)ConfigIt->first, SndControl);
			break;
		case 3:
			TmpNode.EnemyClass = (void*) new Ships::RandomMovingEnemy(BasePath, cox, coy, (Ships::BaseEnemyState)ConfigIt->first, SndControl);
		default:
			throw Exceptions::ProcessingEnemyCriticalError("Критическая ошибка при работе с классами врагов");
			break;
		}
		if(ConfigIt != EnemySVector.end())ConfigIt++;
		Enemys.push_back(TmpNode);
	}

	void SetOfEnemy::DeleteEnemys()
	{
		for (unsigned int i = 0; i < Enemys.size();i++)
		{
			Ships::BaseEnemy *BaseEnemy = (Ships::BaseEnemy*)(Enemys[i].EnemyClass);
			if (BaseEnemy->ReturnDeleteState())
			{
				DeletedEnemy++;
				Enemys.erase(Enemys.begin() + i);
				if (i != 0) i--;
			}
		}
	}

	void SetOfEnemy::UpdateBullets(float time, RenderWindow &window)
	{
		DeleteBullets(); // Удалаяем пули до их обновления или будут заходы на спрайт игрока
		for each(Bullet *var in Bullets)
		{

			var->Move(time);
			var->Draw(window);
		}
		
	}

	void SetOfEnemy::Update(float time, RenderWindow &window)
	{
		UpdateBullets(time, window);
		DeleteEnemys();
		UpdateEnemys(time, window);
		ProcessEnemysShots();
		SpawnNewEnemy();
		
		
		if (ConfigIt == EnemySVector.end()) EndOfEnemys = true;
	}

	void SetOfEnemy::DeleteBullets()
	{
		for (unsigned int i = 0; i < Bullets.size(); i++)
		{
			sf::Vector2f BulletPosition = Bullets[i]->GetSprite().getPosition();
			if (Bullets[i]->IsForDelete() || BulletPosition.x < 0 || BulletPosition.y < 0)
			{
				Bullets.erase(Bullets.begin() + i);
				if (i != 0) i--;
			}
			
		}
	}

}