#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	//private var
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//boolean shits
	bool pressedW;
	bool pressedA;	
	bool pressedS;
	bool pressedD;

	//entity
	sf::RectangleShape shape;
	void initEntity(float x = 0.f, float y = 0.f);
	//private func
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;
	
	//func
	void userInput(sf::Keyboard::Key key, bool isPressed);
	void run();
};

