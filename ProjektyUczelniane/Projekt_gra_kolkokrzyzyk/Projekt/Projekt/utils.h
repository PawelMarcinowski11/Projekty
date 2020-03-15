/** @file */


#ifndef UTILS_HEADER
#define UTILS_HEADER


/** Funkcja przygotowywuj¹ca program do rozpoczêcia nowej rozgrywki.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param wolno_cofac Adres zmiennej zawieraj¹cej informacjê o tym, czy dozwolone jest cofniêcie ruchu.
@param pierwszy_ruch Adres zmiennej zawieraj¹cej informacjê o tym, czy pierwszy ruch zosta³ wykonany, czy jeszcze nie.
@param czas_startu Adres zmiennej zawieraj¹cej niesformatowan¹ datê rozpoczêcia rozgrywki.
@param liczba_ruchow Adres zmiennej zawieraj¹cej liczbê ruchów wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj¹cej liczbê cofniêæ wykonanych przez gracza w trakcie gry.
*/
void inicjalizacja(int * stan_meczu, char tab[WYSOKOSC][SZEROKOSC], int * wolno_cofac, int * pierwszy_ruch, time_t * czas_startu,
	int * liczba_ruchow, int * liczba_cofniec);

/** Funkcja iteruje po dwukierunkowej liœcie wyników, usuwaj¹c ka¿dy z jej elementów.
@param ogon WskaŸnik na ogon listy wyników.
*/
void zwolnijPamiec(wynik * ogon);

/** Funkcja sprawdza liczbê argumentów wiersza poleceñ i, o ile jest wiêksza niz jeden, zwraca pierwszy argument po œcie¿ce pliku.
@param liczba_arg Liczba argumentów wiersza poleceñ.
@param wartosci_arg Argumenty wiersza poleceñ.
@return Nazwa pliku, który bêdzie s³u¿y³ do przechowywania zapisów.
*/
char * wczytajNazwePliku(int liczba_arg, char *wartosci_arg[]);

#endif