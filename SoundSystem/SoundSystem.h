// ����������� ���� ���� ifdef - ��� ����������� ����� �������� ��������, ���������� ��������� 
// �������� �� ��������� DLL. ��� ����� ������ DLL �������������� � �������������� ������� SOUNDSYSTEM_EXPORTS,
// � ��������� ������. ���� ������ �� ������ ���� ��������� � �����-���� �������
// ������������ ������ DLL. ��������� ����� ����� ������ ������, ��� �������� ����� �������� ������ ����, ����� 
// ������� SOUNDSYSTEM_API ��� ��������������� �� DLL, ����� ��� ������ DLL ����� �������,
// ������������ ������ ��������, ��� ����������������.
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
// ���� ����� ������������� �� SoundSystem.dll
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
		vector <pair<void*, int>> SoundSources; //  ������
		vector<SoundItem> Musics; // ������ �������� ������ � ������������� ������
		void CreateMusicData(string PathToSoundConfig); // ������� ������ SoundSources
		void ReadDataMusicDataFromFile(string PathToSoundConfig, vector<SoundData> &Data);
		float CurrentVolume;
		bool MuteState;
	public:
		SoundSystem(string BasePath, string PathToSoundConfig);
		void StopMusic(int id); // ������������� ��� ����� �� ������� id. � �������
		void PlayMusic(int id, bool LoopState); // ������� ����� ������ � Musics � �������� ����������� ����
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