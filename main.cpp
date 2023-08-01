#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;

	while (game.isRunning()) {
		game.run();
	}
	
	return EXIT_SUCCESS;
}