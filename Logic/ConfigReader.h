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
#include <vector>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif
class LOGIC_API ConfigReader
{
private:
	static std::vector<int>* ReadGameConfigArch(std::string Path);
	static std::vector<int>* ReadGameConfigFile(std::string Path);
public:
	ConfigReader();
	std::ifstream infile;
	static void ReadRezolutions(std::string filename, std::list<std::string> &OutPutList); // Читает разрешения экрана из файла
	static std::vector<int>* ReadGameConfig(std::string Path);
};
#endif