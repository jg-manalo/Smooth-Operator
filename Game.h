#ifndef GAME_H
#define GAME_H

#include "dimension.h"
#include "Car.h"
#include "Hurdle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <array>

class Game
{
private:
	//window and event
	sf::RenderWindow window;
	sf::VideoMode videoMode;
	sf::Event event;

	//boolean var for user input
	bool pressedA;
	bool pressedD;
	bool pressedJ;
	bool pressedK;

	//physics
	float backgroundLocation = -SCREEN_HEIGHT;// comes from the predetermined value
	
	//Road backrgound
	sf::Texture road;
	sf::Sprite background;
	
	//menu trigger
	bool atMenu;
	bool isGameOver;

	//game audio
	sf::Music music;
	float musicVolume;

	//fonts & texts
	sf::Text scoreCard;
	sf::Text speedometer;
	sf::Text titleScreen;
	sf::Text gameOver;
	sf::Font font;


	//player and enemy
	Car* hurdle = nullptr;
	Car* player = nullptr;

	//icon
	sf::Image icon;

	//score and mechanics
	float friction;
	uint32_t score;

private: // game settings
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void renderMenu();
	void renderBackground();
	void renderScoreCard();
	void renderSpeedometer();
	void renderGameplay();
	void renderGameOver();
	void resetState(bool& atMenu, bool& isGameOver);
public:
	Game();
	~Game();

	//to check whether the game is isRunning
	const bool isRunning() const;
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 
};
#endif