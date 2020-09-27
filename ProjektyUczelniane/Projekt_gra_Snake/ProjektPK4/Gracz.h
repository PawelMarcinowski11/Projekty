#pragma once

//Do ka�dego gracza - komputerowego, b�d� rzeczywistego - przypisujemy obiekt poni�szej klasy
class gracz {
private:
	waz * pHead; //Wska�nik na g�ow� w�a, nullptr je�eli gracz straci� swojego w�a
	int kontroler; //Spos�b, w jaki gracz pobiera komendy ruchu
	int kierunek; //Bufor zawieraj�cy nast�pny kieruek, w kt�ry zwr�ci si� w��
	int punkty; //Liczba punkt�w zebrana przez gracza w tej rundzie
	std::wstring nazwa; //Nazwa gracza, kt�ra b�dzie si� wy�wietla� na tablicy wynik�w
	sf::Color kolor; //Kolor w�a gracza
public:
	gracz();
	gracz(int,sf::Color);
	waz * getHead();
	void setHead(waz*);
	sf::Color getKolor();
	void setKolor(sf::Color);
	int getKontroler();
	void setKontroler(int);
	void setDirection(int);	//Metoda sprawdza, czy ��dany kierunek nie wymaga zwrotu o 180 stopni. Je�eli nie - nowy kierunek zostaje zbuforowany do zmiennej w obiekcie
	void updateDirection(); //Metoda obraca g�ow� w�a w kierunku zawartym w buforze
	void setPunkty(int);
	void dodajPunkty(int);
	int getPunkty();
	void setNazwa(std::wstring);
	std::wstring getNazwa();
};

class element_listy_graczy {
private:
	element_listy_graczy * pNext;
	gracz * player;
public:
	element_listy_graczy();
	element_listy_graczy *getNext();
	void setNext(element_listy_graczy*);
	gracz * getPlayer();
	void setPlayer(gracz*);
	void rysujGraczy(sf::Sprite, sf::Sprite, sf::Sprite, sf::Sprite, sf::RenderWindow&); //Metoda przyjmuje jako argumenty tekstury i okno, w kt�rym b�d� wy�wietlane, po czym iteruje po li�cie w�y i rysuje je na ekranie
};

class lista_graczy {
private:
	element_listy_graczy * pHead;
public:
	lista_graczy();
	void dodajGracza(gracz *, baza_obiektow&); //Metoda wstawia do listy gracza przekazanego jako argument, a jego w�a umieszcza w bazie obiekt�w
	void usunGracza(gracz *, baza_obiektow&); //Metoda usuwa z listy gracza przekazanego jako argument, a jego w�� zostaje usuni�ty z bazy obiekt�w
	void dodajWeza(gracz *, waz *, baza_obiektow&); //Metoda znajduje na li�cie gracza przekazanego przez argument, po czym przydziela mu nowego w�a - i wstawia go do bazy obiekt�w
	void usunWeza(gracz *, baza_obiektow&);//Metoda znajduje na li�cie gracza przekazanego przez argument, po czym usuwa jego w�a - tak�e z bazy obiekt�w
	element_listy_graczy * getHead();
	~lista_graczy(); //Przed usuni�ciem listy, destruktor upewnia si�, �e razem z ni� skasowane zostan� wszystkie jej elementy
};