#pragma once
#include "Hurdle.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

class Game
{
private: //variables
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
	
	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;
	sf::Music music;

	Hurdle* hurdle; //object for hurdle
	Player* player; //object for player
	Hurdle* hurdle2; //another one
	//score
	unsigned long int score;
private: 
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void renderBG();
	void renderAll(); // main renderer
	
public: //constructor/destructor
	Game();
	virtual ~Game();

	//to check whether the game is running
	const bool isRunning() const;
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 
};
