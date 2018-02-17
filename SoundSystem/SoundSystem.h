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
#include "SoundExceptions.h"
#include <SFML/Audio.hpp>
#include <fstream>
#include <vector>
#include <string>
#include "tinyxml2.h"
// Этот класс экспортирован из SoundSystem.dll
using namespace std;
using namespace sf;

namespace SoundSystem
{
	struct SoundData
	{
		string Name;
		int id;
	};

	struct SoundItem
	{
		Music *snd;
		int id;
		void InitSound(int id, void *SoundData, int MusicSize, bool LoopState)
		{
			this->id = id;
			snd = new sf::Music();
			snd->openFromMemory(SoundData, MusicSize);
			snd->setLoop(LoopState);
			snd->play();
		}
	};

	class SOUNDSYSTEM_API SoundSystem
	{
		int SoundCount;
		string BasePath;
		string PathToSoundConfig;
		vector <pair<void*, int>> SoundSources; //  Музыка
		vector<SoundItem> Musics; // массив хранящий записи о проигрываемых звуках
		void CreateMusicData(string PathToSoundConfig); // создает массив SoundSources
		void ReadDataMusicDataFromFile(string PathToSoundConfig, vector<SoundData> &Data);
		float CurrentVolume;
		bool MuteState;
	public:
		SoundSystem(string BasePath, string PathToSoundConfig);
		void StopMusic(int id); // Останавливает все звуки по данному id. и удаляет
		void PlayMusic(int id, bool LoopState); // Создает новую запись в Musics и начинает проигрывать звук
		void PauseMusic(int id);
		void ResumeSound(int id);
		void Update();
		int GetNumberOfMusic();
		void Mute();
		void UnMute();
		void SetVolume(float value);
		float ReturnCurrentVolume();
		~SoundSystem();
	};
}
#endif