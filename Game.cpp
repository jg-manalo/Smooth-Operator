#include "Game.h"
#include<iostream>
//constructor and destructor

Game::Game(){
	this->initEntity(XDIM, YDIM);
	this->initEnemy(this->playerShape.getPosition().x - 20, this->playerShape.getPosition().y);
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

Game::~Game() {
	delete this->window;
}

//player initializer
void Game::initEntity(const float x,const float y) {
	this->playerShape.setSize(sf::Vector2f(50.f, 50.f));
	this->playerShape.setFillColor(sf::Color::Cyan);
	this->playerShape.setPosition(x, y);
}

//enemy initializer
void Game::initEnemy(float x, float y) {
	this->enemyShape.setRadius(35.f);
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
		update(deltaTime);
		render();
		std::cout << "Time: " << this->playerShape.getPosition().x << '\n';
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
}


//game logic
void Game::update(sf::Time deltaTime){
	const float acceleration = 10.f;
	const float velocity = 50.f;
	sf::Vector2f displacement(0.f, 0.f);
	
	if (pressedA)
		displacement.x -= velocity * deltaTime.asSeconds() * acceleration; 
	else if (pressedD)
		displacement.x += velocity * deltaTime.asSeconds() * acceleration;

	if (this->playerShape.getPosition().x > this->enemyShape.getPosition().x - this->playerShape.getSize().x)
		this->enemyShape.move(5.f, 0);
	else if (this->playerShape.getPosition().x < this->enemyShape.getPosition().x - this->playerShape.getSize().x)
		this->enemyShape.move(-5.f, 0);
	
	this->playerShape.move(displacement);

}

//texture handler or renderer
void Game::render(){
	this->window->clear();
	this->window->draw(this->playerShape);
	this->window->draw(this->enemyShape);
	this->window->display();
}