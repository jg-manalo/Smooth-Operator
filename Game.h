#pragma once
#include "Hurdle.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

class Game
{
private:
	//private var
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//physics
	float velocity;
	const float acceleration;
	float dx;
	float dy;

	//boolean var for user input
	bool pressedA;	
	bool pressedD;
	bool pressedJ;
	bool pressedK;
	
	//Road bg
	sf::Texture road;
	sf::Sprite background;
	

	//bg init
	void renderBG();
	
	//private func
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void render();
	
	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;
	sf::Music music;
public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//to check whether the game is running
	const bool running() const;
	
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 

	Hurdle* hurdle; //object for hurdle
	Player* player; //object for player
};
