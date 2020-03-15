/** @file */
#pragma once

using namespace std;

class Encyklopedia;

/**Obiekty tej klasy tworz� list� jednokierunkow� pyta� wysokiej wagi, dotycz�cych nazwy zwierz�cia i wy�wietlanych dopiero w ostatnim etapie ka�dej rundy.*/
///@param Pole Zawarto�� pola
///@param pNext Wska�nik na nast�pny element listy
///@param pPrev Wska�nik na poprzedni element listy
///@param TrescPytania Tre�� zawartego w bazie pytania
///@param Zuzycie Wynosi 1 gdy pytanie zosta�o ju� wy�wietlone graczowi. Domy�lnie 0, resetuje si� po ka�dej rundzie
///@param LiczbaWystapien Pole inkrementuje si� za ka�dym razem, gdy nowe zwierz� odwo�uje si� do tego pytani. Gdy �adne zwierz�tko si� do niego nie odwo�uje, zostaje ono oznaczone jako przeznaczone do usuni�cia z puli
///@param LicznikPytanNW Licznik okre�laj�cy ��czn� liczb� dost�pnych w bazie pyta� niskiej wagi, kt�re nie s� zu�yte ani przeznaczone do usuni�cia
///@param LicznikPytanWW Licznik okre�laj�cy ��czn� liczb� dost�pnych w bazie pyta� wysokiej wagi, kt�re nie s� zu�yte ani przeznaczone do usuni�cia
class Pytanie {
private:
	Pytanie * pNext; ///< Wska�nik na nast�pny element listy
	Pytanie * pPrev; ///< Wska�nik na poprzedni element listy
	string TrescPytania; ///< Tre�� zawartego w bazie pytania
	int Zuzycie; ///< Wynosi 1 gdy pytanie zosta�o ju� wy�wietlone graczowi. Domy�lnie 0, resetuje si� po ka�dej rundzie
	int LiczbaWystapien; ///< Pole inkrementuje si� za ka�dym razem, gdy nowe zwierz� odwo�uje si� do tego pytani. Gdy �adne zwierz�tko si� do niego nie odwo�uje, zostaje ono oznaczone jako przeznaczone do usuni�cia z puli
public:
	void setTresc(string value);
	Pytanie * getNext();
	Pytanie * getPrev();
	int getZuzycie();
	int getLicznik();
	string getTresc();
	void zwiekszLicznik(int value);
	void setPrev(Pytanie * value);
	void setNext(Pytanie * value);
	void setZuzycie(int value);
	static int LicznikPytanNW; ///< Licznik okre�laj�cy ��czn� liczb� dost�pnych w bazie pyta� niskiej wagi, kt�re nie s� zu�yte ani przeznaczone do usuni�cia
	static int LicznikPytanWW; ///< Licznik okre�laj�cy ��czn� liczb� dost�pnych w bazie pyta� wysokiej wagi, kt�re nie s� zu�yte ani przeznaczone do usuni�cia
	friend ostream & operator << (ostream &wyjscie, const Pytanie *send);
	/// Konstruktor bezargumentowy, ustawia pola obiektu b�d�ce wska�nikami na nullptr i inkrementuje licznik pyta� wysokiej wagi.
	Pytanie();
	/// Konstruktor wieloargumentowy, poza inkrementacj� licznika pyta� wysokiej wagi ustawia warto�ci p�l na podane w argumentach.
	///@param pPrev Wska�nik na poprzedni element listy.
	///@param pNext Wska�nik na nast�pny element listy.
	///@param TrescPytania String zawieraj�cy tre�� pytania.
	Pytanie(Pytanie * pPrev, Pytanie * pNext, string TrescPytania);
	/// Destruktor spina ze sob� poprzednik i nast�pnik usuwanego elementu, o ile jest to mo�liwe.
	~Pytanie();
};

/**Obiekty tej klasy tworz� list� jednokierunkow� pyta� niskiej wagi, dotycz�cych cech zwierz�cia i wy�wietlanych we wst�pnym etapie ka�dej rundy.*/
///@param Pole Zawarto�� pola
///@param pNext Wska�nik na nast�pny element listy
///@param pPrev Wska�nik na poprzedni element listy
///@param Podpowiedz Tre�� podpowiedzi (a tak�e odpowiedzi), przeznaczona do wy�wietlenia u�ytkownikowi
///@param Zaprzeczenie Tre�� zaprzeczenia, przeznaczona do wy�wietlenia u�ytkownikowi
class PytanieNW : public Pytanie {
private:
	PytanieNW * pNext; ///< Wska�nik na nast�pny element listy
	PytanieNW * pPrev; ///< Wska�nik na poprzedni element listy
	string Podpowiedz; ///< Tre�� podpowiedzi (a tak�e odpowiedzi), przeznaczona do wy�wietlenia u�ytkownikowi
	string Zaprzeczenie; ///< Tre�� zaprzeczenia, przeznaczona do wy�wietlenia u�ytkownikowi
public:
	PytanieNW * getNext();
	PytanieNW * getPrev();
	/// Metoda wypisuje na strumie� cout potwierdzenie, �e ta cecha pasuje do rozpatrywanego zwierz�cia.
	void potwierdzenie(); 
	/// Metoda wypisuje na strumie� cout zaprzeczenie, gdy� ta cecha nie pasuje do rozpatrywanego zwierz�cia.
	void zaprzeczenie(); 
	/// Konstruktor bezargumentowy, ustawia pola obiektu b�d�ce wska�nikami na nullptr i inkrementuje licznik pyta� niskiej wagi, a tak�e dekrementuje licznik pyta� wysokiej wagi, wywo�any przez konstruktor Pytanie() klasy bazowej.
	///@see Pytanie()
	PytanieNW();
	/// Konstruktor wieloargumentowy, poza inkrementacj� licznika pyta� niskiej wagi i dekrementacj� licznika pyta� wysokiej wagi ustawia warto�ci p�l na podane w argumentach.
	///@param pPrev Wska�nik na poprzedni element listy
	///@param pNext Wska�nik na nast�pny element listy
	///@param TrescPytania String zawieraj�cy tre�� pytania
	///@param Podpowiedz String zawieraj�cy informacj�, �e dana cecha jest posiadana przez rozpatrywane zwierz�
	///@param Zaprzeczenie String zawieraj�cy informacj�, �e dana cecha nie jest posiadana przez rozpatrywane zwierz�
	PytanieNW(PytanieNW * pPrev, PytanieNW * pNext, string TrescPytania, string Podpowiedz, string Zaprzeczenie);
	/// Destruktor spina ze sob� poprzednik i nast�pnik usuwanego elementu, o ile jest to mo�liwe.
	~PytanieNW();
};

/**Obiekty tej klasy tworz� podwieszan� list� pyta�. Ka�y obiekt klasy Zwierzatko posiada tak� list�, co pozwala na szybkie sprawdzenie czy dane pytanie go dotyczy.*/
///@param Pole Zawarto�� pola
///@param p Wska�nik na pytanie wysokiej wagi
///@param pNW Wska�nik na pytanie niskiej wagi
///@param pNext Wska�nik na nast�pny element listy
///@see Zwierzatko
class PytaniaOsobiste {
private:
	Pytanie * p; ///< Wska�nik na pytanie wysokiej wagi
	PytanieNW * pNW; ///< Wska�nik na pytanie niskiej wagi
	PytaniaOsobiste *pNext; ///< Wska�nik na nast�pny element listy
public:
	/**Metoda pobiera wska�nik na pytanie wysokiej wagi*/
	///@return Pobrany wska�nik
	Pytanie * PobierzWsk();
	/**Metoda pobiera wska�nik na pytanie niskiej wagi*/
	///@return Pobrany wska�nik
	PytanieNW * PobierzWskNW();
	PytaniaOsobiste * PobierzNext();
	void SetNext(PytaniaOsobiste * next);
	/**Metoda wyszukuje w li�cie pyta� do��czonej do obiektu klasy "Encyklopedia" pytanie o podanych atrybutach, b�d� dodaje do niej nowe pytanie, a nast�pnie umieszcza wska�nik do owego pytania na podwieszanej li�cie pyta�.*/
	///@param TrescPytania String zawieraj�cy tre�� pytania
	///@param Podpowiedz String zawieraj�cy informacj�, �e dana cecha jest posiadana przez rozpatrywane zwierz�
	///@param Zaprzeczenie String zawieraj�cy informacj�, �e dana cecha nie jest posiadana przez rozpatrywane zwierz�
	///@param nazwa Nazwa przekazywanej przez referencj� Encyklopedii, kt�ra przechowuje informacje dotycz�ce pyta� i zwierz�t za�adowanych do gry
	///@see Encyklopedia::DodajPytanie()
	void DodajPytanie(string TrescPytania, string Podpowiedz, string Zaprzeczenie, Encyklopedia & nazwa);
	/**Sprawdza, czy zwierz�tko zawiera dane pytanie na swojej li�cie pyta� osobistych.*/
	///@param pyt Wska�nik na szukane pytanie wysokiej wagi
	///@return Je�eli pytanie znajduje si� na li�cie, metoda zwraca jako odpowiedz "1" - je�eli nie, zwraca "0"
	int SprawdzPytanie(Pytanie *pyt);
	/**Sprawdza, czy zwierz�tko zawiera dane pytanie na swojej li�cie pyta� osobistych.*/
	///@param pyt Wska�nik na szukane pytanie niskiej wagi
	///@return Je�eli pytanie znajduje si� na li�cie, metoda zwraca jako odpowiedz "1" - je�eli nie, zwraca "0"
	int SprawdzPytanieNW(PytanieNW *pyt);
	/**Konstruktor tej klasy automatycznie przypisuje zawartym w jej polach wska�nikom warto�� nullptr.*/
	PytaniaOsobiste();
	/**Destruktor wywo�uje usuni�cie nast�pnika obiektu, przez co wywo�anie usuni�cia g�owy listy powoduje rekurencyjne usuni�cie wszystkich zawartych w niej element�w.
	Ponadto, dekrementuje on liczniki wyst�pie� w pytaniach wskazywanych przez ka�dy z element�w. Je�eli usuwane zwierze by�o ostatnim, kt�re si� do nich odnosi�o, zostaj� one oznaczone jako przeznaczone do usuni�cia.*/
	~PytaniaOsobiste();
};

/**Obiekty tej klasy tworz� jednokierunkow� list� zwierz�t, ka�de ze swoj� nazw�, licznikiem wyst�pie� i wska�nikami na swoje pytania osobiste.*/
///@param Pole Zawarto�� pola
///@param LiczbaWystapien Je�eli zwierz�tko pojawi�o sie wczesniej, to nie pojawi sie po raz kolejny, dop�ki wszystkie nie wylosuj� si� cho� jeden raz
///@param nazwa Nazwa zwierz�cia
///@param pNext Wska�nik na na nast�pny element listy zwierz�t�k
///@param pHead Wska�nik na g�ow� listy pyta� osobistych
///@param LicznikZwierzatek
///@see PytaniaOsobiste
class Zwierzatko {
private:
	int LiczbaWystapien; ///< Wynosi "1" je�eli zwierz�tko zosta�o ju� wylosowane, w przeciwnym wypadku "0". Je�eli zwierz�tko pojawi�o si� wczesniej, to nie pojawi sie po raz kolejny, dop�ki wszystkie nie wylosuj� si� cho� jeden raz
	string nazwa; ///< Nazwa zwierz�cia
	Zwierzatko * pNext; ///< Wska�nik na nast�pny element listy zwierz�t
	PytaniaOsobiste * pHead; ///< Wska�nik na g�ow� listy pyta� osobistych
public:
	static int LicznikZwierzatek; ///< Licznik okre�laj�cy ��czn� liczb� dost�pnych w bazie zwierz�tek, kt�re nie wyst�pi�y jeszcze w grze
	PytaniaOsobiste * PobierzWsk();
	Zwierzatko * PobierzNext();
	int getLiczbaWystapien();
	void setNext(Zwierzatko * wsk);
	void setWsk(PytaniaOsobiste * w);
	/**Metoda dodaje do warto�ci pola "LicznikWystapien" liczb� podan� w argumencie.*/
	///@param value Liczba, kt�r� dodaje si� do warto�ci pola. Mo�e by� ujemna.
	void zwiekszLiczbeWystapien(int value);
	string GetNazwa();
	/**Konstruktor ustawia liczb� wyst�pie� zwierz�cia na "0".*/
	Zwierzatko();
	/**Konstruktor ustawia liczb� wyst�pie� zwierz�cia na "0", nadaje mu nazw� i podpina wska�nik na drzewo pyta� osobistych, a ponadto inkrementuje licznik zwierz�tek dost�pnych do wylosowania.*/
	///@param n Nazwa zwierz�cia
	///@param ws Wska�nik na g�ow� listy pyta� osobistych
	Zwierzatko(string n, PytaniaOsobiste * ws);
	/**Destruktor wywo�uje usuni�cie listy pyta� osobistych, a je�eli zwierz� nie wyst�pi�o do tej pory w grze, to dekrementuje licznik dost�pnych do wylosowania zwierz�t.*/
	///@see LicznikZwierzatek
	~Zwierzatko();
};

/**Klasa ta przechowuje w tablicach wska�nik�w wylosowane pytania niskiej wagi, kt�re u�ytkownik mo�e zada�, a tak�e te kt�re ju� zada�.
Jej funkcjonalno�� obejmuje wype�nianie, wy�wietlanie oraz opr�nianie tych tablic, a tak�e sprawdzanie pyta�.*/
///@param Pole Zawarto�� pola
///@param tab[10] Tablica zawiera wska�niki na pytania dost�pne do wybrania przez gracza
///@param zuzyte[10] Tablica zawiera wska�niki na pytania zadane uprzednio przez gracza. Parzyste kom�rki zawieraj� odpowiedzi potwierdzaj�ce, a nieparzyste - przecz�ce
class WyborPytaniaNW {
private:
	PytanieNW * tab[10]; ///< Tablica zawiera wska�niki na pytania dost�pne do wybrania przez gracza
	PytanieNW * zuzyte[10]; ///< Tablica zawiera wska�niki na pytania zadane uprzednio przez gracza. Parzyste kom�rki zawieraj� odpowiedzi potwierdzaj�ce, a nieparzyste - przecz�ce
public:
	/**Metoda wy�wietla zar�wno dost�pne pytania, jak i te zu�yte w obecnej rundzie.*/
	///@see WyswietlZuzyte()
	void WyswietlListe();
	/**Metoda wy�wietla wy��cznie pytania zu�yte w tej rundzie.*/
	void WyswietlZuzyte();
	/**Metoda sprawdza, czy pytanie zawarte w danym miejscu w tablicy "tab" opisuje rozpatrywane zwierz�, oraz umieszcza je w odpowiednim miejscu w tablicy zu�ytych pyta�.*/
	///@param i Numer miejsca w tablicy
	///@param Rozpatrywane Wska�nik na zwierz�tko, kt�re gracz pr�buje zgadn��
	///@return Zwraca "1" je�eli odpowied� brzmi "tak", "0" je�eli odpowied� brzmi "nie" i "-1", je�eli to miejsce w tablicy nie zawiera�o pytania
	int WybierzPytanie(int i, Zwierzatko * Rozpatrywane);
	/**Metoda ustawia na wybrane miejsce w tablicy "tab" podane pytanie.*/
	///@param i Numer miejsca w tablicy
	///@param p Wska�nik na pytanie, kt�ry ma zosta� umieszczony w tablicy
	void setTab(int i, PytanieNW * p);
	/**Czy�ci obie tablice i ustawia zu�ycie zawartych w nich pyta� na "0".*/
	void clearTabs();
	/**Metoda zwraca wska�nik na pytanie znajduj�cy si� w podanym miejscu w tablicy "tab".*/
	///@param i Numer miejsca w tablicy
	///return Wska�nik na pytanie pobrany z podanego miejsca w tablicy
	PytanieNW * GetTab(int i);
	/**Konstruktor ustawia wska�niki w tablicach na warto�� nullptr.*/
	WyborPytaniaNW();
	/**Funkcja zmienia kolor tekstu w konsoli w zale�no�ci od podanej warto�ci.*/
	///@param k Warto�� s�u��ca do zmiany koloru w konsoli. Przyk�adowo: dla k = 10 tekst przyjmuje kolor zielony, a dla k = 15 - bia�y
	void zmienKolor(int k);
};

/**Klasa ta przechowuje w tablicy wska�nik�w wylosowane pytania wysokiej wagi, kt�re u�ytkownik mo�e zada�.
Jej funkcjonalno�� obejmuje wype�nianie, wy�wietlanie oraz opr�nianie tych tablic, a tak�e sprawdzanie pyta�.*/
///@param Pole Zawarto�� pola
///@param tab[10] Tablica zawiera wska�niki na pytania dost�pne do wybrania przez gracza
class WyborPytaniaWW {
private:
	Pytanie * tab[10]; ///< Tablica zawiera wska�niki na pytania dost�pne do wybrania przez gracza
public:
	/**Metoda wy�wietla pytania dost�pne do zadania przez gracza.*/
	void WyswietlListe();
	/**Metoda sprawdza, czy pytanie zawarte w danym miejscu w tablicy opisuje rozpatrywane zwierz�.*/
	///@param i Numer miejsca w tablicy
	///@param Rozpatrywane Wska�nik na zwierz�tko kt�re gracz pr�buje zgadn��
	///@return Zwraca "1" je�eli odpowied� brzmi "tak", "0" je�eli odpowied� brzmi "nie" i "-1", je�eli to miejsce w tablicy nie zawiera�o pytania
	int WybierzPytanie(int i, Zwierzatko * Rozpatrywane);
	/**Metoda ustawia na wybrane miejsce w tablicy podane pytanie.*/
	///@param i Numer miejsca w tablicy
	///@param p Wska�nik na pytanie, kt�ry ma zosta� umieszczony w tablicy
	void setTab(int i, Pytanie * p);
	/**Czy�ci tablic� i ustawia zu�ycie zawartych w nich pyta� na "0".*/
	void clearTab();
	/**Konstruktor ustawia wska�niki w tablicy na warto�� nullptr.*/
	WyborPytaniaWW();
};