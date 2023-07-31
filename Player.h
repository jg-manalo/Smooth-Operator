#pragma once
#include "Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class Player : protected Game
{
public:
	sf::Texture car;
	sf::RectangleShape playerShape;
public:
	Player();
	void drivingSound();
	void drivingSoundStop();
private:
	sf::SoundBuffer buffer;
	sf::Sound driving;
};