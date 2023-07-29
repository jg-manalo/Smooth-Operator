#include "dimension.h"
#include "Player.h"

Player::Player()
{
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(XDIM, YDIM);
}

void Player::drivingSound()
{
	buffer.loadFromFile("sounds/broom.mp3");
	driving.setBuffer(buffer);
	driving.play();
	driving.setVolume(100.f);
	driving.setLoop(true);
}

void Player::drivingSoundStop()
{
	driving.pause();
}
