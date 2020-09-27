#include "Header.h"

//Metoda iteruje cyklicznie po graczach na liœcie, wyznaczaj¹c na bie¿¹co kierunek dla graczy sterowanych przez AI
int gra::obsluzAI(baza_obiektow &obiekty, ai_waz & sztuczna_inteligencja)
{
	int tab[X + 1][Y + 1] = { brak };
	int poprzedni_czas = 100000;
	int obecny_czas = 0;
	while (stan_gry != wylaczanie) {
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		
		//Aby uzyskaæ lepsz¹ wydajnoœæ, obliczam trasê tylko raz na ka¿dy "tick" logiki gry

		obecny_czas = clk.getElapsedTime().asMilliseconds();
		if (obecny_czas < poprzedni_czas) {

			//Sprawdzam czas dzia³ania jednego cyklu pêtli na potrzeby debugowania

			long long czas_dzialania = std::chrono::high_resolution_clock::now().time_since_epoch().count();
			element_listy_graczy * ruszajacy = gracze.getHead();
			obiekt_w_bazie * wyliczanie;

			dostep_do_planszy.lock();

			//Iterujê po wê¿ach poszczególnych graczy, zaznaczaj¹c ich po³o¿enie na mapie kolizji

			wyliczanie = obiekty.getHead();
			while (wyliczanie) {
				wyliczanie->getO()->mapujKolizje(tab);
				wyliczanie = wyliczanie->getNext();
			}

			//Mapa zawiera ju¿ informacje o kolizji z innymi wê¿ami na mapie,
			//jednak trzeba jeszcze zawrzeæ informacjê o kolizji z krawêdziami mapy

			for (int i = 0; i < X + 1; i++) {
				tab[i][0] = zderzenie;
				tab[i][Y] = zderzenie;
			}
			for (int i = 0; i < Y + 1; i++) {
				tab[0][i] = zderzenie;
				tab[X][i] = zderzenie;
			}

			dostep_do_planszy.unlock();

			while (ruszajacy) {
				gracz * gracz_rusz = ruszajacy->getPlayer();
				if (ruszajacy->getPlayer()->getHead() && ruszajacy->getPlayer()->getKontroler() == ai) {

					//Szukam trasy do najbli¿szego jab³ka korzystaj¹c z metody obiektu, przekazanego jako parametr "sztuczna_inteligencja"

					int kier = sztuczna_inteligencja.wybierzKierunek(tab, gracz_rusz->getHead()->getX(), gracz_rusz->getHead()->getY(), gracz_rusz->getHead()->getDirection());
					dostep_do_planszy.lock();
					if (ruszajacy->getPlayer()->getHead()) {
						int poprz_kier = gracz_rusz->getHead()->getDirection();
						gracz_rusz->setDirection(kier);
						try {
							gracz_rusz->updateDirection();

							//Wywo³ujê metodê fakeMove(), aby sprawdziæ gdzie poruszy siê dany w¹¿ - i daæ pozosta³ym graczom sterowanym przez AI informacjê, aby uniknêli kolizji z nim

							coord temp_kor = gracz_rusz->getHead()->fakeMove();
							tab[temp_kor.x][temp_kor.y] = zderzenie;
							gracz_rusz->setDirection(poprz_kier);
							gracz_rusz->updateDirection();
						}
						catch (exception_out_of_bound) {

						}
						gracz_rusz->setDirection(kier);
					}
					dostep_do_planszy.unlock();
				}

				ruszajacy = ruszajacy->getNext();
			}

			//Po odnalezieniu tras dla wszystkich graczy AI, czyszczê tablicê kolizji, aby przygotowaæ j¹ na nastêpny cykl pêtli

			for (int i = 0; i < X + 1; i++) {
				for (int j = 0; j < Y + 1; j++) {
					tab[i][j] = 0;
				}
			}

			//Liczê i wypisujê czas, który zajê³o wykonanie jednego cyklu pêtli

			double czas_obliczenia = (std::chrono::high_resolution_clock::now().time_since_epoch().count() - czas_dzialania);
			czas_obliczenia /= 1000000;
			std::cerr << "Obliczanie ruchow AI: " << czas_obliczenia << "ms\n"; //Czas wykonania obliczeñ dla ai
		}
		poprzedni_czas = obecny_czas;
	}
	return 0;
}


int ai_dijkstra::wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru) {

	//Inicjalizujê niezbêdne tablice i zmienne pomocnicze

	int dijkstra_kier[X + 1][Y + 1] = {};
	int dijkstra[X + 1][Y + 1] = {};
	dijkstra[x][y] = -100000;
	dijkstra_kier[x][y] = kieru;
	int cofanie_x = 0;
	int cofanie_y = 0;
	int najmniejszy_x = 0;
	int najmniejszy_y = 0;
	int najmniejszy_val = 10000000;
	int dijkstra_kier_temp[X + 1][Y + 1] = {};
	int dijkstra_zuzycie[X + 1][Y + 1] = {};
	bool znaleziono = false;

	//Czyszczê informacjê o kolizji w obecnych koordynatach gracza, gdy¿ w¹¿ nie mo¿e zderzyæ siê ze swoj¹ w³asn¹ g³ow¹

	map[x][y] = brak;


	//Rozpoczynaj¹c od pozycji g³owy wê¿a, sprawdzam najbli¿sze pola w poszukiwaniu jab³ka. 

	while (znaleziono == false) {
		najmniejszy_val = 10000000;
		for (int i = 0; i < X + 1; i++) {
			for (int j = 0; j < Y + 1; j++) {
				if (najmniejszy_val > dijkstra[i][j] && dijkstra_zuzycie[i][j] == 0) {
					najmniejszy_x = i;
					najmniejszy_y = j;
					najmniejszy_val = dijkstra[najmniejszy_x][najmniejszy_y];
				}
			}
		}
		if (najmniejszy_val == 10000000) //Je¿eli algorytm Dijkstry przerobi³ wszystkie dostêpne pola na mapie, pêtla zostaje przerwana
			znaleziono = true;
		if (dijkstra_kier_temp[najmniejszy_x][najmniejszy_y] >= 0 && dijkstra_kier_temp[najmniejszy_x][najmniejszy_y] < 4 && (najmniejszy_x != x || najmniejszy_y != y))
			dijkstra_kier[najmniejszy_x][najmniejszy_y] = dijkstra_kier_temp[najmniejszy_x][najmniejszy_y];
		if (map[najmniejszy_x][najmniejszy_y] == posilek) { //Je¿eli algorytm Dijkstry znalaz³ najbli¿sze pole z jab³kiem, pêtla zostaje przerwana
			znaleziono = true;
			cofanie_x = najmniejszy_x;
			cofanie_y = najmniejszy_y;
			dijkstra_zuzycie[najmniejszy_x][najmniejszy_y] = 1;
		}
		else if (map[najmniejszy_x][najmniejszy_y] == zderzenie && (najmniejszy_x != x || najmniejszy_y != y)) { //Je¿eli rozpatrywane pole jest zajête przez innego wê¿a, algorytm zaznaczy je jako zablokowane
			dijkstra[najmniejszy_x][najmniejszy_y] = 100000;
			dijkstra_zuzycie[najmniejszy_x][najmniejszy_y] = 1;
		}
		else {

			//Je¿eli pole jest puste, algorytm przypisze wagi trzem kolejnym polom, na które w¹¿ mo¿e przenieœæ siê z rozpatrywanego punktu
			//Zapamiêtane zostan¹ tak¿e kierunki, z których w¹¿ wszed³ na dane pole

			switch (dijkstra_kier[najmniejszy_x][najmniejszy_y]) {
			case gora:
				if (najmniejszy_x != X && dijkstra_zuzycie[najmniejszy_x + 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x + 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x + 1][najmniejszy_y] = prawo;
				}
				if (najmniejszy_x != 0 && dijkstra_zuzycie[najmniejszy_x - 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x - 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x - 1][najmniejszy_y] = lewo;
				}
				if (najmniejszy_y != 0 && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y - 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y - 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y - 1] = gora;
				}
				break;
			case dol:
				if (najmniejszy_x != X && dijkstra_zuzycie[najmniejszy_x + 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x + 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x + 1][najmniejszy_y] = prawo;
				}
				if (najmniejszy_x != 0 && dijkstra_zuzycie[najmniejszy_x - 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x - 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x - 1][najmniejszy_y] = lewo;
				}
				if (najmniejszy_y != Y && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y + 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y + 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y + 1] = dol;
				}
				break;
			case lewo:
				if (najmniejszy_x != 0 && dijkstra_zuzycie[najmniejszy_x - 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x - 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x - 1][najmniejszy_y] = lewo;
				}
				if (najmniejszy_y != Y && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y + 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y + 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y + 1] = dol;
				}
				if (najmniejszy_y != 0 && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y - 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y - 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y - 1] = gora;
				}
				break;
			case prawo:
				if (najmniejszy_x != X && dijkstra_zuzycie[najmniejszy_x + 1][najmniejszy_y] == 0) {
					dijkstra[najmniejszy_x + 1][najmniejszy_y] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x + 1][najmniejszy_y] = prawo;
				}
				if (najmniejszy_y != Y && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y + 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y + 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y + 1] = dol;
				}
				if (najmniejszy_y != 0 && dijkstra_zuzycie[najmniejszy_x][najmniejszy_y - 1] == 0) {
					dijkstra[najmniejszy_x][najmniejszy_y - 1] = dijkstra[najmniejszy_x][najmniejszy_y] + 1;
					dijkstra_kier_temp[najmniejszy_x][najmniejszy_y - 1] = gora;
				}
				break;
			}
			dijkstra_zuzycie[najmniejszy_x][najmniejszy_y] = 1;
		}
	}


	//Przywracam informacjê o kolizji w obecnych koordynatach gracza, gdy¿ pozostali gracze dalej mog¹ siê z nim w owym punkcie zderzyæ

	map[x][y] = zderzenie;


	int kierunek[4];
	int wyliczanie = 0;
	int kier = 0;
	if (dijkstra[cofanie_x][cofanie_y] > -90000) { //Je¿eli dotarcie do celu wymaga³oby ponad 10000 ruchów, b¹dŸ by³oby ca³kowicie nieosi¹galne, w¹¿ bêdzie porusza³ siê w prymitywny sposób, unikaj¹c kolizji dopóki trasa do jab³ka znów nie bêdzie osi¹galna 
		if (map[x + 1][y] != zderzenie && kieru != lewo && x != X - 1 && map[x + 2][y] != zderzenie)
			return prawo;
		else if (map[x - 1][y] != zderzenie && kieru != prawo && x != 1 && map[x - 2][y] != zderzenie)
			return lewo;
		else if (map[x][y - 1] != zderzenie && kieru != dol && y != Y - 1 && map[x][y - 2] != zderzenie)
			return gora;
		else if (map[x][y + 1] != zderzenie && kieru != gora && y != 1 && map[x][y + 2] != zderzenie)
			return dol;
		else if (map[x + 1][y] != zderzenie && kieru != lewo)
			return prawo;
		else if (map[x - 1][y] != zderzenie && kieru != prawo)
			return lewo;
		else if (map[x][y - 1] != zderzenie && kieru != dol)
			return gora;
		else
			return dol;
	}

	//Je¿eli uda³o siê pomyœlnie ustaliæ trasê, w¹¿ wraca po swoich œladach, a¿ znajdzie pierwszy krok który musi wykonaæ

	while (cofanie_x != x || cofanie_y != y) {
		kier = dijkstra_kier[cofanie_x][cofanie_y];
		if (kier == lewo)
			cofanie_x += 1;
		else if (kier == prawo)
			cofanie_x -= 1;
		else if (kier == gora)
			cofanie_y += 1;
		else if (kier == dol)
			cofanie_y -= 1;
	}

	//Kierunek, w którym musi pod¹¿aæ w¹¿, zostaje zwrócony przez funkcjê - i obrany przez gracza przy najbli¿szym odœwie¿eniu logiki gry

	return kier;
}

int ai_primitive::wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru)
{

	//Inicjalizujê niezbêdne zmienne pomocnicze

	int odleglosc_w_poziomie = X + 1;
	int odleglosc_w_pionie = Y + 1;
	int jedzenie_x = X / 2;
	int jedzenie_y = Y / 2;
	int nowy_kierunek;

	//Szukam jab³ka, którego koordynaty s¹ najbli¿ej gracza - bez uzwglêdniania przeszkód na trasie

	for (int i = 0; i < X + 1; i++) {
		for (int j = 0; j < Y + 1; j++) {
			if (map[i][j] == posilek && (abs(i - x) + abs(j - y)) < (odleglosc_w_poziomie + odleglosc_w_pionie)) {
				jedzenie_x = i;
				jedzenie_y = j;
				odleglosc_w_poziomie = abs(i - x);
				odleglosc_w_pionie = abs(j - y);
			}
		}
	}

	//W¹¿ najpierw stara siê dotrzeæ do celu w osi X, a nastêpnie w osi Y

	if (odleglosc_w_poziomie > 0) {
		if (jedzenie_x > x)
			nowy_kierunek = prawo;
		else
			nowy_kierunek = lewo;
	}

	else {
		if (jedzenie_y > y)
			nowy_kierunek = dol;
		else
			nowy_kierunek = gora;
	}
	if (abs(nowy_kierunek - kieru) == 2)
		nowy_kierunek = (nowy_kierunek + 1) % 4;

	// Funkcja matematyczna podaje pozycjê gracza po przemieszczeniu siê
	// x = x + (nowy_kierunek % 2) * (nowy_kierunek - 2) * -1;
	// y = y + ((nowy_kierunek + 1) % 2) * (nowy_kierunek - 1);
	//    0              [x][y-1]
	//  3   1       [x-1][y]  [x+1][y]
	//    2              [x][y+1]

	//Je¿eli w¹¿ zbli¿y siê do przeszkody, bêdzie stara³ siê omin¹æ j¹ w prymitywny sposób

	if (map[x + (nowy_kierunek % 2) * (nowy_kierunek - 2) * -1][y + ((nowy_kierunek + 1) % 2) * (nowy_kierunek - 1)] == zderzenie) {
		if (map[x + 1][y] != zderzenie && kieru != lewo && x != X - 1 && map[x + 2][y] != zderzenie)
			return prawo;
		else if (map[x - 1][y] != zderzenie && kieru != prawo && x != 1 && map[x - 2][y] != zderzenie)
			return lewo;
		else if (map[x][y - 1] != zderzenie && kieru != dol && y != Y - 1 && map[x][y - 2] != zderzenie)
			return gora;
		else if (map[x][y + 1] != zderzenie && kieru != gora && y != 1 && map[x][y + 2] != zderzenie)
			return dol;
		else if (map[x + 1][y] != zderzenie && kieru != lewo)
			return prawo;
		else if (map[x - 1][y] != zderzenie && kieru != prawo)
			return lewo;
		else if (map[x][y - 1] != zderzenie && kieru != dol)
			return gora;
		else
			return dol;
	}
	return nowy_kierunek;
}

int ai_random::wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru)
{
	//Funkcja wysy³a do wê¿a sygna³y, aby porusza³ siê w losowym kierunku
	//Symuluje to klikanie w klawisze klawiatury w losowej kolejnoœci

	return rand_engine() % 4;
}