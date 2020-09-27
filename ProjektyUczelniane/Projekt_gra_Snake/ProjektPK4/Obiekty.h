#pragma once

struct coord {
	int x;
	int y;
};

//Generyczny obiekt, mog�cy zajmowa� miejsce na planszy i kolidowa� z innymi obiektami
class obiekt_kolidujacy {
private:
	int x;
	int y;
public:
	int getX();
	int getY();
	void setX(int);
	void setY(int);
	virtual int sprawdzKolizje(int, int);
	virtual void mapujKolizje(int[X+1][Y+1]);
	virtual void setDirection(int);
	virtual int getDirection();
	virtual obiekt_kolidujacy * getNext();
};

//Element listy przechowuj�cej obiekty z planszy
class obiekt_w_bazie {
private:
	obiekt_kolidujacy *o;
	obiekt_w_bazie *pPrev;
	obiekt_w_bazie *pNext;
public:
	obiekt_w_bazie(obiekt_kolidujacy*, obiekt_w_bazie*, obiekt_w_bazie*);
	void setO(obiekt_kolidujacy*);
	obiekt_kolidujacy * getO();
	obiekt_w_bazie * getPrev();
	obiekt_w_bazie * getNext();
	void setNext(obiekt_w_bazie *);
	~obiekt_w_bazie();
};

//Lista pozwalaj�ca na manipulacj� obiektami w bazie
class baza_obiektow {
private:
	obiekt_w_bazie * pHead = nullptr;
public:
	obiekt_w_bazie * getHead();
	baza_obiektow & operator +=(obiekt_kolidujacy*); //Przeci��ony operator dodawania dodaje dany obiekt do bazy
	baza_obiektow & operator -=(obiekt_kolidujacy*); //Przeci��ony operator odejmowania usuwa dany obiekt z bazy
	~baza_obiektow();
};

//Obiekt pojawiaj�cy si� w losowym miejscu na mapie
//Celem gry jest zbieranie tych obiekt�w, aby zdoby� punkty i powi�kszy� swojego w�a
class jedzenie : public obiekt_kolidujacy {
public:
	int sprawdzKolizje(int, int);
	void mapujKolizje(int[X + 1][Y + 1]);
	jedzenie(obiekt_w_bazie *); //Konstruktor przypisuje obiektowi koordynaty losowo wybranego, wolnego miejsca na mapie
};

//Obiekt reprezentuj�cy segment w�a
//Mo�e mie� nast�pnika tej samej klasy co on sam
class waz : public obiekt_kolidujacy {
private:
	int direction;
	waz * pNext;
public:
	waz(int, int, int, waz *);
	void setDirection(int);
	void move();
	void move_one(); //Metoda przesuwa segment w�a o jedno pole w danym kierunku
	void elongate(); //Metoda wyd�u�a w�a o jeden segment, w kierunku w kt�rym jest w danym momencie zwr�cony
	waz * getNext();
	int sprawdzKolizje(int, int); //Metoda sprawdza, czy kt�rykolwiek segment w�a koliduje z podanymi koordynatami
	void mapujKolizje(int[X + 1][Y + 1]); //Metoda nak�ada informacj� o wszystkich segmentach w�a na map� kolizji
	void zmienWJedzenie(baza_obiektow &); //Metoda przekszta�ca wszystkie segmenty w�a w jedzenie
	coord fakeMove(); //Funkcja zwraca koordynaty, na kt�re przeniesie si� w�� przy swoim obecnym po�o�eniu i zwrocie
	int getDirection();
	~waz();
};