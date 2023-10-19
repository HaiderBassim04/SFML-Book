#pragma once

#include "SFML/Graphics.hpp"

class Game
{
public:
	Game();
	void Run();

private:
	void ProcessEvents();
		void HandlePlayerInput(sf::Keyboard::Key key, bool isPressed);
	void Update(sf::Time timeStep);
	void Render();

private:
	sf::RenderWindow _window;
	sf::CircleShape _player;

	bool _isMovingUp = false;
	bool _isMovingRight = false;
	bool _isMovingDown = false;
	bool _isMovingLeft = false;
};
