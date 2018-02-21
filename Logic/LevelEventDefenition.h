#pragma once
#include <string>
#include <list>
namespace EnemyEventDef
{
	struct GameOptions
	{
		int vidx;
		int vidy;
		int Volume;
		std::string GameModePath;
		std::string Fullscreen;
	};
	typedef enum{ BossSpawn, MovingEnemySpawn, MessageShow, StationarEnemySpawn } EventType;
	typedef enum{ LineMove, CircleMove, MoveCircle,MoveRandom } MoveType;
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
		int Speed; // Скорость перемещения до следующей точки
		int x; // Конечные точки маршрута
		int y;
		int px; // Промежуточные точки для перемещения по оружности
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