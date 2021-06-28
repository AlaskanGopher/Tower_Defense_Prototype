// Tower.hpp

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#include "Bullet.hpp"

class Tower {
private:
	// Modifable
	sf::Vector2f _pos;
	float _angle_facing = 0;
	float _damage = 1; // Damage per Projectile
	float _attack_speed = 1; // Shots per Second
	float _attack_range = 100; // Range of which the tower can shoot

	// internal
	sf::Clock _attack_timer;
	sf::CircleShape _shape;
	sf::CircleShape _range_shape;
	std::vector<Bullet> _bullets;

public:
	Tower();

	// Set Commands
	void setPosition(sf::Vector2f pos) { _pos = pos; }
	void setAngleFacing(float angle_facing) { _angle_facing = angle_facing; }
	void setDamage(float damage) { _damage = damage; };
	void setAttackSpeed(float speed) { _attack_speed = speed; };
	void setAttackRange(float range) { _attack_range = range; };

	// Get Commands
	sf::Vector2f getPosition() { return _pos; }
	float getAngleFacing() { return _angle_facing; }
	float getDamage() { return _damage; };
	float getAttackSpeed() { return _attack_speed; };
	float getAttackRange() { return _attack_range; };

	void lookAt(sf::Vector2f target);
	void spawnBullet();
	void update(sf::Window &window);
	void draw(sf::RenderWindow &window);
};


