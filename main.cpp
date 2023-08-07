// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <cstdlib>
#include "Game.h"

int main() {
	Game game;

	while (game.isRunning()) {
		game.run();
	}	
	return EXIT_SUCCESS;
}