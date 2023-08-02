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
Game::Game() : speed{ 0.f }, acceleration{ 10.f }, dx{ 0.f }, dy{ 0.f }, 
			   score{ 0 }, musicVol{ 0.f }, atMenu{ true }, friction {32.f},
			   playing { true } 
{
	this->videoMode.height = SCREEN_HEIGHT;
	this->videoMode.width = SCREEN_WIDTH;
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
void Game::renderBG() {
	this->road.loadFromFile("graphics/px_roadstar.png");
	this->background.setTexture(road);
	background.setPosition(0.f, background2_Y);
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
		else if (playing){
			update(deltaTime, SCREEN_WIDTH, SCREEN_HEIGHT);
			renderGameplay();
		}
		else{
			renderGameOver();
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

//displaying score
void Game::renderScoreCard(){
	std::ostringstream scoreDisplay;
	scoreDisplay << "Score: " << score;
	this->scoreCard.setString(scoreDisplay.str());
	this->window->draw(this->scoreCard);
}

//displaying speed
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

	if (score == 1000) {
		this->music.play();
		this->music.setVolume(0);
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
		float dy = 0.f;
		//speed limiter
		accelerate(speed);
		musicVolControl(musicVol);
		background2_Y += (speed) * deltaTime.asSeconds() * acceleration;
		dy += speed / friction * deltaTime.asSeconds() * acceleration;
		hurdle->hurdleShape.move(0, dy);
		score += 20;
	}
	else{
		if (pressedK) {
			dx = 0.f;
			speed -= 2.f;
		}
		speed-= 0.5f;
		musicVol --;
		if (speed < 0 || musicVol < 0) {
			speed = 0.f;
			musicVol = 0.f;
		}
		background2_Y += (speed)*deltaTime.asSeconds() * acceleration;
		
	}
	
	steerAction(speed, dx, acceleration, deltaTime);

	//background scrolling limiter
	background2_Y = (background2_Y > 0) ? background2_Y = -screenHeight : background2_Y;
	


	//collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		crashedSound();
		playing = false;
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
void Game::renderGameplay() {
	this->window->clear();
	renderBG();
	renderScoreCard();
	renderSpeedometer();
	
    this->window->draw(hurdle->hurdleShape);
	this->window->draw(player->playerShape);

	this->window->display();
}

void Game::renderGameOver()
{
	std::ostringstream displayYouLose;
	displayYouLose << "You Lose!\nScore: " << score;
	this->gameOver.setFont(font);
	this->gameOver.setString(displayYouLose.str());
	this->gameOver.setPosition(SCREEN_WIDTH_HALVED - 50.f, SCREEN_HEIGHT_HALVED - 50.f);
	this->window->clear();
	this->window->draw(gameOver);
	this->window->display();
	Sleep(5000);
	atMenu = true;
	dx = 0.f;
	score = 0.f;
	speed = 0.f;
	Coordinate reset = this->hurdle->randomizer();
	this->hurdle->hurdleShape.setPosition(reset.x, reset.y);
	playing = true;
}

float Game::steerAction(float& speed, float& dx, const float& acceleration, sf::Time& deltaTime)
{
	if (speed > 0) {
		if (pressedA)
			dx -= acceleration * deltaTime.asSeconds();
		else if (pressedD)
			dx += acceleration * deltaTime.asSeconds();
	}
	return dx;
}

float Game::accelerate(float& speed)
{
	speed+= 0.5f;
	return speed = (speed > 350.f) ? speed = 350.f : speed;
}

float Game::musicVolControl(float& musicVol)
{
	musicVol += 0.5f;
	return musicVol = (musicVol > 100.f) ? musicVol = 100.f : musicVol; ;
}

void Game::crashedSound()
{
	this->buffer.loadFromFile("sounds/undertaker.mp3");
	this->crash.setBuffer(buffer);
	this->crash.play();
}
