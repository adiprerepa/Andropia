#pragma once
#include <string>

namespace Color
{			
	typedef enum
	{
		COLOR_BLUE = 1,
		COLOR_GREEN,
		COLOR_CYAN,
		COLOR_RED,
		COLOR_PURPLE,
		COLOR_YELLOW,
		COLOR_WHITE,
		COLOR_RESET = 7,
		COLOR_GRAY,
		COLOR_BBLUE,
		COLOR_BGREEN,
		COLOR_BCYAN,
		COLOR_BRED,
		COLOR_BPURPLE,
		COLOR_BYELLOW,
		COLOR_BWHITE,
		COLOR_BGRAY,
	} Color;

	void printcolor(std::string str, Color color = COLOR_RESET);
}
