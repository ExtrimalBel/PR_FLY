#include "stdafx.h"
#include "LevelMenager.h"
LevelMenager::LevelMenager(char *path, double cox, double coy, bool Is_new, char *SaveFile)
{
	
	LevelsEnd = false;
	CurLevel = 0;
	IsScreen = false;
	std::string leveln = path;
	leveln += "names.txt";
	this->cox = cox;
	this->coy = coy;
	basepath = "./data/";
	basepath += path;
	ReadLevelNames();
	levelfile.open(basepath + "set.txt");
	if (!levelfile)
		WriteLogFile("file with info of levels did`t open");
	levelfile >> count;
	std::string logmessage = "set of levels" + basepath + " opened";
	WriteLogFile(logmessage.c_str());
	State = LevelState::TranScr;
	LevelLoaded = false;
	std::thread thr = std::thread(&LevelMenager::LoadLevel,this);
	thr.detach();
	TRSCR = new Screens::TransitScreen(cox, coy, LevelNames[CurLevel].c_str());
}

int LevelMenager::LoadLevel()
{
	char pathtoenemy[100];
	levelfile >> pathtoenemy;
	std::string resultpath = basepath + pathtoenemy;
	WriteLogFile(resultpath.c_str());
	CurrentLevel = new Level(resultpath.c_str(), cox, coy,true,"");
	LevelLoaded = true;
	return 1;
}


void LevelMenager::Update(float time, sf::RenderWindow &window)
{
	/*
	if (LevelsEnd)
	{
		return;
	}
	if (IsScreen)
	{
		TRSCR->Update(window);
		if (TRSCR->IfExit()) IsScreen = false;
		return;
	}
	if (CurrentLevel->ReturnLevelEnd())
	{
		if (CurLevel == count)
		{
			LevelsEnd = true;
		}
		TRSCR = new Screens::TransitScreen(cox, coy, LevelNames[CurLevel].c_str());
		IsScreen = true;
		LoadNextLevel();
		return;
	}
	else
	{
		CurrentLevel->UpdateLevel(time, window);
		return;
	}*/
	switch (State)
	{
	case LevelState::TranScr:
		TRSCR->Update(window);
		if (LevelLoaded)
		{
			TRSCR->SetStateOfScreen(1);
		}
		if (TRSCR->IfExit())
		{
			State = LevelState::InGame;
			delete TRSCR;
			TRSCR = NULL;
			CurrentLevel->ResetClocks();
		}
		break;
	case LevelState::InGame:
		if (CurrentLevel->ReturnLevelEnd())
		{
			CurLevel++;
			if (CurLevel >= count)
			{
				State = LevelState::Pause;
				break;
			}
			LevelLoaded = false;
			
			TRSCR = new Screens::TransitScreen(cox, coy, LevelNames[CurLevel].c_str());
			std::thread thr = std::thread(&LevelMenager::LoadNextLevel, this);
			thr.detach();
			State = LevelState::TranScr;
		}
		else if (TRSCR == NULL)
		{
			CurrentLevel->UpdateLevel(time, window);
		}
	}


}

double LevelMenager::GetHealth()
{
	if (!LevelLoaded) return 100;
	return CurrentLevel->GetPlayerHealth(); 
}

int LevelMenager::LoadNextLevel()
{
	
	
	if (CurLevel >= count)
	{
		LevelsEnd = true;
	}
	else
	{
		delete CurrentLevel;
		LoadLevel();
	}
	
	return 0;
}

void LevelMenager::ReadLevelNames()
{
	levelnames.open(basepath + "names.txt");
	levelnames >> count;
	LevelNames = new std::string[count];
	for (int i = 0; i < count; i++)
	{
		std::string tmpstr;
		levelnames >> tmpstr;
		LevelNames[i] = tmpstr;
	}
}