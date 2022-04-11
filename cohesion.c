#include "cohesion.h"



#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void cohesion(int x, int y, double arr[x*y][x*y],int n){
	
	int i,j,k;
	int a=x*y;
	int edge[a];
	int rand_start;
	int rand_dir;
	
	srand(time(NULL));

	for(i = 0; i < a; i++){
		edge[i]=0;
		for(j = 0; j < a; j++){
			if(arr[i][j]==1){
				edge[i]++;
			}

		}

	}
	rand_start = rand() % a;

	while(edge[rand_start]==4){
		rand_start = rand() % a;
	}
	
	printf("\n");
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%f ",arr[i][j]);
		}
		printf("\n");
	}

	i=0;
	j=0;
	while(i!=2){
		if(arr[j][rand_start]==1){
			arr[j][rand_start] = 0;
			arr[rand_start][j] = 0;
			i++;
		}
		j++;
	}

	printf("\n");
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%f ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n%d - rand_start",rand_start);
	printf("\n");
	for(i=0;i<a;i++){
		printf("%d ",edge[i]);
	}
	printf("\n%d - n\n",n);


}

