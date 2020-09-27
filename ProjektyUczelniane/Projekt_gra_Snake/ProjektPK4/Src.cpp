#include "Header.h"

int main() {

	//Inicjalizujê grê oraz bazê obiektów, w której przechowywane bêd¹ wyœwietlane na planszy obiekty

	baza_obiektow obiekty;
	gra gra;

	std::mutex m;
	std::mutex plansza;

	ai_dijkstra d;
	ai_primitive p;
	ai_random r;

	//Przed przyst¹pieniem do w³aœciwej gry, wywo³ujê okno dialogowe pozwalaj¹ce ustawiæ liczbê graczy i ich atrybuty

	gra.ustawienia(std::ref(obiekty));

	//Program wywo³uje cztery w¹tki dzia³aj¹ce równolegle, odpowiadaj¹ce za dzia³anie gry.
	//Dziêki temu, logika gry nie jest uzale¿niona od liczby klatek na sekundê generowanych przez funkcjê renderuj¹c¹,
	//a zbyt d³ugi czas podejmowania decyzji przez ai nie spowoduje przyciêcia rozgrywki.

	std::thread one(&gra::logika, std::ref(gra), std::ref(obiekty));
	std::thread two(&gra::render, std::ref(gra), std::ref(obiekty));
	std::thread three(&gra::sterowanie, std::ref(gra), std::ref(obiekty));
	std::thread four(&gra::obsluzAI, std::ref(gra), std::ref(obiekty), std::ref(d));
	one.join();
	two.join();
	three.join();
	four.join();
}