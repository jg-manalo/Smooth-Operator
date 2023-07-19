#pragma once
#include <SFML/Graphics.hpp>

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
	sf::CircleShape enemyShape;
	//boolean var for user input
	bool pressedA;	
	bool pressedD;

	//player init
	void initEntity(const float x, const float y);

	//enemy init
	void initEnemy(float x, float y);

	//private func
	void processEvents();
	void update(sf::Time deltaTime);
	void render();

public:
	//positioning default initializer computation ang salaula
	const float SCREEN_WIDTH_HALVED  = 800.f / 2;;
	const float SCREEN_HEIGHT_HALVED = 600.f / 2;
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
};

