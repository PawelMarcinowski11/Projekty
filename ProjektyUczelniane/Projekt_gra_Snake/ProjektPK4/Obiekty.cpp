#include "Header.h"

//Konstruktor obiektu "jedzenie" przypisuje obiektowi koordynaty losowo wybranego, wolnego miejsca na mapie
jedzenie::jedzenie(obiekt_w_bazie * pHead) {
	
	//Losujemy koordynaty x i y, zawieraj¹ce siê w wymiarach planszy

	int x = (rand_engine() % (X - 1)) + 1;
	int y = (rand_engine() % (Y - 1)) + 1;


	//Nastêpnie tworzymy tablicê kolizji, na któr¹ mapujemy wszystkie obecne ju¿ w grze obiekty

	int tab[X + 1][Y + 1] = { brak };

	obiekt_w_bazie * wyliczanie;
	wyliczanie = pHead;
	while (wyliczanie) {
		wyliczanie->getO()->mapujKolizje(tab);
		wyliczanie = wyliczanie->getNext();
	}

	//Sprawdzamy, czy wylosowane przez nas pole jest wolne
	//Je¿eli jest zajête, sprawdzamy kolejne - operacjê powtarzamy do momentu trafienia na dostêpne pole

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

	//Po znalezieniu wolnego pola, umieszczamy na nim nowo powsta³e jab³ko

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

//Metoda przesuwa segment wê¿a o jedno pole w danym kierunku
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

//Metoda przesuwa ca³ego wê¿a o jedno pole
void waz::move() {

	//Przy ruchu wê¿a "przemieszcza siê" tylko jego g³owa
	//Zamiast przesuwaæ ka¿dy element po kolei, tworzê nowy segment na pocz¹tku wê¿a i usuwam segment na jego koñcu
	//Efektem ubocznym jest samoistne rozci¹gniêcie wê¿a 1-segmentowego do 2-segmentowego, jednak zdecydowa³em siê to zostawiæ,
	//gdy¿ do poprawnego wyœwietlenia wê¿a potrzebne s¹ co najmniej 2 segmenty - g³owa i ogon.

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

//Metoda wyd³u¿a wê¿a o jeden segment, w kierunku w którym jest w danym momencie zwrócony
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

//Metoda sprawdza, czy którykolwiek segment wê¿a koliduje z podanymi koordynatami
int waz::sprawdzKolizje(int x_arg, int y_arg) {
	if (getX() == x_arg && getY() == y_arg) {
		return zderzenie;
	}
	if (pNext)
		return pNext->sprawdzKolizje(x_arg, y_arg);
	else
		return brak;
}

//Metoda nak³ada informacjê o wszystkich segmentach wê¿a na mapê kolizji
void waz::mapujKolizje(int tab[X + 1][Y + 1])
{
	tab[getX()][getY()] = zderzenie;
	if (pNext)
		pNext->mapujKolizje(tab);
}

//Metoda przekszta³ca wszystkie segmenty wê¿a w jedzenie
//Dzieje siê to w momencie zderzenia siê wê¿a
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

//Funkcja zwraca koordynaty, na które przeniesie siê w¹¿ przy swoim obecnym po³o¿eniu i zwrocie
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

	//Je¿eli w¹¿ mia³by przenieœæ siê poza krawêdzie mapy, wyrzucony zostanie wyj¹tek

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

//Przeci¹¿ony operator dodawania dodaje dany obiekt do bazy
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

//Przeci¹¿ony operator odejmowania usuwa dany obiekt z bazy
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
				//Je¿eli dany obiekt zawarty w bazie jest wê¿em, to nale¿y usun¹æ wszystkie jego elementy, zamiast samej g³owy

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