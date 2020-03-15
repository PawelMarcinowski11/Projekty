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


int policzGora(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (y == -1)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzGora(y - 1, x, znak, znak2, tab);
}
int policzDol(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (y == WYSOKOSC)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == (WYSOKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzDol(y + 1, x, znak, znak2, tab);
}
int policzLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (x == -1)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (x == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzLewo(y, x - 1, znak, znak2, tab);
}
int policzPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (x == SZEROKOSC)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (x == (SZEROKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzPrawo(y, x + 1, znak, znak2, tab);
}
int policzPionowo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	return policzGora(y - 1, x, znak, znak2, tab) + policzDol(y + 1, x, znak, znak2, tab);
}
int policzPoziomo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	return policzLewo(y, x - 1, znak, znak2, tab) + policzPrawo(y, x + 1, znak, znak2, tab);
}
int policzGoraLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (y == -1 || x == -1)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else if (x == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzGoraLewo(y - 1, x - 1, znak, znak2, tab);
}
int policzDolPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (y == WYSOKOSC || x == SZEROKOSC)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == (WYSOKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else if (x == (SZEROKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzDolPrawo(y + 1, x + 1, znak, znak2, tab);
}
int policzGoraPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	if (y == -1 || x == SZEROKOSC)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else if (x == (SZEROKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzGoraPrawo(y - 1, x + 1, znak, znak2, tab);
}
int policzDolLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {

	if (y == WYSOKOSC || x == -1)
		return 0;
	else if (tab[y][x] != znak && tab[y][x] != znak2)
		return 0;
	else if (y == (WYSOKOSC - 1) && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else if (x == 0 && tab[y][x] == znak && tab[y][x] == znak2)
		return 1;
	else
		return 1 + policzDolLewo(y + 1, x - 1, znak, znak2, tab);
}
int policzLewaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	return policzGoraLewo(y - 1, x - 1, znak, znak2, tab) + policzDolPrawo(y + 1, x + 1, znak, znak2, tab);
}
int policzPrawaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]) {
	return policzGoraPrawo(y - 1, x + 1, znak, znak2, tab) + policzDolLewo(y + 1, x - 1, znak, znak2, tab);
}



void dopelnijDoPiatki(int * y, int * x, int * maxY, int * maxX) {
	*maxY = *y;
	*maxX = *x;
	*y = WYSOKOSC;
	*x = SZEROKOSC;
};

COORD ruchPrzeciwnika(char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu) {
	int tabPriorytetow[WYSOKOSC][SZEROKOSC];
	int maxY = -1, maxX = -1;
	for (int i = 0; i < WYSOKOSC; i++) {
		for (int j = 0; j < SZEROKOSC; j++) {
			if (tab[i][j] == '_') {

				int temp;
				int temp_z_pustymi;
				int temp_obu_graczy;

				tabPriorytetow[i][j] = 0;

				temp = policzPionowo(i, j, 'o', 'n', tab);
				temp_obu_graczy = policzPionowo(i, j, 'o', 'x', tab);
				if (temp >= 4) {
					dopelnijDoPiatki(&i, &j, &maxY, &maxX);
					ustawWynik(-1, stan_meczu);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}


				temp_z_pustymi = policzPionowo(i, j, 'o', '_', tab);
				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_PASYWNOSC;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzPionowo(i, j, 'x', 'n', tab);
				if (temp >= 4) {
					temp *= 100;
					//dopelnijDoPiatki(&i, &j, &maxY, &maxX);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzPionowo(i, j, 'x', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_REAKCJA;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzPoziomo(i, j, 'o', 'n', tab);
				temp_obu_graczy = policzPoziomo(i, j, 'o', 'x', tab);
				if (temp >= 4) {
					dopelnijDoPiatki(&i, &j, &maxY, &maxX);
					ustawWynik(-1, stan_meczu);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzPoziomo(i, j, 'o', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_PASYWNOSC;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzPoziomo(i, j, 'x', 'n', tab);
				if (temp >= 4) {
					temp *= 100;
					//dopelnijDoPiatki(&i, &j, &maxY, &maxX);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzPoziomo(i, j, 'x', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_REAKCJA;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzLewaPrzekatna(i, j, 'o', 'n', tab);
				temp_obu_graczy = policzLewaPrzekatna(i, j, 'o', 'x', tab);
				if (temp >= 4) {
					dopelnijDoPiatki(&i, &j, &maxY, &maxX);
					ustawWynik(-1, stan_meczu);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzLewaPrzekatna(i, j, 'o', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_PASYWNOSC;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzLewaPrzekatna(i, j, 'x', 'n', tab);
				if (temp >= 4) {
					temp *= 100;
					//dopelnijDoPiatki(&i, &j, &maxY, &maxX);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzLewaPrzekatna(i, j, 'x', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_REAKCJA;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzPrawaPrzekatna(i, j, 'o', 'n', tab);
				temp_obu_graczy = policzPrawaPrzekatna(i, j, 'o', 'x', tab);
				if (temp >= 4) {
					dopelnijDoPiatki(&i, &j, &maxY, &maxX);
					ustawWynik(-1, stan_meczu);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzPrawaPrzekatna(i, j, 'o', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_PASYWNOSC;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}


				temp = policzPrawaPrzekatna(i, j, 'x', 'n', tab);
				if (temp >= 4) {
					temp *= 100;
					//dopelnijDoPiatki(&i, &j, &maxY, &maxX);
				}
				else if (temp >= 3 && temp_obu_graczy <= 3) {
					temp *= 3;
				}
				else if (temp >= 3) {
					temp *= 2;
				}

				temp_z_pustymi = policzPrawaPrzekatna(i, j, 'x', '_', tab);

				if (temp_z_pustymi >= 4) {
					tabPriorytetow[i][j] += temp * AI_REAKCJA;
					tabPriorytetow[i][j] += temp_z_pustymi;
				}
			}
			else {
				tabPriorytetow[i][j] = -250;
			}
		}
	}
	if (maxY != -1 && maxX != -1) {
		tab[maxY][maxX] = 'o';
	}
	else {
		int tempMaxPriorytet = -250;
		for (int i = 0; i < WYSOKOSC; i++) {
			for (int j = 0; j < SZEROKOSC; j++) {
				if (tab[i][j] == '_') {
					if (tabPriorytetow[i][j] > tempMaxPriorytet) {
						tempMaxPriorytet = tabPriorytetow[i][j];
						maxY = i;
						maxX = j;
					}
				}
			}
		}
		if (tempMaxPriorytet <= 0)
			ustawWynik(-2, stan_meczu);
		else
			tab[maxY][maxX] = 'o';
	}

	//X = (informacje_o_konsoli.dwCursorPosition.X - POCZATKOWA_X) / ODSTEP_X;
	//X * ODSTEP_X = informacje_o_konsoli.dwCursorPosition.X - POCZATKOWA_X
	//informacje_o_konsoli.dwCursorPosition.X = X * ODSTEP_X + POCZATKOWA_X

	COORD zwrot;
	zwrot.Y = maxY * ODSTEP_Y + POCZATKOWA_Y;
	zwrot.X = maxX * ODSTEP_X + POCZATKOWA_X;
	return zwrot;
}