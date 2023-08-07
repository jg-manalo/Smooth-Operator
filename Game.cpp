// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Game.h"
#include "Car.h"
#include "Hurdle.h"
#include <sstream>
#include <Windows.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>




//constructor and destructor
Game::Game() : speed{ 0.f }, acceleration{ 10.f }, deltaX{ 0.f }, deltaY{ 0.f }, 
			   score{ 0 }, musicVolume{ 0.f }, atMenu{ true }, friction {32.f},
			   isGameOver { false }, pressedA{false}, pressedD{false}, 
			   pressedJ{ false }, pressedK {false}
{
	this->videoMode.height = static_cast<uint32_t>(SCREEN_HEIGHT);
	this->videoMode.width  = static_cast<uint32_t>(SCREEN_WIDTH);

	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);

	
	this->icon.loadFromFile("graphics/leo.png");
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());

	this->window->setFramerateLimit(30);

	initializeBackground();
	initializeMusic();
	initializeFont();
	initializeScorecard();
	initializeSpeedometer();
	initializeCrashedSound();
	initializeGameOverScreen();

	this->player = new Car(); //creates a player object
	this->hurdle = new Hurdle(); //creates a hurdle object 
}

Game::~Game() {
	delete this->player;
	delete this->hurdle;
	delete this->window;
	player = nullptr;
	hurdle = nullptr;
	window = nullptr;
}


void Game::renderMenu(){
	titleScreen.setFont(font);
	titleScreen.setString("Play Now");
	titleScreen.setPosition(SCREEN_WIDTH_HALVED - 100, SCREEN_HEIGHT_HALVED - 100);
	titleScreen.setCharacterSize(50);
	this->window->clear();
	this->window->draw(titleScreen);
	this->window->display();
}

//background init
void Game::renderBackground() {
	background.setPosition(0.f, backgroundLocation);
	this->window->draw(this->background);
}

//runner drive
const bool Game::isRunning() const{
	return this->window->isOpen();
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

//event handler
void Game::processEvents(){
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window->close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				else if (this->event.key.code == sf::Keyboard::Enter)
					atMenu = false;
				userInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window->close();
				userInput(event.key.code, false);
				break;
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

//disisGameOver score
void Game::renderScoreCard(){
	std::ostringstream scoreDisplay;
	scoreDisplay << "Score: " << score;
	this->scoreCard.setString(scoreDisplay.str());
	this->window->draw(this->scoreCard);
}

//disisGameOver speed
void Game::renderSpeedometer() {
	std::ostringstream speedDisplay;
	speedDisplay << "Speed: " << speed << " kph";
	this->speedometer.setString(speedDisplay.str());
	this->window->draw(this->speedometer);
}


//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	sf::Vector2f playerPos = player->carShape.getPosition();
	sf::FloatRect playerBounds = player->carShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->carShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->carShape.getSize();


	//score update and difficulty increase mechanism
	if (score == 1000) {
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
		float deltaY = 0.f;
		player->accelerate(speed);
		player->musicVolumeControl(musicVolume);
		backgroundLocation += speed * deltaTime.asSeconds() * acceleration;
		deltaY += speed / friction * deltaTime.asSeconds() * acceleration;
		hurdle->carShape.move(0, deltaY);
		score += 20;
	}
	else{
		if (pressedK) {
			player->brakingSound();
			deltaX = 0.f;
			speed -= 2.f;
		}

		speed -= 0.5f;
		musicVolume--;

		if (speed < 0 || musicVolume < 0) {
			speed = 0.f;
			musicVolume = 0.f;
		}

		backgroundLocation += speed * deltaTime.asSeconds() * acceleration;	
	}
	
	player->steerAction(speed, deltaX, acceleration, deltaTime);

	//background scrolling limiter
	backgroundLocation = (backgroundLocation > 0) ? backgroundLocation = -screenHeight : backgroundLocation;
	
	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		player->drivingSoundPause();
		player->crashedSound();
		Sleep(1000);
		isGameOver = true;
	}


	if (speed == 1.f) {
		player->drivingSound();
	}
	else if (speed == 0.f) {
		player->drivingSoundPause();
	}
	
	if (playerBounds.left + deltaX < 0)
		deltaX = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		deltaX = screenWidth - playerSize.x - playerBounds.left;

	if (hurdle->carShape.getPosition().y > screenHeight) {
		Coordinate reset = hurdle->randomizer();
		this->hurdle->carShape.setPosition(reset.x, reset.y);
	}

	//character movement
	this->player->carShape.move(deltaX, deltaY);
	this->music.setVolume(musicVolume);
}


//renderer
void Game::renderGameplay(){
	this->window->clear();
	renderBackground();
    this->window->draw(hurdle->carShape);
	this->window->draw(player->carShape);
	renderScoreCard();
	renderSpeedometer();
	this->window->display();
}

void Game::renderGameOver(){
	std::ostringstream displayYouLose;
	displayYouLose << "You Lose!\nScore: " << score;
	this->gameOver.setString(displayYouLose.str());
	this->window->clear();
	this->window->draw(gameOver);
	this->window->display();
	Sleep(5000);
}

//Game states
void Game::resetState(bool& atMenu, bool& isGameOver){
	atMenu = true;
	deltaX = 0.f;
	score  = 0;
	speed  = 0.f;
	player->drivingSoundPause();
	Coordinate reset = this->hurdle->randomizer();
	this->hurdle->carShape.setPosition(reset.x, -200.f);
	this->player->carShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
	friction = 32.f;
	isGameOver  = false;
}



