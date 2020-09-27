#pragma once

//Klasa wirtualna po kt�rej dziedzicz� r�ne algorytmy AI
//Korzystam z niej do zaimplementowania Strategii w projekcie
class ai_waz {
public:
	virtual int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru) = 0;
};

//AI znajduje drog� do najbli�szego jab�ka za pomoc� algorytmu Dijkstry
class ai_dijkstra : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};

//AI pr�buje dotrze� do najbli�szego jab�ka w linii prostej
class ai_primitive : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};

//AI porusza si� w losowym kierunku
class ai_random : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};



//Deklaracja metody zosta�a przeniesiona do pliku "Gra.h"
//int obsluzAI(baza_obiekt�w &obiekty, sf::Clock &clk, gra &gra, std::mutex &plansza, ai_waz & a);
