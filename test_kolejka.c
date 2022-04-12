#include "bfs.h"

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv)
{
	struct kolejka q;
	q.f = q.r = 0;
	q.size = 5; //rozmiar kolejki
	q.arr = (int*)malloc(q.size * sizeof(int));
	int passed = 0;

	printf("\nRozpoczynam test kolejki.\n\n");

	//wstawienie i zwolnienie elementu
	wstaw(&q, 1);
	if ((q.arr[q.r]) == zwolnij(&q))
	{
		passed++;
		printf("\tFunkcja 'wstaw' oraz 'zwolnij' dzialaja poprawnie. (%d/3)\n\n", passed);
	}
	else
	{
		printf("\tFunkcja 'wstaw' lub 'zwolnij' nie dziala poprawnie. (%d/3)\n\n", passed);
	}

	//zapelnienie kolejki
	wstaw(&q, 1);
	wstaw(&q, 2);
	wstaw(&q, 3);
	wstaw(&q, 4);

	if (kpelna(&q) == 1)
	{
		passed++;
		printf("\tFunkcja 'kpelna' dziala poprawnie. (%d/3)\n\n", passed);
	}
	else
	{
		printf("\tFunkcja 'kpelna' nie dziala dziala poprawnie. (%d/3)\n\n", passed);
	}

	//zwolnienie kolejki
	while (!kpusta(&q))
		zwolnij(&q);

	if (kpusta(&q) == 1)
	{
		passed++;
		printf("\tFunkcja 'kpusta' dziala poprawnie. (%d/3)\n\n", passed);
	}
	else
	{
		printf("Funkcja 'kpusta' nie dziala poprawnie. (%d/3)\n\n", passed);
	}

	if (passed == 3)
		printf("\tWszystkie funkcje dzialaja poprawnie.\n\nKoniec testu.\n");
	else
		printf("\tTest nieudany: uzyskany rezultat to (%d/3).\n\nKoniec testu kolejki.\n", passed);

	return 0;
}
