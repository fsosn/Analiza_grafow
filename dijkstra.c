#include "dijkstra.h"

#include<stdio.h>
#include<stdlib.h>

void dijkstra(int x, int y, double arr[x*y][x*y], int ps, int pk){

		int n = x * y;
		double(*cost)[n] = calloc(n, sizeof * cost);
		double(*distance) = calloc(n, sizeof * distance);
		double(*pred) = calloc(n, sizeof * pred);
		double(*visited) = calloc(n, sizeof * visited);
		int count, nextnode, i, j;
		double mindistance;
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (arr[i][j] == 0)
					cost[i][j] = 9999999;
				else
					cost[i][j] = arr[i][j];

		for (i = 0; i < n; i++)
		{
			distance[i] = cost[ps][i];
			pred[i] = ps;
			visited[i] = 0;
		}
		distance[ps] = 0;
		visited[ps] = 1;
		count = 1;
		while (count < n - 1)
		{
			mindistance = 9999999;

			for (i = 0; i < n; i++)
				if (distance[i] < mindistance && !visited[i])
				{
					mindistance = distance[i];
					nextnode = i;
				}

			visited[nextnode] = 1;
			for (i = 0; i < n; i++)
				if (!visited[i])
					if (mindistance + cost[nextnode][i] < distance[i])
					{
						distance[i] = mindistance + cost[nextnode][i];
						pred[i] = nextnode;
					}
			count++;
		}


		for (i = pk; i < pk+1; i++)
			if (i != ps)
			{
				printf("\nDystans od wierzcholka %d = %f", i, distance[i]);
				printf("\nPath=%d", i);
				j = i;
				do
				{
					j = pred[j];
					printf("<- %d", j);
				} while (j != ps);
			}
		printf("\n");
	}



