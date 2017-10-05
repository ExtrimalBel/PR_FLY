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