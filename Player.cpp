#include "dimension.h"
#include "Player.h"

Player::Player() : cruising{false}
{
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(XDIM, YDIM);
}
