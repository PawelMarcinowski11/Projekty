#include "Header.h"

using namespace std;


void Wstep::wyswietlWstep()
{
	system("CLS");
	cout << endl << "Witam w grze Zgadnij Zwierz¥tko!" << endl << endl <<"Twoim zadaniem jest odgadn¥† w ka¾dej rundzie zwierz¥tko wybierane przez program w pseudolosowy spos¢b." << endl <<"Aby zwi©kszy† szans© osi¥gni©cia celu, do twojej dyspozycji zostaˆa oddana mo¾liwo˜† zadawania pytaä i proszenia"<< endl <<"o podpowied«. Pierwsza opcja kosztuje 100 punkt¢w, a druga 500. Za zwyci©stwo, gracz otrzymuje 1000 punkt¢w." << endl	<<"Wygrywanie wielu rund z rz©du jest liczone jako seria zwyci©stw." << endl << "Nieodgadni©cie zwierz©cia resetuje seri© i liczb© punkt¢w."<< endl << endl << "Najlepsze wyniki s¥ zapisywane w pliku \"rekordy.txt\", a historia meczy zapisywana jest w pliku \"historia.txt\"." << endl << endl << "½ycz© dobrej zabawy!" << endl <<"Aby kontynuowa†, naci˜nij dowolny przycisk.";
	_getch();
}


void Gra::loop()
{
	char bufor;
	int test;
	Punktacja wyniki;
	wyniki.WczytajZPliku();
	while (1) {
		Zwierzatko * temp = this->getBaza()->LosujZwierzatko();
		if (temp == nullptr)
			break;
		WyborPytaniaNW tablica = this->getBaza()->Zapelnij();
		int zwrot = 0;
		system("CLS");
		tablica.zmienKolor(15);
		cout << wyniki;
		cout << "Pozostaˆa liczba pytaä:: 5" << endl;
		tablica.WyswietlListe();
		int p = -1;
		for (int d = 0; d < 10; d++) {
			if (temp->PobierzWsk()->SprawdzPytanieNW(tablica.GetTab(d)) == 1) {
				p = d;
				d = 10;
			}
		}
		if (p != -1)
			cout << "p - Podpowied«" << endl;
		cout << "z - Zgaduj teraz" << endl;
		cout << "w - Historia wynik¢w" << endl;
		cout << "esc - Wyjd« z gry" << endl;
		for (int i = 0; i < 5; i++) {
			bufor = _getch();
			if (bufor == '\x1b') { //Przycisk esc wychodzi z pêtli.
				wyniki += zwrot;
				if (wyniki.GetWynik() != 1000 or wyniki.GetSeria() != 0)
					wyniki.ZapiszMeczDoPliku();
				tablica.clearTabs();
				return;
			}
			if (bufor == 'z') { //Przycisk 'z' przenosi do nastêpnego etapu.
				i = 6;
			}
			if (bufor == 'w') {
				wyniki.WypiszZPliku();
				system("CLS");
				cout << wyniki;
				cout << "Pozostaˆa liczba pytaä:: " << 5 - i << endl;
				tablica.WyswietlListe();
				if (p != -1)
					cout << "p - Podpowied«" << endl;
				cout << "z - Zgaduj teraz" << endl;
				cout << "w - Historia wynik¢w" << endl;
				cout << "esc - Wyjd« z gry" << endl;
			}
			if (bufor == 'p' && p != -1) { //Przycisk 'p' podaje jedna podpowiedz na mecz.
				tablica.WybierzPytanie(p, temp);
				tablica.setTab(p, this->getBaza()->LosujPytanieNW());
				wyniki -= 500;
				zwrot += 500;
				system("CLS");
				cout << wyniki;
				cout << "Pozostaˆa liczba pytaä:: " << 4 - i << endl;
				tablica.WyswietlListe();
				cout << "z - Zgaduj teraz" << endl;
				cout << "w - Historia wynik¢w" << endl;
				cout << "esc - Wyjd« z gry" << endl;
				p = -1;
				i++;
			}
			if (bufor >= 48 and bufor <= 57) {
				test = tablica.WybierzPytanie(bufor - 48, temp);
				if (test == -1)
					i--;
				else {
					tablica.setTab(bufor - 48, this->getBaza()->LosujPytanieNW());
					if (bufor - 48 == p) {
						p = -1;
						for (int d = 0; d < 10; d++) {
							if (temp->PobierzWsk()->SprawdzPytanieNW(tablica.GetTab(d)) == 1) {
								p = d;
								d = 10;
							}
						}
					}
					wyniki -= 100;
					zwrot += 100;
					system("CLS");
					cout << wyniki;
					cout << "Pozostaˆa liczba pytaä:: " << 4 - i << endl;
					tablica.WyswietlListe();
					if (p != -1)
						cout << "p - Podpowied«" << endl;
					cout << "z - Zgaduj teraz" << endl;
					cout << "w - Historia wynik¢w" << endl;
					cout << "esc - Wyjd« z gry" << endl;
				}
			}
			else
				i--;
		}
		WyborPytaniaWW tablicaWW = this->getBaza()->ZapelnijWW(temp);
		system("CLS");
		cout << wyniki;
		//tablica.WyswietlListe();
		tablica.WyswietlZuzyte();
		tablicaWW.WyswietlListe();
		cout << "w - Historia wynik¢w" << endl;
		cout << "esc - Wyjd« z gry" << endl;
		int wl = 1;
		while (wl == 1) {
			bufor = _getch();
			if (bufor == '\x1b') { //Przycisk esc wychodzi z pêtli.
				wyniki += zwrot;
				if (wyniki.GetWynik() != 1000 or wyniki.GetSeria() != 0)
					wyniki.ZapiszMeczDoPliku();
				tablica.clearTabs();
				tablicaWW.clearTab();
				return;
			}
			if (bufor == 'w') {
				wyniki.WypiszZPliku();
				system("CLS");
				cout << wyniki;
				//tablica.WyswietlListe();
				tablica.WyswietlZuzyte();
				tablicaWW.WyswietlListe();
				cout << "w - Historia wynik¢w" << endl;
				cout << "esc - Wyjd« z gry" << endl;
			}
			if (bufor >= 97 and bufor <= 106) {
				if (tablicaWW.WybierzPytanie(bufor - 97, temp) == 1) {
					wyniki += 1000;
					wyniki++;
					system("CLS");
					cout << wyniki;
					//tablica.WyswietlListe();
					tablica.WyswietlZuzyte();
					tablicaWW.WyswietlListe();
					tablica.zmienKolor(3);
					cout << "To zwierz© to " << temp->GetNazwa() << "!\n";
					tablica.zmienKolor(14);
					for (int i = wyniki.GetSeria(); i > 0; i--)
						cout << "      \\\\ ";
					cout << endl;
					for (int i = wyniki.GetSeria(); i > 0; i--)
						cout << "    __(')";
					cout << endl;
					for (int i = wyniki.GetSeria(); i > 0; i--)
						cout << "  o(_-\\\_ ";
					//cout << endl;
					tablica.zmienKolor(3);
					cout << "Zwyci©¾yˆe˜! Naci˜nij dowolny przycisk aby zagra† ponownie";
					tablica.zmienKolor(15);
					wyniki.ZapiszRekordDoPliku();
					_getch();
					wl = 0;
				}
				else if (tablicaWW.WybierzPytanie(bufor - 97, temp) == 0) {
					system("CLS");
					cout << wyniki;
					//tablica.WyswietlListe();
					tablica.WyswietlZuzyte();
					tablicaWW.WyswietlListe();
					tablica.zmienKolor(13);
					cout << "To zwierz© to " << temp->GetNazwa() << "!\n";
					cout << "Nie udaˆo si©! Naci˜nij dowolny przycisk aby spr¢bowa† ponownie";
					tablica.zmienKolor(15);
					wyniki += zwrot;
					wyniki.ZapiszMeczDoPliku();
					_getch();
					wl = 0;
					wyniki(1000,0);
				}
			}
		}
		//wyczyscic obie tablice
		tablica.clearTabs();
		tablicaWW.clearTab();
	}
}

void Gra::inicjalizujBaze()
{
	this->baza = new Encyklopedia;
}

void Gra::deinicjalizujBaze()
{
	delete baza;
	baza = nullptr;
}

Encyklopedia * Gra::getBaza()
{
	if (!this->baza)
		this->baza = new Encyklopedia;
	return this->baza;
}