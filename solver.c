#include <stdio.h>
#include<stdlib.h>
#include<time.h>

#define INFINITY 1000
#define MAX 100

void szukacz(double G[MAX][MAX], int n, int START);

int main(int argc, char* argv[]) {

	int aa1 = atoi(argv[1]);
	int aa2 = atoi(argv[2]);

	int i, j, r, c;//iteratory
	int l, w;//zmienne odpowiedzialne za poprawne ulozenie przeszkod w labiryncie
	int start;// start
	double G[MAX][MAX];//zmienna przechwytujaca wypelnione wartosci w macierzy sasiedztwa
	int a = aa1;
	int n = a * a;
	double M[n][n]; //zmienna odpowiedzialna za ulozenie macierzy sasiedztwa
	char labirynt[n][n];//zmienna odpowiedzialna za graficzna reprezentacje labiryntu
	double wartoscprzejsc[n][n];//zmienna odpowiedzialna za wartosci przejsc miedzy wierzcholkami w labiryncie

	if (aa1 <=4 || aa1 >= 11) {//wwarunek na poprawny wymiar labiryntu
		printf("Bledny wymiar labiryntu. Prosze sprobowac ponownie. Akceptowalne wymiary: od 5x5 do 10x10\n");
		return -1;
	}
	else {
		printf("Podano poprawny wymiar labiryntu - %dx%d .\n", atoi(argv[1]), atoi(argv[1]));
	}

	srand(argc > 2 ? aa2 : time(NULL)); //inicjacja generatora liczb losowych

	start = 0;

	if(aa1 == 5){//rozlozenie przeszkod w labiryntach o poszczegolnych wymiarach
		l = 7;
		w = 1;
	}
	if(aa1 == 6){
		l = 4;
		w = 1;
	}
	if(aa1 == 7){
		l = 5;
		w = 2;
	}
	if(aa1 == 8){
		l = 5;
		w = 1;
	}
	if(aa1 == 9){
		l = 7;
		w = 4;
	}
	if(aa1 == 10){
		l = 4;
		w = 1;
	}


	for (i = 0; i < n; i++) {  //Generuje wartosci przejsc do poszczegolnych sasiednich pol
		for (j = 0; j < n; j++) {
			wartoscprzejsc[i][j] = rand() * 10 / (double)RAND_MAX * 10;
			if (wartoscprzejsc[i][j] < 0) {
				wartoscprzejsc[i][j] = (wartoscprzejsc[i][j]) * (-1);
			}
			else {
				wartoscprzejsc[i][j] = wartoscprzejsc[i][j];
			}
		}
	}

	for (r = 0; r < n; r++) {//wypelnia macierz sasiedztwa zerami
		for (c = 0; c < n; c++) {
			M[r][c] = 0;
		}
	}

	for (r = 0; r < a; r++) {// tworzy macierz sasiedztwa siatki 2D o danej wielkosci
		for (c = 0; c < a; c++) {
			i = r * a + c;
			if (c > 0) {
				M[i - 1][i] = wartoscprzejsc[i - 1][i];
				M[i][i - 1] = M[i - 1][i];
			}
			if (r > 0){
				M[i - a][i] = wartoscprzejsc[i - a][i];
				M[i][i - a] = M[i - a][i];
			}
		}
	}

	for (r = 0; r < n; r++) { //Generuje przeszkody ktore beda uwzglednione w labiryncie
		for (c = 0; c < n; c++) {
			if((c>0 &&c%l==0) || (r>0 && r%l==0)){
				M[r][c] = 0;
			}					             
		}
	}

	for (r = 0; r < a - 1; r++) {// usuwa smieci z macierzy sasiedztwa
		for (c = n - a + 1; c < n; c++) {
			M[r][c] = 0;
		}
	}

	printf("\n");

/*	for (r = 0; r < n; r++) { //wypisuje macierz sasiedztwa. Najlepiej sprawdzac na macierzach nie wiekszych niz 7x7.
		for (c = 0; c < n; c++) {
			printf("%f ", M[r][c]);
		}
		printf("\n");
	}*/

	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			G[i][j] = M[i][j];
		}
	}

	szukacz(G, n, start);
	printf("\n");

	for (i = 0; i < aa1 + 2; i++) {         //Generuje podloze labiryntu
		for (j = 0; j < aa1 + 2; j++) {
			labirynt[i][j] = '|';
		}
	}


	for (i = 1; i < aa1 + 1; i++) { //Usuwa wnetrze labiryntu tak aby spelnialo  wymiary podane przez uzytkownika
		for (j = 1; j < aa1+1 ; j++) {
			labirynt[i][j] = ' ';
			if((i*aa1+j+w)%l==0){//generuje przeszody labiryntu
			labirynt[i][j] = '|';
			}
		}
	}
	
	labirynt[1][1] = 'S';
	labirynt[aa1][aa1] = 'F';
	printf("Najkrotsza droga z poczatku do konca labiryntu ^^^ \n");
	printf("Start labiryntu - %d\n", start);
	printf("Koniec labiryntu - %d\n", n-1);
	printf("Wizualizacja wygenerowanego labiryntu:\n");

	for (i = 0; i < aa1 + 2; i++) {         //Wypisuje caly labirynt wraz ze scianami bocznymi
		for (j = 0; j < aa1 + 2; j++) {
			printf("%c " ,labirynt[i][j]);

		}
		printf("\n");
	}

	return 0;
}



void szukacz(double G[MAX][MAX], int n, int START) {

	double koszt[MAX][MAX], dystans[MAX], przod[MAX];
	int odwiedzone[MAX], licznik, mindystans, next, i, j;
	//przod[] ma poprzednika od aktualnego  wierzcholka
	//licznik ile wierzcholkow zostalo odwiedzonych
	//koszt dla kazdej z drog
	for (i = 0; i < n; i++){
		for (j = 0; j < n; j++){
			if (G[i][j] == 0)//dla kazdego 0 w macierzy sasiedztwa przypisuje wartosc 1000
				koszt[i][j] = INFINITY;
			else
				koszt[i][j] = G[i][j];
		}
	}

	for (i = 0; i < n; i++){
		dystans[i] = koszt[START][i];
		przod[i] = START;
		odwiedzone[i] = 0;
	}
	dystans[START] = 0;
	odwiedzone[START] = 1;
	licznik = 1;

	while (licznik < n-1){
		mindystans = INFINITY;
		//nextnode daje wierzcholkowi minimalny dystans
		for (i =0; i < n; i++){
			if (dystans[i] < mindystans && !odwiedzone[i])
			{
				mindystans = dystans[i];
				next = i;
			}
		}

		//sprawdzia czy istnieje lepsza droga
		odwiedzone[next] = 1;
		for (i = 0; i < n; i++){
			if (!odwiedzone[i]){
				if (mindystans + koszt[next][i] < dystans[i])
				{
					dystans[i] = mindystans + koszt[next][i];
					przod[i] = next;
				}
			}
		}
		licznik++;
	}

	//wypisuje sciezke i dystans kazdej z drog
	for (i = 0; i < n; i++){
		if (i != START)
		{
			printf("\nOdleglosc od wierzcholka%d=%f", i, dystans[i]);
			printf("\nDroga=%d", i);
			j = i;
			do
			{	
				j = przod[j];
				printf("<-%d", j);
			} while (j != START);
		}
	}
}
