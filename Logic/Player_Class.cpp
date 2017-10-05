#include "stdafx.h"
#include "Player_Class.h"
#include <iostream>
PlayerO::PlayerO(int x, int y, double shapecox,double shapecoy,bool Isnew)
{
	fireclock.restart();
	this->x = x * shapecox;
	this->y = y * shapecoy;
	this->shapecox = shapecox;
	this->shapecoy = shapecoy;
	//Body.setSize(sf::Vector2f(defsizex, defsizey));
	Gun.setSize(sf::Vector2f(defsizex, defsizey));
	Engine.setSize(sf::Vector2f(defsizex, defsizey));
	// Если игра начинаеться сначала то установить "дефолтные координаты корабля"
	if (!LoadFile(Isnew, NULL))
	//if (true)
	{
		State.energy = 1;
		State.energyco = 1.1;
		State.engine = 1;
		State.fuel = 100;
		State.fuelco = 0.9;
		State.gun = 5;
		State.gunspeed = 1;
		State.health = 100;
		State.life = 1;
	}
	bodyimg.loadFromFile("./img/ship/ship.png");
	BodyTex.loadFromImage(bodyimg,sf::IntRect(0,0,80,64));
	BodyTex.setSmooth(true);
	Body.setTexture(BodyTex);
	Body.setTextureRect(sf::IntRect(0, 0, 80, 64));
	Shield.setRadius(defsizey / 2);
	Body.setScale(sf::Vector2f(shapecox, shapecoy));
	std::cout << shapecox << std::endl << shapecoy << std::endl;
	Gun.setScale(sf::Vector2f(shapecox, shapecoy));
	Engine.setScale(sf::Vector2f(shapecox, shapecoy));
	Shield.setScale(sf::Vector2f(shapecox, shapecoy));
	timerclock.restart();
}

bool PlayerO::LoadFile(bool Isnew, char *filename)	// Нужен для загрузки параметров игрока из бинарного файла
{
	if (Isnew == true) return false;
	else
	{
		std::ifstream loadfile;
		loadfile.open(filename, std::ios::binary | std::ios::in);
			loadfile.read((char *)&State, sizeof(PStatements));
			return true;
	}
}

void PlayerO::Move(sf::RenderWindow &window)
{
	sf::Vector2i pos = sf::Mouse::getPosition(window);
	int xt, yt;
	xt = pos.x;
	yt = pos.y;
	// Пролверяю вышел ли корабль игрока за пределы диапазона
	if (pos.x < 60 * shapecox) xt = 60 * shapecox;
	if (pos.x > 1780 * shapecox) xt = 1780 * shapecox;
	if (pos.y > 980 * shapecoy) yt = 980 * shapecoy;
	if (pos.y < 140 * shapecoy) yt = 140 * shapecoy;
	SetCoord(xt, yt);
}

void PlayerO::SetCoord(int x,int y)
{
	// Сдесь устанавливаю координа для "составных частей корабля"
	Body.setPosition(x, y);
	Gun.setPosition(x, y);
	Engine.setPosition(x, y);
	Shield.setPosition(x, y);
	this->x = x;
	this->y = y;
}


void PlayerO::Draw(sf::RenderWindow &window)
{
	window.draw(Body);
}

void PlayerO::RemoveHealth(int remh)
{
	if (!ShieldActive) // Уменьшать сзоровье только если щит не активен
	{
		State.health -= (remh * State.life); // Уменьшаем здоровье с поправкой на коэффициент
	}

}

void PlayerO::AddHealth(int addh)
{
	State.health += addh;
}
					
void PlayerO::SetEnergy()
{
	if (energytime.getElapsedTime().asSeconds() > 0.2)
	{
		energytime.restart();
		if (ShieldActive) State.energy -= 1 * State.energyco;
		else State.energy += 1 * State.energyco;
	}
}

void PlayerO::ActiveDeactiveS()	// Для активации и деактивации щита
{
	if (State.energy = 0) ShieldActive = false;
	if (State.energy = 100)
	{
		if (sf::Mouse::isButtonPressed(sf::Mouse::Middle))
		{
			ShieldActive = true;
		}
	}
}

PStatements PlayerO::GetPlayerStatements()	 // Метод возвращает структуру в которой храняться параметры игрока Нужен для сохрнанения игры
{
	return State;
}

void PlayerO::SaveState(char *filename)
{
	std::ofstream savefile;
	savefile.open(filename, std::ios::ate);
	savefile.write((char*)&State, sizeof(PStatements));
	savefile.close();
	
}

int PlayerO::GetHealth()	// Возвращае здоровье игрока
{
	return State.health;
}

bool PlayerO::ifShot()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))	  // Если нажата левая кнопка мыши и прошло больше времени чем указано в ограничении скорсти оружия то возвражаем истину
	{
		if (fireclock.getElapsedTime().asSeconds() > State.gunspeed)
		{
			fireclock.restart();
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}


sf::Vector2f PlayerO::GetBulletPosition(int &y) // Раньше рассчітывал позіцію пулі скорее всего удалю
{
	y = bodyimg.getSize().y;
	y *= shapecoy;
	sf::Vector2f pos = Body.getPosition();
	pos.y += (y / 2);
	return pos;
}


PlayerO& PlayerO::operator-(int value)	// Для уменьшения здоровья игрока
{
	State.health -= value;
	return *this;
}


void PlayerO::RemovePBullets()
{
	int i = 0;
	for (; i < SetOfPlayerBullets.size(); i++)	   // Удаляем те пули которые уже "отстреляли свое"
	{
		if (SetOfPlayerBullets[i].IsForDelete())
		{
			SetOfPlayerBullets.erase(SetOfPlayerBullets.begin() + i);
			i--;
		}
	}
}
void PlayerO::Update(sf::RenderWindow &window,float time)
{
	Move(window);
	Draw(window);
	if (ifShot())	   // Если произошёл выстрел то добавим пулю в вектор
	{
		double Bulletx = Body.getPosition().x + Body.getLocalBounds().width;
		double Bullety = Body.getPosition().y + (Body.getLocalBounds().height / 2);
		Bullet *B = new Bullet(sf::Vector2f(Bulletx, Bullety), shapecox, shapecoy, "./img/bullets/bullet.png", 1, State.gunspeed, State.gun);
		SetOfPlayerBullets.push_back(*B);
	}
	for (std::vector<Bullet>::iterator it = SetOfPlayerBullets.begin(); it != SetOfPlayerBullets.end(); it++)
	{
		it->Move(time);
		it->Draw(window);
	}
}
PlayerO& PlayerO::operator+(int value) // Для увеличения здоровья игрока
{
	State.health += value;
	return *this;
}