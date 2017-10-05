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
		// Сдесь прописать исключение
	}
	std::stringstream configss; // Поток для чтения из файла
	configss << infile.rdbuf(); // Читаем файл в поток
	std::string configstring = configss.str(); // Читаем из потока в строку
	std::string tmp = "";
	int i = 0;
	while (configstring[i] != '{')
	{
		tmp += configstring[i];
		i++;
	}
	if (tmp != "BOSS")
	{
		// Дописать исключение
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
			// Обработать исключение
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