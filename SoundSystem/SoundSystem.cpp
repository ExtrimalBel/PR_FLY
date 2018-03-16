// SoundSystem.cpp: ���������� ���������������� ������� ��� ���������� DLL.
//

#include "stdafx.h"
#include "SoundSystem.h"


// ������ ���������������� ����������
namespace SoundSystem
{


	SoundSystem::SoundSystem(string BasePath, string PathToSoundConfig)
	{
		this->BasePath = BasePath;
		this->PathToSoundConfig = PathToSoundConfig;
		CreateMusicData(PathToSoundConfig);
		CurrentVolume = 100;
		MuteState = false;
	}

	void SoundSystem::CreateMusicData(string PathToSoundConfig)
	{
		vector<SoundData> MassOfSound;
		ReadDataMusicDataFromFile(PathToSoundConfig, MassOfSound);
		SoundCount = MassOfSound.size(); // ���-�� ����������� ������� � ������
		for (int i = 0; i < SoundCount; i++)
		{
			pair<void*, int> temppair;
			ifstream tempfile(BasePath + "/" + MassOfSound[i].Name, ios::binary | ios::ate);
			if (!(tempfile.is_open())) throw Exceptions::SoundSystemError("������ ��� ������������� �������� �������");
			temppair.second = static_cast<int>(tempfile.tellg()); // ��������� ������ �����
			temppair.first = (void*)new char[temppair.second];
			tempfile.seekg(0, ios::beg);
			tempfile.read((char*)temppair.first, temppair.second);
			SoundSources.push_back(temppair);
		}
	}



	void SoundSystem::ReadDataMusicDataFromFile(string PathToSoundConfig, vector<SoundData> &Data) // ������ ���������� � ������ �� xml �������
	{
		tinyxml2::XMLDocument xmldoc;
		string FilePath = BasePath;
		FilePath += "/";
		FilePath += PathToSoundConfig;
		xmldoc.LoadFile(FilePath.c_str());
		if (xmldoc.ErrorID() != tinyxml2::XML_SUCCESS) throw Exceptions::SoundSystemError("���������� ������� ���� ��� ���� ���������");
		tinyxml2::XMLNode *RootNode = xmldoc.FirstChildElement("sounds");
		if (RootNode == NULL) throw Exceptions::SoundSystemError("���������� ��������� ���������� � �������� ������");
		tinyxml2::XMLElement *CurrentElenemt = RootNode->FirstChildElement("snd");
		if (CurrentElenemt == NULL) throw Exceptions::SoundSystemError("���������� ��������� ���������� � �������� ������");
		int id = 0;
		do
		{
			SoundData tempsnd;
			tempsnd.id = id++;
			tempsnd.Name = CurrentElenemt->GetText();
			Data.push_back(tempsnd);
			CurrentElenemt = CurrentElenemt->NextSiblingElement("snd");
		} while (CurrentElenemt != NULL);
	}

	void SoundSystem::StopMusic(int id)
	{
		auto it = Musics.begin();
		do
		{
			if (it->id == id)
			{
				it->snd->stop();
				delete it->snd;
				Musics.erase(it);
				break;
			}
			it++;
		} while (it != Musics.end());
	}
	void SoundSystem::PlayMusic(int id, bool LoopState)
	{
		if (id < 0 || id >= SoundCount) throw Exceptions::SoundSystemError("�� ��������� ����� ������������");
		SoundItem tempsnditem;
		Musics.push_back(tempsnditem);

		Musics[Musics.size() - 1].InitSound(id, SoundSources[id].first, SoundSources[id].second, LoopState);
		if (!MuteState)
		Musics[Musics.size() - 1].snd->setVolume(CurrentVolume);
		else Musics[Musics.size() - 1].snd->setVolume(0);
	}

	void SoundSystem::PauseMusic(int id)
	{
		for (unsigned int i = 0; i < Musics.size(); i++)
		{
			if (Musics[i].id == id)
			{
				Musics[i].snd->pause();
			}
		}
	}

	int SoundSystem::GetNumberOfMusic()
	{
		return SoundCount;
	}

	void SoundSystem::ResumeSound(int id)
	{
		for (unsigned int i = 0; i < Musics.size(); i++)
		{
			if (Musics[i].id == id)
			{
				Musics[i].snd->play();
			}
		}
	}

	void SoundSystem::Update()
	{
		// ������� ������� ������
		// ������� ������� ���� �������� ���� ���������� � �� �� ������ ������������ ����������
		for (unsigned int i = 0; i < Musics.size(); i++)
		{
			if (Musics[i].snd->getStatus() == sf::Music::Stopped && !Musics[i].snd->getLoop())
			{
				Musics.erase(Musics.begin() + i);
				if (i != 0) i--;
			}
		}
	}

	void SoundSystem::Mute()
	{
		MuteState = true;
		for (unsigned int i = 0; i < Musics.size(); i++)
		{
			Musics[i].snd->setVolume(0);
		}
	}

	void SoundSystem::UnMute()
	{
		MuteState = false;
		for (unsigned int i = 0; i < Musics.size(); i++)
		{
			Musics[i].snd->setVolume(CurrentVolume);
		}
	}

	void SoundSystem::SetVolume(float value)
	{
		CurrentVolume = value;
		if (MuteState) return;
		UnMute();
	}

	float SoundSystem::ReturnCurrentVolume()
	{
		return CurrentVolume;
	}

	SoundSystem::~SoundSystem()
	{
		auto MusicIt = Musics.begin();
		// ������� ��� �������� ����
		for (; MusicIt < Musics.end(); MusicIt++)
		{
			MusicIt->snd->stop();
			delete MusicIt->snd;
		}
		auto DataIt = SoundSources.begin();
		for (; DataIt < SoundSources.end(); DataIt++)
		{
			delete DataIt->first;
		}
	}
 }