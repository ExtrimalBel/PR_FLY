#pragma once
#ifdef SOUNDSYSTEM_EXPORTS
#define SOUNDSYSTEM_API __declspec(dllexport)
#else
#define SOUNDSYSTEM_API __declspec(dllimport)
#endif
#include "SoundSystem.h"
#include <string>

using namespace std;

namespace SoundControl
{
	static SoundSystem::SoundSystem *SndControl; // ����� ��������� �� �������

	void PlaySound(int id, bool LoopState = false);
	void StopSound(int id);
	void PauseSound(int id);
	void Update();
	int GetNumberOfSound();
	void ResumeSound(int id);
	void Mute();
	void UnMute();
	void SetVolume(float value);
	float ReturnCurrentVolume();
	struct SOUNDSYSTEM_API SoundControlStruct // ������ ��������� ���������� ���� ������� ������� ��������������� �� �������� ����������� � �������� ������ ������� ������ �� ������
	{
		void(*Playsnd)(int, bool);
		void(*StopSound)(int);
		void(*PauseSound)(int);
		void(*ResumeSound)(int);
		int(*GetNumberOfSound)();
		void(*Update)();
		void(*Mute)();
		void(*UnMute)();
		void(*SetVolume)(float);
		float(*ReturnCurrentVolume)();

	};

	SoundControlStruct SOUNDSYSTEM_API InitSoundSystemStruct(string BasePath, string PathToSoundConfig); // ������� �������������� ������ ���������

	void DeleteSoundSystem();
}