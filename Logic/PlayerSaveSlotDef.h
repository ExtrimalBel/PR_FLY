#pragma once
#include "Player.h"
/*
����� ���������� ��������� ����������� "���� ����������"
*/
namespace LoadAndSave
{
	struct SaveSlot
	{
		Ships::PlayerStats PStates; // ������ � ������� ������
		int Cash;
		int NextLevel;
	};
}