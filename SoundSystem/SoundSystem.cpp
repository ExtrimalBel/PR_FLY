// SoundSystem.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "SoundSystem.h"


// Пример экспортированной переменной

namespace SoundSystem
{
	SoundPlayer::SoundPlayer()
	{
		type = State::MainMenu;
		Inicialize();
	}
int	SoundPlayer::Inicialize()
	{
		switch (type)
		{
		case State::MainMenu:
			InicializeMainMenu();
			break;
		default:
			return -1;
			break;
		}
		return 0;
	}

int SoundSystem::SoundPlayer::ChangeType(State type)
{
	this->type = type;
	Inicialize();
	return 0;
}
int SoundPlayer::ChangeSoundState()
{
	switch (type)
	{
	case State::MainMenu:
		if (MainM->select.getStatus() == sf::Sound::Status::Playing)
		{
			MainM->selectplay = true;
		}
		else MainM->selectplay = false;
		break;
	}
	return 0;
}

int SoundPlayer::PlaySound(int id)
{
	ChangeSoundState();
	switch (id)
	{
	case 1:
		if (!(MainM->selectplay) && !MainM->onelement) MainM->select.play();
		break;
	case 2:
		MainM->click.play();
		break;
	case 3:
		if (!(MainM->back_music.getStatus() == sf::Music::Playing))
		{
			MainM->back_music.play();
		}

	}
	return 0;
}

int SoundPlayer::InicializeMainMenu()
{
	// Inicializing select sound
	MainM = new MainMSound;
	MainM->selectbuf.loadFromFile("./sound/select.wav");
	MainM->select.setBuffer(MainM->selectbuf);
	MainM->selectplay = false;
	MainM->onelement = false;
	//Inicializing click sound
	MainM->clickbuf.loadFromFile("./sound/click.wav");
	MainM->click.setBuffer(MainM->clickbuf);
	// Inicializing back theme music
	MainM->back_music.openFromFile("./sound/backmenu.ogg");
	MainM->back_music.setLoop(true);
	return 0;
}

void SoundPlayer::SetVolume(float volume)
{
	this->volume = volume;
	UpdateVolume();
}

int SoundPlayer::UpdateVolume()
{
	switch (type)
	{
	case State::MainMenu:
		UpdateVolume();
		break;
	default:
		return -1;
		break;
	}
}

int SoundPlayer::UpdateVolMainM()
{
	MainM->select.setVolume(volume);
	MainM->click.setVolume(volume);
	MainM->back_music.setVolume(volume);
	return 0;
}

SoundPlayer::~SoundPlayer()
{
	switch (type)
	{
	case State::MainMenu:
		MainM->back_music.stop();
		MainM->click.stop();
		break;
	}
}


}


