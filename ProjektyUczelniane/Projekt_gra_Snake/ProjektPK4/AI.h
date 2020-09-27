#pragma once

//Klasa wirtualna po której dziedzicz¹ ró¿ne algorytmy AI
//Korzystam z niej do zaimplementowania Strategii w projekcie
class ai_waz {
public:
	virtual int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru) = 0;
};

//AI znajduje drogê do najbli¿szego jab³ka za pomoc¹ algorytmu Dijkstry
class ai_dijkstra : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};

//AI próbuje dotrzeæ do najbli¿szego jab³ka w linii prostej
class ai_primitive : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};

//AI porusza siê w losowym kierunku
class ai_random : public ai_waz {
public:
	int wybierzKierunek(int map[X + 1][Y + 1], int x, int y, int kieru);
};



//Deklaracja metody zosta³a przeniesiona do pliku "Gra.h"
//int obsluzAI(baza_obiektów &obiekty, sf::Clock &clk, gra &gra, std::mutex &plansza, ai_waz & a);
