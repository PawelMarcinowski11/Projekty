/** @file */


#ifndef MOVEMENT_HEADER
#define MOVEMENT_HEADER

/**Przesuwa kursor o podan� liczb� p�l, o ile jest to mo�liwe.
@param pozycja Obecna po�o�enie kursora wzd�u� pionu lub poziomu.
@param amount Liczba p�l o kt�re kursor ma zosta� przesuni�ty.
@param granica Kraw�d� pola gry, kt�rej kursor nie mo�e przekroczy�.
*/
void moveCursor(short * pozycja, int amount, short granica);

/**Przesuwa kursor o jedno pole w lewo, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pami�ci zawieraj�cego koordynaty kursora.
*/
void moveLeft(COORD * pozycja);

/**Przesuwa kursor o jedno pole w prawo, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pami�ci zawieraj�cego koordynaty kursora.
*/
void moveRight(COORD * pozycja);

/**Przesuwa kursor o jedno pole w g�r�, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pami�ci zawieraj�cego koordynaty kursora.
*/
void moveUp(COORD * pozycja);

/**Przesuwa kursor o jedno pole w d�, o ile nie jest na krawedzi planszy.
@param pozycja Adres miejsca w pami�ci zawieraj�cego koordynaty kursora.
*/
void moveDown(COORD * pozycja);

/** Funkcja sprawdza czy zosta�a wci�ni�ta strza�ka, po czym wywo�uje odpowiednie funkcje przesuwaj�ce kursor.
@param bufor Bufor, do kt�rego wczytywane s� znaki z wej�cia.
@param POS Adres miejsca w pami�ci zawieraj�cego koordynaty kursora.
*/
void przesuwanieKursora(char * bufor, COORD * POS);


#endif