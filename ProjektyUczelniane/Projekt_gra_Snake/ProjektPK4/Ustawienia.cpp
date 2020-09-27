#include "Header.h"

//Metoda wywo�uje okno dialogowe pozwalaj�ce ustali� liczb� graczy i ich atrybuty
int gra::ustawienia(baza_obiektow &obiekty) {

	//Okno ma wymiary 600x400, a zmienianie ich jest zablokowane

	sf::RenderWindow window(sf::VideoMode(600, 400), "Ustawienia", sf::Style::Titlebar | sf::Style::Close);
	window.setKeyRepeatEnabled(false);
	window.setVerticalSyncEnabled(true);
	window.setFramerateLimit(0);

	//Tworz� jednokolorowe t�o

	sf::RectangleShape bg(sf::Vector2f(600, 400));
	bg.setFillColor(sf::Color(191, 63, 191));

	//�aduj� tekstury z plik�w

	sf::Texture krzyzyk_tex;
	if (!krzyzyk_tex.loadFromFile("sprites/krzyzyk.png"))
		return 0;

	sf::Texture kontroler_tex[3];
	if (!kontroler_tex[0].loadFromFile("sprites/ai.png"))
		return 0;
	if (!kontroler_tex[1].loadFromFile("sprites/wsad.png"))
		return 0;
	if (!kontroler_tex[2].loadFromFile("sprites/arrows.png"))
		return 0;

	//Wczytuj� czcionk� z pliku

	sf::Font f1;
	if (!f1.loadFromFile("segoepr.ttf"))
		return 0;

	//Inicjuj� tablic� z przygotowanymi wcze�niej kolorami

	sf::Color tablicaKolorow[8] = { sf::Color::Red,
									sf::Color::Green,
									sf::Color::Yellow,
									sf::Color(255, 127, 0),
									sf::Color::Cyan,
									sf::Color::Magenta,
									sf::Color(255, 127, 127),
									sf::Color(255, 255, 255) };

	//Inicjalizuj� ci�gi znak�w, kt�re b�d� wy�wietlane w oknie

	std::wstring tekst_nagl = L"Wybierz ustawienia";
	std::wstring tekst_kolor = L"Zmie� kolor";
	std::wstring tekst_dodaj = L"Dodaj gracza";
	std::wstring tekst_sterowanie = L"Zmie� ustawienia sterowania";
	std::wstring tekst_gotowosc = L"Graj";

	//Inicjalizuj� zmienn� pomocnicz�, kt�ra pomaga mi dopasowa� po�o�enie element�w do liczby graczy

	int liczba_graczy = 0;

	//Ustalam po�o�enie, rozmiar i wygl�d poszczeg�lnych napis�w

	sf::Text nagl;
	nagl.setFillColor(sf::Color::White);
	nagl.setCharacterSize(35);
	nagl.setOutlineColor(sf::Color::Black);
	nagl.setOutlineThickness(2);
	nagl.setFont(f1);
	nagl.setString(tekst_nagl);
	sf::FloatRect wymiary = nagl.getLocalBounds();
	nagl.setPosition((600 - wymiary.left - wymiary.width) / 2, (50 - wymiary.top - wymiary.height) / 2); //Pobieram wymiary napisu, aby m�c go wy�rodkowa�


	sf::Text dodaj;
	dodaj.setFillColor(sf::Color::White);
	dodaj.setCharacterSize(25);
	dodaj.setOutlineColor(sf::Color::Black);
	dodaj.setOutlineThickness(2);
	dodaj.setFont(f1);
	dodaj.setString(tekst_dodaj);
	dodaj.setPosition((600 - dodaj.getLocalBounds().left - dodaj.getLocalBounds().width) / 2, 75 + (liczba_graczy * 35) - (dodaj.getLocalBounds().top + dodaj.getLocalBounds().height) / 2); //Pobieram wymiary napisu, aby m�c go wy�rodkowa�


	sf::Text gotowosc;
	gotowosc.setFillColor(sf::Color::White);
	gotowosc.setCharacterSize(35);
	gotowosc.setOutlineColor(sf::Color::Black);
	gotowosc.setOutlineThickness(2);
	gotowosc.setFont(f1);
	gotowosc.setString(tekst_gotowosc);
	wymiary = gotowosc.getLocalBounds();
	gotowosc.setPosition((600 - wymiary.left - wymiary.width) / 2, 75 + (8 * 35) - (wymiary.top + wymiary.height) / 2); //Pobieram wymiary napisu, aby m�c go wy�rodkowa�
	wymiary.top += 75 + 8 * 35;
	wymiary.left = (600 - wymiary.left - wymiary.width) / 2;

	//Inicjalizuj� przyciski do zmiany koloru gracza, zmiany jego sterowania oraz usuni�cia go
	//Do ka�dego gracza przypisany jest zestaw takich przycisk�w

	sf::RectangleShape kolorowy_przycisk[8];
	sf::RectangleShape kontroler_przycisk[8];

	sf::Text zmienkolor_txt[8];
	sf::Text zmienkontroler_txt[8];
	sf::Text numergracza_txt[8];

	sf::Sprite krzyzyk[8];
	sf::Sprite kontroler_obr[8];

	for (int i = 0; i < 8; i++) {
		kolorowy_przycisk[i].setSize(sf::Vector2f(120, 21));
		kolorowy_przycisk[i].setFillColor(sf::Color(255, 255, 255));
		kolorowy_przycisk[i].setPosition(405.0, 62.0 + i * 35.0);
		kolorowy_przycisk[i].setOutlineThickness(2);
		kolorowy_przycisk[i].setOutlineColor(sf::Color::Black);

		zmienkolor_txt[i].setPosition(407.0, 61.0 + i * 35.0);
		zmienkolor_txt[i].setString(tekst_kolor);
		zmienkolor_txt[i].setFont(f1);
		zmienkolor_txt[i].setCharacterSize(18);
		zmienkolor_txt[i].setFillColor(sf::Color::White);
		zmienkolor_txt[i].setOutlineThickness(2);
		zmienkolor_txt[i].setOutlineColor(sf::Color::Black);

		kontroler_przycisk[i].setSize(sf::Vector2f(280, 21));
		kontroler_przycisk[i].setFillColor(sf::Color(127, 127, 127));
		kontroler_przycisk[i].setPosition(61.0, 62.0 + i * 35.0);
		kontroler_przycisk[i].setOutlineThickness(2);
		kontroler_przycisk[i].setOutlineColor(sf::Color::Black);

		zmienkontroler_txt[i].setPosition(64.0, 61.0 + i * 35.0);
		zmienkontroler_txt[i].setString(tekst_sterowanie);
		zmienkontroler_txt[i].setFont(f1);
		zmienkontroler_txt[i].setCharacterSize(18);
		zmienkontroler_txt[i].setFillColor(sf::Color::White);
		zmienkontroler_txt[i].setOutlineThickness(2);
		zmienkontroler_txt[i].setOutlineColor(sf::Color::Black);

		numergracza_txt[i].setPosition(30.0, 57.0 + i * 35.0);
		numergracza_txt[i].setString(std::to_string(i + 1) + ".");
		numergracza_txt[i].setFont(f1);
		numergracza_txt[i].setCharacterSize(22);
		numergracza_txt[i].setFillColor(sf::Color::White);
		numergracza_txt[i].setOutlineThickness(2);
		numergracza_txt[i].setOutlineColor(sf::Color::Black);

		krzyzyk[i].setTexture(krzyzyk_tex);
		krzyzyk[i].setPosition(550.0, 60.0 + i * 35.0);

		kontroler_obr[i].setTexture(kontroler_tex[0]);
		kontroler_obr[i].setPosition(354.0, 59.0 + i * 35.0);
	}

	//Wstawiam kilku domy�lnie przygotowanych graczy

	liczba_graczy = 4;
	gracze.dodajGracza(new gracz(wsad, tablicaKolorow[0]), obiekty);
	kolorowy_przycisk[0].setFillColor(tablicaKolorow[0]);
	kontroler_obr[0].setTexture(kontroler_tex[1]);
	gracze.dodajGracza(new gracz(strzalki, tablicaKolorow[1]), obiekty);
	kolorowy_przycisk[1].setFillColor(tablicaKolorow[1]);
	kontroler_obr[1].setTexture(kontroler_tex[2]);
	gracze.dodajGracza(new gracz(ai, tablicaKolorow[2]), obiekty);
	kolorowy_przycisk[2].setFillColor(tablicaKolorow[2]);
	gracze.dodajGracza(new gracz(ai, tablicaKolorow[3]), obiekty);
	kolorowy_przycisk[3].setFillColor(tablicaKolorow[3]);


	while (window.isOpen())
	{

		sf::Event event;
		while (window.pollEvent(event))
		{
			//P�tla sprawdza, czy kt�ry� z przycisk�w zosta� wci�ni�ty - i odpowiednio na to reaguje

			if (event.type == sf::Event::MouseButtonPressed && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				for (int i = 0; i < liczba_graczy; i++) {
					if (liczba_graczy > 1 && krzyzyk[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						
						//Klikni�cie krzy�yka usuwa wybranego gracza
						
						std::cerr << "Usunieto: " << i << "\n";

						element_listy_graczy * lis = gracze.getHead();

						for (int j = 0; j < i; j++) {
							lis = lis->getNext();
						}

						gracze.usunGracza(lis->getPlayer(), obiekty);
						liczba_graczy--;

						//Po usunieciu gracza, ikonki graczy pozosta�ych ulegaj� od�wie�eniu

						lis = gracze.getHead();
						for (int j = 0; j < i; j++) {
							lis = lis->getNext();
						}
						for (int j = i; j < liczba_graczy; j++) {
							kolorowy_przycisk[j].setFillColor(lis->getPlayer()->getKolor());
							kontroler_obr[j].setTexture(kontroler_tex[lis->getPlayer()->getKontroler()]);
							lis = lis->getNext();
						}

						//Nie da si� nacisn�� dw�ch przycisk�w w tym samym czasie - wi�c w momencie znalezienia naci�ni�tego przycisku, pozosta�e przyciski nie s� sprawdzane

						i = liczba_graczy;
					}
					else if (kolorowy_przycisk[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						
						//Klikni�cie przycisku zmiany koloru
						
						std::cerr << "Zmiana koloru: " << i << "\n";

						element_listy_graczy * lis = gracze.getHead();

						for (int j = 0; j < i; j++) {
							lis = lis->getNext();
						}

						sf::Color temp = lis->getPlayer()->getKolor();

						for (int j = 0; j < 8; j++) {
							if (temp == tablicaKolorow[j]) {
								lis->getPlayer()->setKolor(tablicaKolorow[(j + 1) % 8]);
								kolorowy_przycisk[i].setFillColor(tablicaKolorow[(j + 1) % 8]);
								j = 8;
							}
						}
						i = liczba_graczy;
					}
					else if (kontroler_przycisk[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y) || kontroler_obr[i].getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
						
						//Klikni�cie przycisku zmiany sterowania
						
						std::cerr << "Zmiana sterowania: " << i << "\n";

						element_listy_graczy * lis = gracze.getHead();

						for (int j = 0; j < i; j++) {
							lis = lis->getNext();
						}

						int kontr = lis->getPlayer()->getKontroler();
						lis->getPlayer()->setKontroler((kontr + 1) % 3);
						kontroler_obr[i].setTexture(kontroler_tex[(kontr + 1) % 3]);

						i = liczba_graczy;
					}
				}

				if (liczba_graczy < 8 && dodaj.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {
					
					//Klikni�cie przycisku dodawania gracza
					
					std::cerr << "+1\n";
					liczba_graczy++;
					gracze.dodajGracza(new gracz(ai, tablicaKolorow[liczba_graczy - 1 % 8]), obiekty);
					kolorowy_przycisk[liczba_graczy - 1].setFillColor(tablicaKolorow[liczba_graczy - 1 % 8]);
				}

				else if (gotowosc.getGlobalBounds().contains(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)) {

					//Klikni�cie przycisku "Graj" zamyka okno i przenosi u�ytkownika do nast�pnego etapu

					window.close();
				}

			}

			if (event.type == sf::Event::Closed || sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {

				//Klikni�cie przycisku "esc" na klawiaturze, b�d� krzy�yka w g�rnym prawym rogu, tak�e zamyka okno i przenosi u�ytkownika do nast�pnego etapu

				window.close();
			}
		}

		window.clear();

		window.draw(bg);

		window.draw(nagl);

		//Pozycja przycisku dodawania graczy na bie��co dostosowuje si� do obecnej liczby graczy

		dodaj.setPosition((600 - dodaj.getLocalBounds().left - dodaj.getLocalBounds().width) / 2, 75 + (liczba_graczy * 35) - (dodaj.getLocalBounds().top + dodaj.getLocalBounds().height) / 2);

		//Ponadto, nie wy�wietla si� on w og�le, je�eli liczba graczy osi�gn�a maksimum

		if (liczba_graczy != 8)
			window.draw(dodaj);

		window.draw(gotowosc);

		//Ka�demu z graczy po�wi�cona jest kolejna linijka na ekranie 

		for (int i = 0; i < liczba_graczy; i++) {
			window.draw(numergracza_txt[i]);

			window.draw(kolorowy_przycisk[i]);
			window.draw(zmienkolor_txt[i]);

			window.draw(kontroler_przycisk[i]);
			window.draw(zmienkontroler_txt[i]);
			window.draw(kontroler_obr[i]);
		}
		
		//Je�eli zosta� tylko jeden gracz, przycisk do usuwania nie b�dzie dost�pny

		if (liczba_graczy > 1)
			for (int i = 0; i < liczba_graczy; i++) {
				window.draw(krzyzyk[i]);
			}

		window.display();
	}

	return 0;

}

