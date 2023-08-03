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
	void brakingSound();
private:
	sf::SoundBuffer driveSoundBuffer;
	sf::SoundBuffer brakeSoundBuffer;
	sf::Sound driving;
	sf::Sound braking;
};