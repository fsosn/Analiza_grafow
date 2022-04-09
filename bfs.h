#ifndef _BFS_H_IS_INCLUDED_
#define _BFS_H_IS_INCLUDED_

struct queue
{
    int size;
    int f;
    int r;
    int* arr;
};


int isEmpty(struct queue* q);

int isFull(struct queue* q);

void enqueue(struct queue* q, int val);

int dequeue(struct queue* q);

void bfs(int x, int y, double arr[x*y][x*y], int ps);

#endif


