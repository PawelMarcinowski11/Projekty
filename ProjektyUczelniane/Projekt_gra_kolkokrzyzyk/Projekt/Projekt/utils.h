/** @file */


#ifndef UTILS_HEADER
#define UTILS_HEADER


/** Funkcja przygotowywuj�ca program do rozpocz�cia nowej rozgrywki.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param wolno_cofac Adres zmiennej zawieraj�cej informacj� o tym, czy dozwolone jest cofni�cie ruchu.
@param pierwszy_ruch Adres zmiennej zawieraj�cej informacj� o tym, czy pierwszy ruch zosta� wykonany, czy jeszcze nie.
@param czas_startu Adres zmiennej zawieraj�cej niesformatowan� dat� rozpocz�cia rozgrywki.
@param liczba_ruchow Adres zmiennej zawieraj�cej liczb� ruch�w wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj�cej liczb� cofni�� wykonanych przez gracza w trakcie gry.
*/
void inicjalizacja(int * stan_meczu, char tab[WYSOKOSC][SZEROKOSC], int * wolno_cofac, int * pierwszy_ruch, time_t * czas_startu,
	int * liczba_ruchow, int * liczba_cofniec);

/** Funkcja iteruje po dwukierunkowej li�cie wynik�w, usuwaj�c ka�dy z jej element�w.
@param ogon Wska�nik na ogon listy wynik�w.
*/
void zwolnijPamiec(wynik * ogon);

/** Funkcja sprawdza liczb� argument�w wiersza polece� i, o ile jest wi�ksza niz jeden, zwraca pierwszy argument po �cie�ce pliku.
@param liczba_arg Liczba argument�w wiersza polece�.
@param wartosci_arg Argumenty wiersza polece�.
@return Nazwa pliku, kt�ry b�dzie s�u�y� do przechowywania zapis�w.
*/
char * wczytajNazwePliku(int liczba_arg, char *wartosci_arg[]);

#endif