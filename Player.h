#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class Player
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