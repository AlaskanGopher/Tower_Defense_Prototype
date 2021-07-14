// Bullet.hpp

#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Enemy.hpp"

class Bullet {
private:
	sf::Vector2f _pos;

	// Default values; Adjust in Tower::createTowerType to properly update
	float _angle = 0;
	float _velocity = 0;
	float _duration = 0;
	float _radius = 5;
	float _damage = 1;

	bool _dead = true;

	sf::CircleShape _shape;

public:
	Bullet();

	// Set Functions
	void setPosition(sf::Vector2f pos) { _pos = pos; }
	void setAngle(float angle) { _angle = angle; }
	void setVelocity(float velocity) { _velocity = velocity; }
	void setDuration(float duration) { _duration = duration; }
	void setDead(bool dead) { _dead = dead; }
	void setDamage(float damage) { _damage = damage; }
	void setRadius(float radius) { _radius = radius; }

	// Get Functions
	sf::Vector2f getPos() { return _pos; }
	float getAngle() { return _angle; }
	float getVelocity() { return _velocity; }
	float getDuration() { return _duration; }
	float getDamage() { return _damage; }
	bool getDead() { return _dead; }
	float getRadius(){ return _radius; }

	void update(); // Updates bullet variables
	float checkCollision(Enemy enemy); // Checks if bullet is colliding with enemy and returns damage
	void draw(sf::RenderWindow &window); // Draws bullet
};
