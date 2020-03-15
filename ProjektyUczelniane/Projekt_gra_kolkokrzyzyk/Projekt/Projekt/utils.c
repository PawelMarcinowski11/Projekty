#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>
#include <vld.h>

#ifdef _WIN32
#include <windows.h>
#endif

#ifdef unix
#endif



#define SZEROKOSC 9
#define WYSOKOSC 8
#define POCZATKOWA_X 12
#define POCZATKOWA_Y 6
#define ODSTEP_X 3
#define ODSTEP_Y 2
#define AI_PASYWNOSC 40  //AI skupia siê na uk³adaniu pi¹tki
#define AI_REAKCJA 30 //AI skupia siê na przeszkadzaniu graczowi
#define DLUGOSC_PRZERWY 125 //OpóŸnienie miêdzy ruchem gracza a komputera w milisekundach


#include "wyniki.h"


void inicjalizacja(int * stan_meczu, char tab[WYSOKOSC][SZEROKOSC], int * wolno_cofac, int * pierwszy_ruch, time_t * czas_startu,
	int * liczba_ruchow, int * liczba_cofniec) {
	for (int i = 0; i < WYSOKOSC; i++) {
		for (int j = 0; j < SZEROKOSC; j++) {
			tab[i][j] = '_';
		}
	}
	time(czas_startu);
	*liczba_ruchow = 0;
	*liczba_cofniec = 0;
	*wolno_cofac = 0;
	*pierwszy_ruch = 1;
	*stan_meczu = 0;
}

void zwolnijPamiec(wynik * ogon) {
	wynik * wsk;
	while (ogon) {
		wsk = ogon->pPrev;
		free(ogon);
		ogon = wsk;
	}
}

/**Funkcja sprawdza liczbê argumentów linii poleceñ i, o ile jest wieksza niz jeden, zwraca pierwszy argument po œcie¿ce pliku.*/
char * wczytajNazwePliku(int liczba_arg, char *wartosci_arg[]) {
	if (liczba_arg > 1) {
		return wartosci_arg[1];
	}
	else {
		return "Wyniki_meczow.bin";
	}
}