#include "stdafx.h"
#include "SetOfBullets.h"
void SetOfBullets::Update(float time, sf::RenderWindow &window) // ќбщий метод дл€ обновлени€ всех пуль
{
	Move(time);
	Draw(window);
}

void SetOfBullets::Move(float time)  // ѕеередвижение всех пуль
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

void SetOfBullets::Draw(sf::RenderWindow &window) // ќтрисовка всех пуль
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
{ // ћетот создающий пулю в SetOfBullets
	Bullet *B = new Bullet(position, cx, cy, "./img/bullets/bullet.png", 2, 0.1,demage);
	SOB.push_back(*B);
}

SetOfBullets::SetOfBullets(double cx, double cy)
{
	this->cx = cx;
	this->cy = cy;
}


void SetOfBullets::CountDemageToPlayer(double &demage,sf::IntRect playerrect) // —читаем повреждение от пуль которые пересекаютьс€ с игроком и удал€ем пули с которыми игрок пересекаетс€
{
	int id = 0; // id - »ндекс в векторе
	while (id < SOB.size())	// ¬ыпол€нем цикл пока индекс меньше размера вектора
	{
		if (playerrect.intersects(SOB[id].ReturnBulletRect()))	// ≈сли элемент вектора с индексом пересекаетьс€ с игроком то пересчитываем урон и удал€ем элемент
		{
			demage += SOB[id].GetDemage();
			SOB.erase(SOB.begin() + id);
		}
		else
		{
			id++;	// »наче инкрементируем индекс
		}
	}
}

void SetOfBullets::AddPlayerBullet(sf::Vector2f position, double cx, double cy, int dir, float speed, double demage) // ƒобавление пули выпущенной игроком
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

void SetOfBullets::DeleteBullets() // ћетод удал€ет помеченные на удаление пули
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