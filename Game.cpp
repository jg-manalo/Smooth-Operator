#include "Game.h"
#include<iostream>
//constructor and destructor

Game::Game(){
	this->initEntity(XDIM, YDIM);
	//this->initEnemy(25.f, YDIM);
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator",
										sf::Style::Titlebar | sf::Style::Close);
	this->view = sf::View(sf::FloatRect(0.f, 0.f, SCREEN_WIDTH, SCREEN_HEIGHT));
	this->window->setFramerateLimit(60);
}

Game::~Game() {
	delete this->window;
}




//player initializer
void Game::initEntity(const float x,const float y) {
	this->playerShape.setSize(sf::Vector2f(100.f, 150.f));
	car.loadFromFile("J:/devgame/graphics/car.png");
	this->playerShape.setTexture(&car);
	this->playerShape.setPosition(x, y);
}

//enemy initializer
void Game::initEnemy(float x, float y) {
	this->enemyShape.setSize(sf::Vector2f(50.f, 150.f));
	this->enemyShape.setFillColor(sf::Color::Red);
	this->enemyShape.setPosition(x,y);
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


static float bgy = 0.f;
static float bg2y = -600.f;
//game logic
void Game::update(sf::Time deltaTime, const float screenWidth, const float screenHeight){
	const float acceleration = 10.f;
	float velocity = 50.f;
	float dx = 0.f;
	float dy = 0.f;
	sf::Vector2f playerPos = this->playerShape.getPosition();
	sf::FloatRect playerBounds = this->playerShape.getGlobalBounds();

	sf::Vector2f enemyPos = this->enemyShape.getPosition();
	sf::FloatRect enemyBounds = this->enemyShape.getGlobalBounds();

	const sf::Vector2f playerSize = this->playerShape.getSize();
	const sf::Vector2f enemySize = this->enemyShape.getSize();



	if (pressedJ) {
		bgy += velocity * deltaTime.asSeconds() * acceleration;
		bg2y += velocity * deltaTime.asSeconds() * acceleration;
		if (pressedA)
			dx -= velocity / 2 * deltaTime.asSeconds() * acceleration;
		else if (pressedD)
			dx += velocity / 2 * deltaTime.asSeconds() * acceleration;
	}
	else {
		velocity -= 2.f;
	}

	//bounds checker
	if (bg2y > 0) {
		bgy = 0;
		bg2y = bgy - 500.f;
	}
	if (playerBounds.left + dx < 0)
		dx = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		dx = screenWidth - playerSize.x - playerBounds.left;
	
	//character movement
	this->playerShape.move(dx, dy);
	
}

//texture handler or renderer
void Game::render(){
	this->window->clear();
	this->road.loadFromFile("J:/devgame/graphics/roadstar.jpg");
	background.setPosition(0.f, bgy);
	background2.setPosition(0.f, bg2y);
	this->background.setTexture(road);
	this->background2.setTexture(road);
	this->window->draw(background);
	this->window->draw(background2);
	this->window->draw(this->playerShape);
	this->window->display();
}