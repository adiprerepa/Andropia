#include "ColorStrings.h"
#include <Windows.h>
#include <iostream>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Color::printcolor(std::string str, Color color)
{
	SetConsoleTextAttribute(hConsole, color);
	std::cout << str;
	SetConsoleTextAttribute(hConsole, Color::COLOR_RESET);
}
