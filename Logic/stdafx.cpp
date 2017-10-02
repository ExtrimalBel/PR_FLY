// stdafx.cpp: исходный файл, содержащий только стандартные включаемые модули
// Logic.pch будет предкомпилированным заголовком
// stdafx.obj будет содержать предварительно откомпилированные сведения о типе

#include "stdafx.h"

// TODO: Установите ссылки на любые требующиеся дополнительные заголовки в файле STDAFX.H
// , а не в данном файле
LOGIC_API void  WriteLogFile(const char* szString)
{


	FILE* pFile = fopen("logFile.txt", "a");
	fprintf(pFile, "%s\n", szString);
	fclose(pFile);

}

