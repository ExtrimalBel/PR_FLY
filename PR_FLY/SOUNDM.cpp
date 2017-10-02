#include "stdafx.h"
#include "SOUNDM.h"
sf::SoundBuffer SOUNDSYSTEM::SoundPlayer::buffer;
sf::Sound SOUNDSYSTEM::SoundPlayer::select;
bool SOUNDSYSTEM::SoundPlayer::IS_UP = false;
namespace SOUNDSYSTEM
{

	void SoundPlayer::PlaySound()
	{
		if (!IS_UP)
		{
			//	buffer.loadFromFile("./sound/select.wav");
			//	select.setBuffer(buffer);
			IS_UP = true;

		}
		//	select.play();
	}



}