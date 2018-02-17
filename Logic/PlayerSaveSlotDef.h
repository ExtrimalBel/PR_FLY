#pragma once
#include "Player.h"
/*
—десь определена структура описывающа€ "слот сохранени€"
*/
namespace LoadAndSave
{
	struct SaveSlot
	{
		Ships::PlayerStats PStates; // ƒанные о корабле игрока
		int Cash;
		int NextLevel;
	};
}