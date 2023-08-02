#pragma once
#include "dimension.h"
#include "Hurdle.h"
#include "Player.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>


class Game
{
private:
	//private var
	sf::RenderWindow* window = nullptr;
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
	
	//menu trigger
	bool atMenu;
	bool playing;
	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;
	sf::Music music;
	float musicVol;

	//fonts
	sf::Font font;
	sf::Text scoreCard;
	sf::Text speedometer;
	sf::Text titleScreen;
	sf::Text gameOver;
	//player and enemy
	Hurdle* hurdle;
	Player* player;

	//score and mechanics
	float friction;
	unsigned long int score;
private:
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void renderMenu();
	void renderBG();
	void renderScoreCard();
	void renderSpeedometer();
	void renderGameplay();
	void renderGameOver();
private: //car behaviors
	float steerAction(float& speed, float& dx,const float& acceleration, sf::Time& deltaTime);
	float accelerate(float& speed);
	float musicVolControl(float& musicVol);
	void crashedSound();
public:
	//constructor/destructor
	Game();
	~Game();

	//to check whether the game is isRunning
	const bool isRunning() const;
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 
};
