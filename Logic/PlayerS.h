#ifndef PLAYERS_H
#define PLAYERS_H
struct PStatements{
	int life; // Коэффициент уменьшения жизни
	int health; // Здоровье
	int engine; // Движок тип
	int gun; // Тип оружия
	int gunspeed; // Скорость стрельбы
	int fuel; // Кол-во топлива
	int fuelco; // Коэффициент уменьшения топлива
	int energy; // Энергия
	int energyco; // Коэффициент увеличения энергии
	int body; // Тип корпуса
};
#endif
