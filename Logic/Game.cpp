#include "stdafx.h"
#include "Game.h"
#include "ShipsClasses.h"
#include <ctime>
#define NOMINMAX
GameField::GameField()
{
	
	PlayerTexture.loadFromFile("./img/ships/player.png");
	EnemyTexture.loadFromFile("./img/ships/enemy.png");
	BulletTexture.loadFromFile("./img/bullets/bullet.png");
	p1 = new Player(PlayerTexture);
	p1->Setx(200);
	p1->SetY(200);
	srand(time(NULL));
	Bul_Clock.restart();
	Enemy_Clock.restart();
	UHudText.loadFromFile("./img/game/uhud.png");
	UHudSpr.setTexture(UHudText);
	UHudSpr.setPosition(0, 0);
	fontforScore.loadFromFile("CyrilicOld.TTF");
	Score.setFont(fontforScore);
	Score.setPosition(20, 20);
	Score.setString("0");
	HealthText.setFont(fontforScore);
	HealthText.setPosition(1000, 20);
	HealthText.setString("Очки 0");
	En_Bul.restart();
	Dead_Message.setFont(fontforScore);
	Dead_Message.setCharacterSize(72);
	Dead_Message.setPosition(550, 320);
	Dead_Message.setString("You lose!");
	p2 = new player_object(300, 300, 1.5, 1.5, true);
}

void GameField::updatePlayer(float time, sf::RenderWindow &window)
{
	p2->Move();
	BMenu.Update(time,window);
	window.draw(UHudSpr);
	if (p1->GetHealth() <= 0)
	{
		DrawDeath(window);
	}
	else
	{
		p1->Move(time);
		p1->Draw(window);	
		IfShotInPlayer();
	}

}

int GameField::IfExit()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
	{
		exit = 1;
		return 1;
	}
	else
		return 0;
}


void GameField::AddBullet()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		if ((Bul_Clock.getElapsedTime().asSeconds()) >= 0.5)
		{
			Bul_Clock.restart();
			Bullet B(2, p1->getx() + 70, p1->gety() + 35,BulletTexture);
			Bullets.push_back(B);
		}
	}
	if (p2->Fire() == 1)
	{
		Bullet B(2, p2->getx(), p2->gety(), BulletTexture);
		Bullets.push_back(B);
	}
}


void GameField::IFDELETEBULLET()
{
	for (std::vector<Bullet>::iterator it = Bullets.begin(); it != Bullets.end(); it++)
	{
		if (Bullets.size() == 0) return;
		if (it->Getx() > 1280)
		{
			
			Bullets.erase(it);
			IFDELETEBULLET();
			break;
		}
	}
}

void GameField::Addenemy()
{
	float t = Enemy_Clock.getElapsedTime().asSeconds();
	int x_add = 0;
	if (t > 2)
	{
		int pos = 1 + rand() % 3;
		if (pos == 1) x_add = 200;
		if (pos == 2) x_add = 400;
		if (pos == 3) x_add = 660;
		Enemy_Ship tmp_e(EnemyTexture);
		tmp_e.setx(1280);
		tmp_e.sety(x_add);
		Enemys.push_back(tmp_e);
		Enemy_Clock.restart();
	}
}

void GameField::MoveEnemys(float time)
{
	for (std::vector<Enemy_Ship>::iterator it = Enemys.begin(); it != Enemys.end(); it++)
	{
		it->Move(time);
	}
}

void GameField::IfEnemyKill()
{
	if (Enemys.size() == 0) return;
	if (Bullets.size() == 0) return;
	for (std::vector<Bullet>::iterator buls = Bullets.begin(); buls != Bullets.end(); buls++ )
	for (std::vector<Enemy_Ship>::iterator it = Enemys.begin(); it != Enemys.end(); it++)
	{
		int bulx = buls->Getx();
		int buly = buls->Gety();
		std::cout << "bulx is " << bulx << std::endl;
		if (it->InterSects(bulx,buly))
		{
			sc++;
			Bullets.erase(buls);
			Enemys.erase(it);
			IfEnemyKill();
			return;
		}
	}
}