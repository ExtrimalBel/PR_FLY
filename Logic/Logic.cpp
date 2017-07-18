// Logic.cpp: определяет экспортированные функции для приложения DLL.
//

#include "stdafx.h"
#include "Logic.h"
#include <iostream>

// Пример экспортированной переменной
LOGIC_API int nLogic=0;

// Пример экспортированной функции.
LOGIC_API int fnLogic(void)
{
	
	return 42;
}

// Конструктор для экспортированного класса.
// см. определение класса в Logic.h
