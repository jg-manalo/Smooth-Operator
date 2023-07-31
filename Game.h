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
	float speed;
	const float acceleration;
	float dx;
	float dy;
	float background2_Y = -SCREEN_HEIGHT;// comes from the predetermined value

	//boolean var for user input
	bool pressedA;	
	bool pressedD;
	bool pressedJ;
	bool pressedK;
	
	//Road bg
	sf::Texture road;
	sf::Sprite background;
	
	//private func
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void renderAll();
	
	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;
	sf::Music music;
	float musicVol;

	//fonts
	sf::Font font;
	sf::Text scoreCard;
	sf::Text speedometer;

	//player and enemy
	Hurdle* hurdle;
	Player* player;

	//score
	unsigned long int score;
private:
	//bg initialize
	void renderBG();
	void renderScoreCard();
	void renderSpeedometer();
public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//to check whether the game is running
	const bool running() const;
	
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 
};
