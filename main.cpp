#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;
	//window.setFramerateLimit(30);
	while (game.running()) {
		//float deltaTime = clock.restart().asSeconds();
		//float fps = 1.0f / deltaTime;
		game.run();
	}
	return EXIT_SUCCESS;
}