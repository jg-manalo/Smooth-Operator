#include "Game.h"

//constructor and destructor
Game::Game(){
	this->initEntity();
	this->videoMode.height = 600;
	this->videoMode.width = 800;
	this->window = new sf::RenderWindow(this -> videoMode, "Smooth Operator", sf::Style::Titlebar | sf::Style::Close);
	this->window->setFramerateLimit(60);
}

Game::~Game() {
	delete this->window;
}

//player initializer
void Game::initEntity(float x, float y) {
	this->shape.setSize(sf::Vector2f(50.f, 50.f));
	this->shape.setFillColor(sf::Color::Cyan);
	this->shape.setPosition(x, y);
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
	if (key == sf::Keyboard::W)
		pressedW = isPressed;
	else if (key == sf::Keyboard::A)
		pressedA = isPressed;
	else if (key == sf::Keyboard::S)
		pressedS = isPressed;
	else if (key == sf::Keyboard::D)
		pressedD = isPressed;
	return;
}


//game logic
void Game::update(sf::Time deltaTime){
	sf::Vector2f movement(0.f, 0.f);
	if (pressedW)
		movement.y -= 1.f;
	else if (pressedA)
		movement.x -= 1.f;
	else if (pressedS)
		movement.y += 1.f;
	else if (pressedD)
		movement.x += 1.f;

	this->shape.move(movement * deltaTime.asSeconds());

}

//texture handler or renderer
void Game::render(){
	this->window->clear();
	this->window->draw(this->shape);
	this->window->display();
}