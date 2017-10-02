#include "stdafx.h"
#include "SetOfBullets.h"
void SetOfBullets::Update(float time, sf::RenderWindow &window) // ����� ����� ��� ���������� ���� ����
{
	Move(time);
	Draw(window);
}

void SetOfBullets::Move(float time)  // ������������� ���� ����
{
	for (std::vector<Bullet>::iterator it = SOB.begin(); it != SOB.end(); it++)
	{
		it->Move(time);
	}
	for (std::vector<Bullet>::iterator it = PSOB.begin(); it != PSOB.end(); it++)
	{
		it->Move(time);
	}
}

void SetOfBullets::Draw(sf::RenderWindow &window) // ��������� ���� ����
{
	for (std::vector<Bullet>::iterator it = SOB.begin(); it != SOB.end(); it++)
	{
		it->Draw(window);
	}
	for (std::vector<Bullet>::iterator it = PSOB.begin(); it != PSOB.end(); it++)
	{
		it->Draw(window);
	}
}

void SetOfBullets::AddBullet(sf::Vector2f position, double cx, double cy, int dir, float speed,double demage)
{ // ����� ��������� ���� � SetOfBullets
	Bullet *B = new Bullet(position, cx, cy, "./img/bullets/bullet.png", 2, 0.1,demage);
	SOB.push_back(*B);
}

SetOfBullets::SetOfBullets(double cx, double cy)
{
	this->cx = cx;
	this->cy = cy;
}


void SetOfBullets::CountDemageToPlayer(double &demage,sf::IntRect playerrect) // ������� ����������� �� ���� ������� ������������� � ������� � ������� ���� � �������� ����� ������������
{
	int id = 0; // id - ������ � �������
	while (id < SOB.size())	// ��������� ���� ���� ������ ������ ������� �������
	{
		if (playerrect.intersects(SOB[id].ReturnBulletRect()))	// ���� ������� ������� � �������� ������������� � ������� �� ������������� ���� � ������� �������
		{
			demage += SOB[id].GetDemage();
			SOB.erase(SOB.begin() + id);
		}
		else
		{
			id++;	// ����� �������������� ������
		}
	}
}

void SetOfBullets::AddPlayerBullet(sf::Vector2f position, double cx, double cy, int dir, float speed, double demage) // ���������� ���� ���������� �������
{ 
	Bullet *B = new Bullet(position, cx, cy, "./img/bullets/bullet.png", dir, 0.1, demage);
	PSOB.push_back(*B);
}

void SetOfBullets::RemoveDemageFromBoss(double &demage, const sf::Sprite& bosssprite,sf::Image& bossimg)
{
	int id = 0;
	while (id < PSOB.size())
	{
		//sf::IntRect BulletRect = PSOB[id].ReturnBulletRect();
		sf::Sprite bulletspr = PSOB[id].GetSprite();
		if (PixelPerfectCollision(bulletspr, bosssprite,PSOB[id].GetImage(),bossimg))
		{
			demage += PSOB[id].GetDemage();
			PSOB.erase(PSOB.begin() + id);
		}
		else
		{
			id++;
		}
	}

}

void SetOfBullets::DeleteBullets() // ����� ������� ���������� �� �������� ����
{
	if (SOB.size())
	for (int i = 0; i < SOB.size(); i++)
	{
		if (SOB[i].IsForDelete())
		{
			SOB.erase(SOB.begin() + i);
			i--;
		}
	}
	if (PSOB.size())
	for (int i = 0; i < PSOB.size(); i++)
	{
		if (PSOB[i].IsForDelete())
		{
			PSOB.erase(PSOB.begin() + i);
			i--;
		}
	}
}