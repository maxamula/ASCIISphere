#pragma once
#include "Console.h"
#include "LightSource.h"
#include <math.h>
#include <vector>


#define Z_AXIS_SIZE 300

void ClearSurface();
void Rain();
void RenderSphere(int a, int b, int c, int r);



bool rainMatrix[CONSOLE_HEIGHT][CONSOLE_WIDTH];

const int projectionCenter[3] = { 63, 15, -15};
const char gradient[6] = { '.', ':', '=', '+', '#', '@' };



void ClearSurface()
{
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			surface[i][j] = ' ';
		}
	}
}


void MainLoop()
{
	bool decC = false;
	ZeroMemory(rainMatrix, sizeof(rainMatrix));
	while (true)
	{
		ClearSurface();

		if (C > 15)
			decC = true;
		if (C < -15)
			decC = false;

		if (decC)
			C--;
		else
			C++;

		RenderSphere(60, 15, 30, 40);

		Rain();

		DrawSurface();
		Sleep(100);
	}

}



void Rain()
{


	ZeroMemory(&rainMatrix[29][0], 120);
	ZeroMemory(&rainMatrix[0][0], 120);
	rainMatrix[0][1 + rand() % 120] = true;
	for (int i = 0; i < CONSOLE_HEIGHT; i++)
	{
		for (int j = 0; j < CONSOLE_WIDTH; j++)
		{
			rainMatrix[29 - i][j] = rainMatrix[29 - i - 1][j];
			if (rainMatrix[29 - i][j] && surface[29 - i][j] == ' ')
				surface[29 - i][j] = '$';

		}
	}
	


}



void RenderSphere(int a, int b, int c, int r)
{
	// опустить прямую с каждой точки плоскости сферу
	// найти нормаль в точке на сфере
	// вычислить степень отклонения от перпендикуляра
	// для точки на плоскости окрасить пиксель 

	for (float x = 1.0f; x < CONSOLE_WIDTH; x++)
	{
		for (float y = 1.0f; y < CONSOLE_HEIGHT; y++)
		{
			for (float z = 1.0f; z < Z_AXIS_SIZE; z++)
			{
				if (7*pow((x - a), 2) + 30*pow((y - b), 2) + pow((z - c), 2) - pow(r, 2) < 1.0)
				{
					float lightReflectionAngle = acos((A * (x - a) + B * (y - b) + C * (z - c)) / (sqrt(pow(A, 2) + pow(B, 2) + pow(C, 2)) * sqrt(pow((x - a), 2) + pow((y - b), 2) + pow((z - c), 2))));
					
					if (lightReflectionAngle > 1.571)
					{
						lightReflectionAngle = 1.571 - (lightReflectionAngle-1.571);
					}

					lightReflectionAngle = abs(lightReflectionAngle);
					
					if (lightReflectionAngle < (1.571) && lightReflectionAngle > (1.396))
					
						surface[(int)y][(int)x] = gradient[1];
					
					else if (lightReflectionAngle < (1.396) && lightReflectionAngle > (1.222))
					
						surface[(int)y][(int)x] = gradient[0];
					
					else if (lightReflectionAngle < (1.222) && lightReflectionAngle > (0.785))
					
						surface[(int)y][(int)x] = gradient[2];
					
					else if (lightReflectionAngle < (0.785) && lightReflectionAngle > (0.523))
					
						surface[(int)y][(int)x] = gradient[3];
					
					else if (lightReflectionAngle < (0.523) && lightReflectionAngle > (0.0))
					
						surface[(int)y][(int)x] = gradient[4];
					
					else
					
						surface[(int)y][(int)x] = '@';

				}
			}
		}
	}
}