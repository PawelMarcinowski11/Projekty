/** @file */

#ifndef NAG��WEK_H
#define NAG��WEK_H

/** Struktura parameters zawiera dane kluczowe do dzia�ania kodu, przekazywane za pomoc� prze��cznik�w. */
struct parameters {
	std::string input;  ///< plik wej�ciowy z populacj�
	std::string output; ///< plik wyj�ciowy z populacj�
	unsigned int k; ///< liczba par osobnik�w losowanych do krzy�owania
	unsigned int p; ///< liczba pokole�
	float w; ///< wsp�czynnik wymierania
	float r; ///< wsp�czynnik rozmna�ania
};

/** Element listy tworz�cej chromosom, zawartej w ka�dym elemencie listy osobnik�w. */
struct chromosom {
	unsigned short int wartosc; ///< liczba naturalna b�d�ca pojedynczym fragmentem chromosomu
	chromosom *next; ///< wska�nik na nast�pny element listy tworz�cej chromosom
};

/** Element listy osobnik�w, tworz�cej populacj�. */
struct osobnik {
	float f; ///< warto�� funkcji dopasowania, por�wnywana z wsp�czynnikiem wymierania i rozmna�ania
	osobnik *next; ///< wska�nik na nast�pny element listy osobnik�w
	chromosom *lancuch; ///< wska�nik na g�ow� listy tworz�cej chromosom
};


/** Funkcja sprawdzaj�ca prawid�owo�� argument�w linii polece� i wprowadzaj�ca parametry do zmiennych zale�nie od podanych prze��cznik�w.
@param liczba_arg liczba argument�w wprowadzonych w linii polece�
@param argv[] ci�g znak�w wprowadzony w linii polece�
@param params struktura, do kt�rej zostan� wypisane zmienne kluczowe do prawid�owej pracy programu
@return stan funkcji: 1 - wszystkie parametry zosta�y prawid�owo wprowadzone do odpowiednich zmiennych, 0 - program napotka� na b��dne argumenty i zostanie zatrzymany 
*/
bool sprawdz_przelaczniki(int liczba_arg, char *argv[], parameters & params);

/** Funkcja dodaj�ca kolejny element na koniec listy tworz�cej chromosom.
@param last wska�nik na ostatni element listy fragment�w chromosomu
@param end wska�nik na ogon listy osobnik�w
@param liczba liczba naturalna b�d�ca fragmentem chromosomu
*/
void dodaj_chromosom(chromosom *& last, osobnik *& end, int liczba);

/** Funkcja dodaj�ca kolejny element na koniec listy osobnik�w.
@param start wska�nik na g�ow� listy osobnik�w
@param end wska�nik na ogon listy osobnik�w
*/
void dodaj_osobnik(osobnik *& start, osobnik *& end);

/** Funkcja wczytuj�ca z pliku wej�ciowego dane o populacji.
@param input nazwa pliku wej�ciowego
@param start wska�nik na g�ow� listy osobnik�w
@return stan funkcji : 1 - populacja zosta�a prawid�owo za�adowana z pliku wej�ciowego, 0 - plik wej�ciowy zawiera� b��dy, wi�c program zwolni swoj� pami��, a nast�pnie zostanie zatrzymany
*/
bool wczytaj_z_pliku(std::string input, osobnik *&start);

/** Funkcja losuj�ca miejsce, w kt�rym chromosom wybranego osobnika zostanie przerwany i po��czony z innym chromosomem podczas krzy�owania.
@param os_partner element listy bior�cy udzia� w krzy�owaniu
@return numer elementu listy chromosom�w, w kt�rym nast�pi przepi�cie do fragmentu listy chromosom�w nale��cej do innego osobnika
*/
int losuj_dlugosc_fragmentu(osobnik *& os_partner);

/**	Funkcja wybieraj�ca dw�ch losowych osobnik�w z populacji podan� liczb� razy i wymieniaj�ca fragmenty chromosom�w ka�dej z par. Krok ten jest pomijany, je�eli liczba osobnik�w populacji jest mniejsza ni� 2.
@param k liczba par osobnik�w losowanych do krzy�owania
@param start wska�nik na g�ow� listy osobnik�w	
*/
void krzyzowanie(int k, osobnik *& start);

/** Funkcja interuj�ca po li�cie osobnik�w, usuwaj�c te, kt�rych warto�� funkcji dopasowania f jest poni�ej warto�ci wsp�czynnika wymierania w.
@param w warto�� wsp�czynnika wymierania
@param start wska�nik na g�ow� listy osobnik�w
*/
void wymieranie(float w, osobnik *&start);

/** Funkcja interuj�ca po li�cie osobnik�w, duplikuj�c elementy, kt�rych warto�� funkcji dopasowania f jest powy�ej warto�ci wsp�czynnika rozmna�ania r.
@param r warto�� wsp�czynnika rozmna�ania
@param start wska�nik na g�ow� listy osobnik�w
*/
void rozmnazanie(float r, osobnik *& start);

/** Funkcja wywo�uj�ca kolejno funkcj� krzy�owania, wymierania i rozmna�ania.
@param k liczba par osobnik�w losowanych do krzy�owania
@param w warto�� wsp�czynnika wymierania
@param r warto�� wsp�czynnika rozmna�ania
@param start wska�nik na g�ow� listy osobnik�w
*/
void wykonaj_pokolenie(unsigned int k, float w, float r, osobnik *& start);

/** Funkcja wypisuj�ca pokolenie do pliku wyj�ciowego metod� iteracyjn�.
@param start wska�nik na g�ow� listy osobnik�w
@param output nazwa pliku wyj�ciowego
*/
void wypisz_do_pliku(osobnik *& start, std::string output);

/** Funkcja usuwaj�ca chromosom metod� iteracyjn�.
@param do_usuniecia wska�nik na g�ow� listy tworz�cej chromosom
*/
void usun_lancuch(chromosom *& do_usuniecia);

/** Funkcja usuwaj�ca pojedynczego osobnika.
@param do_usuniecia wska�nik na wybranego osobnika
*/
void usun_osobnika(osobnik *& do_usuniecia);

/** Funkcja usuwaj�ca ca�e pokolenie.
@param start wska�nik na g�ow� listy osobnik�w
*/
void usun_wycieki(osobnik *& start);

#endif