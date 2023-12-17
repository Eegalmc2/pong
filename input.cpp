#include "input.hpp"
#include <iostream>

Input::Input()
{
	button.up = button.down = button.escape = button.A = button.Z = button.Q = button.M = false;
}

Input::Button Input::getButton(void) const
{
	return button;
}

void Input::InputHandler(sf::Event event, sf::RenderWindow& window)
{
	if (event.type == sf::Event::Closed)
		window.close();

	if (event.type == sf::Event::KeyPressed)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			button.escape = true;
			break;
		case sf::Keyboard::Up:
			button.up = true;
			break;
		case sf::Keyboard::Down:
			button.down = true;
			break;
		case sf::Keyboard::A:
			button.A = true;
			break;
		case sf::Keyboard::Z:
			button.Z = true;
			break;
		case sf::Keyboard::M:
			button.M = true;
			break;
		case sf::Keyboard::Q:
			button.Q = true;
			break;
		default:
			break;
		}
	}

	if (event.type == sf::Event::KeyReleased)
	{
		switch (event.key.code)
		{
		case sf::Keyboard::Escape:
			button.escape = false;
			break;
		case sf::Keyboard::Up:
			button.up = false;
			break;
		case sf::Keyboard::Down:
			button.down = false;
			break;
		case sf::Keyboard::A:
			button.A = false;
			break;
		case sf::Keyboard::Z:
			button.Z = false;
		case sf::Keyboard::M:
			button.M = false;
			break;
		case sf::Keyboard::Q:
			button.Q = false;
			break;
		default:
			break;
		}
	}
}
