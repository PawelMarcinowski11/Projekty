/** @file */
#pragma once

/**Ta klasa obejmuje zagadnienia zwi¹zane z liczeniem i przechowywaniem wyników, jakie gracz uzyskuje podczas rozgrywki.*/
///@param Pole Zawartoœæ pola
///@param wynik Pole przechowuje obecny wynik gracza
///@param najwyzszy_wynik Pole przechowuje rekordowy wynik graczy
///@param seria Pole przechowuje liczbê meczy wygranych pod rz¹d przez obecnego gracza
///@param najwyzsza_seria Pole przechowuje rekordow¹ d³ugoœæ serii zwyciêstw
class Punktacja {
private:
	int wynik; ///< Pole przechowuje obecny wynik gracza
	int najwyzszy_wynik; ///< Pole przechowuje rekordowy wynik graczy
	int seria; ///< Pole przechowuje liczbê meczy wygranych pod rz¹d przez obecnego gracza
	int najwyzsza_seria; ///< Pole przechowuje rekordow¹ d³ugoœæ serii zwyciêstw
public:
	int GetWynik();
	int GetNajlepszyWynik();
	int GetSeria();
	int GetNajlepszaSeria();
	void SetNajlepszyWynik(int value);
	void SetNajlepszaSeria(int value);
	/**Metoda wczytuje rekordowy wynik i seriê z pliku "rekordy.txt".*/
	void WczytajZPliku();
	/**Metoda zapisuje rekordowy wynik i seriê do pliku "rekordy.txt".*/
	void ZapiszRekordDoPliku();
	/**Metoda dopisuje rezultat ostatniego meczu do pliku "historia.txt".*/
	void ZapiszMeczDoPliku();
	/**Metoda wczytuje historiê rozgrywek z pliku "historia.txt" i wypisuje j¹ na ekran, po czym czeka na interakcjê gracza aby wróciæ do rozgrywki.*/
	void WypiszZPliku();
	///Operator przekazuje dane z obiektu do strumienia.
	friend ostream & operator << (ostream &wyjscie, Punktacja send);
	///Operator pobiera dane ze strumienia i przypisuje do obiektu.
	friend istream & operator >> (istream &wejscie, Punktacja &get);
	/**Operator podwy¿sza wartoœæ pola "wynik" o wartoœæ podan¹ w argumencie.*/
	///@param val Sta³oprzecinkowa wartoœæ, która jest dodawana do wartoœci pola
	Punktacja operator+=(int val);
	/**Operator podwy¿sza wartoœæ pola "wynik" o wartoœæ podan¹ w argumencie.*/
	///@param val Sta³oprzecinkowa wartoœæ, która jest dodawana do wartoœci pola
	Punktacja operator+(int val);
	/**Operator obni¿a wartoœæ pola "wynik" o wartoœæ podan¹ w argumencie.*/
	///@param val Sta³oprzecinkowa wartoœæ, która jest odejmowana od wartoœci pola
	Punktacja operator-=(int val);
	/**Operator obni¿a wartoœæ pola "wynik" o wartoœæ podan¹ w argumencie.*/
	///@param val Sta³oprzecinkowa wartoœæ, która jest odejmowana od wartoœci pola
	Punktacja operator-(int val);
	/**Operator przypisuje wartoœci z obiektu podanego w argumencie.*/
	///@param val Obiekt, którego wartoœci zostaj¹ przypisane do obiektu po drugiej stronie operatora
	Punktacja operator=(const Punktacja & val);
	/**Operator przypisuje wartoœci wyniku i serii, pozostawiaj¹c pozosta³e pola niezmienione.*/
	Punktacja operator()(int wwynik, int sseria);
	///@param wwynik Sta³oprzecinkowa wartoœæ, która jest przypisywana do pola "wynik"
	///@param sseria Sta³oprzecinkowa wartoœæ, która jest przypisywana do pola "seria"
	/**Operator zwiêksza obecn¹ seriê zwyciêstw o podan¹ wartoœæ, b¹dŸ - je¿eli argument nie zosta³ podany - inkrementuje j¹.*/
	///@param x Opcjonalny argument opisuj¹cy wartoœæ, o jak¹ ma zostaæ zwiêkszona wartoœæ pola "seria"
	Punktacja& operator++(int x);
	///Konstruktor bezargumentowy, 
	Punktacja();
};