// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Player.h"
#include "Game.h"


Player::Player(){
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(XDIM, YDIM);
}

void Player::drivingSound(){
	driveSoundBuffer.loadFromFile("sounds/broom.mp3");
	driving.setBuffer(driveSoundBuffer);
	driving.setLoop(true);
	driving.setVolume(100);
	driving.play();

}

void Player::drivingSoundPause(){
  driving.pause();
}

void Player::brakingSound(){
	brakeSoundBuffer.loadFromFile("sounds/brake.mp3");
	braking.setBuffer(brakeSoundBuffer);
	braking.setVolume(80.f);
	braking.play();
}
