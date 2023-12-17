#include "input.hpp"

#include <iostream>

const int WIN_WIDTH = 800;
const int WIN_HEIGHT = 600;

sf::RenderWindow window;

Input input;

sf::Font font;

sf::Text txt;
sf::Text txt_fps;

bool mode;

int posBatLeftX      = 50;
int posBatRightX     = WIN_WIDTH - 70;
int posBatLeftY      = WIN_HEIGHT / 2;
int posBatRightY     = posBatLeftY;
int batSpeed         = 13;
int batHeight        = 150;
int batWidth         = 20;

int ballSpeed        = 3;
sf::Vector2f ballDir = sf::Vector2f(1, 2);
int ballPosX         = WIN_WIDTH / 2;
int ballPosY         = WIN_HEIGHT / 2;
int ballHeight       = 15;

int scoreJ1          = 0;
int scoreJ2          = 0;

// methodes
static void SetText(sf::Text& txt, sf::String str)
{
	txt.setFont(font);
	txt.setString(str);
	txt.setCharacterSize(26);
	txt.setFillColor(sf::Color::White);
	txt.setPosition((WIN_WIDTH / 2) - 40, 10);
}

static void SetText(sf::Text& txt, sf::String str, int x, int y, int height)
{
	txt.setFont(font);
	txt.setString(str);
	txt.setCharacterSize(height);
	txt.setFillColor(sf::Color::White);
	txt.setPosition(x, y);
}

static void menu()
{
	bool is_mode_taked = false;
	sf::Text mtxt_T, mtxt_A, title;

	SetText(title, "Pong Game !", WIN_WIDTH / 2 - 200, 20, 50);

	SetText(mtxt_T, "Choose a mode: \n", WIN_WIDTH / 2 - 200, 150, 40);
	mtxt_T.setOutlineThickness(1.0f);
	SetText(mtxt_A, "\tA: you vs IA\n\tZ: you vs you", WIN_WIDTH / 2 - 200, 200, 35);

	window.clear(sf::Color::Black);
	window.draw(title);
	window.draw(mtxt_T);
	window.draw(mtxt_A);
	window.display();

	while (!is_mode_taked && window.isOpen())
	{
		sf::Event event;

		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}

		if (input.getButton().A == true)
		{
			mode = true;
			is_mode_taked = true;
		}
		else if (input.getButton().Z == true)
		{
			mode = false;
			is_mode_taked = true;
		}
		if (input.getButton().escape == true)
		{
			window.close();
			return;
		}
	}

	posBatLeftX = 50;
	posBatRightX = WIN_WIDTH - 70;
	posBatLeftY = WIN_HEIGHT / 2;
	posBatRightY = posBatLeftY;

	sf::Vector2f ballDir = sf::Vector2f(1, 2);
	ballPosX = WIN_WIDTH / 2;
	ballPosY = WIN_HEIGHT / 2;

	scoreJ1 = 0;
	scoreJ2 = 0;
	SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
}

static void CheckBtn()
{
	if (input.getButton().up == true)
	{
		if (mode)
		{
			posBatLeftY -= batSpeed;
			if (posBatLeftY < 0)
				posBatLeftY = 0;
		}
		else
		{
			posBatRightY -= batSpeed;
			if (posBatRightY < 0)
				posBatRightY = 0;
		}
	}
	if (input.getButton().down == true)
	{
		if (mode)
		{
			posBatLeftY += batSpeed;
			if (posBatLeftY + batHeight > WIN_HEIGHT)
				posBatLeftY = WIN_HEIGHT - batHeight;
		}
		else
		{
			posBatRightY += batSpeed;
			if (posBatRightY + batHeight > WIN_HEIGHT)
				posBatRightY = WIN_HEIGHT - batHeight;
		}
	}

	if (!mode && input.getButton().A == true)
	{
		posBatLeftY -= batSpeed;
		if (posBatLeftY < 0)
			posBatLeftY = 0;
	}
	if (!mode && input.getButton().Q == true)
	{
		posBatLeftY += batSpeed;
		if (posBatLeftY + batHeight > WIN_HEIGHT)
			posBatLeftY = WIN_HEIGHT - batHeight;
	}

	if (input.getButton().escape == true)
		window.close();
	if (input.getButton().M == true)
		menu();
}

static void UpdateBall()
{
	ballPosX += ballDir.x * ballSpeed;
	ballPosY += ballDir.y * ballSpeed;

	// collision left and right bats
	if ((ballPosX < posBatLeftX + batWidth &&
		ballPosX > posBatLeftX &&
		ballPosY + ballHeight / 2 < posBatLeftY + batHeight &&
		ballPosY + ballHeight / 2 > posBatLeftY)
		||
		(ballPosX > posBatRightX - batWidth &&
		ballPosX < posBatRightX &&
		ballPosY + ballHeight / 2 < posBatRightY + batHeight &&
		ballPosY + ballHeight / 2 > posBatRightY))
	{
		ballDir.x *= -1;
	}

	// collision left wall
	if (ballPosX < 0)
	{
		scoreJ2++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
	}

	// collision right wall
	if (ballPosX > WIN_WIDTH)
	{
		scoreJ1++;
		ballPosX = WIN_WIDTH / 2;
		ballPosY = WIN_HEIGHT / 2;
		ballDir.x = -fabs(ballDir.x);
		ballDir.y *= -1;
		SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));
	}

	// top and botton wall
	if (ballPosY < 0 || ballPosY > WIN_HEIGHT - ballHeight)
	{
		ballDir.y *= -1;
	}
}

static void AIBat()
{
	posBatRightY = ballPosY - batHeight / 2;
	if (posBatRightY < 0)
		posBatRightY = 0;
	if (posBatRightY + batHeight > WIN_HEIGHT)
		posBatRightY = WIN_HEIGHT - batHeight;
}

int main()
{
	window.create(sf::VideoMode(WIN_WIDTH, WIN_HEIGHT, 32), "Pong SFML c++", sf::Style::Default);
	window.setFramerateLimit(60);

	font.loadFromFile("resource/Silkscreen-Regular.ttf");

	menu();

	SetText(txt, std::to_string(scoreJ1) + " | " + std::to_string(scoreJ2));

	sf::CircleShape circleShape(ballHeight);
	circleShape.setPosition(ballPosX, ballPosY);

	sf::RectangleShape rectangleShape(sf::Vector2f(batWidth, batHeight));
	rectangleShape.setPosition(posBatLeftX, posBatLeftY);

	sf::RectangleShape rectangleShape2(sf::Vector2f(batWidth, batHeight));
	rectangleShape2.setPosition(posBatRightX, posBatRightY);

	sf::Clock clock;

	while (window.isOpen())
	{
		int fps = 1 / clock.getElapsedTime().asSeconds();
		clock.restart();
		SetText(txt_fps, "fps: " + std::to_string(fps), WIN_WIDTH - 75, 10, 15);

		sf::Event event;

		while (window.pollEvent(event))
		{
			input.InputHandler(event, window);
		}

		CheckBtn();

		rectangleShape.setPosition(posBatLeftX, posBatLeftY);

		UpdateBall();
		if (mode)
			AIBat();
		rectangleShape2.setPosition(posBatRightX, posBatRightY);

		circleShape.setPosition(ballPosX, ballPosY);


		window.clear(sf::Color::Black);

		window.draw(txt);
		window.draw(txt_fps);
		window.draw(circleShape);
		window.draw(rectangleShape);
		window.draw(rectangleShape2);

		window.display();
	}

	return 0;
}
