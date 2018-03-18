#include "stdafx.h"
#include "Bullet.h"

Bullet::Bullet(sf::Vector2f position, double cx, double cy, const char *image,int dir,float speed,double demage)
{
	// ”станавливаю параметры пулю в том числе загружаю текстуру пули
	this->demage = demage;
	cox = cx;
	coy = cy;
	bulletimg.loadFromFile(image);
	bullettext.loadFromImage(bulletimg);
//	bulletrect.setSize(sf::Vector2f(bulletimg.getSize().x,bulletimg.getSize().y));
	bulletrect.setTexture(bullettext);
	direction = dir;
	bulletrect.setScale(cox, coy);
	bulletrect.setPosition(position);
	this->speed = speed;
}

Bullet::Bullet(sf::Vector2f position, double cx, double cy, sf::Texture &text, int dir, float speed, double demage)
{
	this->demage = demage;
	cox = cx;
	coy = cy;
//	bulletrect.setSize(sf::Vector2f(text.getSize().x,text.getSize().y));
	bulletimg = text.copyToImage();
	bulletrect.setTexture(text);
	direction = dir;
	bulletrect.setScale(cox, coy);
	bulletrect.setPosition(position);
	this->speed = speed;
}

void Bullet::Move(float time)
{
	// ≈сли direction 1 то в право если другое число то влево
	if (direction == 1)
	{
		bulletrect.move(speed * time * cox,0);
	}
	else
	{
		bulletrect.move(-(speed * time * cox), 0);
	}
}

sf::IntRect Bullet::ReturnBulletRect()
{
	// ¬озвращаю объект типа sf::IntRect дл€ дальнешей проверки на пересечение пули с врагом или игроком
	sf::IntRect Bulletrect(bulletrect.getPosition().x, bulletrect.getPosition().y, bulletrect.getGlobalBounds().width, bulletrect.getGlobalBounds().height);
	return Bulletrect;
}

void Bullet::SetDelete(bool value)
{
	Is_For_Delete = value;
}

bool Bullet::IsForDelete()
{
	return Is_For_Delete;
}