#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "Header.h"

int main(int liczba_arg, char *argv[])
{
	parameters params;
	if (!sprawdz_przelaczniki(liczba_arg, argv, params)) {
		return 0; //Je�eli funkcja zwraca warto�� 0 (argumenty linii polece� s� nieprawid�owe), program zostaje przerwany.
	}
	osobnik *start = nullptr;
	if (!wczytaj_z_pliku(params.input, start))
		return 0; //Je�eli funkcja zwraca warto�� 0 (dane wej�ciowe s� nieprawid�owe), program zostaje przerwany.
	srand(std::random_device()()); //Korzystam z biblioteki <random> aby stworzy� seed dla generatora liczb losowych.
	for (unsigned int pokolenia = 0; pokolenia < params.p; pokolenia++) //Tyle razy, ile wynosi liczba pokole� p, wykonuj� kolejno funkcje krzy�owania, wymierania i rozmna�ania.
		wykonaj_pokolenie(params.k, params.w, params.r, start);
	wypisz_do_pliku(start, params.output); //Stan populacji po wykonaniu podanej liczby pokole� zostaje zapisany do pliku wyj�ciowego.
	usun_wycieki(start); //Po wypisaniu populacji do pliku, zostaje ona usuni�ta w celu pozbycia si� wyciek�w pami�ci.
}