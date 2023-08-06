// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Player.h"
#include "Game.h"


Player::Player(){
	initializePlayerLooks();

}

void Player::drivingSound(){
	driving.setLoop(true);
	driving.setVolume(100.f);
	driving.play();
}

void Player::drivingSoundPause(){
  driving.pause();
}

void Player::brakingSound(){
	braking.setVolume(80.f);
	braking.play();
}

void Player::initializePlayerLooks(){
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	this->car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
}

void Player::initializeDrivingSound(){
	driveSoundBuffer.loadFromFile("sounds/broom.mp3");
	driving.setBuffer(driveSoundBuffer);
};

void initializeBrakingSound(){
	rakeSoundBuffer.loadFromFile("sounds/brake.mp3");
	braking.setBuffer(brakeSoundBuffer);
}