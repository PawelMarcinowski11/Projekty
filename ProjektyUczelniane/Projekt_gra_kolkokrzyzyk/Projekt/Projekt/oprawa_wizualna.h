/** @file */


#ifndef OPRAWA_WIZUALNA_HEADER
#define OPRAWA_WIZUALNA_HEADER

/** Funkcja zmniejsza kszta³t okna, aby odpowiada³ rozmiarowi planszy do gry.*/
void dopasujRozmiar();

/** Funkcja rysuje planszê do gry na podstawie tablicy pozycji kó³ek i krzy¿yków.
@param tab Tablica zawieraj¹ca pozycje kó³ek i krzy¿yków na planszy.
@param POS_ZERO Pozycja, na któr¹ kursor wraca po narysowaniu planszy.
*/
void rysujPlansze(char tab[WYSOKOSC][SZEROKOSC], COORD POS_ZERO);

/** Funkcja wyœwietla podany tekst pod plansz¹.
@param text Wyœwietlany ci¹g znaków.
@param POS Pozycja, na któr¹ wraca kursor po wyœwietleniu podanego napisu.
*/
void wyswietlPodSpodem(char * text, COORD POS);

/** Funkcja wyœwietlaj¹ca podziêkowanie po zakoñczeniu gry.*/
void podziekowanie();

#endif