#ifndef TranS
#define TranS
#include <SFML/Graphics.hpp>
namespace Screens
{
	class BaseScreen // Базовый класс для всех "информационных экранов" в нем определены основные функции и объекты текста и сообщения
		/*
		Попытюсь реализовать экраны через ооп
		Определение строки сообщения придусмотрено в 
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
		virtual void Update(sf::RenderWindow &window); // отрисовывает фон сообщения и текст
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
		sf::Clock Tick; // Считает время которе показывает данный экран
		double time; // Время показа экрана
	public:
		BossComingScreen(double cox, double coy, double time);
		int IfExit();
	};
}
#endif