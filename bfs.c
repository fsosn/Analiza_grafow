#include "bfs.h"

#include<stdio.h>
#include<stdlib.h>

int isEmpty(struct queue* q) {
	if (q->r == q->f) {
		return 1;
	}
	return 0;
}

int isFull(struct queue* q) {
	if (q->r == q->size - 1) {
		return 1;
	}
	return 0;
}

void enqueue(struct queue* q, int val) {
	if (isFull(q)) {
		printf("This Queue is full\n");
	}
	else {
		q->r++;
		q->arr[q->r] = val;
		//printf("Enqued element: %d\n", val);
	}
}

int dequeue(struct queue* q) {
	int a = -1;
	if (isEmpty(q)) {
		printf("This Queue is empty\n");
	}
	else {
		q->f++;
		a = q->arr[q->f];
	}
	return a;
}

void bfs(int x, int y, double arr[x * y][x * y], int ps) {

	int n = x * y;
	struct queue l;
	l.size = n + 1;
	l.f = l.r = 0;
	l.arr = (int*)malloc(l.size * sizeof(int));

	int node;
	int r, j;
	int visited[n];

	for (r = 0; r < n; r++) {
		visited[r] = 0;
	}

	printf("Spójne wierzchołki: %d", ps);
	visited[ps] = 1;
	enqueue(&l, ps); // Enqueue i for exploration
	while (!isEmpty(&l))
	{
		int node = dequeue(&l);
		for (j = 0; j < n; j++)
		{
			if (arr[node][j] == 1 && visited[j] == 0) {
				printf(" %d", j);
				visited[j] = 1;
				enqueue(&l, j);
			}
		}
	}

	if (n == j) {
		printf("\nGraf jest spójny");
	}
	else {
		printf("\nGraf nie jest spójny");
	}

	free(l.arr);
}


