#include "Header.h"

//Metoda odpowiada za odbieranie komend z klawiatury i przekazywaniu ich do obiektów graczy
int gra::sterowanie(baza_obiektow &obiekty)
{
	while (stan_gry != wylaczanie) {

		//Czêstotliwoœæ sprawdzania klikniêæ jest ograniczona do 100000 razy na sekundê, aby nie obci¹¿aæ niepotrzebnie procesora

		std::this_thread::sleep_for(std::chrono::microseconds(10));
		element_listy_graczy * ruszajacy = gracze.getHead();

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {

			//Je¿eli klawisz "R" zostanie przytrzymany na oko³o 0.3 sekundy, gra zostanie zrestartowana

			std::this_thread::sleep_for(std::chrono::milliseconds(300));
			std::cerr << "kliknieto\n";
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
				std::cerr << "zrestartowano\n";
				stan_gry = przerwana;
			}
		}

		while (ruszajacy) {
			gracz * gracz_rusz = ruszajacy->getPlayer();

			//W zale¿noœci od wartoœci pola "kontroler", obiekt reaguje na ró¿ne klawisze

			if (ruszajacy->getPlayer()->getHead() && ruszajacy->getPlayer()->getKontroler() == wsad) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
					gracz_rusz->setDirection(gora);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
					gracz_rusz->setDirection(lewo);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
					gracz_rusz->setDirection(dol);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
					gracz_rusz->setDirection(prawo);
			}
			else if (ruszajacy->getPlayer()->getHead() && ruszajacy->getPlayer()->getKontroler() == strzalki) {
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
					gracz_rusz->setDirection(gora);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
					gracz_rusz->setDirection(lewo);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
					gracz_rusz->setDirection(dol);
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
					gracz_rusz->setDirection(prawo);
			}

			ruszajacy = ruszajacy->getNext();
		}

	}
	return 0;
}