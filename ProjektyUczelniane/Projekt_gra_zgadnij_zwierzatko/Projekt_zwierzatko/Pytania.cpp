#include "Header.h"
using namespace std;

PytanieNW::PytanieNW()
{
	LicznikPytanWW--;
	LicznikPytanNW++;
}

PytanieNW * PytanieNW::getNext()
{
	return this->pNext;
}

PytanieNW * PytanieNW::getPrev()
{
	return this->pPrev;
}

int Pytanie::LicznikPytanNW = 0;

int Pytanie::LicznikPytanWW = 0;

int Zwierzatko::LicznikZwierzatek = 0;

Pytanie::Pytanie() {
	LicznikPytanWW++;
	LiczbaWystapien++;
	setPrev(nullptr);
	setNext(nullptr);
	//cout << "konstruktor Pytanie\n";
}

Pytanie::Pytanie(Pytanie * pPrev, Pytanie * pNext, string TrescPytania) {
	LicznikPytanWW++;
	LiczbaWystapien++;
	this->TrescPytania = TrescPytania;
	this->pNext = pNext;
	this->pPrev = pPrev;
	//setPrev(pPrev);
	//setNext(pNext);
	if (pPrev != nullptr) {
		pPrev->pNext = this;
		//pPrev->setNext(this);
	}
	if (pNext != nullptr) {
		pNext->pPrev = this;
		//pNext->setPrev(this);
	}
	//cout << "konstruktor Pytanie\n";
}

void Pytanie::setTresc(string value)
{
	this->TrescPytania = value;
}

PytanieNW::PytanieNW(PytanieNW * pPrev, PytanieNW * pNext, string TrescPytania, string Podpowiedz, string Zaprzeczenie) {
	LicznikPytanWW--;
	LicznikPytanNW++;
	//LiczbaWystapien++;
	this->setTresc(TrescPytania);
	//this->TrescPytania = TrescPytania;
	this->Podpowiedz = Podpowiedz;
	this->Zaprzeczenie = Zaprzeczenie;
	this->setNext(pNext);
	this->setPrev(pPrev);
	//this->pNext = pNext;
	//this->pPrev = pPrev;
	//setPrev(pPrev);
	//setNext(pNext);
	if (pPrev != nullptr) {
		pPrev->pNext = this;
		//pPrev->setNext(this);
	}
	if (pNext != nullptr) {
		pNext->pPrev = this;
		//pNext->setPrev(this);
	}
	//cout << "konstruktor PytanieNW\n";
}

Pytanie::~Pytanie()
{
	if (pPrev) {
		pPrev->pNext = this->pNext;
	}
	if (pNext) {
		pNext->pPrev = this->pPrev;
	}
	//cout << "destruktor Pytanie\n";
}

PytanieNW::~PytanieNW()
{
	if (pPrev) {
		pPrev->pNext = this->pNext;
	}
	if (pNext) {
		pNext->pPrev = this->pPrev;
	}
	//cout << "destruktor PytanieNW\n";
}

ostream & operator << (ostream &wyjscie, const Pytanie *send) {
	if (send != nullptr)
		wyjscie << send->TrescPytania;
	return wyjscie;
}

void PytanieNW::potwierdzenie() {
	if (this)
		cout << "TAK, " << this->Podpowiedz << "\n";
}

void PytanieNW::zaprzeczenie() {
	if (this)
		cout << "NIE, " << this->Zaprzeczenie << "\n";
}

Pytanie * Pytanie::getNext()
{
	return this->pNext;
}

Pytanie * Pytanie::getPrev()
{
	return this->pPrev;
}

void Pytanie::setPrev(Pytanie * value)
{
	pPrev = value;
}

void Pytanie::setNext(Pytanie * value)
{
	pNext = value;
}

void Pytanie::setZuzycie(int value)
{
	Zuzycie = value;
}

int Pytanie::getLicznik()
{
	return LiczbaWystapien;
}

int Pytanie::getZuzycie()
{
	return this->Zuzycie;
}

string Pytanie::getTresc()
{
	return this->TrescPytania;
}

void Pytanie::zwiekszLicznik(int value)
{
	LiczbaWystapien = LiczbaWystapien + value;
}

PytaniaOsobiste::PytaniaOsobiste() {
	p = nullptr;
	pNW = nullptr;
	pNext = nullptr;
}

PytaniaOsobiste::~PytaniaOsobiste() {
	if (this->p) {
		this->p->zwiekszLicznik(-1);
		if(this->p->getLicznik() == 0)
			this->p->LicznikPytanWW--;
	}
	if (this->pNW) {
		this->pNW->zwiekszLicznik(-1);
		if (this->pNW->getLicznik() == 0)
			this->pNW->LicznikPytanNW--;
	}
	if (this->pNext)
		delete this->pNext;
}

void PytaniaOsobiste::DodajPytanie(string TrescPytania, string Podpowiedz, string Zaprzeczenie, Encyklopedia & zbior)
{
	if (Podpowiedz == "[X] BRAK PODPOWIEDZI" || Zaprzeczenie == "[X] BRAK ZAPRZECZENIA") {
		if (p == nullptr)
			p = zbior.DodajPytanie(TrescPytania);
		else {
			PytaniaOsobiste * temp = this;
			while (temp->pNext) {
				if (temp->p != nullptr)
					temp = temp->pNext;
				else {
					temp->p = zbior.DodajPytanie(TrescPytania);
					return;
				}
			}
			temp->pNext = new PytaniaOsobiste;
			temp->pNext->p = zbior.DodajPytanie(TrescPytania);
		}
	}
	else {
		if (pNW == nullptr)
			pNW = zbior.DodajPytanieNW(TrescPytania, Podpowiedz, Zaprzeczenie);
		else {
			PytaniaOsobiste * temp = this;
			while (temp->pNext) {
				if (temp->pNW != nullptr)
					temp = temp->pNext;
				else {
					temp->pNW = zbior.DodajPytanieNW(TrescPytania, Podpowiedz, Zaprzeczenie);
					return;
				}
			}
			temp->pNext = new PytaniaOsobiste;
			temp->pNext->pNW = zbior.DodajPytanieNW(TrescPytania, Podpowiedz, Zaprzeczenie);
		}
	}
}


//PytaniaOsobiste::PytaniaOsobiste() {
//	p = nullptr;
//	pNW = nullptr;
//	pNext = nullptr;
//}

int PytaniaOsobiste::SprawdzPytanie(Pytanie *pyt) {
	PytaniaOsobiste * temp = this;
	while (temp) {
		if (temp->p == pyt) {
			return 1;
		}
		temp = temp->pNext;
	}
	return 0;
}

int PytaniaOsobiste::SprawdzPytanieNW(PytanieNW * pyt)
{
	PytaniaOsobiste * temp = this;
	while (temp) {
		if (temp->pNW == pyt) {
			return 1;
		}
		temp = temp->pNext;
	}
	return 0;
}

Pytanie * PytaniaOsobiste::PobierzWsk()
{
	return this->p;
}

PytanieNW * PytaniaOsobiste::PobierzWskNW()
{
	return this->pNW;
}

PytaniaOsobiste * PytaniaOsobiste::PobierzNext()
{
	return this->pNext;
}

PytaniaOsobiste * Zwierzatko::PobierzWsk()
{
	return this->pHead;
}

void PytaniaOsobiste::SetNext(PytaniaOsobiste * next)
{
	this->pNext = next;
}

string Zwierzatko::GetNazwa()
{
	return nazwa;
}

//void Zwierzatko::DodajPytanie(Encyklopedia zbior){
//}

void Zwierzatko::setWsk(PytaniaOsobiste * w)
{
	pHead = w;
}

void Zwierzatko::zwiekszLiczbeWystapien(int value)
{
	LiczbaWystapien = LiczbaWystapien + value;
}

Zwierzatko * Zwierzatko::PobierzNext()
{
	return pNext;
}

void Zwierzatko::setNext(Zwierzatko * wsk)
{
	this->pNext = wsk;
}

Zwierzatko::Zwierzatko() {
	LiczbaWystapien = 0;
}

Zwierzatko::Zwierzatko(string n, PytaniaOsobiste * ws)
{
	LiczbaWystapien = 0;
	LicznikZwierzatek++;
	nazwa = n;
	pHead = ws;
}

int Zwierzatko::getLiczbaWystapien()
{
	return LiczbaWystapien;
}

Zwierzatko::~Zwierzatko()
{
	if (this->LiczbaWystapien == 0)
		LicznikZwierzatek--;

	delete this->pHead;
	this->pHead = nullptr;
}

WyborPytaniaNW::WyborPytaniaNW()
{
	for (int i = 0; i < 10; i++) {
		tab[i] = nullptr;
		zuzyte[i] = nullptr;
	}
}

void WyborPytaniaNW::setTab(int i, PytanieNW * p)
{
	if (p != nullptr)
		tab[i] = p;
	else {
		while (i < 9 and tab[i + 1] != nullptr) {
			tab[i] = tab[i + 1];
			i++;
		}
		tab[i] = nullptr;
	}
	return;
}

void WyborPytaniaNW::WyswietlListe() {
	for (int i = 0; i < 10; i++) {
		if (tab[i]) {
			cout << i << ". " << tab[i] << endl;
		}
	}
	WyswietlZuzyte();
}

void WyborPytaniaNW::WyswietlZuzyte() {
	zmienKolor(10);
	for (int x = 0; x < 10; x += 2) {
		if (zuzyte[x]) {
			zuzyte[x]->potwierdzenie();
		}
	}
	zmienKolor(15);
	zmienKolor(12);
	for (int x = 1; x < 10; x += 2) {
		if (zuzyte[x]) {
			zuzyte[x]->zaprzeczenie();
		}
	}
	zmienKolor(15);
}

int WyborPytaniaNW::WybierzPytanie(int i, Zwierzatko * Rozpatrywane) {
	PytaniaOsobiste * temp = Rozpatrywane->PobierzWsk();
	int zwracana = -1;
	int x = -1;
	if (tab[i]) {
		if (temp->SprawdzPytanieNW(tab[i])) {
			//tab[i]->potwierdzenie();
			zwracana = 1;
			x = 0;

		}
		else {
			//tab[i]->zaprzeczenie();
			zwracana = 0;
			x = 1;
		}
	for (; zuzyte[x]; x+=2);
	zuzyte[x] = tab[i];
	return zwracana;
	}
	else
		return zwracana;
}

WyborPytaniaWW::WyborPytaniaWW()
{
	for (int i = 0; i < 10; i++)
		tab[i] = nullptr;
}

void WyborPytaniaWW::setTab(int i, Pytanie * p)
{
	tab[i] = p;
	return;
}

void WyborPytaniaWW::WyswietlListe() {
	for (int i = 0; i < 10; i++) {
		if (tab[i]) {
			char a = 'a' + i;
			cout << a << ". " << tab[i] << endl;
		}
	}
}

void WyborPytaniaNW::clearTabs()
{
	for (int i = 0; i < 10; i++) {
		if (tab[i]) {
			tab[i]->setZuzycie(0);
			tab[i]->LicznikPytanNW++;
			tab[i] = nullptr;
		}
	}
	for (int i = 0; i < 10; i++) {
		if (zuzyte[i]) {
			zuzyte[i]->setZuzycie(0);
			zuzyte[i]->LicznikPytanNW++;
			zuzyte[i] = nullptr;
		}
	}
}

void WyborPytaniaWW::clearTab()
{
	for (int i = 0; i < 10; i++) {
		if (tab[i]) {
			tab[i]->setZuzycie(0);
			tab[i]->LicznikPytanWW++;
			tab[i] = nullptr;
		}
	}
}

int WyborPytaniaWW::WybierzPytanie(int i, Zwierzatko * Rozpatrywane) {
	PytaniaOsobiste * temp = Rozpatrywane->PobierzWsk();
	if (tab[i]) {
		if (temp->SprawdzPytanie(tab[i])) {
			return 1;
		}
		else {
			return 0;
		}
	}
	else
		return -1;
}

PytanieNW * WyborPytaniaNW::GetTab(int i)
{
	return this->tab[i];
}

void WyborPytaniaNW::zmienKolor(int k)
{
	HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
	// k15 = bia³y
	// k10 = zielony
	// k12 = czerwony
	// k13 = ró¿owy
	// k3 = ³adnoniebieski
	SetConsoleTextAttribute(hConsole, k);
}