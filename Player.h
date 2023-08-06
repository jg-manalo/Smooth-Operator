#pragma once
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com

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
private: //player's assets initializer
	void initializePlayerLooks();
	void initializeBrakingSound();
	void initializeDrivingSound();
};