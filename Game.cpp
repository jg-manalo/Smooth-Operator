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
Game::Game() : speed{ 0.f }, acceleration{ 10.f }, dx{ 0.f }, dy{ 0.f }, score{ 0 }, musicVol{ 0.f } {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->player = new Player();
	this->hurdle = new Hurdle();
	this->music.openFromFile("sounds/cimh.mp3");
	this->font.loadFromFile("fonts/racing.ttf");
	this->scoreCard.setFont(font);
	this->speedometer.setFont(font);
	this->speedometer.setPosition(SCREEN_HEIGHT, 0.f);
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


//background init
void Game::renderBG() {
	this->road.loadFromFile("graphics/px_roadstar.png");
	this->background.setTexture(road);
	background.setPosition(0.f, background2_Y);
}

//runner drive
const bool Game::running() const{
	return this->window->isOpen();
}

void Game::run() {
	sf::Clock clock;
	while (running()) {
		sf::Time deltaTime = clock.restart();
		processEvents();
		update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
		renderAll();
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
				if (this->event.key.code == sf::Keyboard::Escape) {
					this->window->close();
				}
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

//displaying score
void Game::renderScoreCard(){
	std::stringstream scoreDisplay;
	scoreDisplay << "Score: " << score;
	this->scoreCard.setString(scoreDisplay.str());
}

//displaying speed
void Game::renderSpeedometer() {
	std::stringstream speedDisplay;
	speedDisplay << "Speed: " << speed << " kph";
	this->speedometer.setString(speedDisplay.str());
}

//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	sf::Vector2f playerPos = player->playerShape.getPosition();
	sf::FloatRect playerBounds = player->playerShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->hurdleShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->playerShape.getSize();

	if (score == 1000) {
		this->music.play();
		this->music.setVolume(0);
	}

	if (pressedJ){
		float dy = 0.f;
		
		//speed limiter
		speed++;
		if (speed > 250.f) speed = 250.f;
		background2_Y += (speed) * deltaTime.asSeconds() * acceleration;
		dy += speed / 8 * deltaTime.asSeconds() * acceleration;
		if (pressedA)
			dx -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			dx += acceleration * deltaTime.asSeconds();
		hurdle->hurdleShape.move(0, dy);
		musicVol+= 0.5f;
		if (musicVol > 100.f) musicVol = 100.f;
		score += 20;
	
	}
	else{
		if (pressedK) {
			dx = 0.f;
			speed -= 2.f;
		}
		speed--;
		musicVol --;
		if (speed < 0 || musicVol < 0) {
			speed = 0.f;
			musicVol = 0.f;
		}
		background2_Y += (speed)*deltaTime.asSeconds() * acceleration;
		
	}

	//background scrolling animation
	if (background2_Y > 0)
		background2_Y = -screenHeight;
	

	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		this->buffer.loadFromFile("sounds/undertaker.mp3");
		this->crash.setBuffer(buffer);
		this->crash.play();
		Sleep(2000);
		this->window->close();
	}


	if (speed == 1.f) {
		player->drivingSound();
	}
	else if (speed == 0.f) {
		player->drivingSoundPause();
	}
	
	if (playerBounds.left + dx < 0)
		dx = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		dx = screenWidth - playerSize.x - playerBounds.left;

	if (hurdle->hurdleShape.getPosition().y > screenHeight) {
		Coordinate reset = this->hurdle->randomizer();
		this->hurdle->hurdleShape.setPosition(reset.x, reset.y);
	}

	//character movement
	this->player->playerShape.move(dx, dy);
	this->music.setVolume(musicVol);
}


//renderer
void Game::renderAll() {
	this->window->clear();
	renderBG();
	renderScoreCard();
	renderSpeedometer();
	this->window->draw(this->background);
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);
	this->window->draw(this->scoreCard);
	this->window->draw(this->speedometer);
	this->window->display();
}