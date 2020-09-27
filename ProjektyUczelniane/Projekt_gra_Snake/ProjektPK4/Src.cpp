#include "Header.h"

int main() {

	//Inicjalizuj� gr� oraz baz� obiekt�w, w kt�rej przechowywane b�d� wy�wietlane na planszy obiekty

	baza_obiektow obiekty;
	gra gra;

	std::mutex m;
	std::mutex plansza;

	ai_dijkstra d;
	ai_primitive p;
	ai_random r;

	//Przed przyst�pieniem do w�a�ciwej gry, wywo�uj� okno dialogowe pozwalaj�ce ustawi� liczb� graczy i ich atrybuty

	gra.ustawienia(std::ref(obiekty));

	//Program wywo�uje cztery w�tki dzia�aj�ce r�wnolegle, odpowiadaj�ce za dzia�anie gry.
	//Dzi�ki temu, logika gry nie jest uzale�niona od liczby klatek na sekund� generowanych przez funkcj� renderuj�c�,
	//a zbyt d�ugi czas podejmowania decyzji przez ai nie spowoduje przyci�cia rozgrywki.

	std::thread one(&gra::logika, std::ref(gra), std::ref(obiekty));
	std::thread two(&gra::render, std::ref(gra), std::ref(obiekty));
	std::thread three(&gra::sterowanie, std::ref(gra), std::ref(obiekty));
	std::thread four(&gra::obsluzAI, std::ref(gra), std::ref(obiekty), std::ref(d));
	one.join();
	two.join();
	three.join();
	four.join();
}