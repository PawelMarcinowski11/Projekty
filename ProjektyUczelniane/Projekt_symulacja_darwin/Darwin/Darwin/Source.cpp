#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "Header.h"

int main(int liczba_arg, char *argv[])
{
	parameters params;
	if (!sprawdz_przelaczniki(liczba_arg, argv, params)) {
		return 0; //Je¿eli funkcja zwraca wartoœæ 0 (argumenty linii poleceñ s¹ nieprawid³owe), program zostaje przerwany.
	}
	osobnik *start = nullptr;
	if (!wczytaj_z_pliku(params.input, start))
		return 0; //Je¿eli funkcja zwraca wartoœæ 0 (dane wejœciowe s¹ nieprawid³owe), program zostaje przerwany.
	srand(std::random_device()()); //Korzystam z biblioteki <random> aby stworzyæ seed dla generatora liczb losowych.
	for (unsigned int pokolenia = 0; pokolenia < params.p; pokolenia++) //Tyle razy, ile wynosi liczba pokoleñ p, wykonujê kolejno funkcje krzy¿owania, wymierania i rozmna¿ania.
		wykonaj_pokolenie(params.k, params.w, params.r, start);
	wypisz_do_pliku(start, params.output); //Stan populacji po wykonaniu podanej liczby pokoleñ zostaje zapisany do pliku wyjœciowego.
	usun_wycieki(start); //Po wypisaniu populacji do pliku, zostaje ona usuniêta w celu pozbycia siê wycieków pamiêci.
}