#ifndef GAME_H
#define GAME_H
#include "dimension.h"
#include "Hurdle.h"
#include "Car.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <cstdint>
#include <array>

class Game
{
private:
	//window and event
	sf::RenderWindow* window = nullptr;
	sf::VideoMode videoMode;
	sf::Event event;

	//physics
	float speed;
	const float acceleration;
	float deltaX;
	float deltaY;
	float backgroundLocation = -SCREEN_HEIGHT;// comes from the predetermined value
	
	//Road bg
	sf::Texture road;
	sf::Sprite background;
	
	//menu trigger
	bool atMenu;
	bool isGameOver;

	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;
	sf::Music music;
	float musicVolume;

	//fonts
	sf::Font font;
	sf::Text scoreCard;
	sf::Text speedometer;
	sf::Text titleScreen;
	sf::Text gameOver;

	//player and enemy
	Car* hurdle;
	Car* player;

	//icon
	sf::Image icon;

	//score and mechanics
	float friction;
	unsigned long int score;
private:

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
	//constructor/destructor
	Game();
	~Game();

	//to check whether the game is isRunning
	const bool isRunning() const;
	void userInput(sf::Keyboard::Key key, bool isPressed); //checked if there any input from user
	void run(); 

protected:
	//boolean var for user input
	bool pressedA;
	bool pressedD;
	bool pressedJ;
	bool pressedK;

};
#endif