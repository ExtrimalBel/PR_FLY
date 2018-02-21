#pragma once
#include "SetOfEnemy.h"
#include "Player.h"
#include "PixelPerfect.h"
#include <SFML\Graphics.hpp>
namespace LevelLogic
{
	class SetOfEnemy;
}

namespace Ships
{
	class Player;
}

using namespace Ships;
using namespace LevelLogic;



namespace InterSects
{
	
	

	class InterSectsMenager
	{
	public:
		static Clock TaranClock;
		static void CountDemageToPlayer(Ships::Player &P, SetOfEnemy &EnemyClass)
		{
			
			for each(Bullet *var in EnemyClass.Bullets)
			{
				if (PixelPerfectCollision(var->GetSprite(), P.GetSprite(), var->GetImage(), P.GetImage()))
				{

					double PlayerDemage = var->GetDemage() * P.Stats.LevelCoo;
					PlayerDemage -= PlayerDemage / 100 *  P.Stats.Armor;
					P.Health -= static_cast<int>(PlayerDemage);
					var->SetDelete(true);
				}
				
			}
			EnemyClass.DeleteBullets();
		}
		static void CountDemageToEnemy(Ships::Player &P, SetOfEnemy &EnemyClass)
		{
			// считаем урон от "лобового столкновения" врага и игрока
			for each(EnemyNode var in EnemyClass.Enemys)
			{
				
				BaseEnemy *TempVar = (BaseEnemy*)(var.EnemyClass);
				if (PixelPerfectCollision(TempVar->GetSprite(), P.GetSprite(), TempVar->GetImage(), P.GetImage()))
				{
					if (!(TempVar->ReturnDeathAnim()) && P.TaranClock.getElapsedTime().asSeconds() > 0.5)
					{
						P.TaranClock.restart();
						double EnemyHealth = TempVar->RetrurnEnemyState().Health;
						TempVar->Health -= EnemyHealth / 100 * 20;
						double DemageToPlayer = (20 - (0.2 * static_cast<double>(P.Stats.Armor))) * P.Stats.LevelCoo;
						P.Health -= DemageToPlayer;
						
					}
				}// Считаем урон от пуль игрока
				for each(Bullet *b in P.PlayerBullets)
				{
					if (PixelPerfectCollision(TempVar->GetSprite(), b->GetSprite(), TempVar->GetImage(), b->GetImage()))
					{
						if (TempVar->ReturnDeathAnim()) continue;
						b->SetDelete(true);
						//TempVar->SetForDelete();
						TempVar->Health -= b->GetDemage();
						if (TempVar->Health <= 0 && !TempVar->ReturnDeathAnim())
						{
							P.Cash += TempVar->RetrurnEnemyState().Reward;
						}
					}
				}
			}
			P.DeletePlayerBullet();
		}
	};
}