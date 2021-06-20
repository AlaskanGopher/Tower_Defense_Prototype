#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <math.h>

class Tower {
public:
	Tower() {

	};
	Tower(float damage) : _damage(damage) {

	};
	Tower(float damage, float attack_speed) : _damage(damage), _attack_speed(attack_speed) {

	};
	Tower(float damage, float attack_speed, float attack_range) : _damage(damage), _attack_speed(attack_speed), _attack_range(attack_range) {

	};

	void update(sf::RenderWindow window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition();
		if(_attack_range = std::sqrt(pow(mousePosition.x + _tower.getOrigin().x,2) + pow(mousePosition.y + _tower.getOrigin().y,2))){ 
			
		}
	}

	void draw(sf::RenderWindow window)
	{
		window.draw(_tower);
		for(int i = 0; i < _shots.size(); i++)
		{
			window.draw(_shots[i]);
		}
	};

	// Set Commands
	void setDamage(float damage) {
		_damage = damage;
	};
	void setAttackSpeed(float speed) {
		_attack_speed = speed;
	};
	void setAttackRange(float range) {
		_attack_range = range;
	};

	// Get Commands
	float getDamage() { return _damage; };
	float getAttackSpeed() { return _attack_speed; };
	float getAttackRange() { return _attack_range; };

private:
	// Modifable
	float _damage = 1; // Damage per Projectile
	float _attack_speed = 1; // Shots per Second
	float _attack_range = 100; // Range of which the tower can shoot

	// internal
	sf::CircleShape _tower;
	std::vector<sf::CircleShape> _shots;
	
	void tower_initalize() {
		_tower.setRadius(100);
		_tower.setOrigin(_tower.getPosition().x + _tower.getGlobalBounds().width / 2, _tower.getPosition().y + _tower.getGlobalBounds().height / 2);
		_tower.setPosition(100,100);
	}
};