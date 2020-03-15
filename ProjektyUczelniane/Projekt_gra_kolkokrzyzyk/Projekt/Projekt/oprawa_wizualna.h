/** @file */


#ifndef OPRAWA_WIZUALNA_HEADER
#define OPRAWA_WIZUALNA_HEADER

/** Funkcja zmniejsza kszta�t okna, aby odpowiada� rozmiarowi planszy do gry.*/
void dopasujRozmiar();

/** Funkcja rysuje plansz� do gry na podstawie tablicy pozycji k�ek i krzy�yk�w.
@param tab Tablica zawieraj�ca pozycje k�ek i krzy�yk�w na planszy.
@param POS_ZERO Pozycja, na kt�r� kursor wraca po narysowaniu planszy.
*/
void rysujPlansze(char tab[WYSOKOSC][SZEROKOSC], COORD POS_ZERO);

/** Funkcja wy�wietla podany tekst pod plansz�.
@param text Wy�wietlany ci�g znak�w.
@param POS Pozycja, na kt�r� wraca kursor po wy�wietleniu podanego napisu.
*/
void wyswietlPodSpodem(char * text, COORD POS);

/** Funkcja wy�wietlaj�ca podzi�kowanie po zako�czeniu gry.*/
void podziekowanie();

#endif