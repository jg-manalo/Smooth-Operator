#include <SFML/Graphics.hpp>
#include "dimension.h"
#include "Game.h"
#include "Hurdle.h"
#include <iostream>
int main()
{
	Game game;
	while (game.running()) {
		game.run();
	}
	return EXIT_SUCCESS;
}