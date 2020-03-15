#include "Header.h"

int main() {
	srand(time(NULL));
	Wstep wstep;
	wstep.wyswietlWstep();
	Gra projekcik;
	projekcik.inicjalizujBaze();
	projekcik.getBaza()->DodajZwierzatka("Baza.txt");
	projekcik.loop();
	projekcik.getBaza()->WyrzucZwierzatko("PIES");
	projekcik.getBaza()->WyrzucZwierzatko("");
	projekcik.getBaza()->CzyscListeNW();
	projekcik.getBaza()->CzyscListeWW();
	projekcik.deinicjalizujBaze();
	return 0;
}