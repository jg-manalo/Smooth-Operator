// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include <SFML/Graphics.hpp>
#include <Windows.h>
#include "Game.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
	Game game;

	while (game.isRunning()) {
		game.run();
	}
	
	return EXIT_SUCCESS;
}