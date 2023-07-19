#include <SFML/Graphics.hpp>
#include "Game.h"

int main()
{
	Game game;

	while (game.running()) {
		game.run();
	}
	return EXIT_SUCCESS;
}