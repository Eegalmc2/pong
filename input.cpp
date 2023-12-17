#include "input.hpp"
#include <iostream>

Input::Input()
{
	button.left = button.right = button.up = button.down = button.escape = false;
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
		case sf::Keyboard::Left:
			button.left = true;
			break;
		case sf::Keyboard::Right:
			button.right = true;
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
		case sf::Keyboard::Left:
			button.left = false;
			break;
		case sf::Keyboard::Right:
			button.right = false;
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
		default:
			break;
		}
	}
}