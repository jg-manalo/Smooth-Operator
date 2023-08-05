// This is a personal academic project. Dear PVS-Studio, please check it.

// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Game.h"
#include "Player.h"
#include "Hurdle.h"
#include<iostream>
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
	this->videoMode.height = SCREEN_HEIGHT;
	this->videoMode.width = SCREEN_WIDTH;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);

	
	this->icon.loadFromFile("graphics/leo.png");
	this->window->setIcon(icon.getSize().x, icon.getSize().y, icon.getPixelsPtr());
	this->window->setFramerateLimit(60);
	this->player = new Player();
	this->hurdle = new Hurdle();
	this->music.openFromFile("sounds/cimh.mp3");
	this->font.loadFromFile("fonts/racing.ttf");
	this->scoreCard.setFont(font);
	this->speedometer.setFont(font);
	this->speedometer.setPosition(550.f, 0.f);
	this->scoreCard.setPosition(50.f, 0.f);
	
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
	this->road.loadFromFile("graphics/px_roadstar.png");
	this->background.setTexture(road);
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
	sf::Vector2f playerPos = player->playerShape.getPosition();
	sf::FloatRect playerBounds = player->playerShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->hurdleShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->playerShape.getSize();


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
		accelerate(speed);
		musicVolumeControl(musicVolume);
		backgroundLocation += speed * deltaTime.asSeconds() * acceleration;
		deltaY += speed / friction * deltaTime.asSeconds() * acceleration;
		hurdle->hurdleShape.move(0, deltaY);
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
	
	steerAction(speed, deltaX, acceleration, deltaTime);

	//background scrolling limiter
	backgroundLocation = (backgroundLocation > 0) ? backgroundLocation = -screenHeight : backgroundLocation;
	
	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		player->drivingSoundPause();
		crashedSound();
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

	if (hurdle->hurdleShape.getPosition().y > screenHeight) {
		Coordinate reset = this->hurdle->randomizer();
		this->hurdle->hurdleShape.setPosition(reset.x, reset.y);
	}

	//character movement
	this->player->playerShape.move(deltaX, deltaY);
	this->music.setVolume(musicVolume);
}


//renderer
void Game::renderGameplay(){
	this->window->clear();
	renderBackground();
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);
	renderScoreCard();
	renderSpeedometer();
	this->window->display();
}

void Game::renderGameOver(){
	std::ostringstream displayYouLose;
	displayYouLose << "You Lose!\nScore: " << score;
	this->gameOver.setFont(font);
	this->gameOver.setString(displayYouLose.str());
	this->gameOver.setPosition(SCREEN_WIDTH_HALVED - 50.f, SCREEN_HEIGHT_HALVED - 50.f);
	this->window->clear();
	this->window->draw(gameOver);
	this->window->display();
	Sleep(5000);
}

void Game::resetState(bool& atMenu, bool& isGameOver){
	atMenu = true;
	deltaX = 0.f;
	score = 0;
	speed = 0.f;
	player->drivingSoundPause();
	Coordinate reset = this->hurdle->randomizer();
	this->hurdle->hurdleShape.setPosition(reset.x, -200.f);
	this->player->playerShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
	friction = 32.f;
	isGameOver  = false;
}

float Game::steerAction(float& speed, float& deltaX, const float& acceleration, sf::Time& deltaTime){
	if (speed > 0) {
		if (pressedA)
			deltaX -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			deltaX += acceleration * deltaTime.asSeconds();
	}
	return deltaX;
}

float Game::accelerate(float& speed){
	speed += 0.5f;
	return speed = (speed > 350.f) ? speed = 350.f : speed;
}

float Game::musicVolumeControl(float& musicVolume){
	musicVolume += 0.5f;
	return musicVolume = (musicVolume > 100.f) ? musicVolume = 100.f : musicVolume; ;
}

void Game::crashedSound(){
	this->buffer.loadFromFile("sounds/undertaker.mp3");
	this->crash.setBuffer(buffer);
	this->crash.play();
}
