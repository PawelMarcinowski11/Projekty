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

typedef struct { //Lista wyników
	time_t data;
	time_t czas_gry;
	int liczba_ruchow;
	int liczba_cofniec;
	int wynik;
	struct wynik * pPrev;
	struct wynik * pNext;
}wynik;

void inicjalizujWyniki(char * nazwa_pliku) {
	FILE * f = fopen(nazwa_pliku, "wb+");

	int temp = 0;

	fwrite(&temp, (int)sizeof(int), 1, f);
	fwrite(&temp, (int)sizeof(int), 1, f);
	fwrite(&temp, (int)sizeof(int), 1, f);

	fclose(f);
}

int sprawdzWyniki(char * nazwa_pliku) {
	FILE *f = fopen(nazwa_pliku, "rb+");
	int temp[3];
	if (f == NULL) {
		return 1;
	}
	else if (fread(&temp, (int)sizeof(int), 3, f) != 3) {
		return 1;
	}
	return 0;
}

wynik * wczytajJedenWynik(FILE *f, int * sprawdzPoprawnosc) {
	wynik *wczytywany = malloc(sizeof(wynik));
	fread(&(wczytywany->data), (time_t)sizeof(time_t), 1, f);
	fread(&(wczytywany->czas_gry), sizeof(time_t), 1, f);
	fread(&(wczytywany->liczba_ruchow), sizeof(int), 1, f);
	fread(&(wczytywany->liczba_cofniec), sizeof(int), 1, f);
	*sprawdzPoprawnosc = fread(&(wczytywany->wynik), sizeof(int), 1, f);
	return wczytywany;
}

void stworzCzystaLista(char * nazwa_pliku, int * zwyciestwa, int * porazki, int * remisy) {
	inicjalizujWyniki(nazwa_pliku);
	*zwyciestwa = 0;
	*porazki = 0;
	*remisy = 0;
}

wynik * wczytajWyniki(int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku) {
	if (sprawdzWyniki(nazwa_pliku) == 1) {
		stworzCzystaLista(nazwa_pliku, zwyciestwa, porazki, remisy);
		return NULL;
	}
	else {

		FILE * f = fopen(nazwa_pliku, "rb");

		fseek(f, 0, 0);

		fread(zwyciestwa, (int)sizeof(int), 1, f);
		fread(porazki, (int)sizeof(int), 1, f);
		fread(remisy, (int)sizeof(int), 1, f);

		if (*zwyciestwa < 0 || *zwyciestwa > 1000) {
			fclose(f);
			stworzCzystaLista(nazwa_pliku, zwyciestwa, porazki, remisy);
			return NULL;
		}
		else if (*porazki < 0 || *porazki > 1000) {
			fclose(f);
			stworzCzystaLista(nazwa_pliku, zwyciestwa, porazki, remisy);
			return NULL;
		}
		else if (*remisy < 0 || *remisy > 1000) {
			fclose(f);
			stworzCzystaLista(nazwa_pliku, zwyciestwa, porazki, remisy);
			return NULL;
		}

		int liczba_wynikow = *zwyciestwa + *porazki + *remisy;

		if (liczba_wynikow == 0) {
			return NULL;
		}

		int sprawdzajacy;

		wynik * temp/* = malloc((wynik*)sizeof(wynik))*/;
		temp = wczytajJedenWynik(f, &sprawdzajacy);
		temp->pPrev = NULL;

		for (int i = 1; i < liczba_wynikow; i++) {
			wynik * wczytywany/* = malloc((wynik*)sizeof(wynik))*/;
			wczytywany = wczytajJedenWynik(f, &sprawdzajacy);
			wczytywany->pPrev = temp;
			wczytywany->pNext = NULL;
			temp->pNext = wczytywany;
			temp = wczytywany;
		}
		if (sprawdzajacy == 0) {
			fclose(f);
			stworzCzystaLista(nazwa_pliku, zwyciestwa, porazki, remisy);
			zwolnijPamiec(temp);
			return NULL;
		}

		fclose(f);

		return temp;

	}
}


wynik* zapiszWynik(time_t czas_startu, int liczba_ruchow, int liczba_cofniec, wynik * ogon_wynikow, int rezultat, char * nazwa_pliku) {

	time_t czas_konca;
	time_t roznica_czasu;
	time(&czas_konca);
	roznica_czasu = difftime(czas_konca, czas_startu);

	wynik *nowy = malloc(sizeof(wynik));
	nowy->pNext = NULL;
	nowy->pPrev = ogon_wynikow;

	if (ogon_wynikow) {
		ogon_wynikow->pNext = nowy;
	}
	else {
		ogon_wynikow = nowy;
	}

	nowy->czas_gry = roznica_czasu;
	nowy->data = czas_konca;
	nowy->liczba_cofniec = liczba_cofniec;
	nowy->liczba_ruchow = liczba_ruchow;
	nowy->wynik = rezultat;

	FILE * f = fopen(nazwa_pliku, "rb+");

	int temp;

	if (rezultat == 1) { //zwyciestwo
		fread(&temp, (int)sizeof(int), 1, f);
	}
	else if (rezultat == -1) { //porazka
		fseek(f, (int)sizeof(int), 0);
		fread(&temp, (int)sizeof(int), 1, f);
	}
	else if (rezultat == -2) { //remis
		fseek(f, 2 * (int)sizeof(int), 0);
		fread(&temp, (int)sizeof(int), 1, f);
	}
	temp++;
	fseek(f, -1 * (int)sizeof(int), 1);
	fwrite(&temp, (int)sizeof(int), 1, f);


	fseek(f, 0, 2);
	fwrite(&czas_konca, (time_t)sizeof(time_t), 1, f);
	fwrite(&roznica_czasu, (time_t)sizeof(time_t), 1, f);
	fwrite(&liczba_ruchow, (int)sizeof(int), 1, f);
	fwrite(&liczba_cofniec, (int)sizeof(int), 1, f);
	fwrite(&rezultat, (int)sizeof(int), 1, f);

	fclose(f);

	return nowy;
	//zapisaæ czas_konca, roznica_czasu, liczba_ruchow, liczba_cofniec, wynik


	//printf("Czas gry: %d minut%c, %d sekund%c",sformatowany_Czas_2->tm_min,literka1,sformatowany_Czas_2->tm_sec,literka2);

}
void wypiszWynik(wynik * wynik) {
	struct tm * sformatowany_Czas;
	sformatowany_Czas = localtime(&wynik->data);
	printf("Data: %.2d/%.2d/%.2d %.2d:%.2d\n", sformatowany_Czas->tm_mday, sformatowany_Czas->tm_mon + 1, sformatowany_Czas->tm_year % 100, sformatowany_Czas->tm_hour, sformatowany_Czas->tm_min);

	struct tm * sformatowany_Czas_2;
	sformatowany_Czas_2 = localtime(&wynik->czas_gry);

	char * fleksja1;
	if (sformatowany_Czas_2->tm_min == 1)
		fleksja1 = "a";
	else if (sformatowany_Czas_2->tm_min >= 2 && sformatowany_Czas_2->tm_min <= 4)
		fleksja1 = "y";
	else if (sformatowany_Czas_2->tm_min / 10 != 1 && sformatowany_Czas_2->tm_min % 10 >= 2 && sformatowany_Czas_2->tm_min % 10 <= 4)
		fleksja1 = "y";
	else
		fleksja1 = "";
	char * fleksja2;
	if (sformatowany_Czas_2->tm_sec == 1)
		fleksja2 = "a";
	else if (sformatowany_Czas_2->tm_sec >= 2 && sformatowany_Czas_2->tm_sec <= 4)
		fleksja2 = "y";
	else if (sformatowany_Czas_2->tm_sec / 10 != 1 && sformatowany_Czas_2->tm_sec % 10 >= 2 && sformatowany_Czas_2->tm_sec % 10 <= 4)
		fleksja2 = "y";
	else
		fleksja2 = "";

	printf("Ruchy: %d  Cofniecia: %d\n", wynik->liczba_ruchow, wynik->liczba_cofniec);

	printf("Czas gry: %d minut%s, %d sekund%s\nWynik: ", sformatowany_Czas_2->tm_min, fleksja1, sformatowany_Czas_2->tm_sec, fleksja2);

	switch (wynik->wynik)
	{
	case 1:
		printf("Zwyciestwo\n\n");
		break;
	case -1:
		printf("Porazka\n\n");
		break;
	case -2:
		printf("Remis\n\n");
		break;
	}
}

void wypiszKilkaWynikow(wynik * pierwszy, int liczba) {
	int i = 0;
	while (pierwszy && i < liczba) {
		wypiszWynik(pierwszy);
		pierwszy = pierwszy->pPrev;
		i++;
	}
}

void sprawdzanieTabeliWynikow(char * bufor, COORD POS_ZERO, COORD POS, int * pierwszy_ruch, int * wolno_cofac, int * stan_meczu,
	char * tab, wynik * ogon_wynikow, int win, int lose, int tie) {
	if (*bufor == 'w') { //tabela wynikow
		system("cls");
		wyswietlPodSpodem("\n\n\n\n\nPrzesuwanie: Strzalki\nPowrot: w          ", POS);
		COORD GORNY_LEWY_ROG = { 0,0 };
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), GORNY_LEWY_ROG);

		int obecna_pozycja = 1;
		int zmiana = obecna_pozycja;
		int wyniki_na_strone = 5;
		wynik * temp = ogon_wynikow;
		if (temp == NULL) {
			obecna_pozycja = 0;
		}
		wynik * temp_sprawdzajacy;
		printf("\n\b\b\b\b\b\bW: %d\b", win);
		printf("\n\n\b\b\b\b\b\bP: %d\b", lose);
		printf("\n\n\b\b\b\b\b\bR: %d\b", tie);
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), GORNY_LEWY_ROG);
		wypiszKilkaWynikow(temp, wyniki_na_strone);
		int zakres = obecna_pozycja + 4;
		if (zakres > win + lose + tie) {
			zakres = win + lose + tie;
		}
		printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b %d-%d / %d", obecna_pozycja, zakres, win + lose + tie);

		do
		{
			*bufor = _getch();
			if (*bufor == '\x1b') //przycisk esc
				return;

			if (*bufor == -32) {
				*bufor = _getch();
				switch (*bufor)
				{
				case 72:
					if (obecna_pozycja != 1) {
						obecna_pozycja--;
						temp = temp->pNext;
					}
					break;
				case 75:
					if (obecna_pozycja != 1) {
						obecna_pozycja--;
						temp = temp->pNext;
					}
					break;
				case 77:
					if (obecna_pozycja + 4 < win + lose + tie) {
						obecna_pozycja++;
						temp = temp->pPrev;
					}
					break;
				case 80:
					if (obecna_pozycja + 4 < win + lose + tie) {
						obecna_pozycja++;
						temp = temp->pPrev;
					}
					break;
				}
				if (zmiana != obecna_pozycja) {
					zmiana = obecna_pozycja;
					system("cls");
					wyswietlPodSpodem("\n\n\n\n\nPrzesuwanie: Strzalki\nPowrot: w          ", POS);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), GORNY_LEWY_ROG);
					printf("\n\b\b\b\b\b\bW: %d\b", win);
					printf("\n\n\b\b\b\b\b\bP: %d\b", lose);
					printf("\n\n\b\b\b\b\b\bR: %d\b", tie);
					SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), GORNY_LEWY_ROG);
					wypiszKilkaWynikow(temp, 5);
					printf("\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b\b %d-%d / %d", obecna_pozycja, obecna_pozycja + 4, win + lose + tie);
				}
			}
		} while (*bufor != 'w');
		system("cls");
		rysujPlansze(tab, POS_ZERO);
		if (*stan_meczu == 1) {
			wyswietlPodSpodem("    Zwyciezyles!\n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
		}
		else if (*stan_meczu == -1) {
			wyswietlPodSpodem("    Przegrales!\n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
		}
		else if (*stan_meczu == -2) {
			wyswietlPodSpodem("       Remis!    \n           Nacisnij dowolny przycisk,\n           aby rozpoczac nowa gre.", POS);
		}
		else
			wyswietlPodSpodem("    Sterowanie:\nPoruszanie sie: strzalki\nWstawienie znaku: x lub enter", POS);
		wyswietlPodSpodem("\n\n\nHistoria wynikow: w", POS);
		if (*pierwszy_ruch == 1) {
			wyswietlPodSpodem("\n\n\n\nPozwol przeciwnikowi zaczac: p", POS);
		}
		else if (*wolno_cofac == 1) {
			wyswietlPodSpodem("\n\n\n\nCofnij: c                     ", POS);
		}
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), POS);
	}
}