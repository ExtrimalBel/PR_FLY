#ifndef COORD_H
#define COORD_H
struct coord
{
	double x;
	double y;
	coord *next;
};


struct boss_coord
{
	int x;
	int y;
	int position;
	boss_coord *next;
};
struct EnemyI
{
	int health;
	double demage;
	double speed;
	double gunspeed;
	coord* enemy;
	double time;
	EnemyI *next;

};


#endif