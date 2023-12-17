#ifndef INPUT_HPP
# define INPUT_HPP

#include "SFML/Graphics.hpp"

class Input
{
	struct Button
	{
		bool left, right, up, down, escape, A, Z, M;
	};

public:
	Input();
	Button getButton(void) const;
	void InputHandler(sf::Event event, sf::RenderWindow& window);

private:
	Button button;
};

#endif // !INPUT_HPP