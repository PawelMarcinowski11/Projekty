#pragma once

//Do ka¿dego gracza - komputerowego, b¹dŸ rzeczywistego - przypisujemy obiekt poni¿szej klasy
class gracz {
private:
	waz * pHead; //WskaŸnik na g³owê wê¿a, nullptr je¿eli gracz straci³ swojego wê¿a
	int kontroler; //Sposób, w jaki gracz pobiera komendy ruchu
	int kierunek; //Bufor zawieraj¹cy nastêpny kieruek, w który zwróci siê w¹¿
	int punkty; //Liczba punktów zebrana przez gracza w tej rundzie
	std::wstring nazwa; //Nazwa gracza, która bêdzie siê wyœwietlaæ na tablicy wyników
	sf::Color kolor; //Kolor wê¿a gracza
public:
	gracz();
	gracz(int,sf::Color);
	waz * getHead();
	void setHead(waz*);
	sf::Color getKolor();
	void setKolor(sf::Color);
	int getKontroler();
	void setKontroler(int);
	void setDirection(int);	//Metoda sprawdza, czy ¿¹dany kierunek nie wymaga zwrotu o 180 stopni. Je¿eli nie - nowy kierunek zostaje zbuforowany do zmiennej w obiekcie
	void updateDirection(); //Metoda obraca g³owê wê¿a w kierunku zawartym w buforze
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
	void rysujGraczy(sf::Sprite, sf::Sprite, sf::Sprite, sf::Sprite, sf::RenderWindow&); //Metoda przyjmuje jako argumenty tekstury i okno, w którym bêd¹ wyœwietlane, po czym iteruje po liœcie wê¿y i rysuje je na ekranie
};

class lista_graczy {
private:
	element_listy_graczy * pHead;
public:
	lista_graczy();
	void dodajGracza(gracz *, baza_obiektow&); //Metoda wstawia do listy gracza przekazanego jako argument, a jego wê¿a umieszcza w bazie obiektów
	void usunGracza(gracz *, baza_obiektow&); //Metoda usuwa z listy gracza przekazanego jako argument, a jego w¹¿ zostaje usuniêty z bazy obiektów
	void dodajWeza(gracz *, waz *, baza_obiektow&); //Metoda znajduje na liœcie gracza przekazanego przez argument, po czym przydziela mu nowego wê¿a - i wstawia go do bazy obiektów
	void usunWeza(gracz *, baza_obiektow&);//Metoda znajduje na liœcie gracza przekazanego przez argument, po czym usuwa jego wê¿a - tak¿e z bazy obiektów
	element_listy_graczy * getHead();
	~lista_graczy(); //Przed usuniêciem listy, destruktor upewnia siê, ¿e razem z ni¹ skasowane zostan¹ wszystkie jej elementy
};