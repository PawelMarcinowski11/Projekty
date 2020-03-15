/** @file */
#pragma once

using namespace std;

class Encyklopedia;

/**Obiekty tej klasy tworz¹ listê jednokierunkow¹ pytañ wysokiej wagi, dotycz¹cych nazwy zwierzêcia i wyœwietlanych dopiero w ostatnim etapie ka¿dej rundy.*/
///@param Pole Zawartoœæ pola
///@param pNext WskaŸnik na nastêpny element listy
///@param pPrev WskaŸnik na poprzedni element listy
///@param TrescPytania Treœæ zawartego w bazie pytania
///@param Zuzycie Wynosi 1 gdy pytanie zosta³o ju¿ wyœwietlone graczowi. Domyœlnie 0, resetuje siê po ka¿dej rundzie
///@param LiczbaWystapien Pole inkrementuje siê za ka¿dym razem, gdy nowe zwierzê odwo³uje siê do tego pytani. Gdy ¿adne zwierz¹tko siê do niego nie odwo³uje, zostaje ono oznaczone jako przeznaczone do usuniêcia z puli
///@param LicznikPytanNW Licznik okreœlaj¹cy ³¹czn¹ liczbê dostêpnych w bazie pytañ niskiej wagi, które nie s¹ zu¿yte ani przeznaczone do usuniêcia
///@param LicznikPytanWW Licznik okreœlaj¹cy ³¹czn¹ liczbê dostêpnych w bazie pytañ wysokiej wagi, które nie s¹ zu¿yte ani przeznaczone do usuniêcia
class Pytanie {
private:
	Pytanie * pNext; ///< WskaŸnik na nastêpny element listy
	Pytanie * pPrev; ///< WskaŸnik na poprzedni element listy
	string TrescPytania; ///< Treœæ zawartego w bazie pytania
	int Zuzycie; ///< Wynosi 1 gdy pytanie zosta³o ju¿ wyœwietlone graczowi. Domyœlnie 0, resetuje siê po ka¿dej rundzie
	int LiczbaWystapien; ///< Pole inkrementuje siê za ka¿dym razem, gdy nowe zwierzê odwo³uje siê do tego pytani. Gdy ¿adne zwierz¹tko siê do niego nie odwo³uje, zostaje ono oznaczone jako przeznaczone do usuniêcia z puli
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
	static int LicznikPytanNW; ///< Licznik okreœlaj¹cy ³¹czn¹ liczbê dostêpnych w bazie pytañ niskiej wagi, które nie s¹ zu¿yte ani przeznaczone do usuniêcia
	static int LicznikPytanWW; ///< Licznik okreœlaj¹cy ³¹czn¹ liczbê dostêpnych w bazie pytañ wysokiej wagi, które nie s¹ zu¿yte ani przeznaczone do usuniêcia
	friend ostream & operator << (ostream &wyjscie, const Pytanie *send);
	/// Konstruktor bezargumentowy, ustawia pola obiektu bêd¹ce wskaŸnikami na nullptr i inkrementuje licznik pytañ wysokiej wagi.
	Pytanie();
	/// Konstruktor wieloargumentowy, poza inkrementacj¹ licznika pytañ wysokiej wagi ustawia wartoœci pól na podane w argumentach.
	///@param pPrev WskaŸnik na poprzedni element listy.
	///@param pNext WskaŸnik na nastêpny element listy.
	///@param TrescPytania String zawieraj¹cy treœæ pytania.
	Pytanie(Pytanie * pPrev, Pytanie * pNext, string TrescPytania);
	/// Destruktor spina ze sob¹ poprzednik i nastêpnik usuwanego elementu, o ile jest to mo¿liwe.
	~Pytanie();
};

/**Obiekty tej klasy tworz¹ listê jednokierunkow¹ pytañ niskiej wagi, dotycz¹cych cech zwierzêcia i wyœwietlanych we wstêpnym etapie ka¿dej rundy.*/
///@param Pole Zawartoœæ pola
///@param pNext WskaŸnik na nastêpny element listy
///@param pPrev WskaŸnik na poprzedni element listy
///@param Podpowiedz Treœæ podpowiedzi (a tak¿e odpowiedzi), przeznaczona do wyœwietlenia u¿ytkownikowi
///@param Zaprzeczenie Treœæ zaprzeczenia, przeznaczona do wyœwietlenia u¿ytkownikowi
class PytanieNW : public Pytanie {
private:
	PytanieNW * pNext; ///< WskaŸnik na nastêpny element listy
	PytanieNW * pPrev; ///< WskaŸnik na poprzedni element listy
	string Podpowiedz; ///< Treœæ podpowiedzi (a tak¿e odpowiedzi), przeznaczona do wyœwietlenia u¿ytkownikowi
	string Zaprzeczenie; ///< Treœæ zaprzeczenia, przeznaczona do wyœwietlenia u¿ytkownikowi
public:
	PytanieNW * getNext();
	PytanieNW * getPrev();
	/// Metoda wypisuje na strumieñ cout potwierdzenie, ¿e ta cecha pasuje do rozpatrywanego zwierzêcia.
	void potwierdzenie(); 
	/// Metoda wypisuje na strumieñ cout zaprzeczenie, gdy¿ ta cecha nie pasuje do rozpatrywanego zwierzêcia.
	void zaprzeczenie(); 
	/// Konstruktor bezargumentowy, ustawia pola obiektu bêd¹ce wskaŸnikami na nullptr i inkrementuje licznik pytañ niskiej wagi, a tak¿e dekrementuje licznik pytañ wysokiej wagi, wywo³any przez konstruktor Pytanie() klasy bazowej.
	///@see Pytanie()
	PytanieNW();
	/// Konstruktor wieloargumentowy, poza inkrementacj¹ licznika pytañ niskiej wagi i dekrementacj¹ licznika pytañ wysokiej wagi ustawia wartoœci pól na podane w argumentach.
	///@param pPrev WskaŸnik na poprzedni element listy
	///@param pNext WskaŸnik na nastêpny element listy
	///@param TrescPytania String zawieraj¹cy treœæ pytania
	///@param Podpowiedz String zawieraj¹cy informacjê, ¿e dana cecha jest posiadana przez rozpatrywane zwierzê
	///@param Zaprzeczenie String zawieraj¹cy informacjê, ¿e dana cecha nie jest posiadana przez rozpatrywane zwierzê
	PytanieNW(PytanieNW * pPrev, PytanieNW * pNext, string TrescPytania, string Podpowiedz, string Zaprzeczenie);
	/// Destruktor spina ze sob¹ poprzednik i nastêpnik usuwanego elementu, o ile jest to mo¿liwe.
	~PytanieNW();
};

/**Obiekty tej klasy tworz¹ podwieszan¹ listê pytañ. Ka¿y obiekt klasy Zwierzatko posiada tak¹ listê, co pozwala na szybkie sprawdzenie czy dane pytanie go dotyczy.*/
///@param Pole Zawartoœæ pola
///@param p WskaŸnik na pytanie wysokiej wagi
///@param pNW WskaŸnik na pytanie niskiej wagi
///@param pNext WskaŸnik na nastêpny element listy
///@see Zwierzatko
class PytaniaOsobiste {
private:
	Pytanie * p; ///< WskaŸnik na pytanie wysokiej wagi
	PytanieNW * pNW; ///< WskaŸnik na pytanie niskiej wagi
	PytaniaOsobiste *pNext; ///< WskaŸnik na nastêpny element listy
public:
	/**Metoda pobiera wskaŸnik na pytanie wysokiej wagi*/
	///@return Pobrany wskaŸnik
	Pytanie * PobierzWsk();
	/**Metoda pobiera wskaŸnik na pytanie niskiej wagi*/
	///@return Pobrany wskaŸnik
	PytanieNW * PobierzWskNW();
	PytaniaOsobiste * PobierzNext();
	void SetNext(PytaniaOsobiste * next);
	/**Metoda wyszukuje w liœcie pytañ do³¹czonej do obiektu klasy "Encyklopedia" pytanie o podanych atrybutach, b¹dŸ dodaje do niej nowe pytanie, a nastêpnie umieszcza wskaŸnik do owego pytania na podwieszanej liœcie pytañ.*/
	///@param TrescPytania String zawieraj¹cy treœæ pytania
	///@param Podpowiedz String zawieraj¹cy informacjê, ¿e dana cecha jest posiadana przez rozpatrywane zwierzê
	///@param Zaprzeczenie String zawieraj¹cy informacjê, ¿e dana cecha nie jest posiadana przez rozpatrywane zwierzê
	///@param nazwa Nazwa przekazywanej przez referencjê Encyklopedii, która przechowuje informacje dotycz¹ce pytañ i zwierz¹t za³adowanych do gry
	///@see Encyklopedia::DodajPytanie()
	void DodajPytanie(string TrescPytania, string Podpowiedz, string Zaprzeczenie, Encyklopedia & nazwa);
	/**Sprawdza, czy zwierz¹tko zawiera dane pytanie na swojej liœcie pytañ osobistych.*/
	///@param pyt WskaŸnik na szukane pytanie wysokiej wagi
	///@return Je¿eli pytanie znajduje siê na liœcie, metoda zwraca jako odpowiedz "1" - je¿eli nie, zwraca "0"
	int SprawdzPytanie(Pytanie *pyt);
	/**Sprawdza, czy zwierz¹tko zawiera dane pytanie na swojej liœcie pytañ osobistych.*/
	///@param pyt WskaŸnik na szukane pytanie niskiej wagi
	///@return Je¿eli pytanie znajduje siê na liœcie, metoda zwraca jako odpowiedz "1" - je¿eli nie, zwraca "0"
	int SprawdzPytanieNW(PytanieNW *pyt);
	/**Konstruktor tej klasy automatycznie przypisuje zawartym w jej polach wskaŸnikom wartoœæ nullptr.*/
	PytaniaOsobiste();
	/**Destruktor wywo³uje usuniêcie nastêpnika obiektu, przez co wywo³anie usuniêcia g³owy listy powoduje rekurencyjne usuniêcie wszystkich zawartych w niej elementów.
	Ponadto, dekrementuje on liczniki wyst¹pieñ w pytaniach wskazywanych przez ka¿dy z elementów. Je¿eli usuwane zwierze by³o ostatnim, które siê do nich odnosi³o, zostaj¹ one oznaczone jako przeznaczone do usuniêcia.*/
	~PytaniaOsobiste();
};

/**Obiekty tej klasy tworz¹ jednokierunkow¹ listê zwierz¹t, ka¿de ze swoj¹ nazw¹, licznikiem wyst¹pieñ i wskaŸnikami na swoje pytania osobiste.*/
///@param Pole Zawartoœæ pola
///@param LiczbaWystapien Je¿eli zwierz¹tko pojawi³o sie wczesniej, to nie pojawi sie po raz kolejny, dopóki wszystkie nie wylosuj¹ siê choæ jeden raz
///@param nazwa Nazwa zwierzêcia
///@param pNext WskaŸnik na na nastêpny element listy zwierz¹têk
///@param pHead WskaŸnik na g³owê listy pytañ osobistych
///@param LicznikZwierzatek
///@see PytaniaOsobiste
class Zwierzatko {
private:
	int LiczbaWystapien; ///< Wynosi "1" je¿eli zwierz¹tko zosta³o ju¿ wylosowane, w przeciwnym wypadku "0". Je¿eli zwierz¹tko pojawi³o siê wczesniej, to nie pojawi sie po raz kolejny, dopóki wszystkie nie wylosuj¹ siê choæ jeden raz
	string nazwa; ///< Nazwa zwierzêcia
	Zwierzatko * pNext; ///< WskaŸnik na nastêpny element listy zwierz¹t
	PytaniaOsobiste * pHead; ///< WskaŸnik na g³owê listy pytañ osobistych
public:
	static int LicznikZwierzatek; ///< Licznik okreœlaj¹cy ³¹czn¹ liczbê dostêpnych w bazie zwierz¹tek, które nie wyst¹pi³y jeszcze w grze
	PytaniaOsobiste * PobierzWsk();
	Zwierzatko * PobierzNext();
	int getLiczbaWystapien();
	void setNext(Zwierzatko * wsk);
	void setWsk(PytaniaOsobiste * w);
	/**Metoda dodaje do wartoœci pola "LicznikWystapien" liczbê podan¹ w argumencie.*/
	///@param value Liczba, któr¹ dodaje siê do wartoœci pola. Mo¿e byæ ujemna.
	void zwiekszLiczbeWystapien(int value);
	string GetNazwa();
	/**Konstruktor ustawia liczbê wyst¹pieñ zwierzêcia na "0".*/
	Zwierzatko();
	/**Konstruktor ustawia liczbê wyst¹pieñ zwierzêcia na "0", nadaje mu nazwê i podpina wskaŸnik na drzewo pytañ osobistych, a ponadto inkrementuje licznik zwierz¹tek dostêpnych do wylosowania.*/
	///@param n Nazwa zwierzêcia
	///@param ws WskaŸnik na g³owê listy pytañ osobistych
	Zwierzatko(string n, PytaniaOsobiste * ws);
	/**Destruktor wywo³uje usuniêcie listy pytañ osobistych, a je¿eli zwierzê nie wyst¹pi³o do tej pory w grze, to dekrementuje licznik dostêpnych do wylosowania zwierz¹t.*/
	///@see LicznikZwierzatek
	~Zwierzatko();
};

/**Klasa ta przechowuje w tablicach wskaŸników wylosowane pytania niskiej wagi, które u¿ytkownik mo¿e zadaæ, a tak¿e te które ju¿ zada³.
Jej funkcjonalnoœæ obejmuje wype³nianie, wyœwietlanie oraz opró¿nianie tych tablic, a tak¿e sprawdzanie pytañ.*/
///@param Pole Zawartoœæ pola
///@param tab[10] Tablica zawiera wskaŸniki na pytania dostêpne do wybrania przez gracza
///@param zuzyte[10] Tablica zawiera wskaŸniki na pytania zadane uprzednio przez gracza. Parzyste komórki zawieraj¹ odpowiedzi potwierdzaj¹ce, a nieparzyste - przecz¹ce
class WyborPytaniaNW {
private:
	PytanieNW * tab[10]; ///< Tablica zawiera wskaŸniki na pytania dostêpne do wybrania przez gracza
	PytanieNW * zuzyte[10]; ///< Tablica zawiera wskaŸniki na pytania zadane uprzednio przez gracza. Parzyste komórki zawieraj¹ odpowiedzi potwierdzaj¹ce, a nieparzyste - przecz¹ce
public:
	/**Metoda wyœwietla zarówno dostêpne pytania, jak i te zu¿yte w obecnej rundzie.*/
	///@see WyswietlZuzyte()
	void WyswietlListe();
	/**Metoda wyœwietla wy³¹cznie pytania zu¿yte w tej rundzie.*/
	void WyswietlZuzyte();
	/**Metoda sprawdza, czy pytanie zawarte w danym miejscu w tablicy "tab" opisuje rozpatrywane zwierzê, oraz umieszcza je w odpowiednim miejscu w tablicy zu¿ytych pytañ.*/
	///@param i Numer miejsca w tablicy
	///@param Rozpatrywane WskaŸnik na zwierz¹tko, które gracz próbuje zgadn¹æ
	///@return Zwraca "1" je¿eli odpowiedŸ brzmi "tak", "0" je¿eli odpowiedŸ brzmi "nie" i "-1", je¿eli to miejsce w tablicy nie zawiera³o pytania
	int WybierzPytanie(int i, Zwierzatko * Rozpatrywane);
	/**Metoda ustawia na wybrane miejsce w tablicy "tab" podane pytanie.*/
	///@param i Numer miejsca w tablicy
	///@param p WskaŸnik na pytanie, który ma zostaæ umieszczony w tablicy
	void setTab(int i, PytanieNW * p);
	/**Czyœci obie tablice i ustawia zu¿ycie zawartych w nich pytañ na "0".*/
	void clearTabs();
	/**Metoda zwraca wskaŸnik na pytanie znajduj¹cy siê w podanym miejscu w tablicy "tab".*/
	///@param i Numer miejsca w tablicy
	///return WskaŸnik na pytanie pobrany z podanego miejsca w tablicy
	PytanieNW * GetTab(int i);
	/**Konstruktor ustawia wskaŸniki w tablicach na wartoœæ nullptr.*/
	WyborPytaniaNW();
	/**Funkcja zmienia kolor tekstu w konsoli w zale¿noœci od podanej wartoœci.*/
	///@param k Wartoœæ s³u¿¹ca do zmiany koloru w konsoli. Przyk³adowo: dla k = 10 tekst przyjmuje kolor zielony, a dla k = 15 - bia³y
	void zmienKolor(int k);
};

/**Klasa ta przechowuje w tablicy wskaŸników wylosowane pytania wysokiej wagi, które u¿ytkownik mo¿e zadaæ.
Jej funkcjonalnoœæ obejmuje wype³nianie, wyœwietlanie oraz opró¿nianie tych tablic, a tak¿e sprawdzanie pytañ.*/
///@param Pole Zawartoœæ pola
///@param tab[10] Tablica zawiera wskaŸniki na pytania dostêpne do wybrania przez gracza
class WyborPytaniaWW {
private:
	Pytanie * tab[10]; ///< Tablica zawiera wskaŸniki na pytania dostêpne do wybrania przez gracza
public:
	/**Metoda wyœwietla pytania dostêpne do zadania przez gracza.*/
	void WyswietlListe();
	/**Metoda sprawdza, czy pytanie zawarte w danym miejscu w tablicy opisuje rozpatrywane zwierzê.*/
	///@param i Numer miejsca w tablicy
	///@param Rozpatrywane WskaŸnik na zwierz¹tko które gracz próbuje zgadn¹æ
	///@return Zwraca "1" je¿eli odpowiedŸ brzmi "tak", "0" je¿eli odpowiedŸ brzmi "nie" i "-1", je¿eli to miejsce w tablicy nie zawiera³o pytania
	int WybierzPytanie(int i, Zwierzatko * Rozpatrywane);
	/**Metoda ustawia na wybrane miejsce w tablicy podane pytanie.*/
	///@param i Numer miejsca w tablicy
	///@param p WskaŸnik na pytanie, który ma zostaæ umieszczony w tablicy
	void setTab(int i, Pytanie * p);
	/**Czyœci tablicê i ustawia zu¿ycie zawartych w nich pytañ na "0".*/
	void clearTab();
	/**Konstruktor ustawia wskaŸniki w tablicy na wartoœæ nullptr.*/
	WyborPytaniaWW();
};