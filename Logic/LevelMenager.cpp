#include "stdafx.h"
#include "LevelMenager.h"

namespace LevelLogic
{

	bool SortEnemyConfigs(pair<Ships::BaseEnemyState,int> &str1,pair<Ships::BaseEnemyState,int> &str2)
	{
		return str1.first.SpawnTime < str2.first.SpawnTime;
	}
	LevelMenager::LevelMenager(string BasePath, int StartLevel)
	{
		this->BasePath = BasePath;
		ReadLevelConfig(); // Сдесь читаем данные об уровнях из xml файла
		if (VectorOfLevelConfig.size() < StartLevel) throw Exceptions::LevelMenagerCreateError("Неправильо задан начальный уровень");
		this->CurrentLevel = StartLevel;
		// Сортируем врагов на уровнях
		for each(LevelConfigStruct var in VectorOfLevelConfig)
		{
			sort(var.EnemySVector.begin(), var.EnemySVector.end(), SortEnemyConfigs);
		}
		

	}
	
	LevelMenager::LevelMenager(string BasePath) : LevelMenager(BasePath, 1) {}

	void LevelMenager::ReadLevelConfig()
	{
		string ErrorMessage = "Невозможно прочитать конфигурацию уровней";
		tinyxml2::XMLDocument xmldoc;
		xmldoc.LoadFile((BasePath + "/levels/main.xml").c_str());
		if (xmldoc.ErrorID() != NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		tinyxml2::XMLNode *Root = xmldoc.FirstChildElement("levels");
		if (Root == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		tinyxml2::XMLNode *LevelNode = Root->FirstChildElement("level");
		int LevelNumber = 1; 
		if (LevelNode == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		// Чиатем все уровни по порядку
		do
		{
			LevelConfigStruct tmpstr;
			VectorOfLevelConfig.push_back(tmpstr);
			auto LevelIt = VectorOfLevelConfig.end() - 1;
			tinyxml2::XMLElement *tmpElement = LevelNode->FirstChildElement("BackMusic");
			if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			LevelIt->BackGroundSoundId = atoi(tmpElement->GetText());
			tmpElement = LevelNode->FirstChildElement("BackGroundImage");
			if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			LevelIt->BackGroundPath = tmpElement->GetText();
			tmpElement = LevelNode->FirstChildElement("EnemyPath");
			if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			LevelIt->PathToEnemyConfig = tmpElement->GetText();
			LevelIt->LevelName = LevelNode->ToElement()->Attribute("Name");
			tmpElement = LevelNode->FirstChildElement("SplashPath");
			if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			LevelIt->SlpashPath = tmpElement->GetText();
			tmpElement = LevelNode->FirstChildElement("EndSplash");
			if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
				LevelIt->EndSplashPath = tmpElement->GetText();
				tmpElement = LevelNode->FirstChildElement("StartRockets");
				if (tmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
				LevelIt->StartRocketsCount = atoi(tmpElement->GetText());
			ReadShipsData(LevelIt->EnemySVector,LevelIt->PathToEnemyConfig);
			LevelIt->LevelNumber = LevelNumber++;
			//Only For Debug
			cout << "LevelInfo" << endl;
			cout << "Level Name: " << LevelIt->LevelName << endl;
			cout << "SplashPath" << LevelIt->SlpashPath << endl;
			cout << "EndSplash" << LevelIt->EndSplashPath << endl;
			cout << "Level id " << LevelIt->LevelNumber << endl;
			cout << "Music id" << LevelIt->BackGroundSoundId << endl;
			cout << "Background path" << LevelIt->BackGroundPath << endl;
			cout << "EnemyPath" << LevelIt->PathToEnemyConfig << endl;
			LevelNode = LevelNode->NextSiblingElement();

		} while (LevelNode != NULL);
	}

	void LevelMenager::ReadShipsData(vector<pair<Ships::BaseEnemyState, int>> &ShipsVector, string pathToEnemyConfig)
	{
		tinyxml2::XMLDocument xmldoc;
		xmldoc.LoadFile((BasePath + "/levels/" + pathToEnemyConfig).c_str());
		if (xmldoc.ErrorID() != NULL) throw Exceptions::LevelMenagerReadError("Невозможно прочитать информацию о врагах");
		tinyxml2::XMLNode *Root = xmldoc.FirstChildElement("Enemys");
		if (Root == NULL) throw Exceptions::LevelMenagerReadError("Невозможно прочитать информацию о врагах");
		WriteDataOfEnemyType(Root, "MovingEnemy", 1, ShipsVector);
		WriteDataOfEnemyType(Root, "StayEnemy", 2, ShipsVector);
		ReadSetOfShipsData(Root, "SetMovingEnemy", 1, ShipsVector);
		ReadSetOfShipsData(Root, "SetStayEnemy", 2, ShipsVector);
		WriteDataOfEnemyType(Root, "RandomMovingEnemy", 3,ShipsVector);
		ReadSetOfShipsData(Root, "SetRandomMovingEnemy", 3, ShipsVector);
		for (int i = 0; i < ShipsVector.size(); i++)
		{
			auto it = ShipsVector.begin() + i;
			if (it->second == 1) cout << "Name: MovingEnemy" << endl;
			else cout << "name: StayEnemy" << endl;
			cout << it->first.EnemyImgPath << endl;
			cout << it->first.GunDemage << endl;
			cout << it->first.GunSpeed << endl;
			cout << it->first.Health << endl;
			cout << it->first.SpawnTime << endl;
			cout << it->first.Speed << endl;
			for (int i = 0; i < it->first.MovingCoordinates.size(); i++)
			{
				cout << "(" << it->first.MovingCoordinates[i].first << "," << it->first.MovingCoordinates[i].second << ")";
			}
			cout << endl;
		}
	}

	void LevelMenager::ReadSetOfShipsData(tinyxml2::XMLNode *MainNode, string EnemyName, int Id, vector<pair<Ships::BaseEnemyState, int>> &ShipsVector)
	{
		string ErrorMessage = "Невозможно прочитать информацию о врагах";
		tinyxml2::XMLNode *EnemyNode = MainNode->FirstChildElement(EnemyName.c_str());
		if (EnemyNode == NULL) return; // Нет записей с указанным типом врагов
		do
		{
			pair<Ships::BaseEnemyState, int> TmpNode;
			TmpNode.second = Id;
			//auto EnemyIt = ShipsVector.end() - 1;
			TmpNode.second = Id;
			tinyxml2::XMLElement *TmpElement = EnemyNode->FirstChildElement("EnemyImg");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.EnemyImgPath = TmpElement->GetText();
			TmpElement = EnemyNode->FirstChildElement("GunSpeed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.GunSpeed = atoi(TmpElement->GetText());
			TmpNode.first.GunSpeed /= 10;
			TmpElement = EnemyNode->FirstChildElement("GunDemage");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.GunDemage = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("Speed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.Speed = atoi(TmpElement->GetText());
			TmpNode.first.Speed /= 100;
			TmpElement = EnemyNode->FirstChildElement("Health");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.Health = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("SpawnTime");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.SpawnTime = atof(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("BulletSpeed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.BulletSpeed = atof(TmpElement->GetText());
			TmpNode.first.BulletSpeed /= 10;
			TmpElement = EnemyNode->FirstChildElement("FrameCount");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.FrameCount = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("Reward");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.Reward = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("FrameTime");
			TmpNode.first.FrameTime = atof(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("Coord");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			do
			{
				pair<int, int> TempPair;
				TmpElement->QueryAttribute("X", &TempPair.first);
				TmpElement->QueryAttribute("Y", &TempPair.second);
				TmpNode.first.MovingCoordinates.push_back(TempPair);
				TmpElement = TmpElement->NextSiblingElement("Coord");
			} while (TmpElement != NULL);
			int CountOfEnemys;
			double DelayTime;
			TmpElement = EnemyNode->FirstChildElement("BulletPath");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			TmpNode.first.EnemyBulletPath = TmpElement->GetText();
			TmpElement = EnemyNode->FirstChildElement("Count");
			if (TmpElement == NULL) throw Exceptions::LevelReadError(ErrorMessage);
			CountOfEnemys = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("Delay");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			DelayTime = atof(TmpElement->GetText());
			double TempDelay = TmpNode.first.SpawnTime;
			int i = 0;
			for (int i = 0; i < CountOfEnemys;i++,TempDelay += DelayTime)
			{
				pair<Ships::BaseEnemyState, int> PushStr;
				ShipsVector.push_back(PushStr);
				auto It = ShipsVector.end() - 1;
				It->first.EnemyImgPath = TmpNode.first.EnemyImgPath;
				It->first.GunDemage = TmpNode.first.GunDemage;
				It->first.GunSpeed = TmpNode.first.GunSpeed;
				It->first.Health = TmpNode.first.Health;
				It->first.MovingCoordinates.resize(TmpNode.first.MovingCoordinates.size());
				copy(TmpNode.first.MovingCoordinates.begin(), TmpNode.first.MovingCoordinates.end(), It->first.MovingCoordinates.begin());
				It->first.EnemyBulletPath = TmpNode.first.EnemyBulletPath;
				It->first.SpawnTime = TempDelay;
				It->first.Speed = TmpNode.first.Speed;
				It->first.BulletSpeed = TmpNode.first.BulletSpeed;
				It->first.FrameCount = TmpNode.first.FrameCount;
				It->first.FrameTime = TmpNode.first.FrameTime;
				It->first.Reward = TmpNode.first.Reward;
				It->second = Id;
			}
			EnemyNode = EnemyNode->NextSiblingElement(EnemyName.c_str());
		} while (EnemyNode != NULL);
	}

	void LevelMenager::WriteDataOfEnemyType(tinyxml2::XMLNode *MainNode, string EnemyName, int Id,vector<pair<Ships::BaseEnemyState, int>> &ShipsVector)
	{
		string ErrorMessage = "Невозможно прочитать информацию о врагах";
		tinyxml2::XMLNode *EnemyNode = MainNode->FirstChildElement(EnemyName.c_str());
		if (EnemyNode == NULL) return; // Нет записей с указанным типом врагов
		do
		{
			pair<Ships::BaseEnemyState, int> TmpNode;
			ShipsVector.push_back(TmpNode);
			auto EnemyIt = ShipsVector.end() - 1;
			EnemyIt->second = Id;
			tinyxml2::XMLElement *TmpElement = EnemyNode->FirstChildElement("EnemyImg");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.EnemyImgPath = TmpElement->GetText();
			TmpElement = EnemyNode->FirstChildElement("GunSpeed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.GunSpeed = atoi(TmpElement->GetText());
			EnemyIt->first.GunSpeed /= 10;
			TmpElement = EnemyNode->FirstChildElement("GunDemage");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.GunDemage = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("Speed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.Speed = atoi(TmpElement->GetText());
			EnemyIt->first.Speed /= 100; 
			TmpElement = EnemyNode->FirstChildElement("Health");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.Health = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("SpawnTime");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.SpawnTime = atof(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("BulletPath");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.EnemyBulletPath = TmpElement->GetText();
			TmpElement = EnemyNode->FirstChildElement("Reward");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.Reward = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("FrameCount");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.FrameCount = atoi(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("FrameTime");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.FrameTime = atof(TmpElement->GetText());
			TmpElement = EnemyNode->FirstChildElement("BulletSpeed");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			EnemyIt->first.BulletSpeed = atof(TmpElement->GetText());
			EnemyIt->first.BulletSpeed /= 10; 
			TmpElement = EnemyNode->FirstChildElement("Coord");
			if (TmpElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
			do
			{
				pair<int, int> TempPair;
				TmpElement->QueryAttribute("X",&TempPair.first);
				TmpElement->QueryAttribute("Y", &TempPair.second);
				EnemyIt->first.MovingCoordinates.push_back(TempPair);
				TmpElement = TmpElement->NextSiblingElement("Coord");
			} while (TmpElement != NULL);
			EnemyNode = EnemyNode->NextSiblingElement(EnemyName.c_str());
		} while (EnemyNode != NULL);
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