/** @file */


#ifndef MOVEMENT_HEADER
#define MOVEMENT_HEADER

/**Przesuwa kursor o podan¹ liczbê pól, o ile jest to mo¿liwe.
@param pozycja Obecna po³o¿enie kursora wzd³u¿ pionu lub poziomu.
@param amount Liczba pól o które kursor ma zostaæ przesuniêty.
@param granica KrawêdŸ pola gry, której kursor nie mo¿e przekroczyæ.
*/
void moveCursor(short * pozycja, int amount, short granica);

/**Przesuwa kursor o jedno pole w lewo, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pamiêci zawieraj¹cego koordynaty kursora.
*/
void moveLeft(COORD * pozycja);

/**Przesuwa kursor o jedno pole w prawo, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pamiêci zawieraj¹cego koordynaty kursora.
*/
void moveRight(COORD * pozycja);

/**Przesuwa kursor o jedno pole w górê, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pamiêci zawieraj¹cego koordynaty kursora.
*/
void moveUp(COORD * pozycja);

/**Przesuwa kursor o jedno pole w dó³, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pamiêci zawieraj¹cego koordynaty kursora.
*/
void moveDown(COORD * pozycja);

/** Funkcja sprawdza czy zosta³a wciœniêta strza³ka, po czym wywo³uje odpowiednie funkcje przesuwaj¹ce kursor.
@param bufor Bufor, do którego wczytywane s¹ znaki z wejœcia.
@param POS Adres miejsca w pamiêci zawieraj¹cego koordynaty kursora.
*/
void przesuwanieKursora(char * bufor, COORD * POS);


#endif