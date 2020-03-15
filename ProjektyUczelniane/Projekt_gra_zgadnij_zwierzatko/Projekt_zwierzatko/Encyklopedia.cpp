#include "Header.h"

using namespace std;

Encyklopedia::Encyklopedia()
{
	WysokaWaga = nullptr;
	NiskaWaga = nullptr;
	ListaZwierzat = nullptr;
}

PytanieNW * Encyklopedia::DodajPytanieNW(string TrescPytania, string Podpowiedz, string Zaprzeczenie)
{
	if (NiskaWaga == nullptr) {
		NiskaWaga = new PytanieNW(nullptr, nullptr, TrescPytania, Podpowiedz, Zaprzeczenie);
		return NiskaWaga;
	}
	else
	{
		PytanieNW * temp = NiskaWaga;
		if (temp->getTresc() == TrescPytania) {
			if (temp->getLicznik() == 0)
				temp->LicznikPytanNW++;
			temp->zwiekszLicznik(1);
			return temp;
		}
		while (temp->getNext()) {
			if (temp->getNext()->getTresc() == TrescPytania) {
				if (temp->getNext()->getLicznik() == 0)
					temp->getNext()->LicznikPytanNW++;
				temp->getNext()->zwiekszLicznik(1);
				return temp->getNext();
			}
		temp = temp->getNext();
		}
		return new PytanieNW(temp, nullptr, TrescPytania, Podpowiedz, Zaprzeczenie);
	}
}

Pytanie * Encyklopedia::DodajPytanie(string TrescPytania)
{
	if (WysokaWaga == nullptr) {
		WysokaWaga = new Pytanie(nullptr, nullptr, TrescPytania);
		return WysokaWaga;
	}
	else
	{
		Pytanie * temp = WysokaWaga;
		if (temp->getTresc() == TrescPytania) {
			if (temp->getLicznik() == 0)
				temp->LicznikPytanWW++;
			temp->zwiekszLicznik(1);
			//return nullptr;
			return temp;
		}
		while (temp->getNext()) {
			if (temp->getNext()->getTresc() == TrescPytania) {
				if (temp->getNext()->getLicznik() == 0)
					temp->getNext()->LicznikPytanWW++;
				temp->getNext()->zwiekszLicznik(1);
				//return nullptr;
				return temp->getNext();
			}
			temp = temp->getNext();
		}
		return new Pytanie(temp, nullptr, TrescPytania);
	}
}

Pytanie * Encyklopedia::LosujPytanieWW()
{
	Pytanie * temp = WysokaWaga;
	int wyliczanie = temp->LicznikPytanWW;
	while (temp && wyliczanie > 0) {
		if (temp->getZuzycie() == 0 && rand() % 10000 <= 10000 / wyliczanie) {
			temp->setZuzycie(1);
			temp->LicznikPytanWW--;
			return temp;
		}
		else {
			if (temp->getZuzycie() == 0)
				wyliczanie--;
			temp = temp->getNext();
		}
	}
	return nullptr;
}

PytanieNW * Encyklopedia::LosujPytanieNW()
{
	PytanieNW * temp = NiskaWaga;
	int wyliczanie = temp->LicznikPytanNW;
	while (temp && wyliczanie > 0) {
		if (temp->getZuzycie() == 0 && rand() % 10000 <= 10000 / wyliczanie) {
			temp->setZuzycie(1);
			temp->LicznikPytanNW--;
			return temp;
		}
		else {
			if (temp->getZuzycie() == 0)
				wyliczanie--;
			temp = temp->getNext();
		}
	}
	return nullptr;
}

void Encyklopedia::CzyscListeWW()
{
	Pytanie * temp = WysokaWaga;
	while (temp && temp->getLicznik() <= 0) {
		WysokaWaga = WysokaWaga->getNext();
		delete temp;
		temp = WysokaWaga;
	}
	while (temp && temp->getNext()) {
		if (temp->getNext()->getLicznik() <= 0) {
			delete temp->getNext();
		}
		else {
			temp = temp->getNext();
		}
	}
}


void Encyklopedia::CzyscListeNW()
{
	PytanieNW * temp = NiskaWaga;
	while (temp && temp->getLicznik() <= 0) {
		NiskaWaga = NiskaWaga->getNext();
		delete temp;
		temp = NiskaWaga;
	}
	while (temp && temp->getNext()) {
		if (temp->getNext()->getLicznik() <= 0) {
			delete temp->getNext();
		}
		else {
			temp = temp->getNext();
		}
	}
}

WyborPytaniaNW Encyklopedia::Zapelnij()
{
	WyborPytaniaNW Lista;
	for (int i = 0; i < 10; i++) {
		
		Lista.setTab(i, this->LosujPytanieNW());
	}
	return Lista;
}

WyborPytaniaWW Encyklopedia::ZapelnijWW(Zwierzatko * Wybrane)
{
	WyborPytaniaWW Lista;
	int d = -1;
	Pytanie * temp = Wybrane->PobierzWsk()->PobierzWsk();
	if (temp->LicznikPytanWW > 9) {
		d = rand() % 10;
		Lista.setTab(d, temp);
		temp->setZuzycie(1);
		temp->LicznikPytanWW--;
	}
	for (int i = 0; i < 10; i++) {
		if (i != d)
			Lista.setTab(i, this->LosujPytanieWW());
	}
	return Lista;
}

bool Encyklopedia::PodepnijZwierzatko(Zwierzatko * wsk) { // 0 - zwierzatko juz bylo na liscie
	if (this->ListaZwierzat == nullptr) {
		ListaZwierzat = wsk;
		return 1;
	}
	else {
		Zwierzatko * temp = ListaZwierzat;
		while (temp) {
			if (temp->GetNazwa() == wsk->GetNazwa()) {
				return 0;
			}
			else if (temp->PobierzNext() == nullptr) {
				temp->setNext(wsk);
				return 1;
			}
			temp = temp->PobierzNext();
		}

	}
}

bool Encyklopedia::DodajZwierzatka(string NazwaPliku)
{
	ifstream plik(NazwaPliku);
	if (plik.eof() or !plik) {
		plik.close();
		return 0;
	}
	
	string nazwa;
	string a;
	string b;
	string c;

	string temp;

	Zwierzatko * tempZw = this->ListaZwierzat;
	PytaniaOsobiste * tempPo = new PytaniaOsobiste;

	while (!plik.eof()) {
		if (nazwa == "") {
			getline(plik, nazwa);
			getline(plik, temp);
		}
		getline(plik, a);
		getline(plik, b);
		streampos t = plik.tellg();
		getline(plik, c);
		getline(plik, temp);
		if (b != "" and !plik.eof()) {
			tempPo->DodajPytanie(a, b, c, *this);
		}
		if (b == "" or plik.eof()) {
			while (tempZw) {
				if (tempZw->GetNazwa() == nazwa)
				{
					if (!tempZw->PobierzWsk())
						tempZw->setWsk(tempPo);
					else {
						while (tempZw->PobierzWsk()->PobierzNext()) {
							tempZw->setWsk(tempZw->PobierzWsk());
						}
						tempZw->PobierzWsk()->SetNext(tempPo);
					}
				}
			}
			if (nazwa != "") {
				if (b != "")
					tempPo->DodajPytanie(a, b, c, *this);
				Zwierzatko * w = new Zwierzatko(nazwa, tempPo);
				if (PodepnijZwierzatko(w) == 0) {
					delete w;
					w = nullptr;
					tempPo = nullptr;
				}
			}
			else
				delete tempPo;
			nazwa = a;
			if (!plik.eof()) {
				plik.seekg(t);
				tempPo = new PytaniaOsobiste;
			}
		}
	}

	nazwa = temp;
	plik.close();
	return 1;
}

bool Encyklopedia::WyrzucZwierzatko(string Nazwa)
{
	if (!ListaZwierzat)
		return 0;
	while (Nazwa == "" and ListaZwierzat) {
		Zwierzatko * temp = ListaZwierzat;
		ListaZwierzat = this->ListaZwierzat->PobierzNext();
		delete temp;
	}
	if (Nazwa == "")
		return 1;
	if (this->ListaZwierzat->GetNazwa() == Nazwa) {
		Zwierzatko * temp = ListaZwierzat;
		ListaZwierzat = this->ListaZwierzat->PobierzNext();
		delete temp;
		return 1;
	}
	else {
		Zwierzatko * temp = ListaZwierzat;
		while (temp->PobierzNext()) {
			if (temp->PobierzNext()->GetNazwa() == Nazwa) {
				Zwierzatko * temp2 = temp->PobierzNext()->PobierzNext();
				delete temp->PobierzNext();
				temp->setNext(temp2);
				return 1;
			}
			temp = temp->PobierzNext();
		}
		return 0;
	}
}

Zwierzatko * Encyklopedia::PobierzZwierzatko()
{
	return this->ListaZwierzat;
}

Zwierzatko * Encyklopedia::LosujZwierzatko()
{
	Zwierzatko * temp = this->ListaZwierzat;
	int wyliczanie = temp->LicznikZwierzatek;
	if (wyliczanie == 0 && temp) {
		while (temp) {
			temp->zwiekszLiczbeWystapien(-1);
			temp->LicznikZwierzatek++;
			temp = temp->PobierzNext();
		}
		temp = this->ListaZwierzat;
		wyliczanie = temp->LicznikZwierzatek;
	}
	while (temp && wyliczanie > 0) {
		if (temp->getLiczbaWystapien() == 0 && rand() % 10000 <= 10000 / wyliczanie) {
			temp->zwiekszLiczbeWystapien(1);
			temp->LicznikZwierzatek--;
			return temp;
		}
		else {
			if (temp->getLiczbaWystapien() == 0)
				wyliczanie--;
			temp = temp->PobierzNext();
		}
	}
	return nullptr;
}