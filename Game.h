#pragma once
#include "Hurdle.h"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <array>

struct Coordinate{
	float x;
	float y;
};

class Game
{
private:
	//boiler plate
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//player var
	sf::RectangleShape playerShape;
	//enemy var
	sf::RectangleShape enemyShape;
	//boolean var for user input
<<<<<<< Updated upstream
	bool pressedA;	
	bool pressedD;
	bool pressedJ;
	
	//bool for hurdle creation
	bool noHurdle;
	
	//Road bg
=======
	bool pressedA = false;	
	bool pressedD = false;
	bool pressedJ = false;
	bool crashed = false;
	bool celebrating = false;
	//Road background
>>>>>>> Stashed changes
	sf::Texture road;
	sf::Sprite background;
	

	//player init
	void initEntity(const float x, const float y);
	sf::Texture car;
	//enemy init
<<<<<<< Updated upstream
	
=======
	Hurdle* hurdle = nullptr;
	bool noHurdle = true;

	//audio
	sf::SoundBuffer buffer;
	sf::Sound crash;

	sf::Music music;
	
	//physics
	const float acceleration;
	float velocity;
	float dx;
	float dy;

>>>>>>> Stashed changes

	//private func
	void renderBG(); //background initializer
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void render();
<<<<<<< Updated upstream
	Coordinate randomizer();
	void Hurdleizer();
=======
>>>>>>> Stashed changes
	
public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;
	
	//func
	void userInput(sf::Keyboard::Key key, bool isPressed);
	void run();

<<<<<<< Updated upstream
	Hurdle* hurdle;
=======
	unsigned long int score = 0;
	
>>>>>>> Stashed changes
};
