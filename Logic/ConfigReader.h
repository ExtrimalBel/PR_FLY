#ifndef CONFIGR_H
#define CONFIGR_H
/*
����� ������ ����� ������������ ������ ��� ������ ����� ���������� ����� ������ � ���������

*/
#include <fstream>
#include <string>
#include <map>
#include "coords.h"
#include <sstream>
class ConfigReader
{
	ConfigReader();
	std::ifstream infile;
	boss_coord* ReadBossConfig(std::string filename,std::map<std::string, double> &);
	void ReadBossState(std::map<std::string, double> &Table, std::string str);
};
#endif