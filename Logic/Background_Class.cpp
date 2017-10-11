#include "stdafx.h"
#include "Background_Class.h"

Back_Menu::Back_Menu(double cox,double coy)
{
	
	PosLines[0] = 90;
	for (int i = 1; i < 11; i++)
	{
		PosLines[i] = PosLines[i - 1] + 90;
	}
	PosLines[11] = PosLines[10] + 60;
	this->cox = cox;
	this->coy = coy;
	Up_Clock.restart();
	srand(time(NULL));
	Back_Rec.setSize(sf::Vector2f(1920, 1080));
	Backtex.loadFromFile("./img/back.png");
	StarTexture.loadFromFile("./img/star.png");

	Back_Rec.setTexture(&Backtex);
	Back_Rec.setScale(cox, coy);
	Back_Rec.setPosition(0, 0);
	for (int i = 0; i < 12; i++)
	{
		PosLines[i] *= coy;
	}
}

void Back_Menu::Update(float time, sf::RenderWindow &window)
{
	Draw(time, window);
	AddLine();
	MoveLines(time);
	DelLines();
}
void Back_Menu::Draw(float time, sf::RenderWindow &window)
{
	window.draw(Back_Rec);
	for (std::vector<sf::Sprite>::iterator it = Lines.begin(); it != Lines.end(); it++)
	{
		window.draw(*it);
	}
}

void Back_Menu::AddLine()
{
	int pos = PosLines[rand() % 12];
	sf::RectangleShape tmpline;
	int length = 0;
	length = (rand() % 100 + 1) ;
	int shapecoy = (rand() & 10) / 10;
		if (Up_Clock.getElapsedTime().asSeconds() > 0.7)
		{
				/*sf::RectangleShape tmpline;
				tmpline.setPosition(0 - length, pos);
				tmpline.setSize(sf::Vector2f(length, 4 * coy));
				tmpline.setFillColor(sf::Color::Blue);
				Lines.push_back(tmpline);
				*/
				sf::Sprite tmpspr;
				tmpspr.setTexture(StarTexture);
				tmpspr.setPosition(StarTexture.getSize().x + (1920 * cox), pos);
				tmpspr.setScale(cox, coy);
				Lines.push_back(tmpspr);

				Up_Clock.restart();
	}
}

void Back_Menu::MoveLines(float time)
{
	for (std::vector<sf::Sprite>::iterator it = Lines.begin(); it != Lines.end(); it++)
	{
		it->move(-(time * 0.17 * cox), 0);
	}
}

void Back_Menu::DelLines()
{
	/*for (std::vector<sf::RectangleShape>::iterator it = Lines.begin(); it != Lines.end(); it++)
	{
		sf::Vector2f tmpvec = it->getPosition();
		if (tmpvec.x > int(1920 * cox))
		{
			Lines.erase(it);
			DelLines();
			return;
		}
	}		  */
	int id = 0;
	while (id < Lines.size())
	{
		sf::Vector2f tmpvec = Lines[id].getPosition();
		if (tmpvec.x < int(-StarTexture.getSize().x))
		{
			Lines.erase(Lines.begin() + id);
		}
		else
		{
			id++;
		}
	}
}