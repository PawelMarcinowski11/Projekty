/** @file */
#pragma once

/**Ta klasa obejmuje zagadnienia zwi�zane z liczeniem i przechowywaniem wynik�w, jakie gracz uzyskuje podczas rozgrywki.*/
///@param Pole Zawarto�� pola
///@param wynik Pole przechowuje obecny wynik gracza
///@param najwyzszy_wynik Pole przechowuje rekordowy wynik graczy
///@param seria Pole przechowuje liczb� meczy wygranych pod rz�d przez obecnego gracza
///@param najwyzsza_seria Pole przechowuje rekordow� d�ugo�� serii zwyci�stw
class Punktacja {
private:
	int wynik; ///< Pole przechowuje obecny wynik gracza
	int najwyzszy_wynik; ///< Pole przechowuje rekordowy wynik graczy
	int seria; ///< Pole przechowuje liczb� meczy wygranych pod rz�d przez obecnego gracza
	int najwyzsza_seria; ///< Pole przechowuje rekordow� d�ugo�� serii zwyci�stw
public:
	int GetWynik();
	int GetNajlepszyWynik();
	int GetSeria();
	int GetNajlepszaSeria();
	void SetNajlepszyWynik(int value);
	void SetNajlepszaSeria(int value);
	/**Metoda wczytuje rekordowy wynik i seri� z pliku "rekordy.txt".*/
	void WczytajZPliku();
	/**Metoda zapisuje rekordowy wynik i seri� do pliku "rekordy.txt".*/
	void ZapiszRekordDoPliku();
	/**Metoda dopisuje rezultat ostatniego meczu do pliku "historia.txt".*/
	void ZapiszMeczDoPliku();
	/**Metoda wczytuje histori� rozgrywek z pliku "historia.txt" i wypisuje j� na ekran, po czym czeka na interakcj� gracza aby wr�ci� do rozgrywki.*/
	void WypiszZPliku();
	///Operator przekazuje dane z obiektu do strumienia.
	friend ostream & operator << (ostream &wyjscie, Punktacja send);
	///Operator pobiera dane ze strumienia i przypisuje do obiektu.
	friend istream & operator >> (istream &wejscie, Punktacja &get);
	/**Operator podwy�sza warto�� pola "wynik" o warto�� podan� w argumencie.*/
	///@param val Sta�oprzecinkowa warto��, kt�ra jest dodawana do warto�ci pola
	Punktacja operator+=(int val);
	/**Operator podwy�sza warto�� pola "wynik" o warto�� podan� w argumencie.*/
	///@param val Sta�oprzecinkowa warto��, kt�ra jest dodawana do warto�ci pola
	Punktacja operator+(int val);
	/**Operator obni�a warto�� pola "wynik" o warto�� podan� w argumencie.*/
	///@param val Sta�oprzecinkowa warto��, kt�ra jest odejmowana od warto�ci pola
	Punktacja operator-=(int val);
	/**Operator obni�a warto�� pola "wynik" o warto�� podan� w argumencie.*/
	///@param val Sta�oprzecinkowa warto��, kt�ra jest odejmowana od warto�ci pola
	Punktacja operator-(int val);
	/**Operator przypisuje warto�ci z obiektu podanego w argumencie.*/
	///@param val Obiekt, kt�rego warto�ci zostaj� przypisane do obiektu po drugiej stronie operatora
	Punktacja operator=(const Punktacja & val);
	/**Operator przypisuje warto�ci wyniku i serii, pozostawiaj�c pozosta�e pola niezmienione.*/
	Punktacja operator()(int wwynik, int sseria);
	///@param wwynik Sta�oprzecinkowa warto��, kt�ra jest przypisywana do pola "wynik"
	///@param sseria Sta�oprzecinkowa warto��, kt�ra jest przypisywana do pola "seria"
	/**Operator zwi�ksza obecn� seri� zwyci�stw o podan� warto��, b�d� - je�eli argument nie zosta� podany - inkrementuje j�.*/
	///@param x Opcjonalny argument opisuj�cy warto��, o jak� ma zosta� zwi�kszona warto�� pola "seria"
	Punktacja& operator++(int x);
	///Konstruktor bezargumentowy, 
	Punktacja();
};