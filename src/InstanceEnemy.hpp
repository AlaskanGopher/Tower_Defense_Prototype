// InstanceEnemy.hpp

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Modifier.hpp"

class InstanceEnemy {
private:
	sf::Color _appearance = sf::Color::Blue; // Appearance (default blue) 
	std::string _enemy_name = "Not Initialized"; // Name stored as a strings
	Modifier _no_mod; // Base modifier for type 

	float _health = 1; // Health of enemy
	float _radius= 10; // Radius of Enemy

	int _enemy_type = 0; // Type Integer

	bool _invalid_enemy = false; // Bool for if enemy is made correctly

public:
	// Set Methods
	void setHealth(float health) { _health = health; }
	void setRadius(float radius) { _radius = radius; }
	void setColor(sf::Color app) { _appearance = app; }
	void setIfInvalidEnemy(bool enemy) { _invalid_enemy = enemy; }

	// Get Methods
	float getHealth() { return _health; }
	float getRadius() { return _radius; }
	sf::Color getColor() { return _appearance; }
	bool getIfInvalidEnemy() { return _invalid_enemy; }

	// Class Methods
	void createInstanceEnemy(std::string name, int type, Modifier mod);
	void modifyStats(Modifier mod);
};