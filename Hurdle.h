#pragma once
#include <SFML/Graphics.hpp>

// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com


struct Coordinate {
	float x;
	float y;
};

class Hurdle{
public:
	Hurdle();
	sf::Texture hurdle;
	sf::RectangleShape hurdleShape;
	Coordinate randomizer();
};

