#include "incidence.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void incidence(int x, int y, double arr[x*y][x*y])
{
	int n = x * y;	
	int i;
	int j = 0;
	int k = 1;
	int q = 1;

	for (i = 0; i < n; i++)
	{
		if(i == 0) //pierwszy węzeł
		{
			if(j+1 < n)
				arr[i][j+1] = 1;
			if(j+x < n)
				arr[i][j + x] = 1;
		}
		else if( i == n-1 ) //ostatni węzeł
		{
			if(j-1 < n)
				arr[i][j-1] = 1;
			if(j-x >= 0)
				arr[i][j-x] = 1;
		}
		else if( (i == k*x) && (i != n-1) && (i != 0) ) //lewa strona grafu
		{
			if( y == 2 )
			{
				if(j-x >=0)
					arr[i][j-x] = 1;
				if(j+1 < n)
					arr[i][j+1] = 1;
			}
			else
			{
				if(j-x >=0)
					arr[i][j-x] = 1;
				if(j+1 < n)
					arr[i][j+1] = 1;
				if(j+x < n)
					arr[i][j+x] = 1;
			k++;
			}
		}
		else if( i == x-1) //prawy górny węzeł
		{
			if(j-1 >= 0)
				arr[i][j-1] = 1;
			if(j+x < n)
				arr[i][j+x] = 1;

		}
		else if ( (i == (x-1)+q*x) && (i != n-1) && (i != 0) ) //prawa strona grafu (od drugiego wiersza)
		{
			if(j-x >=0)
				arr[i][j-x] = 1;
			if(j-1 >= 0)
				arr[i][j-1] = 1;
			if(j+x < n)
				arr[i][j+x] = 1;
			q++;
		}
		else //pozostałe węzły
		{
			if(j-x >=0)
				arr[i][j-x] = 1;
			if(j-1 < n)
				arr[i][j-1] = 1;
			if(j+1 < n)
				arr[i][j+1] = 1;
			if(j+x < n)
				arr[i][j+x] = 1;
		}

		j++;
	}
}

