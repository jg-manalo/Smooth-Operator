// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include <Windows.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

//constructor and destructor
Game::Game() : score{ 0 }, musicVolume{ 0.f }, atMenu{ true }, 
			   isGameOver { false }, pressedA{false}, pressedD{false}, 
	           pressedJ{ false }, pressedK{ false }  
{
	this->videoMode.height = static_cast<uint32_t>(SCREEN_HEIGHT);
	this->videoMode.width = static_cast<uint32_t>(SCREEN_WIDTH);
	this->window.create(videoMode, "Smooth Operator", sf::Style::Titlebar | sf::Style::Close);
	this->window.setFramerateLimit(30);

	try {
		if (!road.loadFromFile("graphics/px_roadstar.png"))
			throw std::runtime_error("Could not load px_roadstar.png");
		if (!font.loadFromFile("fonts/racing.ttf"))
			throw std::runtime_error("Could not load racing.ttf");
		if (!music.openFromFile("sounds/cimh.mp3"))
			throw std::runtime_error("Could not load cimh.mp3");
	}
	catch (const std::exception& error) {
		std::cout << "Error: " << error.what();
	}
	
	this->background.setTexture(road);
	
	this->player = new Car(); //creates a player object
	this->hurdle = new Hurdle(); //creates a hurdle object 
	
	this->scoreCard.setFont(font);
	this->scoreCard.setPosition(25.f, 0.f);

	this->speedometer.setFont(font);
	this->speedometer.setPosition(SCREEN_WIDTH - 200.f, 0.f);

	this->gameOver.setFont(font);
	this->gameOver.setPosition(SCREEN_WIDTH_HALVED - 50.f, SCREEN_HEIGHT_HALVED);
}
Game::~Game() {
	delete this->player;
	delete this->hurdle;
	player = nullptr;
	hurdle = nullptr;
}




//event handler
void Game::processEvents(){
	while (this->window.pollEvent(this->event)) {
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window.close();
				else if (this->event.key.code == sf::Keyboard::Enter)
					atMenu = false;
				userInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window.close();
				userInput(event.key.code, false);
				break;
			}

	}
}

//runner drive
const bool Game::isRunning() const{
	return this->window.isOpen();
}

void Game::run() {
	sf::Clock clock;
	while (isRunning()) {
		sf::Time deltaTime = clock.restart();
		processEvents();
		if (atMenu) {
			renderMenu();
		}
		else if (!isGameOver){
			update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
			renderGameplay();
		}
		else{
			renderGameOver();
			resetState(atMenu, isGameOver);
		}
	}
}


//user input handler
void Game::userInput(sf::Keyboard::Key key, bool isPressed) {
	if (key == sf::Keyboard::A)
		pressedA = isPressed;
	else if (key == sf::Keyboard::D)
		pressedD = isPressed;
	else if (key == sf::Keyboard::J)
		pressedJ = isPressed;
	else if (key == sf::Keyboard::K)
		pressedK = isPressed;
}

//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	sf::Vector2f playerPos = player->carShape.getPosition();
	sf::FloatRect playerBounds = player->carShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->carShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->carShape.getSize();


	//score update and difficulty increase mechanism
	if (score == 1000) {
		//the music will be heard while the player is accelerating
		this->music.play();
		this->music.setVolume(0.f);
		this->music.setLoop(true);
	}
	else if (score == 5000) {
		friction /= 2.f;
	}
	else if (score == 23000) {
		friction /= 2.f;
	}
	else if (score == 50000) {
		friction /= 2.f;
	}


	if (pressedJ){
		float deltaY = 0;
		deltaY += hurdle->speed * deltaTime.asSeconds();
		
		player->accelerate(player->speed);
		player->musicVolumeControl(musicVolume);
		hurdle->carShape.move(0, deltaY);
		score += 20;
	}

	else{
		if (pressedK) {
			player->brakingSoundFX();
			player->deltaX = 0.f;
			player->speed -= 0.5f;
		}

		player->speed -= 0.5f;
		musicVolume-= 0.05f;

		if (player->speed < 0 || musicVolume < 0) {
			player->speed = 0.f;
			musicVolume = 0.f;
		}


	}
	
	player->steerAction(player->speed, player->deltaX, player->acceleration, deltaTime, pressedA, pressedD);
	backgroundLocation += player->speed * deltaTime.asSeconds() * player->acceleration;
	//background scrolling limiter
	backgroundLocation = (backgroundLocation > 0) ? backgroundLocation = -screenHeight : backgroundLocation;
	this->background.setPosition(0, backgroundLocation);
	
	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		player->crashedSoundFX();
		player->drivingSoundPauseFX();
		Sleep(1000);
		isGameOver = true;
	}


	if (this->player->speed == 1.f) {
		player->drivingSoundFX();
	}
	else if (player->speed == 0.f) {
		player->drivingSoundPauseFX();
	}
	
	if (playerBounds.left + player->deltaX < 0)
		player->deltaX = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		player->deltaX = screenWidth - playerSize.x - playerBounds.left;

	
	if (hurdle->carShape.getPosition().y > screenHeight) {
		Coordinate reset = hurdle->randomizer();
		this->hurdle->carShape.setPosition(reset.x, reset.y);
	}

	//character movement
	this->player->carShape.move(player->deltaX, 0);
	this->music.setVolume(musicVolume);
}

void Game::renderMenu(){
	titleScreen.setFont(font);
	titleScreen.setString("Play Now");
	titleScreen.setPosition(SCREEN_WIDTH_HALVED - 100, SCREEN_HEIGHT_HALVED - 100);
	titleScreen.setCharacterSize(50);
	window.clear();
	this->window.draw(titleScreen);
	this->window.display();
}
void Game::renderBackground() {
	
	window.draw(this->background);
}
void Game::renderScoreCard(){
	std::ostringstream scoreDisplay;
	scoreDisplay << "Score: " << score;
	this->scoreCard.setString(scoreDisplay.str());
	this->window.draw(this->scoreCard);
}
void Game::renderSpeedometer() {
	std::ostringstream speedDisplay;
	speedDisplay << "Speed: " << player->speed << " kph";
	this->speedometer.setString(speedDisplay.str());
	this->window.draw(this->speedometer);
}

void Game::renderGameplay(){
	this->window.clear();
	this->window.draw(background);
	this->window.draw(this->player->carShape);
    this->window.draw(this->hurdle->carShape);
	renderScoreCard();
	renderSpeedometer();
	this->window.display();
}

void Game::renderGameOver(){
	std::ostringstream displayYouLose;
	displayYouLose << "You Lose!\nScore: " << score;
	this->gameOver.setString(displayYouLose.str());
	this->window.clear();
	this->window.draw(gameOver);
	this->window.display();
	Sleep(5000);
}

void Game::resetState(bool& inMenu, bool& isGameOver){
	inMenu = true;
	player->deltaX = 0.f;
	score  = 0;
	player->speed  = 0.f;
	player->drivingSoundPauseFX();
	Coordinate reset = this->hurdle->randomizer();
	this->hurdle->carShape.setPosition(reset.x, -200.f);
	this->player->carShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
	friction = 32.f;
	isGameOver  = false;
}