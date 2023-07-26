#pragma once
#include "Hurdle.h"
#include <SFML/Graphics.hpp>
#include <array>

struct Coordinate{
	float x;
	float y;
};

class Game
{
private:
	//private var
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;

	//player var
	sf::RectangleShape playerShape;
	//enemy var
	sf::RectangleShape enemyShape;
	//boolean var for user input
	bool pressedA;	
	bool pressedD;
	bool pressedJ;
	
	//bool for hurdle creation
	bool noHurdle;
	
	//Road bg
	sf::Texture road;
	sf::Sprite background;
	sf::Sprite background2;
	

	//bg init
	void renderBG();
	
	//player init
	void initEntity(const float x, const float y);
	sf::Texture car;
	//enemy init
	

	//private func
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void render();
	Coordinate randomizer();
	void Hurdleizer();
	
public:
	//constructor/destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;
	
	//func
	void userInput(sf::Keyboard::Key key, bool isPressed);
	void run();

	Hurdle* hurdle;
};
