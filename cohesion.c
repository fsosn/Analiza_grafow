#include "cohesion.h"
#include "randval.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void cohesion(int x, int y, double arr[x * y][x * y], int n) {

    int a = x * y;
    double(*dystans) = calloc(a, sizeof * dystans);
    double(*przodek) = calloc(a, sizeof * przodek);
    double(*odwiedzone) = calloc(a, sizeof * odwiedzone);
    int(*edge) = calloc(a, sizeof * edge);
    int zlicz, nastepca, i, j, rand_start, rand_end, dzielnik, zamiennik,tura;
    double mindystans;
    dzielnik =2;
    tura = 0;

    srand(time(NULL));

while(tura < n-1){
    for (i = 0; i < a; i++) {
        edge[i] = 0;
        for (j = 0; j < a; j++) {
            if (arr[i][j] == 1) {
                edge[i]++;
            }
        }
    }

    rand_start = rand() % a;

    while (edge[rand_start] == 4 || edge[rand_start] ==0 || rand_start < (x*y)/dzielnik || rand_start > (2*x*y)/dzielnik ||rand_start == 2*(x*y)/dzielnik-1) {	
	rand_start = rand() % a;
    }
    printf("\n%d\n",rand_start);

    rand_end = rand() % a;

    while ((edge[rand_end] == 4 || edge[rand_end] ==0 || rand_end < (x * y) / dzielnik) || rand_end > (2*x*y)/dzielnik || rand_end < rand_start || rand_end == rand_start ) {
        rand_end = rand() % a;

    }

    printf("\n%d lol\n",rand_end);
	
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}


    for (i = 0; i < a; i++)
        for (j = 0; j < a; j++)
            if (arr[i][j] == 0)
                arr[i][j] = 9999999;

    for (i = 0; i < a; i++) {
        dystans[i] = arr[rand_start][i];
        przodek[i] = rand_start;
        odwiedzone[i] = 0;
    }

    dystans[rand_start] = 0;
    odwiedzone[rand_start] = 1;
    zlicz = 1;

    while (zlicz < a - 1) {

        mindystans = 9999999;

        for (i = 0; i < a; i++)
            if (dystans[i] < mindystans && !odwiedzone[i]) {
                mindystans = dystans[i];
                nastepca = i;
            }

        odwiedzone[nastepca] = 1;
        for (i = 0; i < a; i++)
            if (!odwiedzone[i])
                if (mindystans + arr[nastepca][i] < dystans[i]) {
                    dystans[i] = mindystans + arr[nastepca][i];
                    przodek[i] = nastepca;
                }
        zlicz++;
    }
	printf("\n%d - j\n",j);


	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}

	
    for (i = rand_end; i < rand_end + 1; i++)
        if (i != rand_start) 
        {
            printf("\nNajkrótszy dystans od wierzcho³ka %d do werzcho³ka %d = %f", rand_start, rand_end, dystans[i]);
            printf("\nPrzebyta droga = %d", i);
            j = i;
            do
            {
		zamiennik = j;
       	        j = przodek[j];
		arr[zamiennik][j] = 0;
		arr[j][zamiennik] = 0;
		printf("<-%d", j);
            } while (j != rand_start);

	    for( i = 0 ; i < a; i++){
		arr[rand_start][i] = 0;		
		arr[i][rand_start] = 0;

	    }
	}
    	dzielnik =dzielnik * 2;
	tura++;
	printf("TURA - %d ",tura);

	}


	printf("\n");    
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			if(arr[i][j] == 9999999){
				arr[i][j] = 0;
			}
			printf("%f ", arr[i][j]);
		}
		printf("\n");
	}
	printf("\n");


    free(dystans);
    free(przodek);
    free(odwiedzone);
    free(edge);
}
