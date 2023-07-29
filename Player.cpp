#include "dimension.h"
#include "Player.h"

Player::Player()
{
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(XDIM, YDIM);
}

void Player::drivingSound(bool& drivingState)
{
	buffer.loadFromFile("sounds/broom.mp3");
	driving.setBuffer(buffer);
	if (drivingState == 1) {
		driving.play();
	}
}

void Player::drivingSoundStop(bool& drivingState)
{
	if (drivingState == 0) {
		driving.stop();
	}
}
