#include "stdafx.h"
#include "Player_Class.h"
#include <iostream>
player_object::player_object(int x, int y, double shapecox,double shapecoy,bool Isnew)
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

bool player_object::LoadFile(bool Isnew, char *filename)
{
	if (Isnew == true) return false;
	else
	{
		std::ifstream loadfile;
		loadfile.open("save.txt", std::ios::binary | std::ios::in);
			loadfile.read((char *)&State, sizeof(PStatements));
			return true;
	}
}

void player_object::Move(sf::RenderWindow &window)
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

void player_object::SetCoord(int x,int y)
{
	// Сдесь устанавливаю координа для "составных частей корабля"
	Body.setPosition(x, y);
	Gun.setPosition(x, y);
	Engine.setPosition(x, y);
	Shield.setPosition(x, y);
	this->x = x;
	this->y = y;
}


void player_object::Draw(sf::RenderWindow &window)
{
	window.draw(Body);
}

void player_object::IfShot(int inter, int remh)
{
	if (!ShieldActive)
	{
		if (inter == 1) RemoveHealth(remh); // Если в корабль попали то уменьшаем жизни
	}
}

void player_object::RemoveHealth(int remh)
{
	if (!ShieldActive) // Уменьшать сзоровье только если щит не активен
	{
		State.health -= (remh * State.life); // Уменьшаем здоровье с поправкой на коэффициент
	}

}

void player_object::AddHealth(int addh)
{
	State.health += addh;
}

int player_object::Fire()
{// Проверяем если прошло время больше чем в gunspeed и нажата клавиша мыши то возвращаем 1, что означает выстрел и обнуляем счётчик иначе возвращаем 0
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		if (fireclock.getElapsedTime().asSeconds() > 0.5)
		{
			fireclock.restart();
			return 1;
		}
		
		else
			return 0;
	}
	else
		return 0;
}

void player_object::SetEnergy()
{
	if (energytime.getElapsedTime().asSeconds() > 0.2)
	{
		energytime.restart();
		if (ShieldActive) State.energy -= 1 * State.energyco;
		else State.energy += 1 * State.energyco;
	}
}

void player_object::ActiveDeactiveS()
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

PStatements player_object::GetPlayerStatements()
{
	return State;
}

void player_object::SaveState(char *filename)
{
	std::ofstream savefile;
	savefile.open(filename, std::ios::ate);
	savefile.write((char*)&State, sizeof(PStatements));
	savefile.close();
	
}


sf::IntRect player_object::ReturnRect()
{
	sf::IntRect Bodyrect(Body.getPosition().x, Body.getPosition().y, Body.getGlobalBounds().width, Body.getGlobalBounds().height);
	return Bodyrect;

}

int player_object::GetHealth()
{
	return State.health;
}

bool player_object::ifShot()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
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


sf::Vector2f player_object::GetBulletPosition(int &y)
{
	y = bodyimg.getSize().y;
	y *= shapecoy;
	sf::Vector2f pos = Body.getPosition();
	pos.y += (y / 2);
	return pos;
}


player_object& player_object::operator-(int value)
{
	State.health -= value;
	return *this;
}

player_object& player_object::operator+(int value)
{
	State.health += value;
	return *this;
}