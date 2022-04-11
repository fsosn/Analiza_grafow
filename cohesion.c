#include "cohesion.h"



#include<stdio.h>
#include<stdlib.h>
#include<time.h>


void cohesion(int x, int y, double arr[x*y][x*y],int n){
	
	int i,j,k;
	int a=x*y;
	int (*edge) = calloc(a, sizeof * edge);
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
	i = 0;
	j = 0;
	//pierwszy ruch po wyzanczeniu punktu
			if(rand_start % x == 0 && rand_start < 1){	
				rand_dir = 1;
				while(i!=1){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;
						arr[rand_start][j] = 0;
						i++;
					}
					j++;
				}
			}
			if(rand_start < x && rand_start >= 1 ){
				rand_dir = 2;
				while(i!=2){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;
						arr[rand_start][j] = 0;
						i++;
					}
					j++;
				}
			}
			if(rand_start % x == x-1 && rand_start < x){
				rand_dir = 3;
				while(i!=1){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;                                                                                                                                                                                                                      arr[rand_start][j] = 0;                                                                                                                                                                                                                      i++;                                                                                                                                                                                                                                 }
					j++;
				}
			}
			if(rand_start % x == 0 && rand_start >= x && rand_start < x*y-x){
				rand_dir = 1;
				while(i!=2){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;                                                                                                                                                                                                                      arr[rand_start][j] = 0;                                                                                                                                                                                                                      i++;                                                                                                                                                                                                                                 }
					j++;
				}
			}
			if(rand_start % x == x-1 && rand_start > x && rand_start <=x*y-x-1){
				rand_dir = 3;
				while(i!=2){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;
						arr[rand_start][j] = 0;
						i++;
					}
					j++;
				}
			}
			if(rand_start = x*y-x ){
				rand_dir = 1;
				while(i!=1){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;
						arr[rand_start][j] = 0;
						i++;
					}
					j++;
				}
			}
			if(rand_start > x*y-x && rand_start < x*y-1){
				rand_dir = 0;
				while(i!=2){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;                                                                                                                                                                                                                      arr[rand_start][j] = 0;                                                                                                                                                                                                                      i++;                                                                                                                                                                                                                                 }
					j++;
				}
			}
			if(rand_start == x*y-1){
				rand_dir = 3;
				while(i!=1){
					if(arr[j][rand_start]==1){
						arr[j][rand_start] = 0;                                                                                                                                                                                                                      arr[rand_start][j] = 0;                                                                                                                                                                                                                      i++;                                                                                                                                                                                                                                 }
					j++;
				}
			}

			


	printf("\n");
	for(i=0;i<a;i++){
		for(j=0;j<a;j++){
			printf("%f ",arr[i][j]);
		}
		printf("\n");
	}
	printf("\n%d - rand_start",rand_start);

	if(edge[rand_start]==3){
		printf("\ne rand_start - 3");
	}
        else if(edge[rand_start]==2){
		printf("\ne rand_start - 2");
	}
	else{
		printf("\ne rand_start - 1");
	}	
	printf("\nrand_dir - %d",rand_dir);

	printf("\n");
	for(i=0;i<a;i++){
		printf("%d ",edge[i]);
	}
	printf("\n%d - n\n",n);
	
	free(edge);
}

