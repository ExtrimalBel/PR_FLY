#pragma once

#include <SFML/Graphics.hpp>
#include <SoundControl.h>
#include <iostream>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif

using namespace std;
using namespace sf;


namespace Menus
{

	struct LOGIC_API IdOfSounds
	{
		int SelectId;
		int ClickId;
	};
	class LOGIC_API BaseMenu
	{
	protected:
		// �������� ����
		Texture MenuTex; // �������� �������� ����
		Sprite FirstMenuSpr;
		Sprite SecondMenuSpr;
		Sprite ThirdMenuSpr;
		Sprite FourMenuSpr;
		//��� ����
		Texture BackGroundTex;
		Sprite BackGroundSpr;
		//����� ����
		Font MenuFont;
		Text FirstMenuItemText;
		Text SecondMenuItemText;
		Text ThirdMenuItemText;
		Text FourMenuItemText;
		virtual void SetUpText() = 0; // �������������� ����� ������ ���������������� � ������ ����������� ������
		void Draw(RenderWindow &window);
		
		double cox, coy;
		string BaseGamePath;
		SoundControl::SoundControlStruct SndControl;
		IdOfSounds SndId;
		int SelectedMenuItem;
	public:
		BaseMenu(string BaseGamePath, double cox, double coy, SoundControl::SoundControlStruct SndControl, IdOfSounds SndId);
		void Update(RenderWindow &window); // ����������� ��� ������ �������� ����� ��������� ����
		int ReturnSelectedCode(); // ���������� ��� ���������� ������� ����, 0 ���� ������� �� ������

	};
}
