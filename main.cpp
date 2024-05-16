#include "main.h"
#include "Menu.h"
#include "Game.h"
#include <SFML/Audio.hpp>
RenderWindow window;

int main()
{
   window.create(VideoMode(WIN_WIDTH, WIN_HEIGHT), "Pong Game");
    Menu menu(WIN_WIDTH, WIN_HEIGHT);
    while (window.isOpen())
    {
       Event event;
        while (window.pollEvent(event))
        {
            if (event.type == Event::Closed)
                window.close();
            menu.menuHandler(event, window);

        }
        menu.draw(window);

        window.display();
    }
    return 0;
}
