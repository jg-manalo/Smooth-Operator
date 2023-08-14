// This is a personal academic project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++, C#, and Java: https://pvs-studio.com
#include "dimension.h"
#include "Game.h"
#include <sstream>
#include <iostream>
#include <thread>
#include <chrono>
#include <stdexcept>
#include <limits>


using std::this_thread::sleep_for;
using std::chrono::seconds;
using std::numeric_limits;

/*the limit of uint32 is reduced by one, to avoid prematurely setting the score at 0
 . Making it to trigger the resetState functionality first */
Game::Game() : score { 0 }, musicVolume { 0.f } , atMenu { true },
			   isGameOver { false }, pressedA { false }, pressedD { false }, 
	           pressedJ{ false }, pressedK { false }, friction { 32.f }, 
			   event{}, maxScore {std::numeric_limits<uint32_t>::max() - 1}
{
	try {
		if (!road.loadFromFile("graphics/px_roadstar.png"))
			throw std::runtime_error("Could not load px_roadstar.png");
		
		if (!font.loadFromFile("fonts/racing.ttf"))
			throw std::runtime_error("Could not load racing.ttf");
		
		if (!music.openFromFile("sounds/cimh.mp3"))
			throw std::runtime_error("Could not load cimh.mp3");
	}
	catch (const std::exception& error) {
		std::cerr << "Error: " << error.what();
	}
	
	this->videoMode.height = static_cast<uint32_t>(SCREEN_HEIGHT);
	this->videoMode.width = static_cast<uint32_t>(SCREEN_WIDTH);
	this->window.create(videoMode, "Smooth Operator", sf::Style::Titlebar | sf::Style::Close);
	
	this->window.setFramerateLimit(60);

	this->background.setTexture(road);
	
	this->player = new Car(); //creates a player object
	this->hurdle = new Hurdle(); //creates a hurdle object 
	


	this->titleScreen.setFont(font);
	this->titleScreen.setCharacterSize(50);
	this->titleScreen.setString("Play Now");
	this->titleScreen.setPosition(SCREEN_WIDTH_HALVED - 100.f, SCREEN_HEIGHT_HALVED - 100.f);


	this->scoreCard.setFont(font);
	this->scoreCard.setCharacterSize(24);
	this->scoreCard.setPosition(25.f, 0.f);

	this->speedometer.setFont(font);
	this->speedometer.setCharacterSize(24);
	this->speedometer.setPosition(SCREEN_WIDTH - 175.f, 0.f);

	this->gameOver.setFont(font);
	this->gameOver.setCharacterSize(50);
	this->gameOver.setPosition(SCREEN_WIDTH_HALVED - (this->gameOver.getCharacterSize() * 2), 
							  SCREEN_HEIGHT_HALVED - (this->gameOver.getCharacterSize() * 2));
}

Game::~Game() {
	delete this->player;
	delete this->hurdle;
	player = nullptr;
	hurdle = nullptr;
}


void Game::resetState(bool& atMenu, bool& isGameOver) {
	isGameOver = false;
	atMenu = true;
	this->pressedJ = false; //makes sure that the gas pedal is not stepped on to avoid premature increment of the score
	player->deltaX = 0.f;
	player->speed = 0.f;
	player->drivingSoundPauseFX();
	Coordinate reset = this->hurdle->randomizer();
	this->hurdle->carShape.setPosition(reset.x, reset.y);
	this->player->carShape.setPosition(STARTING_PLAYER_XPOSITION, STARTING_PLAYER_YPOSITION);
	this->friction = 32.f;
	this->score = 0;
}

//event handler
void Game::processEvents(){
	while (this->window.pollEvent(this->event)) {
		switch (this->event.type) {
			case sf::Event::Closed:
				this->window.close();
				break;
			case sf::Event::KeyPressed:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window.close();
				else if (this->event.key.code == sf::Keyboard::Enter)
					atMenu = false;
				userInput(event.key.code, true);
				break;
			case sf::Event::KeyReleased:
				if (this->event.key.code == sf::Keyboard::Escape)
					this->window.close();
				userInput(event.key.code, false);
				break;
			}

	}
}

//runner drive
const bool Game::isRunning() const{
	return this->window.isOpen();
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
			resetState(this->atMenu, this->isGameOver);
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
	const sf::Vector2f playerSize = player->carShape.getSize();
	sf::Vector2f playerPosition   = player->carShape.getPosition();
	sf::Vector2f enemyPosition    = hurdle->carShape.getPosition();
	sf::FloatRect playerBounds    = player->carShape.getGlobalBounds();
	sf::FloatRect enemyBounds     = hurdle->carShape.getGlobalBounds();


	//score update and difficulty increase mechanism
	try {
		if (this->score > maxScore){
			throw std::runtime_error("Reached Maximum Score limit");
		}
		else if (this->score == 1000) {
			//the music will be heard while the player is accelerating
			this->music.play();
			this->music.setVolume(0.f);
			this->music.setLoop(true);
		}
		else if (this->score == 5000) {
			this->friction /= 2.f;
		}
		else if (this->score == 23000) {
			this->friction /= 2.f;
			hurdle->speed *= 2.f;
		}
		else if (this->score == 50000) {
			this->friction /= 2.f;
		}
	}
	catch (const std::exception& error){
		std::cerr << "Okay okay... You\'ve won: " << error.what() << '\n';
		resetState(this->atMenu, this->isGameOver);
	}

	if (this->pressedJ && !this->isGameOver){
		player->accelerate(player->speed);
		hurdle->accelerate(hurdle->speed);
		player->musicVolumeControl(musicVolume);
		this->score += 20;
	}

	else{
		if (this->pressedK && !this->isGameOver) {
			//break mechanism
			player->brakingSoundFX();
			//when braking, player's deltaX is counteracted by its equilibrant deltaX
			player->deltaX -= (player->deltaX > 0) ? player->deltaX  : player->deltaX = 0.f;
		}

		player->decelerate(player->speed);
		
		this->musicVolume -= (musicVolume < 0.f) ? musicVolume = 0.f : musicVolume = 0.5f;
	}
	
	//player car's steering mechanism
	player->steerAction(player->speed, player->deltaX, player->speedMultiplier, deltaTime, pressedA, pressedD);
	
	//background scrolls when the player starts moving
	backgroundLocation += player->speed * deltaTime.asSeconds() * player->speedMultiplier;
	
	//background scrolling limiter
	backgroundLocation = (backgroundLocation > 0) ? backgroundLocation = -screenHeight : backgroundLocation;
	this->background.setPosition(0, backgroundLocation);
	
	//player and hurdle collision detection
	if (playerBounds.intersects(enemyBounds)) {
		this->music.stop();
		player->crashedSoundFX();
		player->drivingSoundPauseFX();
		sleep_for(seconds(1));
		isGameOver = true;
	}

	//driving sound detector
	if (player->speed == 1.f) {
		player->drivingSoundFX();
	}
	else if (player->speed == 0.f) {
		player->drivingSoundPauseFX();
	}
	
	//window bounds collision detection of the player
	if (playerBounds.left + player->deltaX < 0)
		player->deltaX = -playerBounds.left;
	else if (playerBounds.left > screenWidth - playerSize.x)
		player->deltaX = screenWidth - playerSize.x - playerBounds.left;

	//enemy position window bounds detection
	if (enemyPosition.y > screenHeight) {
		Coordinate reset = hurdle->randomizer();
		hurdle->carShape.setPosition(reset.x, reset.y);
	}

	//character movement and volume control
	this->player->carShape.move(player->deltaX, 0.f);
	this->music.setVolume(player->speed);

	//hurdle movement control
	float deltaY = 0;
	deltaY += player->speed / this->friction * deltaTime.asSeconds() * hurdle->speedMultiplier;
	hurdle->carShape.move(0, deltaY);
}

void Game::renderMenu(){
	this->window.clear();
	this->window.draw(titleScreen);
	this->window.display();
}
void Game::renderBackground() {
	window.draw(this->background);
}
void Game::renderScoreCard(){
	std::ostringstream scoreDisplay;
	scoreDisplay << "Score: " << score;
	this->scoreCard.setString(scoreDisplay.str());
	this->window.draw(this->scoreCard);
}
void Game::renderSpeedometer() {
	std::ostringstream speedDisplay;
	speedDisplay << "Speed: " << player->speed << " kph";
	this->speedometer.setString(speedDisplay.str());
	this->window.draw(this->speedometer);
}

void Game::renderGameplay(){
	this->window.clear();
	this->window.draw(background);
	this->window.draw(this->player->carShape);
    this->window.draw(this->hurdle->carShape);
	renderScoreCard();
	renderSpeedometer();
	this->window.display();
}

void Game::renderGameOver(){
	std::ostringstream displayYouLose;
	displayYouLose << "You Lose!\nScore: " << score;
	this->gameOver.setString(displayYouLose.str());
	this->window.clear();
	this->window.draw(gameOver);
	this->window.display();
	sleep_for(seconds(5));
}