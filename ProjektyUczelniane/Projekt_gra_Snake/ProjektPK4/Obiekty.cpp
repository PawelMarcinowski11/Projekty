#include "Header.h"

//Konstruktor obiektu "jedzenie" przypisuje obiektowi koordynaty losowo wybranego, wolnego miejsca na mapie
jedzenie::jedzenie(obiekt_w_bazie * pHead) {
	
	//Losujemy koordynaty x i y, zawieraj�ce si� w wymiarach planszy

	int x = (rand_engine() % (X - 1)) + 1;
	int y = (rand_engine() % (Y - 1)) + 1;


	//Nast�pnie tworzymy tablic� kolizji, na kt�r� mapujemy wszystkie obecne ju� w grze obiekty

	int tab[X + 1][Y + 1] = { brak };

	obiekt_w_bazie * wyliczanie;
	wyliczanie = pHead;
	while (wyliczanie) {
		wyliczanie->getO()->mapujKolizje(tab);
		wyliczanie = wyliczanie->getNext();
	}

	//Sprawdzamy, czy wylosowane przez nas pole jest wolne
	//Je�eli jest zaj�te, sprawdzamy kolejne - operacj� powtarzamy do momentu trafienia na dost�pne pole

	while (tab[x][y] != brak) {

		if (y == Y - 1) {
			y = 1;
			x++;
			if (x == X) {
				x = 1;
			}
		}
		else {
			y++;
		}
	}

	//Po znalezieniu wolnego pola, umieszczamy na nim nowo powsta�e jab�ko

	setX(x);
	setY(y);
}

waz::waz(int x_arg, int y_arg, int direction_arg, waz * pNext_arg) {
	setX(x_arg);
	setY(y_arg);
	direction = direction_arg;
	pNext = pNext_arg;
}

void waz::setDirection(int direction_arg) {
	direction = direction_arg;
}

//Metoda przesuwa segment w�a o jedno pole w danym kierunku
void waz::move_one() {
	switch (direction) {
	case lewo:
		setX(getX() - 1);
		break;
	case gora:
		setY(getY() - 1);
		break;
	case prawo:
		setX(getX() + 1);
		break;
	case dol:
		setY(getY() + 1);
		break;
	}
}

//Metoda przesuwa ca�ego w�a o jedno pole
void waz::move() {

	//Przy ruchu w�a "przemieszcza si�" tylko jego g�owa
	//Zamiast przesuwa� ka�dy element po kolei, tworz� nowy segment na pocz�tku w�a i usuwam segment na jego ko�cu
	//Efektem ubocznym jest samoistne rozci�gni�cie w�a 1-segmentowego do 2-segmentowego, jednak zdecydowa�em si� to zostawi�,
	//gdy� do poprawnego wy�wietlenia w�a potrzebne s� co najmniej 2 segmenty - g�owa i ogon.

	pNext = new waz(getX(), getY(), direction, pNext);
	move_one();
	waz* tmp = pNext;
	while (tmp->pNext && tmp->pNext->pNext) {
		tmp = tmp->pNext;
	}
	delete tmp->pNext;
	tmp->pNext = nullptr;
}

int obiekt_kolidujacy::getX() {
	return x;
}

int obiekt_kolidujacy::getY() {
	return y;
}

void obiekt_kolidujacy::setX(int x_arg) {
	x = x_arg;
}

void obiekt_kolidujacy::setY(int y_arg) {
	y = y_arg;
}

//Metoda wyd�u�a w�a o jeden segment, w kierunku w kt�rym jest w danym momencie zwr�cony
void waz::elongate() {
	pNext = new waz(getX(), getY(), direction, pNext);
	move_one();
}

obiekt_kolidujacy * obiekt_kolidujacy::getNext() {
	return nullptr;
}

waz * waz::getNext() {
	return pNext;
}

int obiekt_kolidujacy::sprawdzKolizje(int x_arg, int y_arg) {
	if (x == x_arg && y == y_arg) {
		return zderzenie;
	}
	else
		return brak;
}

void obiekt_kolidujacy::mapujKolizje(int tab[X + 1][Y + 1])
{
	tab[x][y] = zderzenie;
}

void obiekt_kolidujacy::setDirection(int)
{
}

int obiekt_kolidujacy::getDirection()
{
	return 0;
}

//Metoda sprawdza, czy kt�rykolwiek segment w�a koliduje z podanymi koordynatami
int waz::sprawdzKolizje(int x_arg, int y_arg) {
	if (getX() == x_arg && getY() == y_arg) {
		return zderzenie;
	}
	if (pNext)
		return pNext->sprawdzKolizje(x_arg, y_arg);
	else
		return brak;
}

//Metoda nak�ada informacj� o wszystkich segmentach w�a na map� kolizji
void waz::mapujKolizje(int tab[X + 1][Y + 1])
{
	tab[getX()][getY()] = zderzenie;
	if (pNext)
		pNext->mapujKolizje(tab);
}

//Metoda przekszta�ca wszystkie segmenty w�a w jedzenie
//Dzieje si� to w momencie zderzenia si� w�a
void waz::zmienWJedzenie(baza_obiektow& obiekty)
{
	jedzenie * nj = new jedzenie(obiekty.getHead());
	nj->setX(getX());
	nj->setY(getY());
	obiekty += nj;
	if (pNext)
		pNext->zmienWJedzenie(obiekty);
}

int jedzenie::sprawdzKolizje(int x_arg, int y_arg)
{
	if (getX() == x_arg && getY() == y_arg) {
		return posilek;
	}
	else
		return brak;
}

void jedzenie::mapujKolizje(int tab[X + 1][Y + 1])
{
	tab[getX()][getY()] = posilek;
}

obiekt_w_bazie::obiekt_w_bazie(obiekt_kolidujacy * o_arg, obiekt_w_bazie *pPrev_arg, obiekt_w_bazie *pNext_arg) {
	o = o_arg;
	pPrev = pPrev_arg;
	if (pPrev)
		pPrev->pNext = this;
	pNext = pNext_arg;
	if (pNext)
		pNext->pPrev = this;
}

obiekt_kolidujacy * obiekt_w_bazie::getO()
{
	return o;
}

obiekt_w_bazie * obiekt_w_bazie::getPrev()
{
	return pPrev;
}

//Funkcja zwraca koordynaty, na kt�re przeniesie si� w�� przy swoim obecnym po�o�eniu i zwrocie
coord waz::fakeMove() {
	coord ret;
	switch (direction) {
	case lewo:
		ret.x = (getX() - 1);
		ret.y = getY();
		break;
	case gora:
		ret.x = getX();
		ret.y = (getY() - 1);
		break;
	case prawo:
		ret.x = (getX() + 1);
		ret.y = getY();
		break;
	case dol:
		ret.x = getX();
		ret.y = (getY() + 1);
		break;
	}

	//Je�eli w�� mia�by przenie�� si� poza kraw�dzie mapy, wyrzucony zostanie wyj�tek

	if (ret.x == 0 || ret.y == 0 || ret.x == X || ret.y == Y) {
		exception_out_of_bound excp;
		throw excp;
	}
	return ret;
}

int waz::getDirection()
{
	return direction;
}

waz::~waz()
{
	if (pNext)
		delete pNext;
}

obiekt_w_bazie * obiekt_w_bazie::getNext()
{
	return pNext;
}

void obiekt_w_bazie::setNext(obiekt_w_bazie * arg)
{
	pNext = arg;
}

obiekt_w_bazie * baza_obiektow::getHead()
{
	return pHead;
}

//Przeci��ony operator dodawania dodaje dany obiekt do bazy
baza_obiektow & baza_obiektow::operator+=(obiekt_kolidujacy * arg)
{
	if (!pHead) {
		pHead = new obiekt_w_bazie(arg, pHead, nullptr);
		return *this;
	}
	obiekt_w_bazie * ptr = pHead;
	while (ptr->getNext())
		ptr = ptr->getNext();
	ptr->setNext(new obiekt_w_bazie(arg, ptr, nullptr));
	return *this;
}

//Przeci��ony operator odejmowania usuwa dany obiekt z bazy
baza_obiektow & baza_obiektow::operator-=(obiekt_kolidujacy * arg)
{
	if (arg) {
		obiekt_w_bazie * ptr = pHead;
		if (ptr->getO() == arg) {
			pHead = ptr->getNext();
			// RTTI
			if (waz * w = dynamic_cast<waz*>(ptr->getO())) {
				delete w;
			}
			else
				delete ptr->getO();

			delete ptr;
			return *this;
		}
		while (ptr->getNext()) {
			if (ptr->getNext()->getO() == arg) {

				//RTTI
				//Je�eli dany obiekt zawarty w bazie jest w�em, to nale�y usun�� wszystkie jego elementy, zamiast samej g�owy

				if (waz * w = dynamic_cast<waz*>(ptr->getNext()->getO())) {
					delete w;
				}
				else
					delete ptr->getNext()->getO();
				delete ptr->getNext();
				return *this;
			}
			ptr = ptr->getNext();
		}
	}
	return *this;
}

baza_obiektow::~baza_obiektow()
{
	while (pHead) {
		*this -= pHead->getO();
	}
}

obiekt_w_bazie::~obiekt_w_bazie()
{
	if (pPrev)
		pPrev->pNext = pNext;
	if (pNext)
		pNext->pPrev = pPrev;
}