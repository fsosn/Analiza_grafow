#include "dijkstra.h"

#include<stdio.h>
#include<stdlib.h>

void dijkstra(int x, int y, double arr[x*y][x*y], int ps, int pk){
		
		int n = x * y;
		double(*dystans) = calloc(n, sizeof * dystans);
		double(*przodek) = calloc(n, sizeof * przodek);
		double(*odwiedzone) = calloc(n, sizeof * odwiedzone);
		int zlicz, nastepca, i, j;
		double mindystans;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (arr[i][j] == 0)
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

		for (i = pk; i < pk+1; i++)
			if (i != ps)
			{
				printf("\nNajkrótszy dystans od wierzchołka %d do werzchołka %d = %f", ps, pk, dystans[i]);
				printf("\nPrzebyta droga = %d", i);
				j = i;
				do
				{
					j = przodek[j];
					printf("<- %d", j);
				} while (j != ps);
			}
		printf("\n");
	}



