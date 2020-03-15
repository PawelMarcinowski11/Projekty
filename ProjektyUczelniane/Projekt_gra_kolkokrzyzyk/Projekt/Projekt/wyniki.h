/** @file */


#ifndef WYNIKI_HEADER
#define WYNIKI_HEADER

/** Struktura, kt�rej elementy tworz� dwukierunkow� list� wynik�w.*/
typedef struct wynik { 
	time_t data; ///> Niesformatowana data zako�czenia rozgrywki.
	time_t czas_gry; ///> Niesformatowany czas trwania rozgrywki.
	int liczba_ruchow; ///> Liczba ruch�w wykonanych przez gracza w trakcie gry.
	int liczba_cofniec; ///> Liczba cofni�� wykonanych przez gracza w trakcie gry.
	int wynik; ///> Wynik rozgrywki: zwyci�stwo, pora�ka, b�d� remis.
	struct wynik * pPrev; ///> Wska�nik na poprzedni element listy.
	struct wynik * pNext; ///> Wska�nik na nast�pny element listy.
}wynik;

/** Funkcja, kt�ra tworzy nowy plik przechowuj�cy wyniki, b�d� zamazuje obecny, po czym zape�nia pierwsze 12 bajt�w pliku informacjami o liczbie zwyci�stw, pora�ek i remis�w.
@param nazwa_pliku Nazwa pliku, kt�ry b�dzie s�u�y� do przechowywania zapis�w.
*/
void inicjalizujWyniki(char * nazwa_pliku);

/** Funkcja, kt�ra sprawdza czy plik istnieje, oraz czy ma zapisane swoje pierwsze 12 bajt�w.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
@return 1 - w przypadku gdy plik nie istnieje, b�d� nie ma zapisanych swoich pierwszych 12 bajt�w. W innym wypadku 0.
*/
int sprawdzWyniki(char * nazwa_pliku);

/** Funkcja, kt�ra czy�ci plik do przechowywania zapis�w, po czym ustawia liczb� zwyci�stw, pora�ek i remis�w na 0.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
@param zwyciestwa Adres zmiennej, kt�ra przechowuje liczb� zwyci�stw w historii wynik�w.
@param porazki Adres zmiennej, kt�ra przechowuje liczb� pora�ek w historii wynik�w.
@param remisy Adres zmiennej, kt�ra przechowuje liczb� remis�w w historii wynik�w.
*/
void stworzCzystaLista(char * nazwa_pliku, int * zwyciestwa, int * porazki, int * remisy);

/** Funkcja alokuje pami�� dla elementu listy, zape�nia go jednym wynikiem zczytanym z pliku i zwracaja wska�nik na ten element.
@param f Wska�nik do pliku, z kt�rej b�dzie wczytywany wynik.
@param sprawdzPoprawnosc Adres zmiennej typu int, kt�ra przybiera warto�� 0, je�eli wczytywanie z pliku nie powiod�o si�.
@return Wska�nik na element z wczytanym wynikiem.
*/
wynik * wczytajJedenWynik(FILE *f, int * sprawdzPoprawnosc);

/** Funkcja wczytuj�ca wszystkie wyniki z pliku, lub - w razie niepowodzenia, inicjalizuj�ca nowy plik na zapisy.
@param zwyciestwa Adres zmiennej, kt�ra przechowuje liczb� zwyci�stw w historii wynik�w.
@param porazki Adres zmiennej, kt�ra przechowuje liczb� pora�ek w historii wynik�w.
@param remisy Adres zmiennej, kt�ra przechowuje liczb� remis�w w historii wynik�w.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
@return Wska�nik na ogon listy wynik�w.
*/
wynik * wczytajWyniki(int * zwyciestwa, int * porazki, int * remisy, char * nazwa_pliku);

/** Funkcja wczytuj�ca wszystkie wyniki z pliku, lub - w razie niepowodzenia, inicjalizuj�ca nowy plik na zapisy.
@param czas_startu Niesformatowana data rozpocz�cia rozgrywki.
@param liczba_ruchow Liczba ruch�w wykonanych przez gracza w trakcie gry.
@param liczba_cofniec Liczba cofni�� wykonanych przez gracza w trakcie gry.
@param ogon_wynikow Wska�nik na ogon listy wynik�w.
@param rezultat Wynik rozgrywki: zwyci�stwo, pora�ka, b�d� remis.
@param nazwa_pliku Nazwa pliku, kt�ry s�u�y do przechowywania zapis�w.
@return Wska�nik na nowy ogon listy wynik�w.
*/
wynik * zapiszWynik(time_t czas_startu, int liczba_ruchow, int liczba_cofniec, wynik * ogon_wynikow, int rezultat, char * nazwa_pliku);

/** Funkcja wypisuje na ekran jeden wynik w sformatowanej postaci.
@param wynik Wska�nik na wypisywany wynik.
*/
void wypiszWynik(wynik * wynik);

/** Funkcja wypisuje na ekran podan� liczb� wynik�w w sformatowanej postaci.
@param pierwszy Wska�nik na pierwszy z wypisywanych wynik�w.
@param liczba Liczba wynik�w do wypisania.
*/
void wypiszKilkaWynikow(wynik * pierwszy, int liczba);

/** Funkcja pozwala przegl�da� histori� wynik�w, do momentu w kt�rym gracz wci�nie klawisz powrotu do gry.
@param bufor Bufor, do kt�rego wczytywane s� znaki z wej�cia.
@param POS_ZERO Pozycja, na kt�r� kursor wraca przed rysowaniem planszy do gry.
@param POS Pozycja, na kt�r� kursor wraca po zako�czeniu wy�wietlania tabeli wynik�w.
@param pierwszy_ruch Adres zmiennej zawieraj�cej informacj� o tym, czy pierwszy ruch zosta� wykonany, czy jeszcze nie.
@param wolno_cofac Adres zmiennej zawieraj�cej informacj� o tym, czy dozwolone jest cofni�cie ruchu.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param ogon_wynikow Wska�nik na ogon listy wynik�w.
@param win Liczba zwyci�stw.
@param lose Liczba pora�ek.
@param tie Liczba remis�w.
*/
void sprawdzanieTabeliWynikow(char * bufor, COORD POS_ZERO, COORD POS, int * pierwszy_ruch, int * wolno_cofac, int * stan_meczu,
	char * tab, wynik * ogon_wynikow, int win, int lose, int tie);

#endif