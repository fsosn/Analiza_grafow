#include "cohesion.h"



#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void cohesion(int x, int y, double arr[x * y][x * y], int n) {

	int i, j, k;
	int a = x * y;
	int(*edge) = calloc(a, sizeof * edge);
	int rand_start;
	int rand_kier[4];
	rand_kier[0] = -x;
	rand_kier[1] = 1;
	rand_kier[2] = x;
	rand_kier[3] = -1;
	int przodek;

	srand(time(NULL));
	//utworzenie wektora ilosci polaczen
	for (i = 0; i < a; i++) {
		edge[i] = 0;
		for (j = 0; j < a; j++) {
			if (arr[i][j] == 1) {
				edge[i]++;
			}

		}

	}
	rand_start = rand() % a;
	//wybranie wierzcholka z liczba krawedzi rozna od 4
	while (edge[rand_start] == 4) {
		rand_start = rand() % a;
	}
	printf("\n%d - rand_start1\n", rand_start);
	printf("\n%d - x\n", x);
	//macierz przed podzialem
	printf("\n");
	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++) {
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
	i = 0;
	j = 0;
	int z = 0;
	int l;
	//pierwszy ruch i usunnieta krawedz po wyzanczeniu punktu

	if (rand_start == 0 && z == 0) {
		while (i != 1) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[1];
		//printf("wariant1");
		z++;
	}
	else if (rand_start > 0 && rand_start < x - 1 && z == 0) {
		while (i != 2) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[2];
		//printf("wariant2");
		z++;
	}
	else if (rand_start == x - 1 && z == 0) {
		while (i != 1) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[3];
		//printf("wariant3");
		z++;
	}
	else if (rand_start % x == 0 && rand_start > x - 1 && rand_start < x * y - x && z == 0) {
		while (i != 2) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[1];
		//printf("wariant4");
		z++;
	}
	else if (rand_start % x == x - 1 && rand_start > x - 1 && rand_start < x * y - x && z == 0) {
		while (i != 2) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[3];
		//printf("wariant5");
		z++;
	}
	else if (rand_start == x * y - x && z == 0) {
		while (i != 1) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[1];
		//printf("wariant6");
		z++;
	}
	else if (rand_start > x * y - x && rand_start < x * y - 1 && z == 0) {
		while (i != 2) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[0];
		//printf("wariant7");
		z++;
	}
	else if (rand_start == x * y - 1 && z == 0) {
		while (i != 1) {
			if (arr[j][rand_start] == 1) {
				arr[j][rand_start] = 0;
				arr[rand_start][j] = 0;
				i++;
			}
			j++;
		}
		rand_start = rand_start + rand_kier[3];
		//printf("wariant8");
		z++;
	}
	i = 0;
	j = 0;
	z = 0;
	//podzial na n razy
	while (z < n) {
		while (edge[rand_start] != 2) {
			printf("Przejscie-> ");
			k = rand() % 4;
			l = rand_start;
			przodek = rand_start;
			rand_start = rand_start + rand_kier[k];

			while(rand_start > x*y || rand_start < 0){
				k = rand() % 4;
				rand_start = l;
				przodek = rand_start;
				rand_start = rand_start + rand_kier[k];
			}
			l = 0;
			//zachowanie przy napotkaniu wierzcholka z 4 krawedziami
			if (edge[rand_start] == 4 && l==0) {
				while (i != 2) {
					if (arr[j + rand_start][przodek] == 1) {
						arr[j + rand_start][przodek] = 0;
						arr[przodek][j + rand_start] = 0;
						i++;
					}
					j++;
				}
				l++;
			}
			//zachowanie przy napotkaniu wierzcholka z 3 krawedziami
			else if (edge[rand_start] == 3 && l==0) {
				while (i != 1) {
					if (arr[j + rand_start][przodek] == 1) {
						arr[j + rand_start][przodek] = 0;
						arr[przodek][j + rand_start] = 0;
						i++;
					}
					j++;
				}
			}
			//aktualizacja wektora polaczen
			for (i = 0; i < a; i++) {
				edge[i] = 0;
				for (j = 0; j < a; j++) {
					if (arr[i][j] == 1) {
						edge[i]++;
					}
				}
			}
			i=0;
			j=0;
			l=0;
		}
		z++;
	}


	// usuniecie ostatniej krawedzi
	k = rand() % 4;
	l = rand_start;
	przodek = rand_start;
	rand_start = rand_start + rand_kier[k];
	while(rand_start > x*y || rand_start < 0){
		k = rand() % 4;
		rand_start = l;
		przodek = rand_start;
		rand_start = rand_start + rand_kier[k];
	}
	arr[rand_start][przodek] = 0;
	arr[przodek][rand_start] = 0;


	//macierz po podziale
	printf("\n");
	for (i = 0; i < a; i++) {
		for (j = 0; j < a; j++) {
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n%d - rand_start2", rand_start);

	if (edge[rand_start] == 3) {
		printf("\ne rand_start - 3");
	}
	else if (edge[rand_start] == 2) {
		printf("\ne rand_start - 2");
	}
	else {
		printf("\ne rand_start - 1");
	}
	printf("\nrand_dir[0] - %d", rand_kier[0]);

	printf("\n");
	for (i = 0; i < a; i++) {
		printf("%d ", edge[i]);
	}
	printf("\n%d - n\n", n);

	free(edge);
}




