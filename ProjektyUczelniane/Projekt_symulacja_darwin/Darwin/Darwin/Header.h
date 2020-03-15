/** @file */

#ifndef NAG£ÓWEK_H
#define NAG£ÓWEK_H

/** Struktura parameters zawiera dane kluczowe do dzia³ania kodu, przekazywane za pomoc¹ prze³¹czników. */
struct parameters {
	std::string input;  ///< plik wejœciowy z populacj¹
	std::string output; ///< plik wyjœciowy z populacj¹
	unsigned int k; ///< liczba par osobników losowanych do krzy¿owania
	unsigned int p; ///< liczba pokoleñ
	float w; ///< wspó³czynnik wymierania
	float r; ///< wspó³czynnik rozmna¿ania
};

/** Element listy tworz¹cej chromosom, zawartej w ka¿dym elemencie listy osobników. */
struct chromosom {
	unsigned short int wartosc; ///< liczba naturalna bêd¹ca pojedynczym fragmentem chromosomu
	chromosom *next; ///< wskaŸnik na nastêpny element listy tworz¹cej chromosom
};

/** Element listy osobników, tworz¹cej populacjê. */
struct osobnik {
	float f; ///< wartoœæ funkcji dopasowania, porównywana z wspó³czynnikiem wymierania i rozmna¿ania
	osobnik *next; ///< wskaŸnik na nastêpny element listy osobników
	chromosom *lancuch; ///< wskaŸnik na g³owê listy tworz¹cej chromosom
};


/** Funkcja sprawdzaj¹ca prawid³owoœæ argumentów linii poleceñ i wprowadzaj¹ca parametry do zmiennych zale¿nie od podanych prze³¹czników.
@param liczba_arg liczba argumentów wprowadzonych w linii poleceñ
@param argv[] ci¹g znaków wprowadzony w linii poleceñ
@param params struktura, do której zostan¹ wypisane zmienne kluczowe do prawid³owej pracy programu
@return stan funkcji: 1 - wszystkie parametry zosta³y prawid³owo wprowadzone do odpowiednich zmiennych, 0 - program napotka³ na b³êdne argumenty i zostanie zatrzymany 
*/
bool sprawdz_przelaczniki(int liczba_arg, char *argv[], parameters & params);

/** Funkcja dodaj¹ca kolejny element na koniec listy tworz¹cej chromosom.
@param last wskaŸnik na ostatni element listy fragmentów chromosomu
@param end wskaŸnik na ogon listy osobników
@param liczba liczba naturalna bêd¹ca fragmentem chromosomu
*/
void dodaj_chromosom(chromosom *& last, osobnik *& end, int liczba);

/** Funkcja dodaj¹ca kolejny element na koniec listy osobników.
@param start wskaŸnik na g³owê listy osobników
@param end wskaŸnik na ogon listy osobników
*/
void dodaj_osobnik(osobnik *& start, osobnik *& end);

/** Funkcja wczytuj¹ca z pliku wejœciowego dane o populacji.
@param input nazwa pliku wejœciowego
@param start wskaŸnik na g³owê listy osobników
@return stan funkcji : 1 - populacja zosta³a prawid³owo za³adowana z pliku wejœciowego, 0 - plik wejœciowy zawiera³ b³êdy, wiêc program zwolni swoj¹ pamiêæ, a nastêpnie zostanie zatrzymany
*/
bool wczytaj_z_pliku(std::string input, osobnik *&start);

/** Funkcja losuj¹ca miejsce, w którym chromosom wybranego osobnika zostanie przerwany i po³¹czony z innym chromosomem podczas krzy¿owania.
@param os_partner element listy bior¹cy udzia³ w krzy¿owaniu
@return numer elementu listy chromosomów, w którym nast¹pi przepiêcie do fragmentu listy chromosomów nale¿¹cej do innego osobnika
*/
int losuj_dlugosc_fragmentu(osobnik *& os_partner);

/**	Funkcja wybieraj¹ca dwóch losowych osobników z populacji podan¹ liczbê razy i wymieniaj¹ca fragmenty chromosomów ka¿dej z par. Krok ten jest pomijany, je¿eli liczba osobników populacji jest mniejsza ni¿ 2.
@param k liczba par osobników losowanych do krzy¿owania
@param start wskaŸnik na g³owê listy osobników	
*/
void krzyzowanie(int k, osobnik *& start);

/** Funkcja interuj¹ca po liœcie osobników, usuwaj¹c te, których wartoœæ funkcji dopasowania f jest poni¿ej wartoœci wspó³czynnika wymierania w.
@param w wartoœæ wspó³czynnika wymierania
@param start wskaŸnik na g³owê listy osobników
*/
void wymieranie(float w, osobnik *&start);

/** Funkcja interuj¹ca po liœcie osobników, duplikuj¹c elementy, których wartoœæ funkcji dopasowania f jest powy¿ej wartoœci wspó³czynnika rozmna¿ania r.
@param r wartoœæ wspó³czynnika rozmna¿ania
@param start wskaŸnik na g³owê listy osobników
*/
void rozmnazanie(float r, osobnik *& start);

/** Funkcja wywo³uj¹ca kolejno funkcjê krzy¿owania, wymierania i rozmna¿ania.
@param k liczba par osobników losowanych do krzy¿owania
@param w wartoœæ wspó³czynnika wymierania
@param r wartoœæ wspó³czynnika rozmna¿ania
@param start wskaŸnik na g³owê listy osobników
*/
void wykonaj_pokolenie(unsigned int k, float w, float r, osobnik *& start);

/** Funkcja wypisuj¹ca pokolenie do pliku wyjœciowego metod¹ iteracyjn¹.
@param start wskaŸnik na g³owê listy osobników
@param output nazwa pliku wyjœciowego
*/
void wypisz_do_pliku(osobnik *& start, std::string output);

/** Funkcja usuwaj¹ca chromosom metod¹ iteracyjn¹.
@param do_usuniecia wskaŸnik na g³owê listy tworz¹cej chromosom
*/
void usun_lancuch(chromosom *& do_usuniecia);

/** Funkcja usuwaj¹ca pojedynczego osobnika.
@param do_usuniecia wskaŸnik na wybranego osobnika
*/
void usun_osobnika(osobnik *& do_usuniecia);

/** Funkcja usuwaj¹ca ca³e pokolenie.
@param start wskaŸnik na g³owê listy osobników
*/
void usun_wycieki(osobnik *& start);

#endif