#include <SFML/Graphics.hpp>
#include "dimension.h"
#include "Game.h"
#include "Hurdle.h"

int main()
{
	Game game;

	while (game.isRunning()) {
		game.run();
	}
	return EXIT_SUCCESS;
}