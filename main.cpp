#include <iostream>
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Vehicle.hpp"

const unsigned int XDIM = 1280;
const unsigned int YDIM = 720;

int main()
{
	sf::RenderWindow window(sf::VideoMode(XDIM, YDIM), "Smooth Operator", sf::Style::Titlebar | sf::Style::Close);
	sf::Clock clock;
	window.setFramerateLimit(30);
	Car car{};
	
	car.box.setPosition(XDIM / 2 - car.width, YDIM / 2 - car.height);
	while (window.isOpen()) {
		float deltaTime = clock.restart().asSeconds();
		float fps = 1.0f / deltaTime;


		sf::Event event;
		while (window.pollEvent(event)){
			if (event.type == sf::Event::Closed) window.close();
		}

		car.move();
		
		window.clear();
		window.draw(car.box);
		window.display();
	}
	return EXIT_SUCCESS;
}