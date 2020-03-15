/** @file */


#ifndef AI_HEADER
#define AI_HEADER

#define SZEROKOSC 9
#define WYSOKOSC 8

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzGora(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzDol(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo�uj�ca dwie funkcje rekurencyjne, aby policzy� liczb� podanych znak�w w dw�ch przeciwstawnych kierunkach od po�o�enia kursora.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danych kierunkach sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzPionowo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo�uj�ca dwie funkcje rekurencyjne, aby policzy� liczb� podanych znak�w w dw�ch przeciwstawnych kierunkach od po�o�enia kursora.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danych kierunkach sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzPoziomo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzGoraLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzDolPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzGoraPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, kt�ra sprawdza ile p�l w danym kierunku od po�o�enia kursura sk�ada si� z podanych znak�w, po czym zwraca t� liczb�.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danym kierunku sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzDolLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo�uj�ca dwie funkcje rekurencyjne, aby policzy� liczb� podanych znak�w w dw�ch przeciwstawnych kierunkach od po�o�enia kursora.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danych kierunkach sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzLewaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo�uj�ca dwie funkcje rekurencyjne, aby policzy� liczb� podanych znak�w w dw�ch przeciwstawnych kierunkach od po�o�enia kursora.
@param y Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param x Wsp�rz�dna pola na planszy, na kt�rym znajduje si� kursor.
@param znak Jeden ze znak�w, kt�rych liczba jest sprawdzana.
@param znak2 Drugi znak, kt�rych liczba jest sprawdzana.
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@return Liczba p�l w danych kierunkach sk�adaj�ca si� wy��cznie z podanych znak�w.
*/
int policzPrawaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja nadaje polu o napotkanych wsp�rz�dnych najwy�szy priorytet, sprawiaj�c �e gracz komputerowy wstawi tam znak nie zwracaj�c uwagi na inne mo�liwo�ci.
@param y Adres zmiennej zawieraj�cej wsp�rz�dn� pola na planszy, na kt�rym znajduje si� kursor.
@param x Adres zmiennej zawieraj�cej wsp�rz�dn� pola na planszy, na kt�rym znajduje si� kursor.
@param maxY Adres zmiennej zawieraj�cej wsp�rz�dn� o najwy�szym priorytecie dla sztucznej inteligencji.
@param maxX Adres zmiennej zawieraj�cej wsp�rz�dn� o najwy�szym priorytecie dla sztucznej inteligencji.
*/
void dopelnijDoPiatki(int * y, int * x, int * maxY, int * maxX);

/** Funkcja ocenia wszystkie wolne pola na planszy pod wzgl�dem mo�liwo�ci u�o�enia pi�tki, b�d� przeszkodzenia przeciwnikowi w osi�gni�ciu tego celu, po czym zwraca wsp�rz�dne pola najwy�ej ocenionego pola. Zmienia aktualny stan meczu, je�eli wyznaczony ruch skutkuje zwyci�stwem lub remisem. 
@param tab Tablica zawieraj�ca informacje o po�o�eniu wszystkich znak�w na planszy.
@param stan_meczu Adres zmiennej zawieraj�cej informacj� o aktualnym stanie meczu.
@return Wsp�rz�dne pola, w kt�re gracz komputerowy wstawi znak.
*/
COORD ruchPrzeciwnika(char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu);

#endif