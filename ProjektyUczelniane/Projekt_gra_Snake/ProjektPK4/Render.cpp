#include "Header.h"

//Metoda odpowiada za wyœwietlanie okna gry
int gra::render(baza_obiektow &obiekty)
{

	//Wymiary okna s¹ uzale¿nione od liczby pól i wielkoœci pojedynczego pola

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

	//£adujê tekstury z plików

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

	//Tworzê sprite'y, z których tworzone bêd¹ obiekty wyœwietlane na planszy

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

	//£adujê czcionkê z pliku

	sf::Font f1;
	if (!f1.loadFromFile("segoepr.ttf"))
		return 0;

	//Przygotowujê tekst wyœwietlaj¹cy siê po zakoñczeniu meczu, pokazuj¹cy obecn¹ liczbê klatek na sekundê, oraz obecn¹ liczbê punktów ka¿dego z graczy

	std::wstring tekst_gameover = L"Zgin¹³eœ! Naciœnij spacjê, aby spróbowaæ ponownie";
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

		//Naciœniêcie klawisza "esc" lub przycisku w górnym prawym rogu ekranu powoduje wy³¹czanie siê gry

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				stan_gry = wylaczanie;
				window.close();
			}
		}

		window.clear();

		window.draw(ramka);

		//Je¿eli gra zosta³a zatrzymana, rysujemy czerwone t³o z tablic¹ wyników 

		if (stan_gry == przerwana) {
			czerwone_tlo.setFillColor(sf::Color::Red);
			czerwone_tlo.setSize(sf::Vector2f(X*SKALA, Y*SKALA));
			window.draw(czerwone_tlo);
		}

		sf::Time t = clk.getElapsedTime();

		//Wystêpuj¹ce w grze wê¿e s¹ animowane - ka¿de przebycie jednego pola zajmuje 4 klatki animacji
		//Z tego wzglêdu, rysowanie wê¿y zostanie wykonane za pomoc¹ ró¿nych tekstur, w zale¿noœci od czasu brakuj¹cego do przemieszczenia siê na nastêpne pole

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
			
			//Je¿eli tworzenie siê sceny trwa zbyt d³ugo, tekstury zostan¹ prze³adowane miêdzy klatkami, aby unikn¹æ niepoprawnego wyœwietlenia grafik
			//Informuj¹cy o tym komunikat zostaje wpisany na strumieñ cerr
			
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

			//Je¿eli scena wci¹¿ nie zd¹¿y³a utworzyæ siê na czas, wystawiamy kolejny komunikat zostaje wystawiony na strumieñ cerr, ale ju¿ nie dokonujemy prze³adowania

			if (anim_state != (t.asMilliseconds() * 4) / FRAMETIME)
				std::cerr << "Framerate too high to keep up\n";
		}

		//Je¿eli gra zosta³a przerwana, wyœwietlamy ekran z wynikami:

		if (stan_gry == przerwana) {

			//Parsowanie wyników wykonuje siê tylko raz na zakoñczenie meczu
			//Wykonanie parsowania ponownie jest bezcelowe, je¿eli wyniki pozostaj¹ bez zmian

			if (parsowanieWynikow.try_lock()) {

				tekst_gameover = L"\tKoniec gry!\n\tWyniki:";

				dostep_do_bazy.lock();

				//Zapisujê wyniki do multimapy, gdzie kluczem jest liczba punktów gracza, a atrybutem - jego nazwa

				std::multimap<int, std::wstring, std::greater<int>> wyniki;

				element_listy_graczy * lis = gracze.getHead();

				for (int i = 0; lis; i++) {
					wyniki.insert(std::make_pair(lis->getPlayer()->getPunkty(), lis->getPlayer()->getNazwa()));
					lis = lis->getNext();
				}

				dostep_do_bazy.unlock();

				//Przerabiam wartoœci zawarte w multimapie na ci¹gi znaków, które zostan¹ wyœwietlone na ekranie

				for (auto iter = wyniki.begin(); iter != wyniki.end(); iter++) {
					tekst_gameover.append(L"\n\t" + iter->second + L": " + std::to_wstring(iter->first));
				}

				tekst_gameover.append(L"\nNaciœnij spacjê, aby spróbowaæ ponownie!");

				gameover.setString(tekst_gameover);
				gameover.setPosition((window.getSize().x - gameover.getLocalBounds().left - gameover.getLocalBounds().width) / 2, (window.getSize().y - gameover.getLocalBounds().top - gameover.getLocalBounds().height) / 2);
			}

			//Wyœwietlam na ekranie podsumowanie gry

			window.draw(gameover);
		}
		else {
			parsowanieWynikow.try_lock();
			parsowanieWynikow.unlock();
			dostep_do_bazy.lock();

			//Rysujemy wê¿e wszystkich graczy

			gracze.getHead()->rysujGraczy(snake_head, snake_body, snake_curve, snake_tail, window);
			
			//Rysujemy wszystkie jab³ka z bazy obiektów
			//Aby odró¿niæ je od pozosta³ych obiektów, korzystamy z RTTI
			
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

		//Wyliczam liczbê aktualnych klatek na sekundê

		sf::Time frametime = fps_counter.getElapsedTime();
		fps_counter.restart();
		fps.setString("FPS: " + std::to_string((int)(1 / frametime.asSeconds())));
		window.draw(fps);

		element_listy_graczy * punktowany = gracze.getHead();

		std::wstring punktacja = L"";

		//W pasku u góry, wypisujê na bie¿¹co liczbê punktów ka¿dego z graczy

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