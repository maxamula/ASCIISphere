#pragma once
#include <iostream>
#include <string>
#include <string>

#define CONSOLE_WIDTH 120
#define CONSOLE_HEIGHT 30

int surface[CONSOLE_HEIGHT][CONSOLE_WIDTH];

void DrawSurface()
{
	std::string output = "";
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			output += surface[i][j];
		}
		output += "\n";
	}
	std::cout << output;
}




