#include "Game.h"

Game::Game() : _window(sf::VideoMode(640, 480), "SFML Application")
{
	
}

void Game::Run()
{
	ResourceHolder<sf::Texture, Textures::ID> textures;
	textures.Load(Textures::Airplane, "res/Airplane.png");
	_player.setTexture(textures.Get(Textures::Airplane));

	sf::Clock clock;
	sf::Time timeSinceLastUpdate = sf::Time::Zero;
	const sf::Time timeStep = sf::seconds (1.f / 60.f);

	while (_window.isOpen())
	{
		ProcessEvents();

		timeSinceLastUpdate += clock.restart();
		while (timeSinceLastUpdate > timeStep)
		{
			timeSinceLastUpdate -= timeStep;

			ProcessEvents();
			Update(timeStep);
		}
			
		Render();
	}
}

void Game::ProcessEvents()
{
	sf::Event event;

	while (_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::KeyPressed:
			HandlePlayerInput(event.key.code, true);
			break;

		case sf::Event::KeyReleased:
			HandlePlayerInput(event.key.code, false);
			break;

		case sf::Event::Closed:
			_window.close();
			break;
		}
			
	}
}

void Game::HandlePlayerInput(sf::Keyboard::Key key, bool isPressed)
{
	if (key == sf::Keyboard::W)
		_isMovingUp = isPressed;
	else if (key == sf::Keyboard::S)
		_isMovingDown = isPressed;
	else if (key == sf::Keyboard::A)
		_isMovingLeft = isPressed;
	else if (key == sf::Keyboard::D)
		_isMovingRight = isPressed;
}

void Game::Update(sf::Time dt)
{
	sf::Vector2f movement(0.f, 0.f);

	if (_isMovingUp)
		movement.y -= 1.f;
	if (_isMovingDown)
		movement.y += 1.f;
	if (_isMovingLeft)
		movement.x -= 1.f;
	if (_isMovingRight)
		movement.x += 1.f;

	_player.move(movement * dt.asSeconds());
}

void Game::Render()
{
	_window.clear();
	_window.draw(_player);
	_window.display();
}
