#pragma once

struct coord {
	int x;
	int y;
};

//Generyczny obiekt, mog¹cy zajmowaæ miejsce na planszy i kolidowaæ z innymi obiektami
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

//Element listy przechowuj¹cej obiekty z planszy
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

//Lista pozwalaj¹ca na manipulacjê obiektami w bazie
class baza_obiektow {
private:
	obiekt_w_bazie * pHead = nullptr;
public:
	obiekt_w_bazie * getHead();
	baza_obiektow & operator +=(obiekt_kolidujacy*); //Przeci¹¿ony operator dodawania dodaje dany obiekt do bazy
	baza_obiektow & operator -=(obiekt_kolidujacy*); //Przeci¹¿ony operator odejmowania usuwa dany obiekt z bazy
	~baza_obiektow();
};

//Obiekt pojawiaj¹cy siê w losowym miejscu na mapie
//Celem gry jest zbieranie tych obiektów, aby zdobyæ punkty i powiêkszyæ swojego wê¿a
class jedzenie : public obiekt_kolidujacy {
public:
	int sprawdzKolizje(int, int);
	void mapujKolizje(int[X + 1][Y + 1]);
	jedzenie(obiekt_w_bazie *); //Konstruktor przypisuje obiektowi koordynaty losowo wybranego, wolnego miejsca na mapie
};

//Obiekt reprezentuj¹cy segment wê¿a
//Mo¿e mieæ nastêpnika tej samej klasy co on sam
class waz : public obiekt_kolidujacy {
private:
	int direction;
	waz * pNext;
public:
	waz(int, int, int, waz *);
	void setDirection(int);
	void move();
	void move_one(); //Metoda przesuwa segment wê¿a o jedno pole w danym kierunku
	void elongate(); //Metoda wyd³u¿a wê¿a o jeden segment, w kierunku w którym jest w danym momencie zwrócony
	waz * getNext();
	int sprawdzKolizje(int, int); //Metoda sprawdza, czy którykolwiek segment wê¿a koliduje z podanymi koordynatami
	void mapujKolizje(int[X + 1][Y + 1]); //Metoda nak³ada informacjê o wszystkich segmentach wê¿a na mapê kolizji
	void zmienWJedzenie(baza_obiektow &); //Metoda przekszta³ca wszystkie segmenty wê¿a w jedzenie
	coord fakeMove(); //Funkcja zwraca koordynaty, na które przeniesie siê w¹¿ przy swoim obecnym po³o¿eniu i zwrocie
	int getDirection();
	~waz();
};