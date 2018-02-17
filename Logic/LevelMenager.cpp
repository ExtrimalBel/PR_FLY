#include "stdafx.h"
#include "LevelMenager.h"

namespace LevelLogic
{
	LevelMenager::LevelMenager(string BasePath, int StartLevel)
	{
		this->BasePath = BasePath;
		ReadLevelConfig(); // ����� ������ ������ �� ������� �� xml �����
		if (VectorOfLevelConfig.size() > StartLevel) throw Exceptions::LevelMenagerCreateError("���������� ����� ��������� �������");
		this->CurrentLevel = StartLevel;
		

	}
	
	LevelMenager::LevelMenager(string BasePath) : LevelMenager(BasePath, 1) {}

	void LevelMenager::ReadLevelConfig()
	{
		tinyxml2::XMLDocument xmldoc;
		xmldoc.LoadFile((BasePath + "/levels/main.xml").c_str());
		if (xmldoc.ErrorID() != NULL) throw Exceptions::LevelMenagerReadError("���������� ��������� ������������ �������");
		tinyxml2::XMLNode *Root = xmldoc.FirstChildElement("levels");
		if (Root = NULL) throw Exceptions::LevelMenagerReadError("���������� ��������� ������������ �������");
		tinyxml2::XMLNode *LevelNode = Root->FirstChildElement("level");
		int LevelNumber = 1;
		if (LevelNode == NULL) throw Exceptions::LevelMenagerReadError("���������� ��������� ������������ �������");
		do
		{
			LevelConfigStruct tmpstr;// c����
			VectorOfLevelConfig.push_back(tmpstr);
			auto LevelIt = VectorOfLevelConfig.end() - 1;
			tinyxml2::XMLElement *tmpElement = LevelNode->FirstChildElement("BackMusic");

			LevelIt->BackGroundSoundId = atoi(tmpElement->GetText());
		} while (LevelNode != NULL);
	}

	void LevelMenager::ReadShipsData(vector<pair<Ships::BaseEnemyState, int>> &ShipsVector)
	{

	}

	LevelConfigStruct * LevelMenager::ReturnCurrentLevelConfig()
	{
		return &(VectorOfLevelConfig[CurrentLevel - 1]);
	}

	void LevelMenager::NextLevel()	{ CurrentLevel++; }

	void LevelMenager::PrevLevel() { CurrentLevel--; }

	bool LevelMenager::CheckIfLastLevel()
	{
		return (CurrentLevel > VectorOfLevelConfig.size() || CurrentLevel < 1 ? true : false);
	}
}