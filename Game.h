#pragma once
#include "Player.h"
#include "Hurdle.h"
#include <SFML/Graphics.hpp>
#include <array>


class Game
{
private:
	//private var
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//boolean var for user input
	bool pressedA = false;	
	bool pressedD = false;
	bool pressedJ = false;

	
	//Road bg
	sf::Texture road;
	sf::Sprite background;
	sf::Sprite background2;
	

	//bg init
	void renderBG();
	
	//player init
	Player* player = nullptr;
	
	//enemy init
	Hurdle* hurdle = nullptr;

	//private func
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
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
