#include "from_file.h"

#include <stdio.h>
#include <stdlib.h>

void read_dimentions(char* input, int *x, int *y)
{
	FILE *inf = fopen(input, "r");

        if( inf == NULL)
        {
		fprintf(stderr, "Nie mozna odczytac pliku '%s'.\n\n", input);
		exit(EXIT_FAILURE);
	}

	int x_axis, y_axis; 

        fscanf(inf, "%d %d", &x_axis, &y_axis); //skanowanie wymiarów grafu
	
	*x = x_axis;
	*y = y_axis;

	fclose(inf);
}	

void from_file(char* input, int x, int y, double arr[x*y][x*y])
{	
	FILE *inf = fopen(input, "r");

        if( inf == NULL)
        {
		fprintf(stderr, "Nie mozna odczytac pliku '%s'.\n\n", input);
		exit(EXIT_FAILURE);
	}
 
	//pominięcie pierwszej linii pliku
	char c;
	do{
		c = fgetc(inf);
	} while (c != '\n');

	int node; 	//węzeł
	double value;	//wartość przejścia między węzłami

	int i = 0; // do iteracji po wierszach macierzy incydencji
	
	while(!feof(inf))
	{
		while( (fscanf(inf, "%d: %lf", &node, &value)) != '\n' )
		{
			arr[i][node] = value; //przypisuję wartość przejścia dla odpowiedniego węzła
		}
		i++;
	}

	fclose(inf);
}
