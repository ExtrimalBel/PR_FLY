#pragma once
#include <SFML\Graphics.hpp>
#include <vector>
#include <SoundControl.h>
using namespace sf;
using namespace std;

namespace Ships
{

	struct EnemyNode
	{
		int Type;
		void *EnemyClass;
	};

	struct BaseEnemyState
	{
		int SpawnTime;
		double GunSpeed;
		double BulletSpeed;
		double GunDemage;
		double Speed;
		int Health; 
		vector<pair<int, int>> MovingCoordinates; // Сдесь коориднаты перемещения врага
		string EnemyImgPath; // Путь к текстуре врага
		string EnemyBulletPath;
		string DeathSprPath;
		void InitStats(int Health, double GunSpeed, double GunDemage, double Speed, vector<pair<int, int>> &VectorWithCoord, string EnemyImgPath);
		int FrameCount; // Число кадров в анимации
		double FrameTime; // Время между сменой кадров
		double DeathFrameTime;
		int DeathFrameCount;
		int Reward; // Кол-во денег начисляемых за уничтожение корабля
	};
	class BaseEnemy
	{
	protected:
		Clock GunClock;
		Image EnemyImg;
		Texture EnemyText;
		Sprite EnemySprite;
	
		double cox, coy;
		string BasePath;
		BaseEnemyState EnemyState;
		
		virtual void Move(float time) = 0;
		void Draw(RenderWindow &window);
		SoundControl::SoundControlStruct SndControl;
		void ProcessEnemyAnim();
		bool ForDelete = false;
		int CurrentFrame;
		Clock AnimClock;
		bool DeathAnim;
	public:
		bool IfEnemyDead() { return Health <= 0 ? true : false; }
		void SetForDelete() { ForDelete = true; }
		BaseEnemyState RetrurnEnemyState(){ return EnemyState; }
		Sprite& GetSprite() { return EnemySprite; }
		Image& GetImage() { return EnemyImg; }
		bool IfEnemyShot();
		void LoadEnemyImg();
		
		int Health;
		bool ReturnDeleteState() { return ForDelete; }
		BaseEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
		virtual void Update(float time, RenderWindow &window);
		bool ReturnDeathAnim() { return DeathAnim; }
	};
}