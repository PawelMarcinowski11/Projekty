#include <fstream>
#include <sstream>
#include <string>
#include <random>
#include "Header.h"

int losuj_dlugosc_fragmentu(osobnik *& os_partner) {
	int	dlugosc_fragmentu_m = 0;
	for (chromosom *temp_c = os_partner->lancuch; temp_c; temp_c = temp_c->next)
		dlugosc_fragmentu_m += 1;
	if (dlugosc_fragmentu_m == 2)
		dlugosc_fragmentu_m = 1;
	else
		dlugosc_fragmentu_m = rand() % (dlugosc_fragmentu_m - 1) + 1; /*D�ugo�� fragmentu chromosomu, kt�rym wymieniaj� si� osobniki nie mo�e wynosi�
																	  zero, wi�c zamiast losowa� warto�� od 0 do n, losujemy warto�� od 0 do n-1,
																	  po czym dodajemy do niej jedynk� - uzyskuj�c w ten spos�b losowanie
																	  liczby w zakresie od 1 do n. */
	return dlugosc_fragmentu_m;
}

void krzyzowanie(int k, osobnik *& start) {

	int liczba_osobnikow = 0;
	for (osobnik *temp_o = start; temp_o; temp_o = temp_o->next)
		liczba_osobnikow += 1;

	if (liczba_osobnikow > 1) { /*Je�eli populacj� stanowi jeden osobnik, etap krzy�owania nie nast�pi. Nie nast�pi on te�, je�eli umrze ostatni osobnik z gatunku.*/

		for (int v = 0; v < k; v++) {
			int partner = rand() % (liczba_osobnikow);
			int partnerka = rand() % (liczba_osobnikow - 1);
			if (partner <= partnerka)
				partnerka += 1; /*Upewniam si�, �e �aden osobnik nie skrzy�uje si� sam ze sob�*/

			osobnik *os_partner = start; /*Iterowanie po li�cie w celu znalezienia wylosowanego osobnika*/
			for (int i = 0; i < partner; i++)
				os_partner = os_partner->next;
			osobnik *os_partnerka = start;
			for (int i = 0; i < partnerka; i++)
				os_partnerka = os_partnerka->next;

			chromosom *break_m = os_partner->lancuch; /*Iterowanie po li�cie w celu znalezienia wylosowanego punktu p�kni�cia chromosomu*/
			for (int i = 1; i < losuj_dlugosc_fragmentu(os_partner); i++)
				break_m = break_m->next;
			chromosom *break_f = os_partnerka->lancuch;
			for (int i = 1; i < losuj_dlugosc_fragmentu(os_partnerka); i++)
				break_f = break_f->next;

			chromosom temp_c = *break_m; /*Przepinanie fragment�w chromosom�w*/
			break_m->next = break_f->next;
			break_f->next = temp_c.next;
		}
	}
}

void usun_lancuch(chromosom *& do_usuniecia) {
	while (do_usuniecia) {
		chromosom *temp2 = do_usuniecia->next; /*Na pocz�tku p�tli zapami�tujemy wska�nik do nast�pnego elementu listy, gdy� po usuni�ciu obecnego elementu nie b�dzie on mo�liwy do odczytania*/
		delete do_usuniecia;
		do_usuniecia = temp2;
	}
}

void usun_osobnika(osobnik *& do_usuniecia) {
	osobnik *temp = do_usuniecia->next; /*Jak wy�ej*/

	usun_lancuch(do_usuniecia->lancuch);
	delete do_usuniecia;
	do_usuniecia = temp;
}

void usun_wycieki(osobnik *& start) {
	while (start) {
		usun_osobnika(start);
	}
}

bool sprawdz_przelaczniki(int liczba_arg, char *argv[], parameters & params) {
	std::string input = params.input;
	std::string output = params.output;
	unsigned int k = params.k;
	unsigned int p = params.p;
	float w = params.w;
	float r = params.r;
	if (liczba_arg != 13) /*Aby wprowadzi� wszystkie potrzebne zmiennie z linii polece�, u�ytkownik musi u�y� dok�adnie 13 argument�w -
						  - nazwy pliku, 6 przelacznik�w i 6 zmiennych. Z tego powodu je�eli zosta�a ich wprowadzona niewystarczaj�ca
						  liczba, wykonywanie dalszej cz�ci funkji staje si� bezcelowe.*/
		return 0;
	bool w_confirm = 0;
	bool k_confirm = 0;
	bool p_confirm = 0;
	bool r_confirm = 0;
	bool input_confirm = 0;
	bool output_confirm = 0; /*Zmienne te opisuj�, czy odpowiednie przelaczniki zosta�y poprawnie u�yte.*/
	std::string przelacznik;
	for (int i = 1; i < liczba_arg; i++)
	{
		przelacznik = argv[i];
		if (przelacznik == "-w") {
			if (w_confirm) /*Je�eli ka�dy przelacznik ma zosta� u�yty tylko jeden raz, potrzebny b�dzie warunek kt�ry sprawdza czy nie zosta�o to ju� wykonane*/
				return 0;
			i++;
			std::istringstream stream(argv[i]);
			stream >> w;
			if (stream.fail())
				return 0;
			if (w > 1 || w < 0)
				return 0;
			w_confirm = 1;
		}
		else if (przelacznik == "-r") {
			if (r_confirm)
				return 0;
			i++;
			std::istringstream stream(argv[i]);
			stream >> r;
			if (stream.fail())
				return 0;
			if (r > 1 || r < 0)
				return 0;
			r_confirm = 1;
		}
		else if (przelacznik == "-p") {
			if (p_confirm)
				return 0;
			i++;
			std::istringstream stream(argv[i]);
			stream >> p;
			if (stream.fail())
				return 0;
			p_confirm = 1;
		}
		else if (przelacznik == "-k") {
			if (k_confirm)
				return 0;
			i++;
			std::istringstream stream(argv[i]);
			stream >> k;
			if (stream.fail())
				return 0;
			k_confirm = 1;
		}
		else if (przelacznik == "-i") {
			if (input_confirm)
				return 0;
			i++;
			input = argv[i];
			input_confirm = 1;
		}
		else if (przelacznik == "-o") {
			if (output_confirm)
				return 0;
			i++;
			output = argv[i];
			output_confirm = 1;
		}
	}
	if (w_confirm && k_confirm && p_confirm && r_confirm && input_confirm && output_confirm){
		params.input = input;
		params.output = output;
		params.k = k;
		params.p = p;
		params.w = w;
		params.r = r;
		return 1; /*Je�eli wszystkie przelaczniki zosta�y poprawnie u�yte, zwr�� wartosc "true".*/
}
	else
		return 0;
};

void dodaj_osobnik(osobnik *& start, osobnik *& end) {
	if (start == nullptr) { /*Je�eli lista jest pusta, tworzymy jej pierwszy element*/
		start = new osobnik;
		start->next = nullptr;
		end = start;
		end->lancuch = nullptr;
	}
	else { /*Je�eli lista nie jest pusta, dok�adamy nowy element na jej koniec*/
		osobnik *temp = start;
		temp = new osobnik;
		temp->next = nullptr;
		end->next = temp;
		end = temp;
		end->lancuch = nullptr;
	}
}

void dodaj_chromosom(chromosom *& last, osobnik *& end, int liczba) {

	chromosom *temp = last;
	if (last == nullptr) { /*Je�eli lista jest pusta, tworzymy jej pierwszy element*/
		temp = new chromosom;
		temp->next = nullptr;
		temp->wartosc = liczba;
		last = temp;
		end->lancuch = temp;
	}
	else { /*Je�eli lista nie jest pusta, dok�adamy nowy element na jej koniec*/
		temp = new chromosom;
		temp->next = nullptr;
		temp->wartosc = liczba;
		last->next = temp;
		last = temp;
	}
}

bool wczytaj_z_pliku(std::string input, osobnik *&start) {
	std::ifstream plik(input);
	if (plik.eof())
		return 0;
	osobnik *end = nullptr;
	while (plik.is_open())
	{
		std::string line;
		getline(plik, line);
		unsigned short int liczba;
		std::istringstream strumien(line);


		dodaj_osobnik(start, end);

		chromosom *first = end->lancuch;
		chromosom *last = first;
		int licznik = 0;
		while (!strumien.eof())
		{
			strumien >> liczba;
			if (strumien.fail()) { //Plik wej�ciowy zawiera blad, wi�c pami�� zostanie zwolniona a program zostanie zamkni�ty
				usun_wycieki(start);
				return 0;
			}
			dodaj_chromosom(last, end, liczba);
			licznik++;
		}
		if (licznik < 2)
			return 0;
		if (plik.eof()) {
			plik.seekg(0);
			break;
		}

	}
	plik.close();
	return 1;
};

void wymieranie(float w, osobnik *&start) {
	for (osobnik *temp_o = start; temp_o;) {
		if (temp_o == start) {
			temp_o->f = rand() % 1000; /*Wsp�czynnik przystosowania uzyskuj� losuj�c liczb� ca�kowit� z zakresu od 0 do 1000,
									   dziel�c j� nast�pnie przez 1000.*/
			temp_o->f /= 1000;
			if (temp_o->f < w) {				/*W przypadku, gdy wska�nik *temp_o wskazuje na pierwszy element funkcji,
												rozpatrujemy go i jego nast�pnik, gdy� w przypadku usuni�cia pierwszego elementu listy,
												mo�emy przepi�� g�ow� listy *start. W ka�dym innym wypadku rozpatrujemy
												wy��cznie nast�pnik elementu, gdy� w li�cie jednostronnej nie mamy bezpo�redniego dost�pu
												do poprzedniego elementu, wi�c po usuni�ciu elementu "n", nie mogliby�my przepi�� elementu "n-1"
												do elementu "n+1".*/
				osobnik *temp_w = start->next;
				usun_lancuch(temp_o->lancuch);

				start = temp_w;
				delete temp_o;
				temp_o = start;
			}
			else {
				if (temp_o->next != nullptr) {
					temp_o->next->f = rand() % 1000;
					temp_o->next->f /= 1000;
					if (temp_o->next->f < w)
						usun_osobnika(temp_o->next);
					else
						temp_o = temp_o->next;
				}
				else
					temp_o = nullptr;
			}
		}
		else if (temp_o->next != nullptr) {
			temp_o->next->f = rand() % 1000;
			temp_o->next->f /= 1000;
			if (temp_o->next->f < w) {
				usun_osobnika(temp_o->next);
			}
			else
				temp_o = temp_o->next;
		}
		else
			temp_o = nullptr;
	}
}

void rozmnazanie(float r, osobnik *& start) {
	for (osobnik *temp_o = start; temp_o;) {
		if (temp_o->f > r) {
			osobnik *temp_r = new osobnik; //Tworzymy nowy osobnik
			chromosom *temp_ch;
			chromosom *koniec;
			chromosom *start = nullptr;
			temp_ch = new chromosom;
			temp_ch->next = start;
			temp_ch->wartosc = temp_o->lancuch->wartosc;
			start = temp_ch;
			for (chromosom *temp_z = temp_o->lancuch; temp_z->next; temp_z = temp_z->next) { /*Przepisujemy chromosom do nowego osobnika.
																							 (Nie wystarczy ich przepi�� - w�wczas przy
																							 modyfikowaniu jednego z nich w etapie krzy�owania,
																							 zmiany mia�yby efekt na obu.)*/

				chromosom *temp = start;
				while (temp->next) {
					temp = temp->next;
				}
				koniec = new chromosom;
				koniec->wartosc = temp_z->next->wartosc; 
				koniec->next = nullptr;
				temp->next = koniec;

			}

			temp_r->f = temp_o->f;
			temp_r->lancuch = temp_ch;
			temp_r->next = temp_o->next;
			temp_o->next = temp_r;
			temp_o = temp_r->next;
		}
		else
			temp_o = temp_o->next;
	}
}

void wykonaj_pokolenie(unsigned int k, float w, float r, osobnik *& start) {
	krzyzowanie(k, start);
	wymieranie(w, start);
	rozmnazanie(r, start);
}

void wypisz_do_pliku(osobnik *& start, std::string output) {
	std::ofstream plik_2(output);
	for (osobnik *temp_o = start; temp_o; temp_o = temp_o->next) {
		for (chromosom *temp_c = temp_o->lancuch; temp_c; temp_c = temp_c->next) {
			plik_2 << temp_c->wartosc;
			if (temp_c->next != nullptr) //Nie dajemy spacji na ko�cu chromosomu.
				plik_2 << " ";
		}
		if (temp_o->next != nullptr)
			plik_2 << "\n"; //Nie dajemy nowej linii na ko�cu pliku!
	}
	plik_2.close();
}