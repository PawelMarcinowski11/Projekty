/** @file */


#ifndef GAMEPLAY_HEADER
#define GAMEPLAY_HEADER


/** Funkcja zmienia stan meczu na inny.
@param wynik Wynik, na jaki zostaje zmieniony obecny stan meczu.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
*/
void ustawWynik(int wynik, int * stan_meczu);

/** Funkcja sprawdza, czy po ostatnim ruchu gracza, na planszy znajduje siê 5 takich samych znaków w jednej linii. Je¿eli tak, to stan meczu zostaje zmieniony.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
*/
void sprawdzZwyciestwo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu);


/** Funkcja cofa ostatni ruch gracza i jego przeciwnika.
@param POS Pozycja, na któr¹ kursor wraca po zakoñczeniu wyœwietlania tabeli wyników.
@param COFNIJ_POS Pozycja znaku, który jako ostatni zosta³ wstawiony na planszê przez gracza.
@param COFNIJ2_POS Pozycja znaku, który jako ostatni zosta³ wstawiony na planszê przez gracza komputerowego.
@param pierwszy_ruch Adres zmiennej zawieraj¹cej informacjê o tym, czy pierwszy ruch zosta³ wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj¹cej informacjê o tym, czy dozwolone jest cofniêcie ruchu.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param liczba_ruchow Adres zmiennej zawieraj¹cej liczbê ruchów wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj¹cej liczbê cofniêæ wykonanych przez gracza w trakcie gry.
*/
void cofnij(COORD POS, COORD COFNIJ_POS, COORD COFNIJ2_POS, int * pierwszy_ruch, int * wolno_cofac, char * tab, int * liczba_ruchow, int * liczba_cofniec);

/** Funkcja zapisuje wynik meczu, po czym resetuje wszystkie dane z nim zwi¹zane i przygotowywuje program do nastêpnej rozgrywki.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
@param bufor Bufor, do którego wczytywane s¹ znaki z wejœcia.
@param POS_ZERO Pozycja, na któr¹ kursor wraca przed rysowaniem planszy do gry.
@param POS Pozycja, na któr¹ kursor wraca po zakoñczeniu wyœwietlania tabeli wyników.
@param COFNIJ_POS Pozycja znaku, który jako ostatni zosta³ wstawiony na planszê przez gracza.
@param TEMP_POS Pozycja znaku, który jako ostatni zosta³ wstawiony na planszê przez gracza komputerowego.
@param pierwszy_ruch Adres zmiennej zawieraj¹cej informacjê o tym, czy pierwszy ruch zosta³ wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj¹cej informacjê o tym, czy dozwolone jest cofniêcie ruchu.
@param liczba_ruchow Adres zmiennej zawieraj¹cej liczbê ruchów wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Adres zmiennej zawieraj¹cej liczbê cofniêæ wykonanych przez gracza w trakcie gry.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param czas_startu Adres zmiennej zawieraj¹cej niesformatowan¹ datê rozpoczêcia rozgrywki.
@param ogon_wynikow Adres wskaŸnika na ogon listy wyników.
@param zwyciestwa Adres zmiennej zawieraj¹cej liczbê zwyciêstw.
@param porazki Adres zmiennej zawieraj¹cej liczbê pora¿ek.
@param remisy Adres zmiennej zawieraj¹cej liczbê remisów.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
*/
void finalizacjaMeczu(int * stan_meczu, char * bufor, COORD POS_ZERO, COORD POS, COORD COFNIJ_POS, COORD TEMP_POS, int * pierwszy_ruch, int * wolno_cofac, int * liczba_ruchow, int * liczba_cofniec, char * tab, time_t * czas_startu, wynik ** ogon_wynikow, int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku);

/** Funkcja odpowiadaj¹ca za poprawne dzia³anie gry w kó³ko i krzy¿yk.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
*/
void kolkoKrzyzyk(char * nazwa_pliku);

#endif