#include "from_file.h"

#include <stdio.h>
#include <stdlib.h>

#define MAX 512

void read_dimentions(char* input, int* x, int* y)
{
	FILE* inf = fopen(input, "r");

	if (inf == NULL)
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

void SkipFirstLine(FILE* input)
{
	rewind(input);
	char c;
	do {
		c = fgetc(input);
	} while (c != '\n');
}

void from_file(char* input, int x, int y, double arr[x * y][x * y])
{
	FILE* inf = fopen(input, "r");

	if (inf == NULL)
	{
		fprintf(stderr, "Nie mozna odczytac pliku '%s'.\n\n", input);
		exit(EXIT_FAILURE);
	}

	//sprawdzenie ile jest wierszy z węzłami w pliku
	int NumberOfRows = 0; 	//liczba wierszy z wartościami przejścia	
	char q;

	SkipFirstLine(inf); //pominięcie pierwszej linii, w której są jedynie wymiary grafu

	for (q = getc(inf); q != EOF; q = getc(inf)) {
		if (q == '\n')
		{
			NumberOfRows++;
		}
	}

	char buf[MAX]; 		// bufor
	int node_number = 0; 	// numer węzła
	int NumOfLinks; 		// ile jest połączeń wychodzących od danego węzła
	int i = 0; 		// do iteracji po buforze

	//alokacja pamięci na tablicę przechowującą informacje o liczbie
	//połączeń z innymi wierzchołkami dla danego węzła
	int* LinksArray = (int*)calloc(NumberOfRows, sizeof(int));

	SkipFirstLine(inf);

	while (fgets(buf, MAX, inf) != NULL)
	{
		NumOfLinks = 0;
		while (buf[i] != '\n')
		{
			if (buf[i] == ':')	//jeśli zostanie znaleziony dwukropek, oznacza to, że występuje połączenie między węzłami
			{
				NumOfLinks++;	//zostaje wtedy zwiększona liczba połączeń
			}
			i++;
		}
		i = 0;
		LinksArray[node_number] = NumOfLinks; //informacja o liczbie połączeń wychodzących od danego wezła jest zapisywana do tej tablicy
		node_number++;
	}

	SkipFirstLine(inf);

	int row, node, LinkNum, HowManyLinks;
	double value;	//wartość przejścia między węzłami

	for (row = 0; row <= NumberOfRows; row++)
	{
		HowManyLinks = LinksArray[row];
		for (LinkNum = 0; LinkNum < HowManyLinks; LinkNum++)
		{
			fscanf(inf, "%d : %lg", &node, &value); //skanowanie po pliku według ustalonego formatu
			arr[row][node] = value; //przypisuję wartość przejścia dla odpowiedniego węzła
		}
	}

	fclose(inf);
}