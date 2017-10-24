#ifndef UPGRADESCRH
#define UPGRADESCRH
#include <SFML\Graphics.hpp>
#include "PlayerS.h"
namespace Screens
{
	class UpgradeScreen
	{
		// ���������� �������
		sf::Texture BackGroundTex;
		sf::Texture ShipTex;
		sf::Texture FirstBackButtonTex;
		sf::Texture SecondButtonTex;
		sf::Texture FirstButtonTex;
		// ���������� ��������
		sf::Sprite BackGround;
		sf::Sprite Ship;
		sf::Sprite FirstBackButton;
		sf::Sprite PrevItem;
		sf::Sprite NextItem;
		sf::Sprite UpgradeItem;
		sf::Sprite DowngradeItem;
		sf::Sprite ExitFromScreen;
		sf::Sprite SecondButton;

		//����� ������
		PStatements State;

		// ������ ������
		bool IfUpgradeFinish = false; // ���������� �� �������
		int menuitem = 0; // ������� ������ ����
		void SetMenuItemActive(sf::RenderWindow &window);
		void SetButtonActive();
		void UpgradeShip();
		void DrawScreen(sf::RenderWindow &window);

	public:
		UpgradeScreen();
		void Init(PStatements &State);
		void Update(float time, sf::RenderWindow &window);
		bool IfExit();

	};
}

#endif