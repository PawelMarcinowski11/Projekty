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

#include "AI.h"
#include "wyniki.h"

void ustawWynik(int wynik, int * stan_meczu) {
	if (*stan_meczu == 0) {
		*stan_meczu = wynik;
	}
}

void sprawdzZwyciestwo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu) {
	if (policzPoziomo(y, x, znak, znak2, tab) >= 4)
		ustawWynik(1, stan_meczu);
	else if (policzPionowo(y, x, znak, znak2, tab) >= 4)
		ustawWynik(1, stan_meczu);
	else if (policzLewaPrzekatna(y, x, znak, znak2, tab) >= 4)
		ustawWynik(1, stan_meczu);
	else if (policzPrawaPrzekatna(y, x, znak, znak2, tab) >= 4)
		ustawWynik(1, stan_meczu);
}




void cofnij(COORD POS, COORD COFNIJ_POS, COORD COFNIJ2_POS, int * pierwszy_ruch, int * wolno_cofac, char * tab, int * liczba_ruchow, int * liczba_cofniec) {
	int tempY = (COFNIJ2_POS.Y - POCZATKOWA_Y) / ODSTEP_Y;
	int tempX = (COFNIJ2_POS.X - POCZATKOWA_X) / ODSTEP_X;
	char *t = (tab + tempY * SZEROKOSC + tempX);
	*t = '_';
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COFNIJ2_POS);
	printf("_");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COFNIJ_POS);
	printf("_\b");
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
	tempY = (COFNIJ_POS.Y - POCZATKOWA_Y) / ODSTEP_Y;
	tempX = (COFNIJ_POS.X - POCZATKOWA_X) / ODSTEP_X;
	t = (tab + tempY * SZEROKOSC + tempX);
	*t = '_';
	*pierwszy_ruch += 1;
	if (*liczba_ruchow != 0)
		*liczba_ruchow -= 1;
	*wolno_cofac = 0;
	*liczba_cofniec += 1;
}




void finalizacjaMeczu(int * stan_meczu, char * bufor, COORD POS_ZERO, COORD POS, COORD COFNIJ_POS, COORD TEMP_POS, int * pierwszy_ruch, int * wolno_cofac,
	int * liczba_ruchow, int * liczba_cofniec, char * tab, time_t * czas_startu, wynik ** ogon_wynikow, int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku) {
	while (*stan_meczu != 0) {

		do {
			*bufor = _getch();
		} while (*bufor == '\0');

		if (*bufor == 'c') {
			*stan_meczu = 0;
			wyswietlPodSpodem("                \n                                     \n                                  \n\n                              ", POS);
			wyswietlPodSpodem("    Sterowanie:\nPoruszanie sie: strzalki\nWstawienie znaku: x lub enter", POS);
			cofnij(POS, COFNIJ_POS, TEMP_POS, pierwszy_ruch, wolno_cofac, tab, liczba_ruchow, liczba_cofniec);
		}
		sprawdzanieTabeliWynikow(bufor, POS_ZERO, POS, pierwszy_ruch, wolno_cofac, stan_meczu, tab, *ogon_wynikow, *zwyciestwa, *porazki, *remisy);
		if (*bufor != 'c' && *bufor != 'w') {
			if (*stan_meczu == 1) {
				*zwyciestwa += 1;
			}
			else if (*stan_meczu == -1) {
				*porazki += 1;
			}
			else {
				*remisy += 1;
			}
			*ogon_wynikow = zapiszWynik(*czas_startu, *liczba_ruchow, *liczba_cofniec, *ogon_wynikow, *stan_meczu, nazwa_pliku);
			inicjalizacja(stan_meczu, tab, wolno_cofac, pierwszy_ruch, czas_startu, liczba_ruchow, liczba_cofniec);
			system("cls");
			rysujPlansze(tab, POS_ZERO);
			wyswietlPodSpodem("    Sterowanie:\nPoruszanie sie: strzalki\nWstawienie znaku: x lub enter\nHistoria wynikow: w", POS);
			wyswietlPodSpodem("\n\n\n\nPozwol przeciwnikowi zaczac: p", POS);
		}
	}
}

void kolkoKrzyzyk(char * nazwa_pliku) { 


	// Definicje i inicjalizacje niezbêdnych zmiennych.


	int zwyciestwa;
	int porazki;
	int remisy;
	wynik * ogon_wynikow = wczytajWyniki(&zwyciestwa, &porazki, &remisy, nazwa_pliku);
	dopasujRozmiar();

	COORD POS_ZERO = { POCZATKOWA_X,POCZATKOWA_Y };
	COORD POS = { POCZATKOWA_X,POCZATKOWA_Y };
	COORD TEMP_POS = { POCZATKOWA_X,POCZATKOWA_Y };
	COORD COFNIJ_POS = { POCZATKOWA_X,POCZATKOWA_Y };

	char tab[WYSOKOSC][SZEROKOSC];
	int stan_meczu;
	int liczba_ruchow;
	int liczba_cofniec;
	int wolno_cofac = 0;
	int pierwszy_ruch = 1;
	time_t czas_startu;
	inicjalizacja(&stan_meczu, tab, &wolno_cofac, &pierwszy_ruch, &czas_startu, &liczba_ruchow, &liczba_cofniec);
	system("cls");
	rysujPlansze(tab, POS_ZERO);
	wyswietlPodSpodem("    Sterowanie:\nPoruszanie sie: strzalki\nWstawienie znaku: x lub enter\nHistoria wynikow: w\nPozwol przeciwnikowi zaczac: p", POS);
	char bufor;
	while (1) {

		//Pêtla bêdzie trwa³a, dopóki gracz nie wciœnie klawisza esc.

		finalizacjaMeczu(&stan_meczu, &bufor, POS_ZERO, POS, COFNIJ_POS, TEMP_POS, &pierwszy_ruch, &wolno_cofac,
			&liczba_ruchow, &liczba_cofniec, tab, &czas_startu, &ogon_wynikow, &zwyciestwa, &porazki, &remisy, nazwa_pliku);

		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
		bufor = _getch();
		CONSOLE_SCREEN_BUFFER_INFO informacje_o_konsoli;

		sprawdzanieTabeliWynikow(&bufor, POS_ZERO, POS, &pierwszy_ruch, &wolno_cofac, &stan_meczu, tab, ogon_wynikow, zwyciestwa, porazki, remisy);

		if (bufor == 'c' && wolno_cofac == 1) { //Wciœniêcie klawisza c cofnie ostatni ruch obojga graczy.
			cofnij(POS, COFNIJ_POS, TEMP_POS, &pierwszy_ruch, &wolno_cofac, tab, &liczba_ruchow, &liczba_cofniec);
			if (pierwszy_ruch == 1) {
				wyswietlPodSpodem("\n\n\n\nPozwol przeciwnikowi zaczac: p", POS);
			}
			else {
				wyswietlPodSpodem("\n\n\n\n                              ", POS);
			}
		}
		if (bufor == 'p' && pierwszy_ruch == 1) { //Wciœniêcie klawisza p sprawi, ¿e przeciwnik komputerowy wykona pierwszy ruch.
			COFNIJ_POS = POS;
			wolno_cofac = 1;
			wyswietlPodSpodem("\n\n\n\nCofnij: c                     ", POS);
			pierwszy_ruch -= 1;
			TEMP_POS = ruchPrzeciwnika(tab, &stan_meczu);
			Sleep(DLUGOSC_PRZERWY);
			if (stan_meczu != -2 && stan_meczu != 1) {
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TEMP_POS);
				printf("O");
				SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
			}
		}
		if (bufor == 'x' || bufor == '\r') { //Przyciski enter oraz x s³u¿¹ do wstawiania w³asnych znaków na planszê.
			GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &informacje_o_konsoli);
			int tempY = (informacje_o_konsoli.dwCursorPosition.Y - POCZATKOWA_Y) / ODSTEP_Y;
			int tempX = (informacje_o_konsoli.dwCursorPosition.X - POCZATKOWA_X) / ODSTEP_X;
			if (tab[tempY][tempX] == '_') {
				tab[tempY][tempX] = 'x';
				if (wolno_cofac == 1 && pierwszy_ruch <= -1) {
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), COFNIJ_POS);
					printf("x");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
				}
				printf("X\b");
				COFNIJ_POS = POS;
				sprawdzZwyciestwo(tempY, tempX, 'x', 'n', tab, &stan_meczu);
				if (wolno_cofac == 0) {
					wyswietlPodSpodem("\n\n\n\nCofnij: c                     ", POS);
				}
				if (stan_meczu != -2 && stan_meczu != 1) {

					//Je¿eli mecz nie zosta³ zakoñczony, to przeciwnik wykonuje swój ruch.

					Sleep(DLUGOSC_PRZERWY);
					if (wolno_cofac == 1) {
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TEMP_POS);
						printf("o");
						SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
					}
					TEMP_POS = ruchPrzeciwnika(tab, &stan_meczu);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TEMP_POS);
					printf("O");
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
				}

				liczba_ruchow++;
				pierwszy_ruch -= 1;
				wolno_cofac = 1;

				//Je¿eli ostatni ruch zmieni³ stan meczu, to zostaje to wyœwietlone.

				if (stan_meczu == 1) {
					wyswietlPodSpodem("    Zwyciezyles!\n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
				}
				else if (stan_meczu == -1) {
					wyswietlPodSpodem("    Przegrales!\n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
				}
				else if (stan_meczu == -2) {
					wyswietlPodSpodem("       Remis!    \n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
				}
			}
		}
		if (bufor == '\x1b') { //Przycisk esc wychodzi z pêtli.
			zwolnijPamiec(ogon_wynikow);
			return;
		}
		przesuwanieKursora(&bufor, &POS);
		//system("cls");
	}
}