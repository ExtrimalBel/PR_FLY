#ifndef THH
#define THH

#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API  SetOfBullets;
class LOGIC_API SetOFEnemy;
class LOGIC_API  player_object;
class Level_Boss;
#include "Player_Class.h"
#include "SetOfBullets.h"
#include "setofenemy.h"
#include "Intersectsmenager.h"
#include "LevelBoss.h"
void RemoveDemageFromPlayers(player_object &Player, SetOfBullets &SetOFB, SetOfEnemy &ENM);

void AddEnemyBullets(SetOfEnemy &SOE, SetOfBullets &SOB);


#endif