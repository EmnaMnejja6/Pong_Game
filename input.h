#ifndef INPUT_H
#define INPUT_H

#include <SFML/Graphics.hpp>
using namespace sf;


class Input
{	
	//structure qui stocke l'etat des boutons
	struct Button {
		bool left, right, up, down, escape;
	};
public:
	Input();
	Button GetButton(void) const;
	void InputHandler2Players(Event event,RenderWindow& window); //gérer l'input pour le mode 2 joueurs
	void InputHandler1Player(Event event, RenderWindow& window); //gérer l'input pour le mode 1 joueur
private:
	Button button;
};


#endif 
