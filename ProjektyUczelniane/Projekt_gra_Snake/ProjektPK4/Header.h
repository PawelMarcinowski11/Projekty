#pragma once

const int X = 48; //Szeroko�� mapy, wliczaj�c 1 pole ramki
const int Y = 25; //Wysoko�� mapy, wliczaj�c 1 pole ramki
const int SKALA = 30; //Wymiary pojedynczego pola w pixelach
const int FRAMETIME = 66; //Odst�p mi�dzy poszczeg�lnymi od�wie�eniami logiki gry
const int ROZMIAR_WEZA = 3; //Pocz�tkowy rozmiar w�a (w segmentach)

#include <SFML/Graphics.hpp>
#include <mutex>
#include "Windows.h"
#include "Obiekty.h"
#include "AI.h"
#include "Gracz.h"
#include "Exceptions.h"
#include "Sterowanie.h"
#include "Logika.h"
#include "Render.h"
#include "Gra.h"
#include "Ustawienia.h"
#include <map>
#include <iterator>
#include <Random>
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>
#include <string.h>
//#include <vld.h>


//Generator liczb losowych
static std::mt19937 rand_engine(std::chrono::high_resolution_clock::now().time_since_epoch().count());

//Kierunki zwrotu w�a
typedef enum { gora, prawo, dol, lewo };

//Typy interakcji mi�dzy obiektami
typedef enum { brak, zderzenie, posilek };

//Stany gry
typedef enum { trwa, przerwana, wylaczanie };

//Sposobby kontrolowania w�a
typedef enum { ai, wsad, strzalki };