/** @file */
#pragma once

/**Klasa ta zawiera wskaŸniki na g³owy list pytañ i zwierz¹tek, obejmuje zadania zwi¹zane z ich wype³nianiem, czyszczeniem i wybieraniem z nich losowych elementów.*/
///@param Pole Zawartoœæ pola
///@param WysokaWaga WskaŸnik na g³owê listy pytañ wysokiej wagi
///@param NiskaWaga WskaŸnik na g³owê listy pytañ niskiej wagi
///@param ListaZwierzat WskaŸnik na g³owê listy zwierz¹t
class Encyklopedia {
private:
	Pytanie * WysokaWaga; ///< WskaŸnik na g³owê listy pytañ wysokiej wagi
	PytanieNW * NiskaWaga; ///< WskaŸnik na g³owê listy pytañ niskiej wagi
	Zwierzatko * ListaZwierzat; ///< WskaŸnik na g³owê listy zwierz¹t
public:
	/**Metoda wyszukuje w liœcie pytañ niskiej wagi pytanie o podanych atrybutach i inkrementuje jego licznik wyst¹pieñ, b¹dŸ dodaje do niej nowe pytanie.*/
	///@param TrescPytania String zawieraj¹cy treœæ pytania
	///@param Podpowiedz String zawieraj¹cy informacjê, ¿e dana cecha jest posiadana przez rozpatrywane zwierzê
	///@param Zaprzeczenie String zawieraj¹cy informacjê, ¿e dana cecha nie jest posiadana przez rozpatrywane zwierzê
	///@return WskaŸnik do znalezionego b¹dŸ dodanego pytania
	PytanieNW * DodajPytanieNW(string TrescPytania, string Podpowiedz, string Zaprzeczenie);
	/**Metoda wyszukuje w liœcie pytañ wysokiej wagi pytanie o podanej nazwie i inkrementuje jego licznik wyst¹pieñ, b¹dŸ dodaje do niej nowe pytanie.*/
	///@param TrescPytania String zawieraj¹cy treœæ pytania
	///@return WskaŸnik do znalezionego b¹dŸ dodanego pytania
	Pytanie * DodajPytanie(string TrescPytania);
	/**Metoda losuje pytanie niskiej wagi spoœród niezu¿ytych jeszcze pytañ.*/
	///@return WskaŸnik do wylosowanego pytania, b¹dŸ nullptr je¿eli pytania siê skoñczy³y
	PytanieNW * LosujPytanieNW();
	/**Metoda losuje pytanie wysokiej wagi spoœród niezu¿ytych jeszcze pytañ.*/
	///@return WskaŸnik do wylosowanego pytania, b¹dŸ nullptr je¿eli pytania siê skoñczy³y
	Pytanie * LosujPytanieWW();
	/**Metoda czyœci z listy pytañ niskiej wagi te pytania, do których nie odwo³uje siê ¿adne zwierzê.*/
	void CzyscListeNW();
	/**Metoda czyœci z listy pytañ wysokiej wagi te pytania, do których nie odwo³uje siê ¿adne zwierzê.*/
	void CzyscListeWW();
	/**Metoda próbuje otworzyæ plik o podanej w argumencie nazwie i wczytaæ z niego informacje odnoœnie zwierz¹t i pytañ do odpowiadaj¹cych im list.*/
	///@param NazwaPliku Nazwa pliku, z którego wczytywane s¹ zwierz¹tka i ich pytania
	///@return Metoda zwraca "1" je¿eli plik szukany pod dan¹ nazw¹ istnieje i nie jest pusty. W przeciwnym wypadku zwraca "0".
	bool DodajZwierzatka(string NazwaPliku);
	/**Metoda próbuje podpi¹æ zwierz¹tko o danej nazwie do listy zwierz¹t, o ile nie istnieje w niej ju¿ zwierzê o takiej nazwie.*/
	///@param wsk WskaŸnik na podpinane zwierz¹tko
	///@return Metoda zwraca "1" je¿eli uda³o siê podpi¹æ zwierz¹tko i "0", je¿eli ju¿ wczeœniej by³o na liœcie.
	bool PodepnijZwierzatko(Zwierzatko * wsk);
	/**Metoda wyszukuje w liœcie zwierz¹tko o podanej nazwie i je kasuje. Je¿eli nie zosta³a podana ¿adna nazwa, skasowane zostaj¹ wszystkie zwierz¹tka.*/
	///@param Nazwa Nazwa usuwanego zwierz¹tka. Je¿eli wynosi "", funkcja usunie ca³¹ listê.
	///@return Metoda zwraca "1" je¿eli uda³o siê usun¹æ zwierz¹tko i "0", je¿eli nie znajduje siê ono na liœcie.
	bool WyrzucZwierzatko(string Nazwa);
	/**Konstruktor tej klasy automatycznie przypisuje zawartym w jej polach wskaŸnikom wartoœæ nullptr.*/
	Encyklopedia();
	/**Metoda w miarê mo¿liwoœci zape³nia tablicê pytaniami niskiej wagi i zwraca j¹.*/
	///@return Wype³niona tablica
	WyborPytaniaNW Zapelnij();
	/**Metoda w miarê mo¿liwoœci zape³nia tablicê pytaniami wysokiej wagi w taki sposób, aby jedno z nich mia³o odpowiedŸ "tak" i zwraca j¹.*/
	///@param Wybrane Zwierzê, które gracz próbuje w tej rundzie zgadn¹æ
	///@return Wype³niona tablica
	WyborPytaniaWW ZapelnijWW(Zwierzatko * Wybrane);
	/**Metoda pobiera wskaŸnik na g³owê listê zwierz¹t*/
	///@return Pobrany wskaŸnik
	Zwierzatko * PobierzZwierzatko();
	/**Metoda losuje zwierz¹tko spoœród tych, które nie wyst¹pi³y jeszcze w grze. Je¿eli ka¿de z nich wyst¹pi³o ju¿ w grze, funkcja resetuje ich liczniki i losuje zwierz¹tko z ca³ej puli.*/
	///@return WskaŸnik do wylosowanego zwierz¹tka
	Zwierzatko * LosujZwierzatko();
};