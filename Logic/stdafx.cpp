// stdafx.cpp: �������� ����, ���������� ������ ����������� ���������� ������
// Logic.pch ����� ������������������� ����������
// stdafx.obj ����� ��������� �������������� ����������������� �������� � ����

#include "stdafx.h"

// TODO: ���������� ������ �� ����� ����������� �������������� ��������� � ����� STDAFX.H
// , � �� � ������ �����
LOGIC_API void  WriteLogFile(const char* szString)
{


	FILE* pFile = fopen("logFile.txt", "a");
	fprintf(pFile, "%s\n", szString);
	fclose(pFile);

}

