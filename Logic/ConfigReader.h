#ifndef CONFIGR_H
#define CONFIGR_H
/*
Класс читает файлы конфигурации боссов или врагов тутже происходит отлов ошибок в синаксисе

*/
#include <fstream>
#include <string>
#include <map>
#include "coords.h"
#include <sstream>
#include "ExceptionsDefenitions.hpp"
#include "tinyxml2.h"
#include <iostream>
#include <list>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API ConfigReader
{
public:
	ConfigReader();
	std::ifstream infile;
	boss_coord* ReadBossConfig(std::string filename,std::map<std::string, double> &);
	void ReadBossState(std::map<std::string, double> &Table, std::string str);
	static void ReadRezolutions(std::string filename, std::list<std::string> &OutPutList); // Читает разрешения экрана из файла
};
#endif