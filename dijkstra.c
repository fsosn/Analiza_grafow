#include "dijkstra.h"

#include<stdio.h>
#include<stdlib.h>

void dijkstra(int x, int y, double arr[x * y][x * y], int ps, int pk)
{
	int n = x * y;
	double(*dystans) = calloc(n, sizeof * dystans);
	double(*przodek) = calloc(n, sizeof * przodek);
	double(*odwiedzone) = calloc(n, sizeof * odwiedzone);
	int zlicz, nastepca, i, j;
	double mindystans;

	for (i = 0; i < n; i++)
		for (j = 0; j < n; j++)
			if (arr[i][j] == -1)
				arr[i][j] = 9999999;

	for (i = 0; i < n; i++)
	{
		dystans[i] = arr[ps][i];
		przodek[i] = ps;
		odwiedzone[i] = 0;
	}

	dystans[ps] = 0;
	odwiedzone[ps] = 1;
	zlicz = 1;

	while (zlicz < n - 1)
	{
		mindystans = 9999999;

		for (i = 0; i < n; i++)
			if (dystans[i] < mindystans && !odwiedzone[i])
			{
				mindystans = dystans[i];
				nastepca = i;
			}

		odwiedzone[nastepca] = 1;
		for (i = 0; i < n; i++)
			if (!odwiedzone[i])
				if (mindystans + arr[nastepca][i] < dystans[i])
				{
					dystans[i] = mindystans + arr[nastepca][i];
					przodek[i] = nastepca;
				}
		zlicz++;
	}

	char buffer[64];
	snprintf(buffer, sizeof(buffer), "dane/dijkstra_%dx%d_%d_%d", x, y, ps, pk);

	FILE* out = fopen(buffer, "w");
	if (out == NULL)
	{
		fprintf(stderr, "Nie udalo sie otworzyć pliku '%s'.\n", buffer);
		exit(EXIT_FAILURE);
	}
	fprintf(out, "x: %d\ny: %d\nps: %d\npk: %d\n\n", x, y, ps, pk);

	int k = 0;

	for (i = pk; i < pk + 1; i++)
		if (i != ps)
		{
			printf("Najkrótszy dystans od wierzchołka %d do wierzchołka %d: %lf\n\n", ps, pk, dystans[i]);

			fprintf(out, "Najkrótszy dystans od wierzchołka %d do wierzchołka %d: %lf\n\n", ps, pk, dystans[i]);
			fprintf(out, "Przebyta droga:\n%d", i);

			j = i;
			do
			{
				j = przodek[j];
				fprintf(out, " <- %d", j);
				k++;
				if (k % 10 == 0)
					fprintf(out, "\n");
			} while (j != ps);
		}
	fclose(out);

	printf("(Szczegolowe informacje o przebytej drodze znajduja sie w pliku '%s')\n\n", buffer);

	free(dystans);
	free(przodek);
	free(odwiedzone);
}
