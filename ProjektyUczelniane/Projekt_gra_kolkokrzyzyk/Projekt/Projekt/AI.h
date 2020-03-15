/** @file */


#ifndef AI_HEADER
#define AI_HEADER

#define SZEROKOSC 9
#define WYSOKOSC 8

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzGora(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzDol(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo³uj¹ca dwie funkcje rekurencyjne, aby policzyæ liczbê podanych znaków w dwóch przeciwstawnych kierunkach od po³o¿enia kursora.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danych kierunkach sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzPionowo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo³uj¹ca dwie funkcje rekurencyjne, aby policzyæ liczbê podanych znaków w dwóch przeciwstawnych kierunkach od po³o¿enia kursora.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danych kierunkach sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzPoziomo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzGoraLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzDolPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzGoraPrawo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja rekurencyjna, która sprawdza ile pól w danym kierunku od po³o¿enia kursura sk³ada siê z podanych znaków, po czym zwraca tê liczbê.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danym kierunku sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzDolLewo(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo³uj¹ca dwie funkcje rekurencyjne, aby policzyæ liczbê podanych znaków w dwóch przeciwstawnych kierunkach od po³o¿enia kursora.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danych kierunkach sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzLewaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja wywo³uj¹ca dwie funkcje rekurencyjne, aby policzyæ liczbê podanych znaków w dwóch przeciwstawnych kierunkach od po³o¿enia kursora.
@param y Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param x Wspó³rzêdna pola na planszy, na którym znajduje siê kursor.
@param znak Jeden ze znaków, których liczba jest sprawdzana.
@param znak2 Drugi znak, których liczba jest sprawdzana.
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@return Liczba pól w danych kierunkach sk³adaj¹ca siê wy³¹cznie z podanych znaków.
*/
int policzPrawaPrzekatna(int y, int x, char znak, char znak2, char tab[WYSOKOSC][SZEROKOSC]);

/** Funkcja nadaje polu o napotkanych wspó³rzêdnych najwy¿szy priorytet, sprawiaj¹c ¿e gracz komputerowy wstawi tam znak nie zwracaj¹c uwagi na inne mo¿liwoœci.
@param y Adres zmiennej zawieraj¹cej wspó³rzêdn¹ pola na planszy, na którym znajduje siê kursor.
@param x Adres zmiennej zawieraj¹cej wspó³rzêdn¹ pola na planszy, na którym znajduje siê kursor.
@param maxY Adres zmiennej zawieraj¹cej wspó³rzêdn¹ o najwy¿szym priorytecie dla sztucznej inteligencji.
@param maxX Adres zmiennej zawieraj¹cej wspó³rzêdn¹ o najwy¿szym priorytecie dla sztucznej inteligencji.
*/
void dopelnijDoPiatki(int * y, int * x, int * maxY, int * maxX);

/** Funkcja ocenia wszystkie wolne pola na planszy pod wzglêdem mo¿liwoœci u³o¿enia pi¹tki, b¹dŸ przeszkodzenia przeciwnikowi w osi¹gniêciu tego celu, po czym zwraca wspó³rzêdne pola najwy¿ej ocenionego pola. Zmienia aktualny stan meczu, je¿eli wyznaczony ruch skutkuje zwyciêstwem lub remisem. 
@param tab Tablica zawieraj¹ca informacje o po³o¿eniu wszystkich znaków na planszy.
@param stan_meczu Adres zmiennej zawieraj¹cej informacjê o aktualnym stanie meczu.
@return Wspó³rzêdne pola, w które gracz komputerowy wstawi znak.
*/
COORD ruchPrzeciwnika(char tab[WYSOKOSC][SZEROKOSC], int * stan_meczu);

#endif