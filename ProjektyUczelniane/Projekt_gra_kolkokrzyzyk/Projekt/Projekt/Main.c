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

#include "AI.h"
#include "movement.h"
#include "wyniki.h"
#include "oprawa_wizualna.h"
#include "gameplay.h"
#include "utils.h"


#define SZEROKOSC 9
#define WYSOKOSC 8
#define POCZATKOWA_X 12
#define POCZATKOWA_Y 6
#define ODSTEP_X 3
#define ODSTEP_Y 2
#define AI_PASYWNOSC 40  //AI skupia si� na uk�adaniu pi�tki
#define AI_REAKCJA 30 //AI skupia si� na przeszkadzaniu graczowi
#define DLUGOSC_PRZERWY 125 //Op�nienie mi�dzy ruchem gracza a komputera w milisekundach


int main(int liczba_arg, char *wartosci_arg[]) {
	char * nazwa_pliku = wczytajNazwePliku(liczba_arg,wartosci_arg);
	kolkoKrzyzyk(nazwa_pliku);
	podziekowanie();
}