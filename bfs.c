#include "bfs.h"

#include<stdio.h>
#include<stdlib.h>

int kpusta(struct kolejka* q)
{
	if (q->r == q->f)
	{
		return 1;
	}
	return 0;
}

int kpelna(struct kolejka* q)
{
	if (q->r == q->size - 1)
	{
		return 1;
	}
	return 0;
}

void wstaw(struct kolejka* q, int val)
{
	if (kpelna(q))
	{
		printf("Kolejka jest pelna.\n");
	}
	else
	{
		q->r++;
		q->arr[q->r] = val;
	}
}

int zwolnij(struct kolejka* q)
{
	int a = -1;
	if (kpusta(q))
	{
		printf("Kolejka jest pusta.\n");
	}
	else
	{
		q->f++;
		a = q->arr[q->f];
	}
	return a;
}

void bfs(int x, int y, double arr[x * y][x * y], int ps)
{

	int n = x * y;
	struct kolejka l;
	l.size = n + 1;
	l.f = l.r = 0;
	l.arr = (int*)malloc(l.size * sizeof(int));

	int node;
	int r, j;
	int odwiedzone[n];

	for (r = 0; r < n; r++) {
		odwiedzone[r] = 0;
	}

	char buffer[64];
	int k = 0;
	snprintf(buffer, sizeof(buffer), "dane/bfs_%dx%d_%d", x, y, ps);

	FILE* out = fopen(buffer, "w");
	if (out == NULL)
	{
		fprintf(stderr, "Nie udalo sie otworzyć pliku '%s'.\n", buffer);
		exit(EXIT_FAILURE);
	}
	fprintf(out, "x: %d\ny: %d\nps: %d\n\n", x, y, ps);

	fprintf(out, "Spójne wierzchołki:\n %d", ps);

	odwiedzone[ps] = 1;

	wstaw(&l, ps);

	while (!kpusta(&l))
	{
		int node = zwolnij(&l);
		for (j = 0; j < n; j++)
		{
			if (arr[node][j] == 1 && odwiedzone[j] == 0) {
				fprintf(out, " %d", j);
				k++;
				if (k % 10 == 0)
					fprintf(out, "\n");

				odwiedzone[j] = 1;
				wstaw(&l, j);
			}
		}
	}

	if (n == j) {
		printf("\nGraf jest spójny.\n\n");
		fprintf(out, "\n\nGraf jest spójny.");
	}
	else {
		printf("\nGraf nie jest spójny.\n\n");
		fprintf(out, "\n\nGraf nie jest spójny.\n");
	}

	fclose(out);

	printf("(Szczegolowe informacje o spojnosci grafu znajduja sie w pliku '%s')\n\n", buffer);

	free(l.arr);
}
