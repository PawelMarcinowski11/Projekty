/** @file */


#ifndef WYNIKI_HEADER
#define WYNIKI_HEADER

/** Struktura, której elementy tworz¹ dwukierunkow¹ listê wyników.*/
typedef struct wynik { 
	time_t data; ///> Niesformatowana data zakoñczenia rozgrywki.
	time_t czas_gry; ///> Niesformatowany czas trwania rozgrywki.
	int liczba_ruchow; ///> Liczba ruchów wykonanych przez gracza w trakcie gry.
	int liczba_cofniec; ///> Liczba cofniêæ wykonanych przez gracza w trakcie gry.
	int wynik; ///> Wynik rozgrywki: zwyciêstwo, pora¿ka, b¹dŸ remis.
	struct wynik * pPrev; ///> WskaŸnik na poprzedni element listy.
	struct wynik * pNext; ///> WskaŸnik na nastêpny element listy.
}wynik;

/** Funkcja, która tworzy nowy plik przechowuj¹cy wyniki, b¹dŸ zamazuje obecny, po czym zape³nia pierwsze 12 bajtów pliku informacjami o liczbie zwyciêstw, pora¿ek i remisów.
@param nazwa_pliku Nazwa pliku, który bêdzie s³u¿y³ do przechowywania zapisów.
*/
void inicjalizujWyniki(char * nazwa_pliku);

/** Funkcja, która sprawdza czy plik istnieje, oraz czy ma zapisane swoje pierwsze 12 bajtów.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
@return 1 - w przypadku gdy plik nie istnieje, b¹dŸ nie ma zapisanych swoich pierwszych 12 bajtów. W innym wypadku 0.
*/
int sprawdzWyniki(char * nazwa_pliku);

/** Funkcja, która czyœci plik do przechowywania zapisów, po czym ustawia liczbê zwyciêstw, pora¿ek i remisów na 0.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
@param zwyciestwa Adres zmiennej, która przechowuje liczbê zwyciêstw w historii wyników.
@param porazki Adres zmiennej, która przechowuje liczbê pora¿ek w historii wyników.
@param remisy Adres zmiennej, która przechowuje liczbê remisów w historii wyników.
*/
void stworzCzystaLista(char * nazwa_pliku, int * zwyciestwa, int * porazki, int * remisy);

/** Funkcja alokuje pamiêæ dla elementu listy, zape³nia go jednym wynikiem zczytanym z pliku i zwracaja wskaŸnik na ten element.
@param f WskaŸnik do pliku, z której bêdzie wczytywany wynik.
@param sprawdzPoprawnosc Adres zmiennej typu int, która przybiera wartoœæ 0, je¿eli wczytywanie z pliku nie powiod³o siê.
@return WskaŸnik na element z wczytanym wynikiem.
*/
wynik * wczytajJedenWynik(FILE *f, int * sprawdzPoprawnosc);

/** Funkcja wczytuj¹ca wszystkie wyniki z pliku, lub - w razie niepowodzenia, inicjalizuj¹ca nowy plik na zapisy.
@param zwyciestwa Adres zmiennej, która przechowuje liczbê zwyciêstw w historii wyników.
@param porazki Adres zmiennej, która przechowuje liczbê pora¿ek w historii wyników.
@param remisy Adres zmiennej, która przechowuje liczbê remisów w historii wyników.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
@return WskaŸnik na ogon listy wyników.
*/
wynik * wczytajWyniki(int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku);

/** Funkcja wczytuj¹ca wszystkie wyniki z pliku, lub - w razie niepowodzenia, inicjalizuj¹ca nowy plik na zapisy.
@param czas_startu Niesformatowana data rozpoczêcia rozgrywki.
@param liczba_ruchow Liczba ruchów wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Liczba cofniêæ wykonanych przez gracza w trakcie gry.
@param ogon_wynikow WskaŸnik na ogon listy wyników.
@param rezultat Wynik rozgrywki: zwyciêstwo, pora¿ka, b¹dŸ remis.
@param nazwa_pliku Nazwa pliku, który s³u¿y do przechowywania zapisów.
@return WskaŸnik na nowy ogon listy wyników.
*/
wynik * zapiszWynik(time_t czas_startu, int liczba_ruchow, int liczba_cofniec, wynik * ogon_wynikow, int rezultat, char * nazwa_pliku);

/** Funkcja wypisuje na ekran jeden wynik w sformatowanej postaci.
@param wynik WskaŸnik na wypisywany wynik.
*/
void wypiszWynik(wynik * wynik);

/** Funkcja wypisuje na ekran podan¹ liczbê wyników w sformatowanej postaci.
@param pierwszy WskaŸnik na pierwszy z wypisywanych wyników.
@param liczba Liczba wyników do wypisania.
*/
void wypiszKilkaWynikow(wynik * pierwszy, int liczba);

/** Funkcja pozwala przegl¹daæ historiê wyników, do momentu w którym gracz wciœnie klawisz powrotu do gry.
@param bufor Bufor, do którego wczytywane s¹ znaki z wejœcia.
@param POS_ZERO Pozycja, na któr¹ kursor wraca przed rysowaniem planszy do gry.
@param POS Pozycja, na któr¹ kursor wraca po zakoñczeniu wyœwietlania tabeli wyników.
@param pierwszy_ruch Adres zmiennej zawieraj¹cej informacjê o tym, czy pierwszy ruch zosta³ wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj¹cej informacjê o tym, czy dozwolone jest cofniêcie ruchu.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param ogon_wynikow WskaŸnik na ogon listy wyników.
@param win Liczba zwyciêstw.
@param lose Liczba pora¿ek.
@param tie Liczba remisów.
*/
void sprawdzanieTabeliWynikow(char * bufor, COORD POS_ZERO, COORD POS, int * pierwszy_ruch, int * wolno_cofac, int * stan_meczu,
	char * tab, wynik * ogon_wynikow, int win, int lose, int tie);

#endif