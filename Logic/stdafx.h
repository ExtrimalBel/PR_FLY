// stdafx.h: ���������� ���� ��� ����������� ��������� ���������� ������
// ��� ���������� ������ ��� ����������� �������, ������� ����� ������������, ��
// �� ����� ����������
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // ��������� ����� ������������ ���������� �� ���������� Windows
// ����� ���������� Windows:
#include <windows.h>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif


// TODO: ���������� ����� ������ �� �������������� ���������, ����������� ��� ���������
#include <algorithm>
#include <SoundControl.h>
#include "PixelPerfect.h"
#include "ExceptionsDefenitions.hpp"
#include <SoundControl.h>
LOGIC_API void WriteLogFile(const char* szString);