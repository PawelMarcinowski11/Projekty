/** @file */
#pragma once

/**Klasa ta zawiera wska�niki na g�owy list pyta� i zwierz�tek, obejmuje zadania zwi�zane z ich wype�nianiem, czyszczeniem i wybieraniem z nich losowych element�w.*/
///@param Pole Zawarto�� pola
///@param WysokaWaga Wska�nik na g�ow� listy pyta� wysokiej wagi
///@param NiskaWaga Wska�nik na g�ow� listy pyta� niskiej wagi
///@param ListaZwierzat Wska�nik na g�ow� listy zwierz�t
class Encyklopedia {
private:
	Pytanie * WysokaWaga; ///< Wska�nik na g�ow� listy pyta� wysokiej wagi
	PytanieNW * NiskaWaga; ///< Wska�nik na g�ow� listy pyta� niskiej wagi
	Zwierzatko * ListaZwierzat; ///< Wska�nik na g�ow� listy zwierz�t
public:
	/**Metoda wyszukuje w li�cie pyta� niskiej wagi pytanie o podanych atrybutach i inkrementuje jego licznik wyst�pie�, b�d� dodaje do niej nowe pytanie.*/
	///@param TrescPytania String zawieraj�cy tre�� pytania
	///@param Podpowiedz String zawieraj�cy informacj�, �e dana cecha jest posiadana przez rozpatrywane zwierz�
	///@param Zaprzeczenie String zawieraj�cy informacj�, �e dana cecha nie jest posiadana przez rozpatrywane zwierz�
	///@return Wska�nik do znalezionego b�d� dodanego pytania
	PytanieNW * DodajPytanieNW(string TrescPytania, string Podpowiedz, string Zaprzeczenie);
	/**Metoda wyszukuje w li�cie pyta� wysokiej wagi pytanie o podanej nazwie i inkrementuje jego licznik wyst�pie�, b�d� dodaje do niej nowe pytanie.*/
	///@param TrescPytania String zawieraj�cy tre�� pytania
	///@return Wska�nik do znalezionego b�d� dodanego pytania
	Pytanie * DodajPytanie(string TrescPytania);
	/**Metoda losuje pytanie niskiej wagi spo�r�d niezu�ytych jeszcze pyta�.*/
	///@return Wska�nik do wylosowanego pytania, b�d� nullptr je�eli pytania si� sko�czy�y
	PytanieNW * LosujPytanieNW();
	/**Metoda losuje pytanie wysokiej wagi spo�r�d niezu�ytych jeszcze pyta�.*/
	///@return Wska�nik do wylosowanego pytania, b�d� nullptr je�eli pytania si� sko�czy�y
	Pytanie * LosujPytanieWW();
	/**Metoda czy�ci z listy pyta� niskiej wagi te pytania, do kt�rych nie odwo�uje si� �adne zwierz�.*/
	void CzyscListeNW();
	/**Metoda czy�ci z listy pyta� wysokiej wagi te pytania, do kt�rych nie odwo�uje si� �adne zwierz�.*/
	void CzyscListeWW();
	/**Metoda pr�buje otworzy� plik o podanej w argumencie nazwie i wczyta� z niego informacje odno�nie zwierz�t i pyta� do odpowiadaj�cych im list.*/
	///@param NazwaPliku Nazwa pliku, z kt�rego wczytywane s� zwierz�tka i ich pytania
	///@return Metoda zwraca "1" je�eli plik szukany pod dan� nazw� istnieje i nie jest pusty. W przeciwnym wypadku zwraca "0".
	bool DodajZwierzatka(string NazwaPliku);
	/**Metoda pr�buje podpi�� zwierz�tko o danej nazwie do listy zwierz�t, o ile nie istnieje w niej ju� zwierz� o takiej nazwie.*/
	///@param wsk Wska�nik na podpinane zwierz�tko
	///@return Metoda zwraca "1" je�eli uda�o si� podpi�� zwierz�tko i "0", je�eli ju� wcze�niej by�o na li�cie.
	bool PodepnijZwierzatko(Zwierzatko * wsk);
	/**Metoda wyszukuje w li�cie zwierz�tko o podanej nazwie i je kasuje. Je�eli nie zosta�a podana �adna nazwa, skasowane zostaj� wszystkie zwierz�tka.*/
	///@param Nazwa Nazwa usuwanego zwierz�tka. Je�eli wynosi "", funkcja usunie ca�� list�.
	///@return Metoda zwraca "1" je�eli uda�o si� usun�� zwierz�tko i "0", je�eli nie znajduje si� ono na li�cie.
	bool WyrzucZwierzatko(string Nazwa);
	/**Konstruktor tej klasy automatycznie przypisuje zawartym w jej polach wska�nikom warto�� nullptr.*/
	Encyklopedia();
	/**Metoda w miar� mo�liwo�ci zape�nia tablic� pytaniami niskiej wagi i zwraca j�.*/
	///@return Wype�niona tablica
	WyborPytaniaNW Zapelnij();
	/**Metoda w miar� mo�liwo�ci zape�nia tablic� pytaniami wysokiej wagi w taki spos�b, aby jedno z nich mia�o odpowied� "tak" i zwraca j�.*/
	///@param Wybrane Zwierz�, kt�re gracz pr�buje w tej rundzie zgadn��
	///@return Wype�niona tablica
	WyborPytaniaWW ZapelnijWW(Zwierzatko * Wybrane);
	/**Metoda pobiera wska�nik na g�ow� list� zwierz�t*/
	///@return Pobrany wska�nik
	Zwierzatko * PobierzZwierzatko();
	/**Metoda losuje zwierz�tko spo�r�d tych, kt�re nie wyst�pi�y jeszcze w grze. Je�eli ka�de z nich wyst�pi�o ju� w grze, funkcja resetuje ich liczniki i losuje zwierz�tko z ca�ej puli.*/
	///@return Wska�nik do wylosowanego zwierz�tka
	Zwierzatko * LosujZwierzatko();
};