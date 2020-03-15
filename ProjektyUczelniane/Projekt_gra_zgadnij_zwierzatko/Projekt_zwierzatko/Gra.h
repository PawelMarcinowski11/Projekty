/** @file */
#pragma once

/**Klasa obejmuj�ca wy�wietlanie powitania przed w�a�ciwym przyst�pieniem do gry.*/
class Wstep {
public:
	void wyswietlWstep(); /**Funkcja wy�wietla wst�p do gry, po czym czeka a� u�ytkownik wprowadzi dowolny znak aby przej�� do nast�pnego etapu.*/
};

/**Klasa odpowiedzialna za funkcjonowanie w�a�ciwej cz�ci rozgrywki.*/
///@param Pole Zawarto�� pola
///@param baza Wska�nik na obiekt przechowuj�cy listy pyta� i zwierz�t
class Gra {
private:
	Encyklopedia * baza; ///< Wska�nik na obiekt przechowuj�cy listy pyta� i zwierz�t
public:
	/**Metoda tworzy nowy obiekt klasy "encyklopedia".*/
	void inicjalizujBaze();
	/**Metoda usuwaj�ca obiekt znajduj�cy si� pod wska�nikiem "baza".*/
	///@see inicjalizujBaze()
	void deinicjalizujBaze();
	Encyklopedia * getBaza();
	/**Metoda tworzy p�tl� w kt�rej gracz mo�e rozegra� dowoln� liczb� rund, dop�ki nie wyjdzie z niej za pomoc� klawisza "esc".*/
	void loop();
};