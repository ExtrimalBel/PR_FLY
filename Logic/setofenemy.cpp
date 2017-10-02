#include "stdafx.h"

#include "setofenemy.h"
#include <fstream>
#include <iostream>
SetOfEnemy::SetOfEnemy(const char *enemyfilename, double cx, double cy)
{
	EnemyCount = 0;
	std::cout << "cx" << cx;
	cox = cx;
	coy = cy;
	
	std::string inputstr = enemyfilename;
	std::ifstream inputfile;
	inputfile.open(inputstr);
	
	WriteLogFile(enemyfilename);
	
	if (!inputfile) WriteLogFile("error");
	double tmp;
	inputfile >> tmp;
	if (tmp != -1000)
	{
		std::cout << "Syntax error in enemy.txt" << std::endl; // Если не обнаружено клчевое -1000 в начале файла то сигнализировать об ошибке
		WriteLogFile("Syntax error in enemy.txt. Begin -1000 not found");
	}
	
	BeginofEnemy = new EnemyI;
	CurrentEnemy = BeginofEnemy;
	inputfile >> tmp;
	while (tmp != -1003) // Цикл занимаеться анализом файла в котором содержитсья инофрмация о том какие враги должны появиться на определённом уровне
	{
		if (tmp == -1004) addSetOfEnemy(inputfile); // Если обнаружено ключевое слово -1004 то разбирать как "пачку врагов"
		else
		{
			EnemyCount++; // Если добавляем одного врага то инкрементируем счётчик врагов
			CurrentEnemy->time = tmp;
			inputfile >> tmp;
			CurrentEnemy->health = tmp;
			inputfile >> tmp;
			CurrentEnemy->gunspeed;
			inputfile >> tmp;
			CurrentEnemy->speed = tmp;
			inputfile >> tmp;
			CurrentEnemy->demage = tmp;
			CurrentEnemy->enemy = new coord;
			coord *currentcoord = CurrentEnemy->enemy;
			inputfile >> tmp;
			do
			{

				
				currentcoord->x = (tmp * cox);
				inputfile >> tmp;
				currentcoord->y = (tmp * coy);
				currentcoord->next = new coord;
				currentcoord = currentcoord->next;
				inputfile >> tmp;

			} while (tmp != -1001); // Читаем пары координат пока не наткнемся на -1001
			currentcoord->x = -2000; // В конце каждого спіска коордінат есть нода со значением икса -2000 что указывает на конец координат перемещения
			currentcoord = CurrentEnemy->enemy;
		}
		CurrentEnemy->next = new EnemyI;
		CurrentEnemy = CurrentEnemy->next;
		inputfile >> tmp;
	}
	CurrentEnemy->time = 3000;
	EnemyLeft = EnemyCount;
	SortEnemyList(); // Сортируем список пузырём для того чтобы можно было в "с врагами" не беспокоиться о порядке записей
	CurrentEnemy = BeginofEnemy;
	timer.restart();
	std::cout << "Enemy count" << EnemyLeft;
}


void SetOfEnemy::Update(float time,sf::RenderWindow &window) // Общий метод для обновления объекта
{
	//if (CurrentEnemy->time == 3000) return;
	if (timer.getElapsedTime().asSeconds() >= CurrentEnemy->time) 
	{
		if (CurrentEnemy->time != 3000)
		{
			//timer.restart();
			Enemy *TMPEN = new Enemy(cox, coy,CurrentEnemy->health,CurrentEnemy->gunspeed, CurrentEnemy->enemy,CurrentEnemy->speed,CurrentEnemy->demage);
			CurrentEnemy = CurrentEnemy->next;
			SOE.push_back(*TMPEN);
			
		}
	}
	for (std::vector<Enemy>::iterator it = SOE.begin(); it != SOE.end(); it++) // Пересчитываем координаты врагов и отрисовываем их
	{
		it->Move(time);
		it->Draw(window);
	}
	DeleteEnemy();
}

void SetOfEnemy::DeleteEnemy() // Если врага надо удалить то удаляем
{
	for (std::vector<Enemy>::iterator it = SOE.begin(); it != SOE.end(); it++)
	{
		if (it->IsForDelete())
		{
			EnemyLeft--;
			SOE.erase(it);
			return;
		}
	}
}



void SetOfEnemy::addSetOfEnemy(std::ifstream &inputfile) // Создаем "пачку врагов"
{
	coord *Coordofenemy; // Общий указатель на координаты для всех врагов
	coord *BeginOfcoordenemy;

	double count, speed, demage, starttime, dtime,health,gunspeed; // dtime времени для врагов
	inputfile >> count;
	inputfile >> health;
	inputfile >> gunspeed;
	inputfile >> speed;
	inputfile >> demage;
	inputfile >> starttime;
	inputfile >> dtime;
	double startx, starty;
	Coordofenemy = new coord;
	BeginOfcoordenemy = Coordofenemy;
	EnemyCount += count;
	double tmp;
	inputfile >> tmp;
	while (tmp != -1001)
	{
		Coordofenemy->x = (tmp * cox);
		inputfile >> tmp;
		Coordofenemy->y = (tmp * coy);
		Coordofenemy->next = new coord;
		Coordofenemy = Coordofenemy->next;
		inputfile >> tmp;
	}

	Coordofenemy->x = -2000;
	coord *tmpc = BeginOfcoordenemy;
	CurrentEnemy->demage = demage;
	CurrentEnemy->health = health;
	CurrentEnemy->gunspeed = gunspeed;
	CurrentEnemy->speed = speed;
	CurrentEnemy->time = starttime;
	starttime += dtime;
	CurrentEnemy->enemy = BeginOfcoordenemy;
	for (int i = 0; i < count - 1; i++)
	{
		CurrentEnemy->next = new EnemyI;
		CurrentEnemy = CurrentEnemy->next;
		CurrentEnemy->enemy = BeginOfcoordenemy;
		CurrentEnemy->demage = demage;
		CurrentEnemy->speed = speed;
		CurrentEnemy->gunspeed = gunspeed;
		CurrentEnemy->health = health;
		CurrentEnemy->time = starttime;
		starttime += dtime;
	}
}


void SetOfEnemy::SortEnemyList() //  Метод для сортировки списка врагов по времени их появления
{
	EnemyI *tmpEn = BeginofEnemy;
	for (int i = 0; i < EnemyCount; i++)
	{
		while (tmpEn->next->time != 3000)
		{
			if (tmpEn->time > tmpEn->next->time)
			{
				SwapEnemyInList(tmpEn, tmpEn->next,tmpEn);
			}
			else
			{
				tmpEn = tmpEn->next;
			}
		}
		tmpEn = BeginofEnemy;
	}
}


void SetOfEnemy::SwapEnemyInList(EnemyI *First, EnemyI *Second, EnemyI *tmpEn) // Обмен двух нод с врагам в списке
{
	if (First == BeginofEnemy) // Для начала списка отдельный код
	{
		First->next = Second->next;
		Second->next = First;
		BeginofEnemy = Second;
	}
	else
	{
		EnemyI *PFirst = BeginofEnemy;
		while (PFirst->next != First)
		{
			PFirst = PFirst->next;
		}
		EnemyI *PSECOND = Second->next;
		PFirst->next = Second;
		Second->next = First;
		First->next = PSECOND;
	}
}


sf::IntRect GetIntersectRect(sf::IntRect first, sf::IntRect second)
{
	sf::IntRect interrect;
	int count = 0;
	bool tl = false, tr = false, bl = false, br = false;
	if (first.contains(sf::Vector2i(second.left, second.top)))
	{
		count++;
		tl = true;
	}
	if (first.contains(sf::Vector2i(second.left + second.width, second.top)))
	{
		count++;
		tr = true;
	}
	if (first.contains(sf::Vector2i(second.left, second.top + second.height)))
	{
		count++;
		br = true;
	}
	if (first.contains(sf::Vector2i(second.left + second.width, second.top + second.height)))
	{
		count++;
		tl = true;
	}
	if (count == 1)
	{
		if (br && !(tl || tr || bl))
		{
			interrect.top = first.top;
			interrect.left = first.left;
		}
	}
	return interrect;
}


std::vector<Enemy> * SetOfEnemy::ReturnEnemysVector()
{
	return &SOE;
}