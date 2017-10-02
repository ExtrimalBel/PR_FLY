#include "stdafx.h"
#include "loadgameclass.h"
#include "BaseMenu.h"
LoadM::LoadM(double cox, double coy, SoundSystem::SoundPlayer &SPlayer) : BaseMenu(cox, coy, SPlayer)
{
	SetUpText();
}

void LoadM::Update(float time, sf::RenderWindow &window)
{
	BaseMenu::Update(time, window);
}

void LoadM::Draw(sf::RenderWindow &window)
{
	BaseMenu::Draw(window);
}

void LoadM::IfMenuItemSelected(sf::RenderWindow &window)
{
	BaseMenu::IfMenuItemSelected(window);
}


int LoadM::MenuSelect()
{



	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		
		switch (menuitem) // � ����������� �� ���������� ������ ���� ����������� SaveFile ������������ ���� �� ����� ����������
		{
		case 1:
			//throw LoadM::OverFlow();
			SaveFile = "./saves/save1.txt";
			return 1;
		case 2:
			SaveFile = "./saves/save2.txt";
			return 2;
			break;
		case 3:
			SaveFile = "./saves/save3.txt";
			return 3;
			break;
		case 4:
			return  4;
			break;
		}
	}
}


void LoadM::SetUpText()
{
	// ������������ ����� "����� ����"
	textfont.loadFromFile("./CyrilicOld.TTF");
	firstitemtext.setFont(textfont);
	firstitemtext.setCharacterSize(48);
	firstitemtext.setScale(cox, coy);
	firstitemtext.setFillColor(sf::Color(178, 34, 34));
	sf::String str = "���� �������� 1";
	firstitemtext.setString(str);
	firstitemtext.setPosition(840 * cox, 220 * coy);

	// ������������� ����� "���������� ����"
	seconditemtext.setFont(textfont);
	seconditemtext.setCharacterSize(48);
	seconditemtext.setScale(cox, coy);
	seconditemtext.setFillColor(sf::Color(178, 34, 34));
	sf::String loadstr = "���� �������� 2";
	seconditemtext.setString(loadstr);
	seconditemtext.setPosition(810 * cox, 370 * coy);
	// ������������� ����� "���������" 
	thirditemtext.setFont(textfont);
	thirditemtext.setCharacterSize(48);
	thirditemtext.setScale(cox, coy);
	thirditemtext.setFillColor(sf::Color(178, 34, 34));
	sf::String settingstr = "���� �������� 3";
	thirditemtext.setString(settingstr);
	thirditemtext.setPosition(830 * cox, 520 * coy);

	fouritemtext.setFont(textfont);
	fouritemtext.setCharacterSize(48);
	fouritemtext.setScale(cox, coy);
	fouritemtext.setFillColor(sf::Color(178, 34, 34));
	sf::String exitstr = "�����";
	fouritemtext.setString(exitstr);
	fouritemtext.setPosition(850 * cox, 670 * coy);
}


char * LoadM::ReturnSaveFile()
{
	return SaveFile;
}