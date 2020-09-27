#include "Header.h"


gracz::gracz()
{
	kontroler = ai;
	kierunek = prawo;
	pHead = nullptr;
	kolor = sf::Color::White;
	punkty = 0;
	nazwa = L"";
}

gracz::gracz(int kontroler_arg, sf::Color kolor_arg)
{
	kontroler = kontroler_arg;
	kolor = kolor_arg;
}

waz * gracz::getHead()
{
	return pHead;
}

void gracz::setHead(waz *nowy)
{
	pHead = nowy;
}

sf::Color gracz::getKolor()
{
	return kolor;
}

void gracz::setKolor(sf::Color k)
{
	kolor = k;
}

int gracz::getKontroler()
{
	return kontroler;
}

void gracz::setKontroler(int arg)
{
	kontroler = arg;
}

//Metoda sprawdza, czy ¿¹dany kierunek nie wymaga zwrotu o 180 stopni. Je¿eli nie - nowy kierunek zostaje zbuforowany do zmiennej w obiekcie
void gracz::setDirection(int direction_arg) {
	if (this->getHead() && this->getHead()->getDirection() - direction_arg != 2 && this->getHead()->getDirection() - direction_arg != -2) //Nie mo¿na zmieniæ kierunku o 180 stopni, tj z lewej na praw¹, b¹dŸ z góry na dó³
		kierunek = direction_arg;
}

//Metoda obraca g³owê wê¿a w kierunku zawartym w buforze
void gracz::updateDirection()
{
	this->getHead()->setDirection(kierunek);
}

void gracz::setPunkty(int arg)
{
	punkty = arg;
}

void gracz::dodajPunkty(int arg)
{
	punkty += arg;
}

int gracz::getPunkty()
{
	return punkty;
}

void gracz::setNazwa(std::wstring arg)
{
	nazwa = arg;
}

std::wstring gracz::getNazwa()
{
	return nazwa;
}

element_listy_graczy::element_listy_graczy()
{
	pNext = nullptr;
	player = nullptr;
}

element_listy_graczy * element_listy_graczy::getNext()
{
	return pNext;
}

void element_listy_graczy::setNext(element_listy_graczy * nowy)
{
	pNext = nowy;
}

gracz * element_listy_graczy::getPlayer()
{
	return player;
}

void element_listy_graczy::setPlayer(gracz * nowy)
{
	player = nowy;
}

//Metoda przyjmuje jako argumenty tekstury i okno, w którym bêd¹ wyœwietlane, po czym iteruje po liœcie wê¿y i rysuje je na ekranie
void element_listy_graczy::rysujGraczy(sf::Sprite snake_head, sf::Sprite snake_body, sf::Sprite snake_curve, sf::Sprite snake_tail, sf::RenderWindow & window)
{
	element_listy_graczy * lis = this;
	while (lis) {
		obiekt_kolidujacy * temp = lis->player->getHead();

		//Pobieram kolor wê¿a ze zmiennej zawartej w obiekcie, po czym zabarwiam tekstury na dany kolor

		sf::Color k = lis->player->getKolor();
		snake_head.setColor(k);
		snake_body.setColor(k);
		snake_curve.setColor(k);
		snake_tail.setColor(k);


		if (temp) {

			//Najpierw rysujê g³owê wê¿a

			snake_head.setPosition(temp->getX()*SKALA, temp->getY()*SKALA);
			snake_head.setRotation(temp->getDirection() * 90);
			if (temp->getNext())
				temp = temp->getNext();
			window.draw(snake_head);

			//Nastêpnie, w zale¿noœci od przebytej przez wê¿a trasy, rysujê prosty fragment, b¹dŸ zakrêt wê¿a

			while (temp->getNext()) {
				int dif = temp->getNext()->getDirection() - temp->getDirection();

				//Odpowiednio obracam i przesuwam tekstury, aby by³y dopasowane na ka¿dym zagiêciu

				if (dif == 1 || dif == -3) {
					snake_curve.setPosition(temp->getX()*SKALA, temp->getY()*SKALA);
					snake_curve.setScale(SKALA / -10, SKALA / 10);
					snake_curve.setRotation(temp->getDirection() * 90);
					window.draw(snake_curve);
				}
				else if (dif == -1 || dif == 3) {
					snake_curve.setPosition(temp->getX()*SKALA, temp->getY()*SKALA);
					snake_curve.setScale(SKALA / 10, SKALA / 10);
					snake_curve.setRotation(temp->getDirection() * 90);
					window.draw(snake_curve);
				}
				else {
					snake_body.setPosition(temp->getX()*SKALA, temp->getY()*SKALA);
					snake_body.setRotation(temp->getDirection() * 90);
					window.draw(snake_body);
				}

				temp = temp->getNext();
			}

			//Je¿eli dany fragment nie ma nastêpnika, a nie jest g³ow¹ listy, to zostaje narysowany jako ogon wê¿a

			snake_tail.setPosition(temp->getX()*SKALA, temp->getY()*SKALA);
			snake_tail.setRotation(temp->getDirection() * 90);
			window.draw(snake_tail);
		}
		lis = lis->getNext();
	}
}

lista_graczy::lista_graczy()
{
	pHead = nullptr;
}

//Metoda wstawia do listy gracza przekazanego jako argument, a jego wê¿a umieszcza w bazie obiektów
void lista_graczy::dodajGracza(gracz * nowy, baza_obiektow & baza)
{
	if (!pHead) {
		pHead = new element_listy_graczy;
	}
	if (!pHead->getPlayer())
		pHead->setPlayer(nowy);
	else {
		element_listy_graczy * temp = pHead;
		while (temp->getNext()) {
			temp = temp->getNext();
		}
		temp->setNext(new element_listy_graczy);
		temp->getNext()->setPlayer(nowy);
	}
	if (nowy->getHead() != nullptr)
		baza += nowy->getHead();
}

//Metoda usuwa z listy gracza przekazanego jako argument, a jego w¹¿ zostaje usuniêty z bazy obiektów
void lista_graczy::usunGracza(gracz * do_usuniecia, baza_obiektow & baza)
{
	baza -= do_usuniecia->getHead();
	if (!pHead)
		return;
	element_listy_graczy * tmp = pHead;
	if (pHead->getPlayer() == do_usuniecia) {
		delete pHead->getPlayer();
		pHead = pHead->getNext();
		delete tmp;
	}
	else {
		while (tmp->getNext()) {
			if (tmp->getNext()->getPlayer() == do_usuniecia) {
				element_listy_graczy * tmp_del = tmp->getNext();
				tmp->setNext(tmp_del->getNext());
				delete tmp_del->getPlayer();
				delete tmp_del;
				return;
			}
			else
				tmp = tmp->getNext();
		}
	}
}

//Metoda znajduje na liœcie gracza przekazanego przez argument, po czym przydziela mu nowego wê¿a - i wstawia go do bazy obiektów
void lista_graczy::dodajWeza(gracz * do_dodania, waz * nowy, baza_obiektow & baza)
{
	element_listy_graczy * tmp = pHead;
	while (tmp) {
		if (tmp->getPlayer() == do_dodania) {
			baza += nowy;
			tmp->getPlayer()->setHead(nowy);
			tmp->getPlayer()->setDirection(nowy->getDirection());
			return;
		}
		tmp = tmp->getNext();
	}
}

//Metoda znajduje na liœcie gracza przekazanego przez argument, po czym usuwa jego wê¿a - tak¿e z bazy obiektów
void lista_graczy::usunWeza(gracz * do_usuniecia, baza_obiektow & baza)
{
	element_listy_graczy * tmp = pHead;
	while (tmp) {
		if (tmp->getPlayer() == do_usuniecia) {
			baza -= tmp->getPlayer()->getHead();
			tmp->getPlayer()->setHead(nullptr);
			return;
		}
		tmp = tmp->getNext();
	}
}

element_listy_graczy * lista_graczy::getHead()
{
	return pHead;
}

//Przed usuniêciem listy, destruktor upewnia siê, ¿e razem z ni¹ skasowane zostan¹ wszystkie jej elementy
lista_graczy::~lista_graczy()
{
	for (element_listy_graczy * temp = pHead; temp; temp = pHead) {
		pHead = pHead->getNext();
		delete temp->getPlayer();
		delete temp;
	}
}
