#include "dimension.h"
#include "Game.h"
#include "Player.h"
#include "Hurdle.h"
#include<iostream>
#include <Windows.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

//constructor and destructor
Game::Game() : velocity{ 0.f }, acceleration{ 10.f }, dx{ 0.f }, dy{ 0.f }, score{ 0 } {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->player  = new Player();
	this->hurdle  = new Hurdle();
	this->music.openFromFile("sounds/cimh.mp3");
}

Game::~Game() {
	delete this->player;
	delete this->hurdle;
	delete this->window;
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
const bool Game::isRunning() const{
	return this->window->isOpen();
}

void Game::run() {
	sf::Clock clock;
	while (isRunning()) {
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


//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	sf::Vector2f playerPos = player->playerShape.getPosition();
	sf::Vector2f hurdlePos = hurdle->hurdleShape.getPosition();
	sf::FloatRect playerBounds = player->playerShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->hurdleShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->playerShape.getSize();


	if (pressedJ){
		bool inMaxVelocity = velocity > 250.f;
		float dy = 0.f; //makes the delta y into 0 so that the player's delta y is not affected
		background2_Y += (velocity) * deltaTime.asSeconds() * acceleration; // movement of the background
		dy += velocity / 8 * deltaTime.asSeconds() * acceleration;
		velocity++;
		
		if (inMaxVelocity) velocity = 250.f;
		if (pressedA)
			dx -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			dx += acceleration * deltaTime.asSeconds();
		hurdle->hurdleShape.move(dx / 16.f, dy);
		score += 25;
	}
	else{
		if (pressedK) {
			dx = 0.f;
			velocity -= 2.f;
		}
		velocity--;
		if (velocity < 0) velocity = 0.f;
		background2_Y += (velocity)*deltaTime.asSeconds() * acceleration;
		
	}

	//background scrolling animation
	if (background2_Y > 0)
		background2_Y = -screenHeight;
	
	if (playerBounds.left + dx < 0)
		dx = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		dx = screenWidth - playerSize.x - playerBounds.left;

	if (hurdlePos.y > screenHeight) {
		Coordinate reset = this->hurdle->randomizer();
		this->hurdle->hurdleShape.setPosition(reset.x, reset.y);
	}

	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		this->buffer.loadFromFile("sounds/undertaker.mp3");
		this->crash.setBuffer(buffer);
		this->crash.play();
		Sleep(2000);
		this->window->close();
	}

	//character movement
	this->player->playerShape.move(dx, dy);

	if (score == 900) {
		this->music.play();
		this->music.setRelativeToListener(true);
		this->music.setVolume(5.f);
	}

	//kung nagddrive ba
	if (velocity == 5.f) {
		player->drivingSound();
	}
	else if (velocity == 0.f) {
		player->drivingSoundStop();
	}
}

//renderer
void Game::renderAll() {
	this->window->clear();
	renderBG();
	this->window->draw(this->background);
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);
	this->window->display();
}