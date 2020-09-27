#include "Header.h"

//Metoda odpowiada za wy�wietlanie okna gry
int gra::render(baza_obiektow &obiekty)
{

	//Wymiary okna s� uzale�nione od liczby p�l i wielko�ci pojedynczego pola

	sf::RenderWindow window(sf::VideoMode(X * SKALA, Y * SKALA), "SNAKE");
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(0);

	sf::RectangleShape czerwone_tlo(sf::Vector2f(SKALA, SKALA));
	czerwone_tlo.setFillColor(sf::Color::Magenta);
	sf::RectangleShape ramka(sf::Vector2f((X - 1) * SKALA, (Y - 1) * SKALA));
	ramka.setOutlineThickness(SKALA / 2);
	ramka.setFillColor(sf::Color::Transparent);
	ramka.setOutlineColor(sf::Color(255, 255, 127));
	ramka.setPosition(SKALA / 2, SKALA / 2);

	std::mutex parsowanieWynikow;

	//�aduj� tekstury z plik�w

	sf::Texture snake_h1;
	if (!snake_h1.loadFromFile("sprites/snake_h1.png"))
		return 0;
	sf::Texture snake_b1;
	if (!snake_b1.loadFromFile("sprites/snake_b1.png"))
		return 0;
	sf::Texture snake_c1;
	if (!snake_c1.loadFromFile("sprites/snake_c1.png"))
		return 0;
	sf::Texture snake_t1;
	if (!snake_t1.loadFromFile("sprites/snake_t1.png"))
		return 0;
	sf::Texture snake_h2;
	if (!snake_h2.loadFromFile("sprites/snake_h2.png"))
		return 0;
	sf::Texture snake_b2;
	if (!snake_b2.loadFromFile("sprites/snake_b2.png"))
		return 0;
	sf::Texture snake_c2;
	if (!snake_c2.loadFromFile("sprites/snake_c2.png"))
		return 0;
	sf::Texture snake_t2;
	if (!snake_t2.loadFromFile("sprites/snake_t2.png"))
		return 0;
	sf::Texture snake_h3;
	if (!snake_h3.loadFromFile("sprites/snake_h3.png"))
		return 0;
	sf::Texture snake_b3;
	if (!snake_b3.loadFromFile("sprites/snake_b3.png"))
		return 0;
	sf::Texture snake_c3;
	if (!snake_c3.loadFromFile("sprites/snake_c3.png"))
		return 0;
	sf::Texture snake_t3;
	if (!snake_t3.loadFromFile("sprites/snake_t3.png"))
		return 0;
	sf::Texture snake_h4;
	if (!snake_h4.loadFromFile("sprites/snake_h4.png"))
		return 0;
	sf::Texture snake_b4;
	if (!snake_b4.loadFromFile("sprites/snake_b4.png"))
		return 0;
	sf::Texture snake_c4;
	if (!snake_c4.loadFromFile("sprites/snake_c4.png"))
		return 0;
	sf::Texture snake_t4;
	if (!snake_t4.loadFromFile("sprites/snake_t4.png"))
		return 0;

	sf::Texture apple_tex;
	if (!apple_tex.loadFromFile("sprites/apple.png"))
		return 0;

	//Tworz� sprite'y, z kt�rych tworzone b�d� obiekty wy�wietlane na planszy

	sf::Sprite snake_head;
	snake_head.setTexture(snake_h1);
	snake_head.setOrigin(5, 5);
	snake_head.setScale(SKALA / 10, SKALA / 10);
	sf::Sprite snake_body;
	snake_body.setTexture(snake_b1);
	snake_body.setOrigin(5, 5);
	snake_body.setScale(SKALA / 10, SKALA / 10);
	sf::Sprite snake_curve;
	snake_curve.setTexture(snake_c1);
	snake_curve.setOrigin(5, 5);
	snake_curve.setScale(SKALA / 10, SKALA / 10);
	sf::Sprite snake_tail;
	snake_tail.setTexture(snake_t1);
	snake_tail.setOrigin(5, 5);
	snake_tail.setScale(SKALA / 10, SKALA / 10);
	sf::Sprite apple;
	apple.setTexture(apple_tex);
	apple.setOrigin(5, 5);
	apple.setScale(SKALA / 10, SKALA / 10);

	//�aduj� czcionk� z pliku

	sf::Font f1;
	if (!f1.loadFromFile("segoepr.ttf"))
		return 0;

	//Przygotowuj� tekst wy�wietlaj�cy si� po zako�czeniu meczu, pokazuj�cy obecn� liczb� klatek na sekund�, oraz obecn� liczb� punkt�w ka�dego z graczy

	std::wstring tekst_gameover = L"Zgin��e�! Naci�nij spacj�, aby spr�bowa� ponownie";
	sf::Text gameover;
	gameover.setFillColor(sf::Color::Black);
	gameover.setFont(f1);
	gameover.setString(tekst_gameover);
	gameover.setPosition(1 * SKALA, 3 * SKALA);

	sf::Text fps;
	fps.setFillColor(sf::Color::Cyan);
	fps.setOutlineColor(sf::Color::Blue);
	fps.setCharacterSize(SKALA*0.55);
	fps.setOutlineThickness(SKALA / 20);
	fps.setFont(f1);
	fps.setPosition(0, -SKALA * 0.1);

	sf::Text punkty;
	punkty.setFillColor(sf::Color::Cyan);
	punkty.setOutlineColor(sf::Color::Blue);
	punkty.setCharacterSize(SKALA*0.55);
	punkty.setOutlineThickness(SKALA / 20);
	punkty.setFont(f1);
	punkty.setPosition(3 * SKALA, -SKALA * 0.1);

	sf::Clock fps_counter;int anim_state = 0;

	while (window.isOpen())
	{

		sf::Event event;

		//Naci�ni�cie klawisza "esc" lub przycisku w g�rnym prawym rogu ekranu powoduje wy��czanie si� gry

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				stan_gry = wylaczanie;
				window.close();
			}
		}

		window.clear();

		window.draw(ramka);

		//Je�eli gra zosta�a zatrzymana, rysujemy czerwone t�o z tablic� wynik�w 

		if (stan_gry == przerwana) {
			czerwone_tlo.setFillColor(sf::Color::Red);
			czerwone_tlo.setSize(sf::Vector2f(X*SKALA, Y*SKALA));
			window.draw(czerwone_tlo);
		}

		sf::Time t = clk.getElapsedTime();

		//Wyst�puj�ce w grze w�e s� animowane - ka�de przebycie jednego pola zajmuje 4 klatki animacji
		//Z tego wzgl�du, rysowanie w�y zostanie wykonane za pomoc� r�nych tekstur, w zale�no�ci od czasu brakuj�cego do przemieszczenia si� na nast�pne pole

		anim_state = (t.asMilliseconds() * 4) / FRAMETIME;

		switch (anim_state) {
		case 0:
			snake_head.setTexture(snake_h1);
			snake_body.setTexture(snake_b1);
			snake_curve.setTexture(snake_c1);
			snake_tail.setTexture(snake_t1);
			break;
		case 1:
			snake_head.setTexture(snake_h2);
			snake_body.setTexture(snake_b2);
			snake_curve.setTexture(snake_c2);
			snake_tail.setTexture(snake_t2);
			break;
		case 2:
			snake_head.setTexture(snake_h3);
			snake_body.setTexture(snake_b3);
			snake_curve.setTexture(snake_c3);
			snake_tail.setTexture(snake_t3);
			break;
		case 3:
			snake_head.setTexture(snake_h4);
			snake_body.setTexture(snake_b4);
			snake_curve.setTexture(snake_c4);
			snake_tail.setTexture(snake_t4);
			break;
		}

		t = clk.getElapsedTime();

		if (anim_state != (t.asMilliseconds() * 4) / FRAMETIME) {
			
			//Je�eli tworzenie si� sceny trwa zbyt d�ugo, tekstury zostan� prze�adowane mi�dzy klatkami, aby unikn�� niepoprawnego wy�wietlenia grafik
			//Informuj�cy o tym komunikat zostaje wpisany na strumie� cerr
			
			std::cerr << "Frame reloaded\n";
			anim_state = (t.asMilliseconds() * 4) / FRAMETIME;

			switch (anim_state) {
			case 0:
				snake_head.setTexture(snake_h1);
				snake_body.setTexture(snake_b1);
				snake_curve.setTexture(snake_c1);
				snake_tail.setTexture(snake_t1);
				break;
			case 1:
				snake_head.setTexture(snake_h2);
				snake_body.setTexture(snake_b2);
				snake_curve.setTexture(snake_c2);
				snake_tail.setTexture(snake_t2);
				break;
			case 2:
				snake_head.setTexture(snake_h3);
				snake_body.setTexture(snake_b3);
				snake_curve.setTexture(snake_c3);
				snake_tail.setTexture(snake_t3);
				break;
			case 3:
				snake_head.setTexture(snake_h4);
				snake_body.setTexture(snake_b4);
				snake_curve.setTexture(snake_c4);
				snake_tail.setTexture(snake_t4);
				break;
			}
			t = clk.getElapsedTime();

			//Je�eli scena wci�� nie zd��y�a utworzy� si� na czas, wystawiamy kolejny komunikat zostaje wystawiony na strumie� cerr, ale ju� nie dokonujemy prze�adowania

			if (anim_state != (t.asMilliseconds() * 4) / FRAMETIME)
				std::cerr << "Framerate too high to keep up\n";
		}

		//Je�eli gra zosta�a przerwana, wy�wietlamy ekran z wynikami:

		if (stan_gry == przerwana) {

			//Parsowanie wynik�w wykonuje si� tylko raz na zako�czenie meczu
			//Wykonanie parsowania ponownie jest bezcelowe, je�eli wyniki pozostaj� bez zmian

			if (parsowanieWynikow.try_lock()) {

				tekst_gameover = L"\tKoniec gry!\n\tWyniki:";

				dostep_do_bazy.lock();

				//Zapisuj� wyniki do multimapy, gdzie kluczem jest liczba punkt�w gracza, a atrybutem - jego nazwa

				std::multimap<int, std::wstring, std::greater<int>> wyniki;

				element_listy_graczy * lis = gracze.getHead();

				for (int i = 0; lis; i++) {
					wyniki.insert(std::make_pair(lis->getPlayer()->getPunkty(), lis->getPlayer()->getNazwa()));
					lis = lis->getNext();
				}

				dostep_do_bazy.unlock();

				//Przerabiam warto�ci zawarte w multimapie na ci�gi znak�w, kt�re zostan� wy�wietlone na ekranie

				for (auto iter = wyniki.begin(); iter != wyniki.end(); iter++) {
					tekst_gameover.append(L"\n\t" + iter->second + L": " + std::to_wstring(iter->first));
				}

				tekst_gameover.append(L"\nNaci�nij spacj�, aby spr�bowa� ponownie!");

				gameover.setString(tekst_gameover);
				gameover.setPosition((window.getSize().x - gameover.getLocalBounds().left - gameover.getLocalBounds().width) / 2, (window.getSize().y - gameover.getLocalBounds().top - gameover.getLocalBounds().height) / 2);
			}

			//Wy�wietlam na ekranie podsumowanie gry

			window.draw(gameover);
		}
		else {
			parsowanieWynikow.try_lock();
			parsowanieWynikow.unlock();
			dostep_do_bazy.lock();

			//Rysujemy w�e wszystkich graczy

			gracze.getHead()->rysujGraczy(snake_head, snake_body, snake_curve, snake_tail, window);
			
			//Rysujemy wszystkie jab�ka z bazy obiekt�w
			//Aby odr�ni� je od pozosta�ych obiekt�w, korzystamy z RTTI
			
			obiekt_w_bazie * tmp = obiekty.getHead();
			while (tmp) {

				//RTTI
				if (jedzenie * j = dynamic_cast<jedzenie*>(tmp->getO())) {
					apple.setPosition(j->getX()*SKALA, j->getY()*SKALA);
					window.draw(apple);
				}
				tmp = tmp->getNext();
			}
			dostep_do_bazy.unlock();
		}

		//Wyliczam liczb� aktualnych klatek na sekund�

		sf::Time frametime = fps_counter.getElapsedTime();
		fps_counter.restart();
		fps.setString("FPS: " + std::to_string((int)(1 / frametime.asSeconds())));
		window.draw(fps);

		element_listy_graczy * punktowany = gracze.getHead();

		std::wstring punktacja = L"";

		//W pasku u g�ry, wypisuj� na bie��co liczb� punkt�w ka�dego z graczy

		dostep_do_bazy.lock();
		while (punktowany) {
			punktacja.append(L"   " + punktowany->getPlayer()->getNazwa() + L": " + std::to_wstring(punktowany->getPlayer()->getPunkty()));
			punktowany = punktowany->getNext();
		}
		dostep_do_bazy.unlock();

		punkty.setString(punktacja);
		window.draw(punkty);

		window.display();
	}

	parsowanieWynikow.try_lock();
	parsowanieWynikow.unlock();
	return 0;

}