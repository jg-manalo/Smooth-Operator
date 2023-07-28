#include "dimension.h"
#include "Game.h"
#include "Player.h"
#include "Hurdle.h"
#include<iostream>
#include <Windows.h>
#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

//constructor and destructor
Game::Game() :  velocity{ 50.f }, acceleration{ 10.f }, dx{ 0.f }, dy { 0.f } {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
	this->player = new Player();
	this->hurdle = new Hurdle();

	
}

Game::~Game() {
	delete this->hurdle;
	delete this->window;
	hurdle = nullptr;
	window = nullptr;
}


//background init
void Game::renderBG() {
	this->road.loadFromFile("graphics/roadstar.jpg");
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
		render();
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
	sf::FloatRect playerBounds = player->playerShape.getGlobalBounds();
	sf::FloatRect enemyBounds = hurdle->hurdleShape.getGlobalBounds();
	const sf::Vector2f playerSize = player->playerShape.getSize();

	if (pressedJ){
		float dy = 0.f;
		background2_Y += (velocity++) * deltaTime.asSeconds() * acceleration;
		dy += velocity / 8 * deltaTime.asSeconds() * acceleration;
		if (pressedA)
			dx -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			dx += acceleration * deltaTime.asSeconds();
		hurdle->hurdleShape.move(0, dy);
	}
	else if (pressedK){
		dx = 0.f;
		background2_Y += (velocity--) * deltaTime.asSeconds() * acceleration;
	}
	else {
		velocity = 50.f;
	}

	//background scrolling animation
	if (background2_Y > 0)
		background2_Y = -screenHeight;
	
	if (playerBounds.left + dx < 0)
		dx = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		dx = screenWidth - playerSize.x - playerBounds.left;

	if (hurdle->hurdleShape.getPosition().y > playerPos.y) {
		Coordinate reset = this->hurdle->randomizer();
		this->hurdle->hurdleShape.setPosition(reset.x, reset.y);
	}

	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->buffer.loadFromFile("sounds/congtv.mp3");
		this->crash.setBuffer(buffer);
		this->crash.play();
		this->window->close();
	}

	if (hurdle->hurdleShape.getPosition().y > playerPos.y) {
		Coordinate newCoord = this->hurdle->randomizer();
		hurdle->hurdleShape.setPosition(newCoord.x, 0.f);
	}
	//character movement
	this->player->playerShape.move(dx, dy);
}


//renderer
void Game::render() {
	this->window->clear();
	renderBG();
	this->window->draw(this->background);
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);
	this->window->display();
}