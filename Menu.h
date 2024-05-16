#pragma once
#include "SFML/Graphics.hpp"
#include "Game.h"
#include "main.h"

class Menu
{
public:
	Menu(int width, int height);
	~Menu();

	void draw(sf::RenderWindow& window);
	void MoveUp(sf::Text[], int& selectedIndex);
	void MoveDown(sf::Text[],int& selectedIndex , int max);
	int GetPressedItem() { return selectedItemIndex; } //retourne l'item selectionné
	int GetPressedOption() { return selectedOptionIndex;  } //retourne l'option selectionnée
	void menuHandler(sf::Event& event , sf::RenderWindow& window); //fonction qui gére main menu
	void options(sf::Event& event,sf::RenderWindow& window); //fonction qui affiche options menu
	void optionsHandler(sf::Event& event,sf::RenderWindow& window); //fonction qui gére options menu
private: 
	int selectedItemIndex;
	int selectedOptionIndex;
	sf::Font font;
	sf::Text menu[3];
	sf::Texture bg,optionsbg;
	sf::Sprite background,optionsBackground;
	//options
	sf::Text options_menu[2]; 
	SoundBuffer buttonbuffer;
	Sound buttonsound;
};