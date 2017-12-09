#include "stdafx.h"
#include "BaseForEnemys.h"
#include <iostream>
namespace Enemys
{
	BaseEnemy::BaseEnemy(double cx, double cy, EnemyEventDef::EnemyData &DataStruct)
	{
		/*
		this->demage = demage; // Just for debug
		this->speed = speed;
		this->life = health;
		this->gunspeed = gunspeed;
		lasshot.restart();*/
		// Установкка параметров стрельбы
		this->FirstGunSpeed = DataStruct.FirstGunSpeed;
		this->SecondGunSpeed = DataStruct.SecondGunSpeed;
		this->FirstGunDemage = DataStruct.FirstGunDemage;
		this->SecondGunDemage = DataStruct.SecondGunDemage;
		for_delete = false;
		// Установка параметорв спрайтов и анимации
		this->Heigth = DataStruct.Height;
		this->Width = DataStruct.Width;
		DeathType = DataStruct.DeathType;
		this->AnimType = DataStruct.AnimType;
		cox = cx;
		coy = cy;
		this->EnemyImgPath = DataStruct.PathToEnemyImg;
		this->EnemyDeathPath = DataStruct.DeathAnimPath;
		//copy(st.begin(), st.end() - 1, coordst.begin());
	
	}

	float BaseEnemy::GetTimeFromLastFirstGunShot()
	{
		return FirstGunLastShot.getElapsedTime().asSeconds();
	}

	float BaseEnemy::GetTimeFromLastSecondGunShot()
	{
		return SecondGunLastShot.getElapsedTime().asSeconds();
	}

	void BaseEnemy::ResetClock()
	{
		FirstGunLastShot.restart();
		SecondGunLastShot.restart();
	}

	sf::Vector2f BaseEnemy::GetPostion()
	{
		sf::Vector2f pos = Enemy.getPosition();
		//	pos.y -= enemy.getSize().y / 2;
		return pos;
	}

	void BaseEnemy::RemoveHealth(int health)
	{
		life -= health;
	}
	
	bool BaseEnemy::IsForDelete()
	{
		if (life <= 0)
		{
			for_delete = true;
		}
		return for_delete;
	}

	void BaseEnemy::DeathAnimUpdate(float time, sf::RenderWindow &window)
	{
		float CurrentAnimTime = AnimSpeed.getElapsedTime().asSeconds();
		if (DeathType == EnemyEventDef::Static)
		{
			if (CurrentAnimTime > DeathS)
			{
				for_delete = true;
			}
			return;
		}
		if (DeathType == EnemyEventDef::None)
		{
			for_delete = true;
			return;
		}

		if (AnimFrame >= DeathFrames)
		{
			for_delete = true;
			return;
		}
		if ( CurrentAnimTime > AnimS)
		{
			AnimFrame += 1;
			int x = AnimFrame * Width;
			Enemy.setTextureRect(sf::IntRect(x, 0, Width, Heigth));
			AnimSpeed.restart();
		}
	}

	void BaseEnemy::EnemyAnimUpdate(float time, sf::RenderWindow &window)
	{
		
		if (AnimFrame > AnimFrames)
		{
			AnimFrame = 0;
			
		}
		if (AnimSpeed.getElapsedTime().asSeconds() > AnimS)
		{
			AnimFrame += 1;
			int x = AnimFrame * Width;
			Enemy.setTextureRect(sf::IntRect(x, 0, Width, Heigth));
			AnimSpeed.restart();
		}
	}

	void BaseEnemy::LoadEnemyDeathImage()
	{
		if (!EnemyImg.loadFromFile(EnemyDeathPath)) throw Exceptions::ImageLoadError("Не возможно создать врага");
		EnemyTex.loadFromImage(EnemyImg);
		Enemy.setTexture(EnemyTex);
		int H = Enemy.getLocalBounds().height;
		int W = Enemy.getLocalBounds().width;
		if (Width * DeathFrames < W) throw Exceptions::ImageLoadError("Картинка не корректна");
		if (Heigth > H) throw Exceptions::ImageLoadError("Кортинка не корректна");
		Enemy.setTextureRect(sf::IntRect(0, 0, Width, Heigth));
	}

	void BaseEnemy::LoadEnemyImage()
	{
		if (!EnemyImg.loadFromFile(EnemyImgPath)) throw Exceptions::ImageLoadError("Не возможно создать врага");
		EnemyTex.loadFromImage(EnemyImg);
		Enemy.setTexture(EnemyTex);
		int H = Enemy.getLocalBounds().height;
		int W = Enemy.getLocalBounds().width;
		if (Width * AnimFrames < W) throw Exceptions::ImageLoadError("Картинка не корректна");
		if (Heigth > H) throw Exceptions::ImageLoadError("Кортинка не корректна");
		Enemy.setTextureRect(sf::IntRect(0, 0, Width, Heigth));
	}
}