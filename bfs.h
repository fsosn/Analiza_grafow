#ifndef _BFS_H_IS_INCLUDED_
#define _BFS_H_IS_INCLUDED_

struct kolejka
{
	int size;
	int f;
	int r;
	int* arr;
};


int kpusta(struct kolejka* q);

int kpelna(struct kolejka* q);

void wstaw(struct kolejka* q, int val);

int zwolnij(struct kolejka* q);

void bfs(int x, int y, double arr[x * y][x * y], int ps);

#endif
