#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>
class Player
{
public:
	Player();
	sf::Texture car;
	sf::RectangleShape playerShape;
	void drivingSound();
	void drivingSoundPause();
private:
	sf::SoundBuffer buffer;
	sf::Sound driving;
};