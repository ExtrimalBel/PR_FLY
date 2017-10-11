// stdafx.h: включаемый файл дл€ стандартных системных включаемых файлов
// или включаемых файлов дл€ конкретного проекта, которые часто используютс€, но
// не часто измен€ютс€
//

#pragma once

#include "targetver.h"

#define WIN32_LEAN_AND_MEAN             // »сключите редко используемые компоненты из заголовков Windows
// ‘айлы заголовков Windows:
#include <windows.h>
#ifdef LOGIC_EXPORTS
#define LOGIC_API __declspec(dllexport)
#else
#define LOGIC_API __declspec(dllimport)
#endif


// TODO: ”становите здесь ссылки на дополнительные заголовки, требующиес€ дл€ программы
#include <algorithm>

#include "PixelPerfect.h"
#include "ExceptionsDefenitions.hpp"

LOGIC_API void WriteLogFile(const char* szString);