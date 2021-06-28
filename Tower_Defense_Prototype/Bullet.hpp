// Bullet.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Bullet {
private:
	sf::Vector2f _pos;
	float _angle = 0;
	float _velocity = 0;
	sf::CircleShape _shape;

public:
	Bullet();

	// Set Functions
	void setPosition(sf::Vector2f pos) { _pos = pos; }
	void setAngle(float angle) { _angle = angle; }
	void setVelocity(float velocity) { _velocity = velocity; }

	// Get Functions
	sf::Vector2f getPos() { return _pos; }
	float getAngle() { return _angle; }
	float getVelocity() { return _velocity; }

	void update();
	void draw(sf::RenderWindow &window);
};
