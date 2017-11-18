#include "stdafx.h"
#include "ConfigReader.h"

ConfigReader::ConfigReader()
{
}


boss_coord* ConfigReader::ReadBossConfig(std::string filename, std::map<std::string, double> &BossStats)
{
	infile.open(filename);
	if (!infile.is_open())
	{
		// ����� ��������� ����������
	}
	std::stringstream configss; // ����� ��� ������ �� �����
	configss << infile.rdbuf(); // ������ ���� � �����
	std::string configstring = configss.str(); // ������ �� ������ � ������
	std::string tmp = "";
	int i = 0;
	while (configstring[i] != '{')
	{
		tmp += configstring[i];
		i++;
	}
	if (tmp != "BOSS")
	{
		// �������� ����������
	}
	int starti = 0;
	while (configstring[i] == ' ' || configstring[i] == '=\n')
	{
		i++;
	}
	starti = i;
	while (configstring[i] != '}')
	{
		i++;
		if (i > configstring.size())
		{
			// ���������� ����������
		}
	}
	int endi = i - 1;
	ReadBossState(BossStats, configstring.substr(starti,endi));
	boss_coord *f;
	return f;
}

void ConfigReader::ReadBossState(std::map<std::string, double> &Table, std::string str)
{

}

void ConfigReader::ReadRezolutions(std::string filename,std::list<std::string> &OutPutList)
{
	tinyxml2::XMLDocument doc;
	doc.LoadFile(filename.c_str());
	if (doc.ErrorID() != 0) throw Exceptions::XMLDocumentReadError("�� �������� ��������� �������� xml");
	tinyxml2::XMLNode *Root = doc.FirstChild();
	if (Root == nullptr) throw Exceptions::XMLDocumentReadError("������������ ��������� ����������������� �����");
	tinyxml2::XMLElement *FirstRez = Root->FirstChildElement("rez");
	if (FirstRez == nullptr) throw Exceptions::XMLDocumentReadError("� ���������������� ����� �� ���������� ����������");
	do 
	{
		const char *s = FirstRez->GetText();
		std::string tmpstr = s;
		OutPutList.push_back(tmpstr);
		FirstRez = FirstRez->NextSiblingElement("rez");
	} while (FirstRez != nullptr);
}

