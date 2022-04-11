#include "randval.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void ChangeZeroes(int x, int y, double arr[x * y][x * y])
{
	int i, j;
	int n = x * y;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (arr[i][j] == 0)
				arr[i][j] = -1;
}

void randval(int x, int y, double arr[x * y][x * y], double min, double max)
{
	int i, j;
	int n = x * y;
	double random_value;

	ChangeZeroes(x, y, arr);

	srand(time(NULL));

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (arr[i][j] == 1)
			{
				random_value = ((double)rand() * (max - min)) / (double)RAND_MAX + min;

				arr[i][j] = random_value;
				arr[j][i] = arr[i][j];
			}
		}
	}
}
