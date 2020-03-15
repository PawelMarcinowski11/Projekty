/** @file */


#ifndef GAMEPLAY_HEADER
#define GAMEPLAY_HEADER


/** Funkcja zmienia stan meczu na inny.
@param wynik Wynik, na jaki zostaje zmieniony obecny stan meczu.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
*/
void ustawWynik(int wynik, int * stan_meczu);

/** Funkcja sprawdza, czy po ostatnim ruchu gracza, na planszy znajduje si� 5 takich samych znak�w w jednej linii. Je�eli tak, to stan meczu zostaje zmieniony.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
*/
void sprawdzZwyciestwo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu);


/** Funkcja cofa ostatni ruch gracza i jego przeciwnika.
@param POS Pozycja, na kt�r� kursor wraca po zako�czeniu wy�wietlania tabeli wynik�w.
@param COFNIJ_POS Pozycja znaku, kt�ry jako ostatni zosta� wstawiony na plansz� przez gracza.
@param COFNIJ2_POS Pozycja znaku, kt�ry jako ostatni zosta� wstawiony na plansz� przez gracza komputerowego.
@param pierwszy_ruch Adres zmiennej zawieraj�cej informacj� o tym, czy pierwszy ruch zosta� wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj�cej informacj� o tym, czy dozwolone jest cofni�cie ruchu.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param liczba_ruchow Adres zmiennej zawieraj�cej liczb� ruch�w wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj�cej liczb� cofni�� wykonanych przez gracza w trakcie gry.
*/
void cofnij(COORD POS, COORD COFNIJ_POS, COORD COFNIJ2_POS, int * pierwszy_ruch, int * wolno_cofac, char * tab, int * liczba_ruchow, int * liczba_cofniec);

/** Funkcja zapisuje wynik meczu, po czym resetuje wszystkie dane z nim zwi�zane i przygotowywuje program do nast�pnej rozgrywki.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
@param bufor Bufor, do kt�rego wczytywane s� znaki z wej�cia.
@param POS_ZERO Pozycja, na kt�r� kursor wraca przed rysowaniem planszy do gry.
@param POS Pozycja, na kt�r� kursor wraca po zako�czeniu wy�wietlania tabeli wynik�w.
@param COFNIJ_POS Pozycja znaku, kt�ry jako ostatni zosta� wstawiony na plansz� przez gracza.
@param TEMP_POS Pozycja znaku, kt�ry jako ostatni zosta� wstawiony na plansz� przez gracza komputerowego.
@param pierwszy_ruch Adres zmiennej zawieraj�cej informacj� o tym, czy pierwszy ruch zosta� wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj�cej informacj� o tym, czy dozwolone jest cofni�cie ruchu.
@param liczba_ruchow Adres zmiennej zawieraj�cej liczb� ruch�w wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj�cej liczb� cofni�� wykonanych przez gracza w trakcie gry.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param czas_startu Adres zmiennej zawieraj�cej niesformatowan� dat� rozpocz�cia rozgrywki.
@param ogon_wynikow Adres wska�nika na ogon listy wynik�w.
@param zwyciestwa Adres zmiennej zawieraj�cej liczb� zwyci�stw.
@param porazki Adres zmiennej zawieraj�cej liczb� pora�ek.
@param remisy Adres zmiennej zawieraj�cej liczb� remis�w.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
*/
void finalizacjaMeczu(int * stan_meczu, char * bufor, COORD POS_ZERO, COORD POS, COORD COFNIJ_POS, COORD TEMP_POS, int * pierwszy_ruch, int * wolno_cofac, int * liczba_ruchow, int * liczba_cofniec, char * tab, time_t * czas_startu, wynik ** ogon_wynikow, int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku);

/** Funkcja odpowiadaj�ca za poprawne dzia�anie gry w k�ko i krzy�yk.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
*/
void kolkoKrzyzyk(char * nazwa_pliku);

#endif