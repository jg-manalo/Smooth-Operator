#pragma once
#include <SFML/Graphics.hpp>

class Game
{
private:
	//private var
	sf::RenderWindow* window;
	sf::VideoMode videoMode;
	sf::Event event;
	sf::View view;


	//player var
	sf::RectangleShape playerShape;
	//enemy var
	sf::RectangleShape enemyShape;
	//boolean var for user input
	bool pressedA;	
	bool pressedD;
	bool pressedJ;

	//player init
	void initEntity(const float x, const float y);
	sf::Texture car;
	//enemy init
	void initEnemy(float x, float y);

	//private func
	void processEvents();
	void update(sf::Time deltaTime, const float screenWidth, const float screenHeight);
	void render();

public:
	//positioning default initializer computation ang salaula
	const float SCREEN_HEIGHT = 600.f;
	const float SCREEN_WIDTH = 800.f;
	const float SCREEN_WIDTH_HALVED  = 800.f / 2.f;
	const float SCREEN_HEIGHT_HALVED = 600.f / 2.f;
	const float XDIM = SCREEN_WIDTH_HALVED  - 50.f;
	const float YDIM = SCREEN_HEIGHT_HALVED - 50.f + 200;

	//constructor/destructor
	Game();
	virtual ~Game();

	//Accessor
	const bool running() const;
	
	//func
	void userInput(sf::Keyboard::Key key, bool isPressed);
	void run();

	//Road bg
	sf::Texture road;
	sf::Sprite background;
	sf::Sprite background2;


};

