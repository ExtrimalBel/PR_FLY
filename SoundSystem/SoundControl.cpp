#include "stdafx.h"
#include "SoundControl.h"

namespace SoundControl
{
	SoundControlStruct InitSoundSystemStruct(string BasePath, string PathToSoundConfig)
	{
		SndControl = new SoundSystem::SoundSystem(BasePath, PathToSoundConfig); // Создаем экземпляр класса звуковой системы
		SoundControlStruct sndcontrolstr;
		// Присваеваем указателям адреса функций
		sndcontrolstr.Playsnd = PlaySound;
		sndcontrolstr.GetNumberOfSound = GetNumberOfSound;
		sndcontrolstr.PauseSound = PauseSound;
		sndcontrolstr.StopSound = StopSound;
		sndcontrolstr.ResumeSound = ResumeSound;
		sndcontrolstr.Update = Update;
		sndcontrolstr.Mute = Mute;
		sndcontrolstr.UnMute = UnMute;
		sndcontrolstr.SetVolume = SetVolume;
		sndcontrolstr.ReturnCurrentVolume = ReturnCurrentVolume;
		return sndcontrolstr;
	}

	void Update()
	{
		SndControl->Update();
	}

	void ResumeSound(int id)
	{
		SndControl->ResumeSound(id);
	}

	void PlaySound(int id, bool LoopState)
	{
		SndControl->PlayMusic(id, LoopState);
	}
	void StopSound(int id)
	{
		SndControl->StopMusic(id);
	}
	void PauseSound(int id)
	{
		SndControl->PauseMusic(id);
	}

	int GetNumberOfSound()
	{
		return SndControl->GetNumberOfMusic();
	}

	void Mute()
	{
		SndControl->Mute();
	}
	void UnMute()
	{
		SndControl->UnMute();
	}
	void SetVolume(float value)
	{
		SndControl->SetVolume(value);
	}

	float ReturnCurrentVolume()
	{
		return SndControl->ReturnCurrentVolume();
	}

	void DeleteSoundSystem()
	{
		delete SndControl;
		cout << "Sound System Was deleted" << endl;
	}
};