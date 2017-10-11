// Приведенный ниже блок ifdef - это стандартный метод создания макросов, упрощающий процедуру 
// экспорта из библиотек DLL. Все файлы данной DLL скомпилированы с использованием символа SOUNDSYSTEM_EXPORTS,
// в командной строке. Этот символ не должен быть определен в каком-либо проекте
// использующем данную DLL. Благодаря этому любой другой проект, чьи исходные файлы включают данный файл, видит 
// функции SOUNDSYSTEM_API как импортированные из DLL, тогда как данная DLL видит символы,
// определяемые данным макросом, как экспортированные.
#ifndef SND
#define SND
#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
#include <SFML/Audio.hpp>
#include "SoundStruct.hpp"
// Этот класс экспортирован из SoundSystem.dll
namespace SoundSystem
{
	enum State { MainMenu, Game, Settings, Pause };
	class SOUNDSYSTEM_API SoundPlayer
	{
		float volume;
		State type;
		MainMSound *MainM;
	public:
		~SoundPlayer();
		SoundPlayer();
		int Inicialize();
		int PlaySound(int id);
		int ChangeType(State type);
		int ChangeSoundState();
		int SetOnElement(bool val) { MainM->onelement = val; return 0; }
		void SetVolume(float volume); // Установка переменной громкости
	private:
		int InicializeMainMenu();

		int UpdateVolume(); // Обновление громкости для всех звуков]
		int UpdateVolMainM();
	
	};
}
#endif