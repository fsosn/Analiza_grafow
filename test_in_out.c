#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LENGHT 512
#define MAX_NAME 32

// U¿ycie: 
// ./test_in_out bfs1 bfs2 dij1 dij2
// 
// Gdzie: 
// bfs1 i bfs2 to odpowiednio nazwy pliku zawieraj¹cych informacje o BFS uzyskanych z obu trybów programu (dla tego samego grafu),
// dij1 i dij2 to odpowiednio nazwy pliku zawieraj¹cych informacje o Dijkstrze uzyskanych z obu trybów programu (dla tego samego grafu),

int main(int argc, char** argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "\nNiepoprawnie wprowadzone argumenty.\n");
		exit(EXIT_FAILURE);
	}
	// ³añcuchy pomocnicze do skanowania pliku
	char str1[MAX_LENGHT];
	char str2[MAX_LENGHT];
	char str3[MAX_LENGHT];
	char str4[MAX_LENGHT];

	//nazwy plików z informacjami o bfs
	char bfs1[MAX_NAME];
	char bfs2[MAX_NAME];

	//nazwy plików z informacjami o dijkstrze
	char dij1[MAX_NAME];
	char dij2[MAX_NAME];

	int passed = 0;

	snprintf(bfs1, sizeof(bfs1), "%s", argv[1]);
	snprintf(bfs2, sizeof(bfs2), "%s", argv[2]);
	snprintf(dij1, sizeof(dij1), "%s", argv[3]);
	snprintf(dij2, sizeof(dij2), "%s", argv[4]);

	FILE* f_bfs1 = fopen(bfs1, "r");
	FILE* f_bfs2 = fopen(bfs2, "r");
	FILE* f_dij1 = fopen(dij1, "r");
	FILE* f_dij2 = fopen(dij2, "r");

	if (f_bfs1 == NULL || f_bfs2 == NULL || f_dij1 == NULL || f_dij2 == NULL)
	{
		fprintf(stderr, "\nNie mozna otworzyc jednego z plikow.\n");
		exit(EXIT_FAILURE);
	}

	printf("\nRozpoczynam test uzyskanych wynikow z trybu zapisu i odczytu:\n\n");

	while (!feof(f_bfs1) && !feof(f_bfs2))
	{
		if (!feof(f_bfs1) && !feof(f_bfs2))
		{
			fgets(str1, MAX_LENGHT, f_bfs1);
			fgets(str2, MAX_LENGHT, f_bfs2);

			if (strcmp(str1, str2) != 0)
			{
				fprintf(stdout, "\tTest nieudany dla plikow '%s' oraz '%s'.\n\n", bfs1, bfs2);
				passed--;
				break;
			}
		}
	}
	passed++;

	printf("\tTest trybu odczytu i trybu zapisu dotyczacy informacji o BFS zakonczony pozytywnie. (%d/2)\n\n", passed);

	while (!feof(f_dij1) && !feof(f_dij2))
	{
		if (!feof(f_dij1) && !feof(f_dij2))
		{
			fgets(str3, MAX_LENGHT, f_dij1);
			fgets(str4, MAX_LENGHT, f_dij2);

			if (strcmp(str3, str4) != 0)
			{
				fprintf(stderr, "\tTest nieudany dla plikow '%s' oraz '%s'.\n\n", dij1, dij2);
				passed--;
				break;
			}
		}
	}
	passed++;
	if (passed == 2)
		printf("\tTest trybu odczytu i trybu zapisu dotyczacy informacji o Dijkstrze zakonczony pozytywnie. (%d/2)\n\n", passed);

	if (passed == 2)
		printf("\tPliki z informacjami o wynikach algorytmow sa zapisywane i odczytywane poprawnie. Wynik testu: (%d/2) \n\nKoniec testu.\n", passed);
	if (passed != 2)
		printf("\tPliki z informacjami o wynikach algorytmow nie sa zapisywane/odczytywane poprawnie. Wynik testu: (%d/2)\n\nKoniec testu.\n", passed);

	return 0;
}
