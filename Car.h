#ifndef CAR_H
#define CAR_H

#include<SFML/Graphics.hpp>
#include<SFML/Audio.hpp>

struct Coordinate {
	float x;
	float y;
};

class Car{
public:
	Car();

	Coordinate randomizer();

	void drivingSoundFX();
	void drivingSoundPauseFX();
	void brakingSoundFX();
	void crashedSoundFX();

	float steerAction(const float& speed, float& deltaX, const float& acceleration, sf::Time& deltaTime, const float& pressedA, const float& pressedD);
	float accelerate(float& speed);
	float musicVolumeControl(float& musicVolume);

public:
	sf::Texture carSkin;
	sf::RectangleShape carShape;
private:
	sf::SoundBuffer driveSoundBuffer;
	sf::SoundBuffer brakeSoundBuffer;
	sf::SoundBuffer crashedSoundBuffer;
	sf::Sound drivingSound;
	sf::Sound brakingSound;
	sf::Sound crashedSound;

public: //physics variables
	float speed;
	const float acceleration;
	float deltaX;
	float deltaY;
	float friction;
};

#endif