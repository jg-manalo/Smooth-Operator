#include "dimension.h"
#include "Game.h"
#include "Hurdle.h"
#include<iostream>
#include<cstdlib>
#include<array>
#include<Windows.h>


//constructor and destructor
Game::Game() : acceleration{ 10.f }, dx{ 0.f }, dy{ 0.f }, velocity{ 50.f } {
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);

	
	this->window->setFramerateLimit(60);
	this->hurdle = new Hurdle();
	this->player = new Player();
	
}

Game::~Game() {
	delete this->hurdle;
	delete this->window;
	hurdle = nullptr;
	window = nullptr;
}

//player initializer
void Game::initEntity(const float x,const float y) {
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(x, y);
}



//background init
void Game::renderBG() {
	this->road.loadFromFile("graphics/roadstar.jpg");
	background.setPosition(0.f, bgy);
	background2.setPosition(0.f, bg2y);
	this->background.setTexture(road);
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
		if (noHurdle) {
			this->hurdle = new Hurdle();
			noHurdle = false;
		}
		update(deltaTime,SCREEN_WIDTH, SCREEN_HEIGHT);
		render();
		
	}
}

//event handler
void Game::processEvents()
{
	while (this->window->pollEvent(this->event)) {
		switch (this->event.type) {

		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->event.key.code == sf::Keyboard::Escape)
				this->window->close();
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
void Game::userInput(sf::Keyboard::Key key, bool isPressed){
	if (key == sf::Keyboard::A)
		pressedA = isPressed;
	else if (key == sf::Keyboard::D)
		pressedD = isPressed;
	else if (key == sf::Keyboard::J)
		pressedJ = isPressed;
}


//randomizing location of coordinates
Coordinate Game::randomizer() {
	Coordinate result;

	std::array<float, 3> xCoord = { 200.f , 100.f, 300.f };
	std::array<float, 3> yCoord = { 0.f , 20.f, 40.f };

	int selectX = std::rand() % 3;
	int selectY = std::rand() % 3;

	result.x = xCoord[selectX];
	result.y = yCoord[selectY];
	return result;
}

void Game::Hurdleizer(){
	if (noHurdle) {
		Coordinate coordinate = randomizer();
		hurdle = new Hurdle(coordinate.x, coordinate.y);
		noHurdle = false;
	}
}

//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	const float acceleration = 10.f;
	float velocity = 50.f;
	float dx = 0.f;
	float dy = 0.f;
	
	sf::Vector2f playerPos = this->player->playerShape.getPosition();
	sf::FloatRect playerBounds = this->player->playerShape.getGlobalBounds();
	sf::FloatRect enemyBounds = this->hurdle->hurdleShape.getGlobalBounds();
	const sf::Vector2f playerSize = this->player->playerShape.getSize();

	if (pressedJ){
		float dy = 0.f;
		bgy += velocity * deltaTime.asSeconds() * acceleration;
		bg2y += velocity * deltaTime.asSeconds() * acceleration;
		dy += velocity / 8 * deltaTime.asSeconds() * acceleration;

		if (pressedA)
			dx -= velocity * deltaTime.asSeconds() * acceleration;
		else if (pressedD)
			dx += velocity * deltaTime.asSeconds() * acceleration;

		this->hurdle->hurdleShape.move(0, dy);
	}

	else {
		velocity -= 2.f;
	}

	//background scrolling animation
	if (bg2y > 0) {
		bgy = 0;
		bg2y = bgy - 500.f;
	}
	
	if (playerBounds.left + dx < 0)
		dx = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		dx = screenWidth - playerSize.x - playerBounds.left;
	

	//window collision checker for the hurdle
	if (hurdle->hurdleShape.getPosition().y > playerPos.y) {
		Coordinate newCoord = randomizer();
		hurdle->hurdleShape.setPosition(newCoord.x, 0.f);
	}


	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		//std::cout << "Collided,crash\n";
		//dx += (velocity / 10.f * 3.f) * deltaTime.asSeconds() * (acceleration * 2.f);
		this->window->close();
	}

	//default character movement
	this->player->playerShape.move(dx, dy);
}


//renderer
void Game::render(){
	this->window->clear();
	renderBG();
	this->window->draw(this->background);
	this->window->draw(this->background2);
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);
	this->window->display();
}