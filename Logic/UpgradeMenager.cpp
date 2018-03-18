#include "stdafx.h"
#include "UpgradesMenager.h"

namespace LevelLogic
{
	UpgradesMenager::UpgradesMenager(string BasePath)
	{
		this->BasePath = BasePath;
		ReadConfig();
	}

	void UpgradesMenager::ReadConfig()
	{
		tinyxml2::XMLDocument xmldoc;
		xmldoc.LoadFile((BasePath + "/Upgrades.xml").c_str());
		if (xmldoc.ErrorID() != tinyxml2::XML_SUCCESS) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		tinyxml2::XMLElement *Root = xmldoc.FirstChildElement("Upgrades");
		if (Root == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.ArmorUpgrades.push_back(pair<int, double>(0, 0));
		Config.FirstGunDemageUpgrades.push_back(pair<int, double>(0, 0));
		Config.FirstGunSpeedUpgrades.push_back(pair<int, double>(0, 0));
		Config.SecondGunDemageUpgrades.push_back(pair<int, double>(0, 0));
		Config.SecondGunSpeedUpgrades.push_back(pair<int, double>(0, 0));
		ReadArmorUpgrades(Root);
		ReadFirstGunSpeedUpgrades(Root);
		ReadSecondGunSpeedUpgrades(Root);
		ReadFirstGunDemageUpgrades(Root);
		ReadSecondGunDemageUpgrades(Root);
		ReadSoundIds(Root);
	}

	void UpgradesMenager::ReadSoundIds(tinyxml2::XMLElement *Element)
	{
		tinyxml2::XMLElement *TempElement; // Хранит адрес ноды "Sounds"
		TempElement = Element->FirstChildElement("Sounds");
		if (TempElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		tinyxml2::XMLElement *CurrentElement = TempElement->FirstChildElement("UpId");
		if (CurrentElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.UpId = atoi(CurrentElement->GetText());
		CurrentElement = TempElement->FirstChildElement("BadUpId");
		if (CurrentElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.BadUpId = atoi(CurrentElement->GetText());
		CurrentElement = TempElement->FirstChildElement("ClickId");
		if (CurrentElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.ClickId = atoi(CurrentElement->GetText());
		CurrentElement = TempElement->FirstChildElement("BackId");
		if (CurrentElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.BackId = atoi(CurrentElement->GetText());
		CurrentElement = TempElement->FirstChildElement("SelectId");
		if (CurrentElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		Config.SelectId = atoi(CurrentElement->GetText());
	}

	void UpgradesMenager::ReadOneUpgrade(tinyxml2::XMLElement *Element)
	{
		if (Element == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		tinyxml2::XMLElement *TempElement; // Сдесь будет храниться года с описанием апгрейда
		TempElement = Element->FirstChildElement("Upgrade");
		if (TempElement == NULL) throw Exceptions::LevelMenagerReadError(ErrorMessage);
		pair<double, int> tmpup; // Сдесь храняться извлеченные значения
		do
		{
			tmpup.first = atof(TempElement->GetText());
			TempElement->QueryIntAttribute("cash", &tmpup.second);
			TempUpgradeVector.push_back(tmpup);
			TempElement = TempElement->NextSiblingElement("Upgrade");
		} while (TempElement != NULL);
	}

	void UpgradesMenager::ReadFirstGunSpeedUpgrades(tinyxml2::XMLElement *Element)
	{
		TempUpgradeVector.clear();
		ReadOneUpgrade(Element->FirstChildElement("FirstGunSpeed"));
		//Config.FirstGunSpeedUpgrades.resize(TempUpgradeVector.size() + 1);
		copy(TempUpgradeVector.begin(), TempUpgradeVector.end(), std::back_inserter(Config.FirstGunSpeedUpgrades));
	}

	void UpgradesMenager::ReadSecondGunDemageUpgrades(tinyxml2::XMLElement *Element)
	{
		TempUpgradeVector.clear();
		ReadOneUpgrade(Element->FirstChildElement("SecondGunDemage"));
		//Config.SecondGunDemageUpgrades.resize(TempUpgradeVector.size() + 1);
		copy(TempUpgradeVector.begin(), TempUpgradeVector.end(), std::back_inserter(Config.SecondGunDemageUpgrades));
	}

	void UpgradesMenager::ReadFirstGunDemageUpgrades(tinyxml2::XMLElement *Element)
	{
		TempUpgradeVector.clear();
		ReadOneUpgrade(Element->FirstChildElement("FirstGunDemage"));
		//Config.FirstGunDemageUpgrades.resize(TempUpgradeVector.size() + 1);
		copy(TempUpgradeVector.begin(), TempUpgradeVector.end(), std::back_inserter(Config.FirstGunDemageUpgrades));
	}

	void UpgradesMenager::ReadSecondGunSpeedUpgrades(tinyxml2::XMLElement *Element)
	{
		TempUpgradeVector.clear();
		ReadOneUpgrade(Element->FirstChildElement("SecondGunSpeed"));
		//Config.SecondGunSpeedUpgrades.resize(TempUpgradeVector.size()  + 1);
		copy(TempUpgradeVector.begin(), TempUpgradeVector.end(), std::back_inserter(Config.SecondGunSpeedUpgrades));
	}

	void UpgradesMenager::ReadArmorUpgrades(tinyxml2::XMLElement *Element)
	{
		TempUpgradeVector.clear();
		ReadOneUpgrade(Element->FirstChildElement("ArmorUpgrade"));
		//Config.ArmorUpgrades.resize(TempUpgradeVector.size() + 2);
		copy(TempUpgradeVector.begin(), TempUpgradeVector.end(), std::back_inserter(Config.ArmorUpgrades));
	}

	CurrentPlayerUpgrades * MakeClearPlayerUpgrades()
	{
		CurrentPlayerUpgrades *tmpup = new CurrentPlayerUpgrades();
		tmpup->Armorid = 0;
		tmpup->FirstGunDemageId = 0;
		tmpup->FirstGunSpeedId = 0;
		tmpup->SecondGunDemageId = 0;
		tmpup->SecondGunSpeedId = 0;
		return tmpup;
	}
}