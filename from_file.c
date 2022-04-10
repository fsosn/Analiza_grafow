#include "from_file.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX 1024

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
	
	//przypisanie uzyskanych wartości do parametrów wykorzystywanych w programie
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

	//liczba wierszy z wartościami przejścia	
	char q;
	
	//sprawdzenie ile jest wierszy z węzłami w pliku
	int NumberOfRows = 0;

	for (q = getc(inf); q != EOF; q = getc(inf)){
		if (q == '\n')
		{
			NumberOfRows++;
		}
	}
	
	char buf[MAX]; 		// bufor
	int node_number = 0; 	// numer węzła
	int val; 		// ile jest połączeń wychodzących od danego węzła
	int i = 0; 		// do iteracji po buforze

	//alokacja pamięci na tablicę przechowującą informacje o liczbie
	//połączeń z innymi wierzchołkami dla danego węzła
	int* LinksArray = (int*)calloc(NumberOfRows, sizeof(int));
	
	//pominięcie pierwszej linii pliku
	rewind(inf);
	do{
		c = fgetc(inf);
	} while (c != '\n');


	while( fgets(buf, MAX, inf) != NULL )
	{
		val = 0;
		while( buf[i] != '\n' )
		{
			if( buf[i] == ':' )
			{
				val++;
			}
			i++;
		}
		i = 0;
		LinksArray[node_number] = val;
		node_number++;
	
	}

	//pominięcie pierwszej linii pliku
	rewind(inf);
	do{
		c = fgetc(inf);
	} while (c != '\n');

	int row, LinkNum, HowManyLinks;
	
	for(row=0; row <= NumberOfRows; row++)
	{
		HowManyLinks = LinksArray[row];
		for(LinkNum=0; LinkNum < HowManyLinks; LinkNum++)
		{
			fscanf(inf, "%d : %lg", &node, &value);
			arr[row][node] = value; //przypisuję wartość przejścia dla odpowiedniego węzła
		}

	}

	fclose(inf);
}
