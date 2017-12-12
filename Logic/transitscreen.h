#ifndef TranS
#define TranS
#include <SFML/Graphics.hpp>

namespace Screens
{
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
	class BaseScreen // ������� ����� ��� ���� "�������������� �������" � ��� ���������� �������� ������� � ������� ������ � ���������
		/*
		�������� ����������� ������ ����� ���
		����������� ������ ��������� ������������� � 
		*/
	{
	protected:
		std::string BasePath;
		sf::Texture BackgroundText;
		sf::Sprite Background;
		double cox, coy;
		sf::Text Message;
		sf::Font TextFont;
	public:
		BaseScreen(double cox,double coy,std::string BasePath);
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
		TransitScreen(double cox,double coy,const char *levelname,std::string BasePath);
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
		BossComingScreen(double cox, double coy, double time,std::string BasePath);
		int IfExit();
	};

	class LOGIC_API ErrorScreen : public BaseScreen
	{
		bool ToExit;
	public:
		ErrorScreen(double cox,double coy,std::string BasePath,std::string Message);
		int IfExit();
		void Update(sf::RenderWindow &window);
	};
}
#endif