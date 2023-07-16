#include "Vehicle.hpp"
#include <SFML/Graphics.hpp>
#include<cmath>
#include <iostream>

//init car properties
Car::Car() : box(sf::Vector2f(width, height)) {
	box.setFillColor(sf::Color::Red);
}

void Car::move() {
	float currentTheta = this -> box.getRotation();

	bool turnL = currentTheta < 360 && currentTheta > 270;
	bool turnR = currentTheta > 5 && currentTheta < 90;
	bool invertedU = currentTheta >= 90 && currentTheta < 135;
	bool invertedH = currentTheta >= 180 && currentTheta < 360;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {

		//ayusin mo na lang yung turning physics
		if (invertedU || invertedH) this->box.move(sf::Vector2f(-5, 0));
		else if (turnL)      this->box.move(sf::Vector2f(5, 0));
		else if (turnR) this->box.move(sf::Vector2f(-5, 0));
		
		this->box.move(sf::Vector2f(0, 5));
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		if (invertedU || invertedH) this->box.move(sf::Vector2f(5, 5));
		else if (turnR)             this->box.move(sf::Vector2f(-5, 0));
		else if (turnL)             this->box.move(sf::Vector2f(5, 0));
		this->box.move(sf::Vector2f(0, -5));
	}
	//kakanan
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		currentTheta--;
		this->box.rotate(currentTheta );
	}
	//kakaliwa
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		currentTheta++;
		this->box.rotate(currentTheta);
	}

	std::cout << "Current theta: " << currentTheta << '\n';
	this -> box.setRotation(currentTheta);
}
	