#include "Header.h"

using namespace std;

int Punktacja::GetWynik()
{
	return wynik;
}

int Punktacja::GetNajlepszyWynik()
{
	return najwyzszy_wynik;
}

int Punktacja::GetSeria()
{
	return seria;
}

int Punktacja::GetNajlepszaSeria()
{
	return najwyzsza_seria;
}

void Punktacja::SetNajlepszyWynik(int value)
{
	najwyzszy_wynik = value;
}

void Punktacja::SetNajlepszaSeria(int value)
{
	najwyzsza_seria = value;
}

void Punktacja::WczytajZPliku()
{
	ifstream plik("rekordy.txt");
	if (!plik) {
		plik.close();
		return;
	}
	plik >> *this;
	plik.close();
	return;
}

void Punktacja::WypiszZPliku() {
	ifstream plik("historia.txt");
	if (!plik) {
		plik.close();
		return;
	}
	system("cls");
	cout << "Historia wynik¢w:" << endl;
	int punkty, seria;
	time_t czas;
	tm * sf_czas = new tm;
	plik >> punkty; // Na wypadek zakoñczenia pliku bia³ym znakiem, jeden wyraz zostaje wczytany przed sprawdzeniem warunku pêtli
	while (!plik.eof()) {
		plik >> seria >> czas;
		localtime_s(sf_czas, &czas);
		cout << "Liczba punkt¢w: " << setw(5) << setfill(' ') << punkty << "  Seria zwyci©stw: " << setw(2) << seria << "  Data: ";
		cout << setw(2) << setfill('0') << sf_czas->tm_mday << "/" << setw(2) << sf_czas->tm_mon + 1 << "/" << sf_czas->tm_year % 100 << " " << setw(2) << sf_czas->tm_hour << ":" << setw(2) << sf_czas->tm_min << endl;
		plik >> punkty; // Na wypadek zakoñczenia pliku bia³ym znakiem, jeden wyraz zostaje wczytany przed sprawdzeniem warunku pêtli
	}
	cout << "w - powr¢t";
	delete sf_czas;
	plik.close();
	while (_getch() != 'w');
	return;
}

void Punktacja::ZapiszRekordDoPliku()
{
	if (wynik == najwyzszy_wynik or seria == najwyzsza_seria) {
		ofstream plik("rekordy.txt");
		//plik << *this;
		plik << GetNajlepszyWynik() << " " << GetNajlepszaSeria();
		plik.close();
	}
	return;
}

void Punktacja::ZapiszMeczDoPliku()
{
	ofstream plik("historia.txt", ios::app);
	//plik << *this;
	time_t czas;
	time(&czas);
	plik << GetWynik() << " " << GetSeria() << " " << czas << endl;
	plik.close();
	return;
}

Punktacja Punktacja::operator+=(int val)
{
	wynik += val;
	if (wynik > najwyzszy_wynik)
		najwyzszy_wynik = wynik;
	return *this;
}

Punktacja Punktacja::operator+(int val)
{
	wynik += val;
	if (wynik > najwyzszy_wynik)
		najwyzszy_wynik = wynik;
	return *this;
}

Punktacja Punktacja::operator-=(int val)
{
	wynik -= val;
	return *this;
}

Punktacja Punktacja::operator-(int val)
{
	wynik -= val;
	return *this;
}

Punktacja Punktacja::operator=(const Punktacja & val)
{
	if (&val != this) {
		wynik = val.wynik;
		seria = val.seria;
		najwyzszy_wynik = val.najwyzszy_wynik;
		najwyzsza_seria = val.najwyzsza_seria;
		return *this;
	}
}

Punktacja Punktacja::operator()(int wwynik, int sseria)
{
	wynik = wwynik;
	seria = sseria;
	return *this;
}

Punktacja& Punktacja::operator++(int x)
{
	if (x == 0)
		seria++;
	else
		seria += x;
	if (seria > najwyzsza_seria)
		najwyzsza_seria = seria;
	return *this;
}

Punktacja::Punktacja()
{
	wynik = 1000;
	najwyzszy_wynik = 0;
	seria = 0;
	najwyzsza_seria = 0;
}

ostream & operator << (ostream & wyjscie, Punktacja send)
{
	wyjscie << "Liczba punkt¢w: " << send.GetWynik() << "  Najlepszy wynik: " << send.GetNajlepszyWynik() << endl;
	wyjscie << "Seria zwyci©stw: " << send.GetSeria() << "  Najlepsza seria: " << send.GetNajlepszaSeria() << endl;
	return wyjscie;
}

istream & operator >> (istream & wejscie, Punktacja &get)
{
	int value;
	wejscie >> value;
	get.SetNajlepszyWynik(value);
	wejscie >> value;
	get.SetNajlepszaSeria(value);
	return wejscie;
}
