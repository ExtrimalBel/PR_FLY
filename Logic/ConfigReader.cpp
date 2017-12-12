#include "stdafx.h"
#include "ConfigReader.h"

ConfigReader::ConfigReader()
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


std::vector<int>* ConfigReader::ReadGameConfigFile(std::string Path,EnemyEventDef::GameOptions &Options)
{
	std::vector<int> *ReturnVec = new std::vector<int>;
	tinyxml2::XMLDocument xmldoc;
	xmldoc.LoadFile(Path.c_str());
	if (xmldoc.ErrorID() != 0) throw Exceptions::XMLDocumentReadError("������ ��� ������ �������� ����");
	tinyxml2::XMLNode *Root = xmldoc.FirstChild();
	if (Root == nullptr) throw Exceptions::XMLDocumentReadError("������������ ��������� ����������������� �����");
	if (Root->Value != "GameSettings") throw Exceptions::XMLDocumentReadError("������ ��� ������ ����� ��������");
	tinyxml2::XMLNode *VideoElement = Root->FirstChildElement("VideoMode");
	if (VideoElement == nullptr) throw Exceptions::XMLDocumentReadError("������ ��� ������ ����� ��������");
	int vidx = 0, vidy = 0,volume = 0,mode = 0;
	tinyxml2::XMLElement *VideoModeElement = VideoElement->ToElement();
	VideoModeElement->QueryAttribute("height", &vidx);
	VideoModeElement->QueryAttribute("width", &vidx);
	std::string Mode = VideoModeElement->GetText();
	if (Mode == "Windowed") mode = 1;
	else if (Mode == "Fullscreen") mode = 2;
	else  throw Exceptions::XMLDocumentReadError("������ ��� ������ ����� ��������");
		VidxElem->

}
