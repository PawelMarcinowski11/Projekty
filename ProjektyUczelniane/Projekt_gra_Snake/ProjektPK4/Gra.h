#pragma once

//Metody tej klasy odpowiedzialne s� za poszczeg�lne aspekty funkcjonowania gry
class gra {
private:
	int stan_gry;
	lista_graczy gracze;
	std::mutex dostep_do_bazy;
	std::mutex dostep_do_planszy;
	sf::Clock clk;
public:
	int logika(baza_obiektow &obiekty); //Metoda odpowiada za tworzenie w�y graczy, przemieszczanie ich oraz obs�ugiwanie kolizji pomi�dzy r�nymi obiektami
	int render(baza_obiektow &obiekty); //Metoda odpowiada za wy�wietlanie okna gry
	int sterowanie(baza_obiektow &obiekty); //Metoda odpowiada za odbieranie komend z klawiatury i przekazywaniu ich do obiekt�w graczy
	int obsluzAI(baza_obiektow &obiekty, ai_waz & a); //Metoda iteruje cyklicznie po graczach na li�cie, wyznaczaj�c na bie��co kierunek dla graczy sterowanych przez AI
	int ustawienia(baza_obiektow &obiekty); //Metoda wywo�uje okno dialogowe pozwalaj�ce ustali� liczb� graczy i ich atrybuty
};