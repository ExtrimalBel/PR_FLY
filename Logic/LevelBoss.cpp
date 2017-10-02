#include "stdafx.h"
#include "LevelBoss.h"

Level_Boss::Level_Boss(char *pathtofile, double cox, double coy)
{ 
	// сбрасываем таймеры оружия босса
	FirstBulletClock.restart();
	SecondBulletClock.restart();
	this->cox = cox;
	this->coy = coy;
	inputfile.open(pathtofile);
	if (!inputfile)
	{
		WriteLogFile("Boss data not opened");
	}

	double tmp; // Временная переменная для чтения данных
	inputfile >> tmp;
	if ((int)tmp != -1000) WriteLogFile("Syntax error in boss config file. Mission opening keyword");
	char imgpath[100];
	inputfile >> imgpath;
	bossimg.loadFromFile(imgpath);
	bosstex.loadFromImage(bossimg);
	bossprite.setTexture(bosstex);
	bossprite.setScale(cox, coy);
	inputfile >> tmp;
	this->demage = tmp;
	inputfile >> tmp;
	this->speed = tmp;
	inputfile >> tmp;
	this->fgunspeed = tmp;
	inputfile >> tmp;
	fguninterval = tmp;
	inputfile >> tmp;
	this->sgunspeed = tmp;
	inputfile >> tmp;
	sguninterval = tmp;
	inputfile >> tmp;
	this->health = tmp;
	char buf[10];
	inputfile >> buf;
	if (!strcmp(buf,"random")) this->TypeOfMoving = 1;
	else if (!strcmp(buf,"circle")) this->TypeOfMoving = 2;
	else
	{
		WriteLogFile("Unknown Moving Type");
		this->TypeOfMoving = 0;
	}
	MakeCoordList(); // Создадим список из координат по которым может перемещатсья босс))
	currentnumber = 1;
	bossprite.setPosition(Coordinates->x, Coordinates->y);
	Is_Moving = false;
	bllettext.loadFromFile("./img/bullets/bullet.png");
	bossprite.setRotation(180);
	for_delete = false;
}

int Level_Boss::MakeCoordList()
{
	maxnumber = 0;
	// Make first element
	boss_coord *Current_Coord = Coordinates;
	Current_Coord = new boss_coord;
	Coordinates = Current_Coord;
	int number = 1; // Номер элемента списка
	double tmp;
	inputfile >> tmp;
	while ((int)tmp != -1001)
	{
		Current_Coord->position = number;
		number++;
		Current_Coord->x = (int)(tmp * cox);
		inputfile >> tmp;
		Current_Coord->y = (int)(tmp * coy);
		maxnumber++;
		Current_Coord->next = new boss_coord;
		Current_Coord = Current_Coord->next;
		inputfile >> tmp;
	}
#ifdef _DEBUG
	char bf[10];
	itoa(maxnumber, bf, 10);
	WriteLogFile(bf);
#endif
	Current_Coord->next = Coordinates;
	return 0;
}

boss_coord * Level_Boss::FindNumberInList(int number)
{
	boss_coord *Current = Coordinates;
	if (Current->position == number) return Current;
	do
	{
		Current = Current->next;
	} while (Current->position != number);
	return Current;
}

int Level_Boss::Move(float time)
{
	if (TypeOfMoving == 1) MoveRandom(time);
	else if (TypeOfMoving == 2) MoveCircle(time);
	else
	return -1;
	return 0;
}

void Level_Boss::MoveRandom(float time)
{
	if (!Is_Moving)
	{
		currentnumber = 1 + rand() % maxnumber;
		boss_coord *Number = FindNumberInList(currentnumber);
		nextx = Number->x;
		nexty = Number->y;
		Is_Moving = true;
	}
	sf::Vector2f playerpos = CountNextPoint(time);
	bossprite.setPosition(playerpos.x, playerpos.y);
	if (IfPointReached(playerpos)) Is_Moving = false;
}

void Level_Boss::MoveCircle(float time)
{
	if (!Is_Moving)
	{
		currentnumber++;
		if (currentnumber > maxnumber) currentnumber = 1;
		Is_Moving = true;
		boss_coord *Number = FindNumberInList(currentnumber);
		nextx = Number->x;
		nexty = Number->y;
	}
	sf::Vector2f playerpos = CountNextPoint(time);
	bossprite.setPosition(playerpos.x, playerpos.y);
	if (IfPointReached(playerpos)) Is_Moving = false;

}

sf::Vector2f Level_Boss::CountNextPoint(float time)
{
	int xn, yn;
	int x1 = bossprite.getPosition().x;
	int y1 = bossprite.getPosition().y;
	sf::Vector2f direction = sf::Vector2f(nextx, nexty) - bossprite.getPosition();
	float magnitude = std::sqrt((direction.x * direction.x) + (direction.y * direction.y));
	sf::Vector2f unitVector(direction.x / magnitude, direction.y / magnitude);
	unitVector = unitVector * time * (float)speed;
	sf::Vector2f playerpos = bossprite.getPosition();
	playerpos = playerpos + unitVector;
	return playerpos;
}

bool Level_Boss::IfPointReached(sf::Vector2f playerpos)
{
	if ((nextx - 4 < playerpos.x && nextx + 4 > playerpos.x) && (nexty - 4 < playerpos.y && nexty + 4 > playerpos.y))
	{
		return true;
	}
	else return false;
}


void Level_Boss::Update(float time, sf::RenderWindow &window)
{
	Move(time);
	Draw(window);
	Shot();
	MoveBullets(time);
	DrawBullets(window);
	if (health <= 0) for_delete = true;
}

void Level_Boss::Draw(sf::RenderWindow &window)
{
	window.draw(bossprite);
}


int Level_Boss::Shot()
{
	if (FirstBulletClock.getElapsedTime().asSeconds() > fguninterval) // Если интервал стельбы из главного оружия преввыщен то стреляем
	{
		FirstBulletClock.restart();
		FirstGunShot();
	}
	if (SecondBulletClock.getElapsedTime().asSeconds() > sguninterval) // Тоже только для второго
	{
		SecondBulletClock.restart();
		SecondGunShot();
	}
	return 0;
}

int Level_Boss::FirstGunShot()
{
	// Рассчитываем координаты появления пули 
	sf::Vector2f playerpos = bossprite.getPosition();
	sf::Vector2f posbullet;
	posbullet.x = playerpos.x - bossprite.getLocalBounds().width;
	posbullet.y = playerpos.y - (bossprite.getLocalBounds().height / 2);
	Bullet *B = new Bullet(posbullet, cox, coy, bllettext, 2, fgunspeed, demage);
	SetofFBullet.push_back(*B);
	return 0;
}

int Level_Boss::SecondGunShot()
{
	sf::Vector2f playerpos = bossprite.getPosition();
	sf::Vector2f posbullet;
	posbullet.x = playerpos.x - bossprite.getLocalBounds().width;
	posbullet.y = playerpos.y - (bossprite.getLocalBounds().height / 2);
	SetofSBullet.push_back(Bullet(posbullet, cox, coy, bllettext, 2, sgunspeed, demage));
	return 0;
}

void Level_Boss::MoveBullets(float time)
{
	for (std::vector<Bullet>::iterator it = SetofFBullet.begin(); it != SetofFBullet.end(); it++)
	{
		it->Move(time);
	}
	for (std::vector<Bullet>::iterator it = SetofSBullet.begin(); it != SetofSBullet.end(); it++)
	{
		it->Move(time);
	}
}

void Level_Boss::DrawBullets(sf::RenderWindow &window)
{
	for (std::vector<Bullet>::iterator it = SetofFBullet.begin(); it != SetofFBullet.end(); it++)
	{
		it->Draw(window);
	}
	for (std::vector<Bullet>::iterator it = SetofSBullet.begin(); it != SetofSBullet.end(); it++)
	{
		it->Draw(window);
	}
}





void Level_Boss::DeleteBullets()
{
	int i = 0;
	for (; i < SetofFBullet.size();i++)
	{
		if (SetofFBullet[i].IsForDelete())
		{
			SetofFBullet.erase(SetofFBullet.begin() + i);
			i--;
		}
	}
	i = 0;
	for (; i < SetofSBullet.size(); i++)
	{
		if (SetofSBullet[i].IsForDelete())
		{
			SetofSBullet.erase(SetofSBullet.begin() + i);
			i--;
		}
	}
}