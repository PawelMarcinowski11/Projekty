/** @file */
#pragma once

/**Klasa obejmuj¹ca wyœwietlanie powitania przed w³aœciwym przyst¹pieniem do gry.*/
class Wstep {
public:
	void wyswietlWstep(); /**Funkcja wyœwietla wstêp do gry, po czym czeka a¿ u¿ytkownik wprowadzi dowolny znak aby przejœæ do nastêpnego etapu.*/
};

/**Klasa odpowiedzialna za funkcjonowanie w³aœciwej czêœci rozgrywki.*/
///@param Pole Zawartoœæ pola
///@param baza WskaŸnik na obiekt przechowuj¹cy listy pytañ i zwierz¹t
class Gra {
private:
	Encyklopedia * baza; ///< WskaŸnik na obiekt przechowuj¹cy listy pytañ i zwierz¹t
public:
	/**Metoda tworzy nowy obiekt klasy "encyklopedia".*/
	void inicjalizujBaze();
	/**Metoda usuwaj¹ca obiekt znajduj¹cy siê pod wskaŸnikiem "baza".*/
	///@see inicjalizujBaze()
	void deinicjalizujBaze();
	Encyklopedia * getBaza();
	/**Metoda tworzy pêtlê w której gracz mo¿e rozegraæ dowoln¹ liczbê rund, dopóki nie wyjdzie z niej za pomoc¹ klawisza "esc".*/
	void loop();
};