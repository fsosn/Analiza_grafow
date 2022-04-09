#include "from_file.h"

#include <stdio.h>
#include <stdlib.h>

double* from_file(char* input)
{
	FILE *inf = fopen(input, "r");

        if( inf == NULL)
        {
		fprintf(stderr, "Nie mozna odczytac pliku '%s'.\n\n", input);
		exit(EXIT_FAILURE);
	}
 
        printf("Czytam z pliku '%s'", input);
	
	int x, y;
        fscanf(inf, "%d %d", &x, &y); //skanowanie wymiarów grafu
	
	int p = x*y; //wymiar krawędzi macierzy incydencji

	double (*arr)[p] = calloc(p, sizeof *arr);
	
	if(arr == NULL)
	{
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
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

	return *arr;
}
