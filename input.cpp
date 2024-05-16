#include "input.h"
Input::Input()
{
	button.left = button.right = button.up = button.down = button.escape = false;
}
Input::Button Input::GetButton(void) const
{
	return button;
}
void Input::InputHandler2Players(Event event, RenderWindow& window)
{
	if (event.type == Event::Closed)
		window.close();
	//gestion des inputs
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            button.escape = true;
            break;
        case Keyboard::S:
            button.left = true;
            break;
        case Keyboard::Z:
            button.right = true;
            break;
        case Keyboard::Up:
            button.up = true;
            break;
        case Keyboard::Down:
            button.down = true;
            break;
        default:
            break;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            button.escape = false;
            break;
        case Keyboard::S:
            button.left = false;
            break;
        case Keyboard::Z:
            button.right = false;
            break;
        case Keyboard::Up:
            button.up = false;
            break;
        case Keyboard::Down:
            button.down = false;
            break;
        default:
            break;
        }
    }

}

void Input::InputHandler1Player(Event event, RenderWindow& window)
{
    if (event.type == Event::Closed)
        window.close();
    //gestion des inputs
    if (event.type == sf::Event::KeyPressed)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            button.escape = true;
            break;
        case Keyboard::Up:
            button.up = true;
            break;
        case Keyboard::Down:
            button.down = true;
            break;
        default:
            break;
        }
    }
    if (event.type == sf::Event::KeyReleased)
    {
        switch (event.key.code)
        {
        case Keyboard::Escape:
            button.escape = false;
            break;
        case Keyboard::Up:
            button.up = false;
            break;
        case Keyboard::Down:
            button.down = false;
            break;
        default:
            break;
        }
    }
}
