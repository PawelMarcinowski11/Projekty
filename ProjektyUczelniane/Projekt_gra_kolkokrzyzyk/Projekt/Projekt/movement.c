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



void moveCursor(short * pozycja, int amount, short granica) {
	if (*pozycja != granica)
		*pozycja += amount;
}


void moveLeft(COORD * pozycja) {
	moveCursor(&pozycja->X, -ODSTEP_X, POCZATKOWA_X);
};


void moveRight(COORD * pozycja) {
	moveCursor(&pozycja->X, ODSTEP_X, POCZATKOWA_X + (SZEROKOSC - 1) * ODSTEP_X);
};


void moveUp(COORD * pozycja) {
	moveCursor(&pozycja->Y, -ODSTEP_Y, POCZATKOWA_Y);
};


void moveDown(COORD * pozycja) {
	moveCursor(&pozycja->Y, ODSTEP_Y, POCZATKOWA_Y + (WYSOKOSC - 1) * ODSTEP_Y);
};


void przesuwanieKursora(char * bufor, COORD * POS) {
	if (*bufor == -32) // || bufor == 0) //Je¿eli _getch zwróci któr¹s z tych wartoœci, to znaczy ¿e wprowadzony
									//znak sk³ada siê z dwóch bajtów, w przypadku strza³ek jest to -32
									//i jeden z podanych poni¿ej, a w przypadku strza³ek z klawiatury
									//alfanumerycznej jest to 0 i jeden z podanych poni¿ej.

									//Aktualizacja - na niektórych systemach funkcja _getch zwraca '\0'
									//po znakach liter, co zmusza do wy³¹czenia funkcjonalnoœci sterowania
									//klawiatur¹ alfanumeryczn¹

	{
		*bufor = _getch(); //72 - góra, 77 - prawo, 80 - dó³, 75 - lewo
							//71 - w górê i lewo, 73 - w górê i prawo
							//79 - w dó³ i lewo, 81 - w dó³ i prawo
		switch (*bufor)
		{

			/*case 71:
				moveUp(&POS);
				moveLeft(&POS);
				break;
			case 73:
				moveUp(&POS);
				moveRight(&POS);
				break;
			case 79:
				moveDown(&POS);
				moveLeft(&POS);
				break;
			case 81:
				moveDown(&POS);
				moveRight(&POS);
				break;*/

		case 72:
			moveUp(POS);
			break;
		case 75:
			moveLeft(POS);
			break;
		case 77:
			moveRight(POS);
			break;
		case 80:
			moveDown(POS);
			break;
		}
	}
}
