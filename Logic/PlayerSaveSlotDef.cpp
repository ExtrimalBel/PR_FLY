#include "stdafx.h"
#include "PlayerSaveSlotDef.h"

namespace LoadAndSave
{
	SaveSlot LoadFromFile(string BasePath, int SaveSlot)
	{
		string PathToSaveFile;
		switch (SaveSlot)
		{
		case 1:
			PathToSaveFile = BasePath + "/saves/slot1.bin";
			break;
		case 2:
			PathToSaveFile = BasePath + "/saves/slot2.bin";
			break;
		case 3:
			PathToSaveFile = BasePath + "/saves/slot3.bin";
			break;
		default:
			throw Exceptions::GameLoadError("Невозможно загрузить игру");
			break;
		}
		ifstream infile;
		infile.open(PathToSaveFile,ios::binary);
		if (!infile.is_open()) throw Exceptions::GameLoadError("Невозможно открыть файл " + PathToSaveFile);
		LoadAndSave::SaveSlot tmpslot;
		char *tmpmas = new char[sizeof(tmpslot)];
		infile.read(tmpmas, sizeof(tmpslot));
		tmpslot = *((LoadAndSave::SaveSlot*)tmpmas);
		infile.close();
		return tmpslot;
	}

	void SaveToFile(SaveSlot DataToSave, string BasePath, int SaveSlot)
	{
		string PathToSaveFile;
		switch (SaveSlot)
		{
		case 1:
			PathToSaveFile = BasePath + "/saves/slot1.bin";
			break;
		case 2:
			PathToSaveFile = BasePath + "/saves/slot2.bin";
			break;
		case 3:
			PathToSaveFile = BasePath + "/saves/slot3.bin";
			break;
		default:
			throw Exceptions::GameSaveError("Невозможно сохранить игру");
			break;
		}
		ofstream outfile;
		outfile.open(PathToSaveFile, ios::binary);
		if (!outfile.is_open()) throw Exceptions::GameSaveError("Невозможно сохранить игру");
		outfile.write((char *)(&DataToSave), sizeof(LoadAndSave::SaveSlot));
		outfile.close();
	}
}