#pragma once

//Metody tej klasy odpowiedzialne s¹ za poszczególne aspekty funkcjonowania gry
class gra {
private:
	int stan_gry;
	lista_graczy gracze;
	std::mutex dostep_do_bazy;
	std::mutex dostep_do_planszy;
	sf::Clock clk;
public:
	int logika(baza_obiektow &obiekty); //Metoda odpowiada za tworzenie wê¿y graczy, przemieszczanie ich oraz obs³ugiwanie kolizji pomiêdzy ró¿nymi obiektami
	int render(baza_obiektow &obiekty); //Metoda odpowiada za wyœwietlanie okna gry
	int sterowanie(baza_obiektow &obiekty); //Metoda odpowiada za odbieranie komend z klawiatury i przekazywaniu ich do obiektów graczy
	int obsluzAI(baza_obiektow &obiekty, ai_waz & a); //Metoda iteruje cyklicznie po graczach na liœcie, wyznaczaj¹c na bie¿¹co kierunek dla graczy sterowanych przez AI
	int ustawienia(baza_obiektow &obiekty); //Metoda wywo³uje okno dialogowe pozwalaj¹ce ustaliæ liczbê graczy i ich atrybuty
};