#include "Header.h"

//Metoda odpowiada za tworzenie w�y graczy, przemieszczanie ich oraz obs�ugiwanie kolizji pomi�dzy r�nymi obiektami
int gra::logika(baza_obiektow &obiekty)
{
	element_listy_graczy * lis = gracze.getHead();

	//Przy rozpocz�ciu gry, ka�demu z graczy zostaje przyznana nazwa

	for (int i = 0; lis; i++) {
		if (lis->getPlayer()->getKontroler() == ai)
			lis->getPlayer()->setNazwa(L"AI " + std::to_wstring(i + 1));
		else
			lis->getPlayer()->setNazwa(L"Gracz " + std::to_wstring(i + 1));
		
		//Numer gracza determinuje jego pozycj� na planszy za pomoc� wzoru matematycznego

		gracze.dodajWeza(lis->getPlayer(), new waz(((i / 2) % 2)*(X - 2 - (10 * (i / 4))) + (i / 4) * 5 + 1, i % 2 * (Y - 2) + 1, ((i % 4) / 2) * 2 + 1, nullptr), obiekty);
		
		//W�e zostaj� wyd�u�ane do momentu, w kt�rym osi�gn� wymagany rozmiar
		
		for (int j = 1; j < ROZMIAR_WEZA; j++) {
			lis->getPlayer()->getHead()->elongate();
		}
		lis = lis->getNext();
	}

	//W losowym miejscu na mapie ustawione zostaje jab�ko

	jedzenie * j = new jedzenie(obiekty.getHead());
	obiekty += j;

	//Po zako�czeniu przygotowa�, gra rozpoczyna si�

	stan_gry = trwa;

	//P�ki gra nie dostanie sygna�u do zako�czenia dzia�ania, logika gry b�dzie od�wie�a� si� w r�wnych interwa�ach (domy�lnie: co 66ms)

	while (stan_gry != wylaczanie)
	{
		std::this_thread::sleep_for(std::chrono::microseconds(10));
		while (stan_gry == przerwana) {
			std::this_thread::sleep_for(std::chrono::microseconds(100));

			//Je�eli gra zosta�a zako�czona, wci�ni�cie klawisza spacji b�d� "R" zrestartuje j�

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

				//Restartuj�c gr�, czy�cimy wszystkie obiekty kt�re pozosta�y na planszy

				dostep_do_planszy.lock();

				obiekt_w_bazie * tmp = obiekty.getHead();
				dostep_do_bazy.lock();
				while (tmp) {
					obiekty -= tmp->getO();
					tmp = obiekty.getHead();
				}
				dostep_do_bazy.unlock();

				//Zerujemy punkty graczy

				element_listy_graczy * zerowanie_punktow = gracze.getHead();

				while (zerowanie_punktow) {
					zerowanie_punktow->getPlayer()->setPunkty(0);
					zerowanie_punktow = zerowanie_punktow->getNext();
				}

				//Przydzielamy ka�demu z nich nowego w�a

				element_listy_graczy * iterator = gracze.getHead();

				for (int i = 0; iterator; i++) {
					gracze.dodajWeza(iterator->getPlayer(), new waz(((i / 2) % 2)*(X - 2 - (10 * (i / 4))) + (i / 4) * 5 + 1, i % 2 * (Y - 2) + 1, ((i % 4) / 2) * 2 + 1, nullptr), obiekty);
					for (int j = 1; j < ROZMIAR_WEZA; j++) {
						iterator->getPlayer()->getHead()->elongate();
					}
					iterator = iterator->getNext();
				}

				//Wstawiamy jedno jab�ko w losowe pole na mapie

				j = new jedzenie(obiekty.getHead());

				obiekty += j;

				dostep_do_planszy.unlock();

				//Zmieniamy stan gry

				stan_gry = trwa;
			}
		}

		//Je�eli dostali�my sygna� do wy��czenia gry, metoda ko�czy dzia�anie

		if (stan_gry == wylaczanie) {
			return 0;
		}

		sf::Time t = clk.getElapsedTime();

		//Stan gry od�wie�a si� wy��cznie po up�ywie wymaganego czasu

		if (t.asMilliseconds() > FRAMETIME) {
			dostep_do_planszy.lock();
			clk.restart();
			element_listy_graczy * ruszajacy = gracze.getHead();
			while (ruszajacy) {
				gracz * gracz_rusz = ruszajacy->getPlayer();

				if (ruszajacy->getPlayer()->getHead()) {

					gracz_rusz->updateDirection();
					try {
						coord sprawdz = gracz_rusz->getHead()->fakeMove();

						int test = 0;

						//Sprawdzamy, czy w�� po wykonaniu ruchu b�dzie kolidowa� z kt�rym� z obiekt�w

						obiekt_w_bazie * wyliczanie = obiekty.getHead();
						while (wyliczanie) {
							test = wyliczanie->getO()->sprawdzKolizje(sprawdz.x, sprawdz.y);
							if (test != brak) {
								int liczba_wystapien = 0;
								element_listy_graczy * gracz_temp = gracze.getHead();
								switch (test) {
								case zderzenie:

									//Je�eli w�� zderzy si� z innym w�em, zostaje zmieniony w jedzenie, a gracz odpada z gry

									gracz_rusz->getHead()->zmienWJedzenie(obiekty);
									dostep_do_bazy.lock();
									gracze.usunWeza(gracz_rusz, obiekty);
									dostep_do_bazy.unlock();
									while (gracz_temp) {
										if (gracz_temp->getPlayer()->getHead()) {
											if (gracz_temp->getPlayer()->getHead()->getX() == sprawdz.x && gracz_temp->getPlayer()->getHead()->getY() == sprawdz.y) {

												//Je�eli w�e zderzy�y si� swoimi g�owami - to oba zostaj� zmienione w jedzenie i obaj gracze odpadaj� z gry

												gracz_temp->getPlayer()->getHead()->zmienWJedzenie(obiekty);
												dostep_do_bazy.lock();
												gracze.usunWeza(gracz_temp->getPlayer(), obiekty);
												dostep_do_bazy.unlock();
											}
											else
												liczba_wystapien++;
										}
										gracz_temp = gracz_temp->getNext();
									}

									//Je�eli po zderzeniu okazuje si�, �e wszyscy gracze odpadli z gry, gra zostaje wstrzymana

									if (liczba_wystapien == 0)
										stan_gry = przerwana;
									break;
								case posilek:

									//Je�eli w�� zetknie si� z jab�kiem, wyd�u�a si� o jeden segment, a gracz zyskuje 10 punkt�w

									gracz_rusz->getHead()->elongate();
									gracz_rusz->dodajPunkty(10);
									dostep_do_bazy.lock();

									//Je�eli by�o to ostatnie jab�ko na mapie, tworzymy nowe w losowym, wolnym miejscu

									liczba_wystapien = 0;
									obiekt_w_bazie * tmp = obiekty.getHead();
									while (tmp && tmp->getO() && liczba_wystapien < 2) {
										if (jedzenie * j = dynamic_cast<jedzenie*>(tmp->getO())) {
											liczba_wystapien++;
										}
										tmp = tmp->getNext();
									}
									obiekty -= wyliczanie->getO();
									if (liczba_wystapien == 1) {
										j = new jedzenie(obiekty.getHead());
										obiekty += j;
									}
									dostep_do_bazy.unlock();
									break;
								}
								wyliczanie = nullptr;
							}
							else
								wyliczanie = wyliczanie->getNext();
						}

						if (test == brak) {
							dostep_do_bazy.lock();
							gracz_rusz->getHead()->move();
							dostep_do_bazy.unlock();
						}
					}
					catch (exception_out_of_bound) {
						
						//Je�eli w�� zderzy si� z kraw�dzi� mapy, zostaje zmieniony w jedzenie, a gracz odpada z gry

						element_listy_graczy * gracz_temp = gracze.getHead();
						gracz_rusz->getHead()->zmienWJedzenie(obiekty);
						dostep_do_bazy.lock();
						gracze.usunWeza(gracz_rusz, obiekty);
						dostep_do_bazy.unlock();
						int liczba_wystapien = 0;
						while (gracz_temp) {
							if (gracz_temp->getPlayer()->getHead())
								liczba_wystapien++;
							gracz_temp = gracz_temp->getNext();
						}
						if (liczba_wystapien == 0)

							//Je�eli po zderzeniu okazuje si�, �e wszyscy gracze odpadli z gry, gra zostaje wstrzymana

							stan_gry = przerwana;
					}
				}
				ruszajacy = ruszajacy->getNext();

			}
			dostep_do_planszy.unlock();
		}

	}
	return 0;
}