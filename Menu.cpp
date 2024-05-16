#include "Menu.h"
#include <iostream>

Menu::Menu(int width, int height)
{	//main menu background
	bg.loadFromFile("ressources/menu.jpg");
	background.setTexture(bg); 
	if (!font.loadFromFile("ressources/Minercraftory.ttf"))
	{
		std::cout<< "Erreur de chargement de font";
	}
	//options background
	optionsbg.loadFromFile("ressources/optionsbg.jpg");
	optionsBackground.setTexture(optionsbg);

	//click des boutons 
	buttonbuffer.loadFromFile("ressources/button.ogg");
	buttonsound.setBuffer(buttonbuffer);

	//main menu
	menu[0].setFont(font);
	menu[0].setFillColor(sf::Color::Red);
	menu[0].setString("Play");
	menu[0].setPosition(sf::Vector2f(width / 2, height / 4 * 1));
	menu[0].setCharacterSize(50);

	menu[1].setFont(font);
	menu[1].setFillColor(sf::Color::White);
	menu[1].setString("Options");
	menu[1].setPosition(sf::Vector2f(width / 2, height / 4 * 2));
	menu[1].setCharacterSize(50);

	menu[2].setFont(font);
	menu[2].setFillColor(sf::Color::White);
	menu[2].setString("Exit");
	menu[2].setPosition(sf::Vector2f(width / 2, height / 4 * 3));
	menu[2].setCharacterSize(50);
	
	//options menu
	options_menu[0].setFont(font);
	options_menu[0].setFillColor(sf::Color::Red);
	options_menu[0].setString("1 player");
	options_menu[0].setPosition(sf::Vector2f(width / 2 + 20, height / 6));
	options_menu[0].setCharacterSize(50);

	options_menu[1].setFont(font);
	options_menu[1].setFillColor(sf::Color::White);
	options_menu[1].setString("2 players");
	options_menu[1].setPosition(sf::Vector2f(width / 2 + 20, height / 3));
	options_menu[1].setCharacterSize(50);

	selectedItemIndex = 0;
	selectedOptionIndex = 0;

}

Menu::~Menu() {}

void Menu::draw(sf::RenderWindow& window)
{
	window.draw(background);
	for (int i = 0;i < 3; i++)
	{
		window.draw(menu[i]);
	}
}

void Menu::MoveUp(sf::Text m[] ,int& selectedIndex)
{
	buttonsound.play();
	if (selectedIndex - 1 >= 0)
	{
		m[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex--;
		m[selectedIndex].setFillColor(sf::Color::Red);
		
	}
}

void Menu::MoveDown(sf::Text m[],int& selectedIndex , int max)
{
	buttonsound.play();
	if (selectedIndex + 1 < max)
	{
		m[selectedIndex].setFillColor(sf::Color::White);
		selectedIndex++;
		m[selectedIndex].setFillColor(sf::Color::Red);
		
	}

}

//fonction qui gére le main menu
void Menu::menuHandler(sf::Event& event, sf::RenderWindow& window)
{
	switch (event.type)
	{
	case sf::Event::KeyReleased:
		switch (event.key.code)
		{
		case sf::Keyboard::Up:
			MoveUp(menu, selectedItemIndex);
			break;

		case sf::Keyboard::Down:
			MoveDown(menu, selectedItemIndex, 3);
			break;

		case sf::Keyboard::Enter:
			switch (GetPressedItem())
			{
			case 0:
				std::cout << "game started";
				while (window.isOpen())
				{
					Event aevent;
					while (window.pollEvent(aevent))
					{
						if (aevent.type == Event::Closed)
						{
							window.close();
						}

						if (aevent.type == Event::KeyPressed)
						{
							if (event.key.code == Keyboard::Escape)
							{
								window.close();
							}
						}
					}
					Game game(window);
					//commencer le jeu en mode 1 joueur par défaut
					game.start_game(window, event, 1);
					window.clear();
				}
				break;
			case 1:
				std::cout << "Options button pressed" << std::endl;
				options(event,window);
				return;
				break;
			case 2:
				window.close();
				break;
				break;
			}
			break;
		case sf::Keyboard::Escape:
			window.close();
			break;
		}
	}
}

//fonction qui gére options menu
void Menu::optionsHandler(sf::Event& event,sf::RenderWindow& window)
{
			switch (event.type)
			{
			case sf::Event::KeyReleased:
				switch (event.key.code)
				{
				case sf::Keyboard::Up:
					MoveUp(options_menu, selectedOptionIndex);
					std::cout << "Selected Index:" << selectedOptionIndex << std::endl;
					break;

				case sf::Keyboard::Down:
					MoveDown(options_menu, selectedOptionIndex, 2);
					std::cout << "Selected Index:" << selectedOptionIndex << ", Max:2 " << std::endl;
					break;

				case sf::Keyboard::Enter:
					switch (GetPressedOption())
					{
					case 0:
						std::cout << "1 player game started" << std::endl;
						while (window.isOpen())
						{
							Event aevent;
							while (window.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									window.close();
								}

								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										window.close();
									}
								}
							}
							Game game(window);
							//commencer le jeu en mode 1 joueur
							game.start_game(window, event, 1);
							window.clear();
						}
						break;
					case 1:
						std::cout << "2 Players game started" << std::endl;
						while (window.isOpen())
						{
							Event aevent;
							while (window.pollEvent(aevent))
							{
								if (aevent.type == Event::Closed)
								{
									window.close();
								}

								if (aevent.type == Event::KeyPressed)
								{
									if (aevent.key.code == Keyboard::Escape)
									{
										window.close();
									}
								}
							}
							Game game(window);
							//commencer le jeu en mode 2 joueurs
							game.start_game(window, event, 2);
							window.clear();
						}
						break;
					}
					break;
				case sf::Keyboard::Escape:
					window.close();
					break;
				}
			}
			if (event.type == Event::KeyPressed)
			{
				if (event.key.code == Keyboard::Escape)
				{
					window.close();
				}
			}

}
//fonction qui affiche options menu
void Menu::options(sf::Event& event,sf::RenderWindow& window)
{
	while (window.isOpen())
	{
		while (window.pollEvent(event))
		{
			optionsHandler(event,window);
		}
		window.clear();
		window.draw(optionsBackground);
		window.draw(options_menu[0]);
		window.draw(options_menu[1]);
		window.display();
	}	
}


