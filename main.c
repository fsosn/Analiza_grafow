#include "incidence.h"
#include "bfs.h"
#include "randval.h"
#include "dijkstra.h"
#include "to_file.h"
#include "from_file.h"

#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <math.h>
#include <string.h>

void show_usage() 
{
    printf("Jak wprowadzic dane:\n");
    printf("\t./graf -x (liczba) -y (liczba) [-n (liczba)] [-min (liczba)] [-max (liczba)] [-out (nazwa_pliku)]\n");
    printf("lub\n");
    printf("\t./graf -in (nazwa_pliku) [-ps (liczba)] [-pk (liczba)]\n");
}

int main(int argc, char** argv) 
{
    int opt = 0;
    int long_index = 0;

    int x = -1, y = -1, n = -1, ps = -1 , pk = -1;
    double min = -1, max = -1;

    int text_size = 32;
    char in[text_size]; 
    char out[text_size];
    out[0] = '\0';
    in[0] = 0; out[0] = 0;
    
    static struct option long_options[] = 
    {
        {"min" , required_argument, 0,  'l' },
        {"max" , required_argument, 0,  'g' },
        {"ps"  , required_argument, 0,  's' },
        {"pk"  , required_argument, 0,  'e' },
        {"in"  , required_argument, 0,  'i' },
        {"out" , required_argument, 0,  'o' },
        {"help",    no_argument   , 0,  'h' }
    };

    //podanie argumentow
    while( (opt = getopt_long(argc, argv, "x:y:n:l:g:s:e:i:o:h", long_options, &long_index)) != -1) 
    {     
        switch (opt)
        {       
        case 'x':
            x = atoi(optarg);
            if (x < 0 || x > pow(10, 8))
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'x = %d'. (0 < x < 10^8)\n\n", x);
                exit(EXIT_FAILURE);
            }  
            printf("x: %d\n", x) ;
            break;

        case 'y':
            y = atoi(optarg);
            if (y < 0 || y > pow(10, 8))
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'y = %d'. (0 < y < 10^8)\n\n", y);
                exit(EXIT_FAILURE);
            }
            printf("y: %d\n", y);
            break;

        case 'n':
            if( x == -1 || y == -1)
            {
                fprintf(stderr, "Przed podaniem wartosci 'ps', prosze okreslic parametr 'x' oraz 'y'.\n\n");
                exit(EXIT_FAILURE);
            }
            n = atoi(optarg);
            if( n < 1 || (n > (x*y/4)) )
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'n = %d'. (1 <= n < %d)\n\n", n, (x*y/4) );
                exit(EXIT_FAILURE);
            }  
            printf("n: %d\n", n);
            break;

        case 'l':
            min = atof(optarg);
            if( min < 0 || min > 1)
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'min = %g'. (0 <= min <= 1)\n\n", min);
                exit(EXIT_FAILURE);
            }
            printf("min: %g\n", min);
        break;
        
        case 'g':
            max = atof(optarg);
            if( max < 0 || max > 1)
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'min = %g'. (0 <= max <= 1)\n\n", max);
                exit(EXIT_FAILURE);
            }
            printf("max: %g\n", max);
        break;
        
        case 's':
            if( x == -1 || y == -1)
            {
                fprintf(stderr, "Przed podaniem wartosci 'ps', prosze okreslic parametr 'x' oraz 'y'.\n\n");
                exit(EXIT_FAILURE);
            }
            ps = atoi(optarg);
            if( ps < 0 || (ps > (x*y - 1)) )
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'ps = %d'. (0 <= ps <= %d)\n\n", ps, (x*y - 1));
                exit(EXIT_FAILURE);
            }
            printf("ps: %d\n", ps);
        break;
        
        case 'e':
            if( x == -1 || y == -1)
            {
                fprintf(stderr, "Przed podaniem wartosci 'pk', prosze okreslic parametr 'x' oraz 'y'.\n\n");
                exit(EXIT_FAILURE);
            }
            pk = atoi(optarg);
            if( pk < 0 || (pk > (x*y -1)) )
            {
                fprintf(stderr, "Nieprawidlowa wartosc 'pk = %d'. (0 <= pk <= %d)\n\n", pk, (x*y - 1));
                exit(EXIT_FAILURE);
            }
            printf("pk: %d\n", pk);
        break;
        
        case 'i':
            if(strlen(optarg)>31)
            {
                fprintf(stderr, "Zbyt dluga nazwa pliku wejsciowego: %ld. Maksymalna dlugosc to: %d", strlen(optarg), text_size - 1);
                exit(EXIT_FAILURE);
            }
            strcpy(in, optarg);
            printf("in: %s\n", in);
        break;
        
        case 'o':
            if(strlen(optarg)>31)
            {
                fprintf(stderr, "Zbyt dluga nazwa pliku wyjsciowego: %ld. Maksymalna dlugosc to: %d", strlen(optarg), text_size - 1);
                exit(EXIT_FAILURE);
            }
            strcpy(out, optarg);
            printf("out: %s\n", out);
        break;

        case 'h':
            show_usage();
	        exit(EXIT_FAILURE);
        break;
        }
    }

    // tryb drugi (odczyt z pliku)
    if( in[0] != '\0' )
    {
	    from_file(in);
        if( ps == -1)
        {
            ps = 0; //wartosc domyslna punktu startowego
        }

        if( pk == -1)
        {
            pk = ( (x*y) - 1); //wartosc domyslna punktu koncowego
        }

        return 0;
    }

    if( argc == 1 )
    {
        fprintf(stderr, "%s", "Nie podano argumentow. Prosze wprowadzic dane.\n\n");
        show_usage();
        exit(EXIT_FAILURE);
    }

    if( x == -1 )
    {
        fprintf(stderr, "%s", "Nie podano wartosci dla parametru x. Prosze wprowadzic dane ponownie.\n\n");
        exit(EXIT_FAILURE);
    }

    if( y == -1 )
    {
        fprintf(stderr, "%s", "Nie podano wartosci dla parametru y. Prosze wprowadzic dane ponownie.\n\n");
        show_usage();
        exit(EXIT_FAILURE);
    }

    //tryb pierwszy - zapis do pliku

    if(out[0] == '\0')
    {
        strcpy(out, "mygraph"); //domyslna nazwa pliku wyjsciowego
    }

	if( ps == -1)
        {
            ps = 0; //wartosc domyslna punktu startowego
        }

        if( pk == -1)
        {
            pk = ( (x*y) - 1); //wartosc domyslna punktu koncowego
        }


    if(min == -1)
	{
		min = 0;
	}
	
    if(max == -1)
	{
		max = 1;
	}

    //tutaj bedzie dalsza czesc programu
	int p = x*y;


	//alokacja pamięci
	double (*arr)[p] = calloc(p, sizeof *arr);
	if(arr == NULL){
		fprintf(stderr, "%s", "Nieudana alokacja pamieci\n");
		exit(EXIT_FAILURE);
	}	
	
	//utworzenie macierzy incydencji
	incidence(x, y, arr); //utworzenie macierzy incydencji
	
	bfs(x, y, arr, ps);

	to_file(x, y, arr, out);	
	//nadanie losowych wartości przejść
	randval(x, y, arr, min, max);
	
	dijkstra(x, y, arr, ps, pk);

	//do sprawdzenia czy macierz jest poprawna

/*	for(int o = 0; o < p; o++){
		for(int z = 0; z < p; z++){
			printf("%g ", arr[o][z]);
		}
		printf("\n");
	}
	
*/	
	free(arr);
    
	return 0;
}
