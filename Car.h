#ifndef CAR_H
#define CAR_H

#include "Game.h"
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
struct Coordinate {
	float x;
	float y;
};


class Car : private Game
{
public:
	Car();
	void drivingSound();
	void drivingSoundPause();
	void brakingSound();
	Coordinate randomizer();

	float steerAction(float& speed, float& deltaX, const float& acceleration, sf::Time& deltaTime);
	float accelerate(float& speed);
	float musicVolumeControl(float& musicVolume);
	void crashedSound();

private: //asset loader
	void setCrashedSound();
	void setCarSkin();
	
public:
	sf::Texture carSkin;
	sf::RectangleShape carShape;
private:
	sf::SoundBuffer driveSoundBuffer;
	sf::SoundBuffer brakeSoundBuffer;
	sf::Sound driving;
	sf::Sound braking;
};
#endif