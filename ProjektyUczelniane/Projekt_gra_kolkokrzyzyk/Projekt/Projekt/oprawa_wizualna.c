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


void dopasujRozmiar()
{

#ifdef _WIN32

	int szer_okna = POCZATKOWA_X * 2 + (SZEROKOSC - 1) * ODSTEP_X + 1;
	int wys_okna = POCZATKOWA_Y * 2 + (WYSOKOSC - 1) * ODSTEP_Y + 1;
	COORD coord;
	coord.X = szer_okna;
	coord.Y = wys_okna;

	SMALL_RECT Rect;
	Rect.Top = 0;
	Rect.Left = 0;
	Rect.Bottom = wys_okna - 1;
	Rect.Right = szer_okna - 1;

	HANDLE Handle = GetStdHandle(STD_OUTPUT_HANDLE);      // Get Handle 
	SetConsoleWindowInfo(Handle, TRUE, &Rect);            // Set Window Size 
	SetConsoleScreenBufferSize(Handle, coord);            // Set Buffer Size 
#endif

#ifdef unix
#endif
}

void rysujPlansze(char tab[WYSOKOSC][SZEROKOSC], COORD POS_ZERO) {

	int szerokosc_okna = POCZATKOWA_X * 2 + (SZEROKOSC - 1) * ODSTEP_X + 1;
	int wysokosc_okna = POCZATKOWA_Y * 2 + (WYSOKOSC - 1) * ODSTEP_Y + 1;

	for (int k = 0; k < (szerokosc_okna - 22) / 2; k++) { //Dopisujê tyle bia³ych znaków, ile jest potrzebne do wyœrodkowania napisu.
		printf(" ");
	}
	printf("Witaj w grze w piatke!\n\nAby wygrac, utworz ciag pieciu symboli\nw rzedzie, kolumnie lub na ukos."); //22 znaki
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS_ZERO);
	for (int i = 0; i < WYSOKOSC; i++) {
		for (int j = 0; j < SZEROKOSC; j++) {
			printf("%c", tab[i][j]);
			for (int k = 1; k < ODSTEP_X; k++) {
				printf(" ");
			}
		}
		POS_ZERO.Y += ODSTEP_Y;
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS_ZERO);
	}
	POS_ZERO.Y -= WYSOKOSC * ODSTEP_Y;
}

void wyswietlPodSpodem(char * text, COORD POS) {
	COORD TEMP_POS;
	TEMP_POS.X = POCZATKOWA_X + ODSTEP_X;
	TEMP_POS.Y = POCZATKOWA_Y + ODSTEP_Y * WYSOKOSC;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), TEMP_POS);
	printf(text);
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
};

void podziekowanie() {
	system("cls");
	int szerokosc_okna = POCZATKOWA_X * 2 + (SZEROKOSC - 1) * ODSTEP_X + 1;
	int wysokosc_okna = POCZATKOWA_Y * 2 + (WYSOKOSC - 1) * ODSTEP_Y + 1;
	for (int k = 0; k < wysokosc_okna / 2; k++) { //Przesuwam tekst o tyle linijek, ile jest potrzebne do wyœrodkowania napisu.
		printf("\n");
	}
	for (int k = 0; k < (szerokosc_okna - 16) / 2; k++) { //Dopisujê tyle bia³ych znaków, ile jest potrzebne do wyœrodkowania napisu.
		printf(" ");
	}
	printf("Dziekuje za gre!");
	Sleep(1250);
	system("cls");
}