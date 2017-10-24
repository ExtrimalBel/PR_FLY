#include "stdafx.h"
#include "UpgradeScreen.h"

namespace Screens
{
	UpgradeScreen::UpgradeScreen()
	{
		IfUpgradeFinish = false;
		menuitem = 0;
	}

	void UpgradeScreen::Init(PStatements &State)
	{
		this->State = State;
	}

	void UpgradeScreen::Update(float time, sf::RenderWindow &window)
	{
		SetMenuItemActive(window);
		UpgradeScreen();
		DrawScreen(window);
	}

	void UpgradeScreen::SetMenuItemActive(sf::RenderWindow &window)
	{
		/*
			menuitem  = 1 Предыдущий элемент апгрейда
			menuitem  = 2 Следующий элемент апгрейда
			menuitem  = 3 Улутшить
			menuitem  = 4 Убрать апгрейд
			menuitem  = 5 Выйти из меню апгреда
		*/
		sf::Vector2f MousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
		if (PrevItem.getLocalBounds().contains(MousePosition))
		{
			menuitem = 1;
		}
		else if (NextItem.getLocalBounds().contains(MousePosition))
		{
			menuitem = 2;
		}
		else if (UpgradeItem.getLocalBounds().contains(MousePosition))
		{
			menuitem = 3;
		}
		else if (DowngradeItem.getLocalBounds().contains(MousePosition))
		{
			menuitem = 4;
		}
		else if (ExitFromScreen.getLocalBounds().contains(MousePosition))
		{
			menuitem = 5;
		}
		else menuitem = 0;
	}

	void UpgradeScreen::DrawScreen(sf::RenderWindow &window)
	{
		window.draw(BackGround);
		window.draw(Ship);
		window.draw(NextItem);
		window.draw(PrevItem);
		window.draw(ExitFromScreen);
		window.draw(DowngradeItem);
		window.draw(UpgradeItem);
		window.draw(FirstBackButton);
		window.draw(SecondButton);

	}


}