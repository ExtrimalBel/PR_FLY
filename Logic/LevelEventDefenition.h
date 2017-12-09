#pragma once
#include <string>
#include <list>
namespace EnemyEventDef
{
	typedef enum{ BossSpawn, MovingEnemySpawn, MessageShow, StationarEnemySpawn } EventType;
	typedef enum{ LineMove, CircleMove } MoveType;
	typedef enum{ Yes,No } AnimationType;
	typedef enum{Static,Dynamic,None} DeathAnimType;
	struct LevelEvent
	{
		EventType Type;
		void *Data;
	};

	struct MessageEvent
	{
		std::string Message;
	};

	struct SoundMessageEvent
	{
		std::string Message;
		int SoundId;
	};


	struct CoordDef
	{

		MoveType Type;
		int Speed; // �������� ����������� �� ��������� �����
		int x; // �������� ����� ��������
		int y;
		int px; // ������������� ����� ��� ����������� �� ���������
		int py;
	};
	struct EnemyData
	{
		std::list<CoordDef> Coordinates;
		int FirstGunSpeed;
		int SecondGunSpeed;
		int Height;
		int Width;
		int FirstGunDemage;
		int SecondGunDemage;
		AnimationType AnimType;
		std::string PathToEnemyImg;
		std::string DeathAnimPath;
		DeathAnimType DeathType;
		int DeathFrames;
		int AnimFrames;
		float AnimSpeed;
	};
}