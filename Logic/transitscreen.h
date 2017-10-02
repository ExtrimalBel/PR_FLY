#ifndef TranS
#define TranS
#include <SFML/Graphics.hpp>
namespace Screens
{
	class BaseScreen // ������� ����� ��� ���� "�������������� �������" � ��� ���������� �������� ������� � ������� ������ � ���������
		/*
		�������� ����������� ������ ����� ���
		����������� ������ ��������� ������������� � 
		*/
	{
	protected:
		sf::Texture BackgroundText;
		sf::Sprite Background;
		double cox, coy;
		sf::Text Message;
		sf::Font TextFont;
	public:
		BaseScreen(double cox,double coy);
		virtual void Update(sf::RenderWindow &window); // ������������ ��� ��������� � �����
		virtual int IfExit() = 0;
		virtual void SetTextString(sf::String str);


	};
	class TransitScreen : public BaseScreen
	{
		bool loaded;
	
		bool ToExit;
		const char *levelname;
	public:
		TransitScreen(double cox,double coy,const char *levelname);
		//void Update(sf::RenderWindow &window);
		void Update(sf::RenderWindow &window);
		int IfExit();
		void SetStateOfScreen(int state);
	};
	class BossComingScreen : public BaseScreen
	{
		sf::Clock Tick; // ������� ����� ������ ���������� ������ �����
		double time; // ����� ������ ������
	public:
		BossComingScreen(double cox, double coy, double time);
		int IfExit();
	};
}
#endif