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
		void Enemy();
	};

	struct BaseEnemyState
	{
		double GunSpeed;
		double GunDemage;
		double Speed;
		int Health; 
		vector<pair<int, int>> MovingCoordinates; // Сдесь коориднаты перемещения врага
		string EnemyImgPath; // Путь к текстуре врага
		void InitStats(int Health,double GunSpeed,double GunDemage,double Speed,vector<pair<int,int>> &VectorWithCoord,string EnemyImgPath);
	};
	class BaseEnemy
	{
	protected:
		Clock GunClock;
		Image EnemyImg;
		Texture EnemyText;
		Sprite EnemySprite;
		Sprite* GetSprite() { return &EnemySprite; }
		Image* GetImage() { return &EnemyImg; }
		double cox, coy;
		string BasePath;
		BaseEnemyState EnemyState;
		BaseEnemyState RetrurnEnemyState(){ return EnemyState; }
		virtual void Move(float time) = 0;
		void Draw(RenderWindow &window);
		SoundControl::SoundControlStruct SndControl;
		bool IfEnemyDead() { Health < 0 ? true : false; }
		bool ForDelete;
	public:
		bool IfEnemyShot();
		void LoadEnemyImg();
		int &Health;
		bool ReturnDeleteState() { return ForDelete; }
		BaseEnemy(string BasePath, double cox, double coy, BaseEnemyState &EnemyState, SoundControl::SoundControlStruct &SndControl);
		virtual void Update(float time, RenderWindow &window) = 0;
	};
}