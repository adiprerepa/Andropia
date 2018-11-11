#include "ColorStrings.h"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

void Color::printcolor(std::string str, Color color)
{
	SetConsoleTextAttribute(hConsole, color);
	printf("%s", str.c_str());
	SetConsoleTextAttribute(hConsole, Color::COLOR_RESET);
}
