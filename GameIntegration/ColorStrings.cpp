#include "ColorStrings.h"
#include <Windows.h>

HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);

const char colcatc(Color::ForeColor fcolor, Color::BackColor bcolor)
{
	return fcolor + (bcolor << 4);
}

const char COLOR_RESET = colcatc(Color::FORECOLOR_RESET, Color::BACKCOLOR_RESET);

void Color::print(std::string str, ForeColor fcolor, BackColor bcolor)
{
	SetConsoleTextAttribute(hConsole, colcatc(fcolor, bcolor));
	printf("%s", str.c_str());
	SetConsoleTextAttribute(hConsole, COLOR_RESET);
}

void Color::printcolors(std::string str)
{
	for (unsigned char k = 1; k != 0; ++k)
	{
		SetConsoleTextAttribute(hConsole, k);
		printf("%i %s\n", k, str.c_str());
	}
	SetConsoleTextAttribute(hConsole, COLOR_RESET);
}