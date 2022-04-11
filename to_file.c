#include "to_file.h"

#include <stdio.h>
#include <stdlib.h>

void to_file(int x, int y, double arr[x*y][x*y], char* output)
{
	FILE* out = fopen(output, "w");
	
	if( out == NULL )
	{
		fprintf(stderr, "%s", "Nie udalo sie otworzyć pliku wyjsciowego.\n");
		exit(EXIT_FAILURE);
	}

	int i, j;
	int n = x * y;
	
	fprintf(out, "%d %d\n", x, y);

	for(i = 0; i < n; i++)
	{
		fprintf(out, "\t");

		for(j = 0; j < n; j++)
		{
			if(arr[i][j] != -1)
			{
				fprintf(out, "%d: %f ", j, arr[i][j]);
			}
		}
		if( i != n-1 )
			fprintf(out, "\n");	
	}

	fclose(out);
}
