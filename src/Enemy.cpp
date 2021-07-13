// Enemy.cpp

#include "Enemy.hpp"
#include "InstanceEnemy.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Vectors.hpp"
#include "Modifier.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

Enemy::Enemy() {};

void Enemy::draw(sf::RenderWindow& window) {
	_shape.setPosition(_pos);
	_shape.setRadius(_instance_radius);
	_shape.setOrigin(_instance_radius, _instance_radius);
	_shape.setFillColor(_instance_color);
	window.draw(_shape);
}

void Enemy::update(float damage) {

	// Make sure there's still an enemy to get color, size, etc
	if (_enemy_vector.size() != 0) {

		// Set health values for an invalid enemy to 1
		if (_invalid_enemy && _health[0] > 0) {
			for (int i = 0; i < _HEALTH_ARRAY_SIZE; i++) {
				_health[i] = 0.1;
			}
		}

		// Set instance variables to the front enemy in the enemy vector
		_instance_color = _enemy_vector[0].getColor();
		_instance_radius = _enemy_vector[0].getRadius();

		// Add the enemy health to the health vector if not yet done
		if (!_initialized) {
			_health[0] += _enemy_vector[0].getHealth();
			_initialized = !_initialized;
		}

		// Inflict damage values to enemy
		_health[0] -= damage;
		_health[1] -= damage;
		
		// Cause enemy to re-initialize if instance health < 0
		while ((_health[0] <= 0) && _enemy_vector.size() > 0) {
			_enemy_vector.erase(_enemy_vector.begin());
			_initialized = !_initialized;
		}
	}
	else {
		_dead = true;
	}
}

void Enemy::clear() {
	_enemy_vector.clear();

	_initialized = false;
	_dead = true;
	_invalid_enemy = false;
}

void Enemy::modifiyAllEnemyStats(Modifier mod) {
	if (!_invalid_enemy) {
		for (int i = 0; i < _enemy_vector.size(); i++) {
			_enemy_vector[i].modifyStats(mod);
		}
	}
}

void Enemy::modifiyInstanceEnemyStats(Modifier mod, int i) {
	if (!_invalid_enemy && (i < _enemy_vector.size()) && (i >= 0)) {
		_enemy_vector[i].modifyStats(mod);
	}
}

void Enemy::createEnemyType(std::string enemyName, int type, sf::Vector2f pos, Modifier mod) {

	if (_first_loop) {
		clear();
		_first_loop = false;
	}

	InstanceEnemy enemy;


	if (enemyName.compare("Green") == 0) {
		sf::Color greenAppearance = sf::Color::Green;
		switch (type) {
			// Case 1 doesn't impliment red recursion
		case 1: {
			enemy.createInstanceEnemy(enemyName, type, mod);
			_enemy_vector.push_back(enemy);
			break;
		}
		default: {
			enemy.createInstanceEnemy(enemyName, type, mod);
			_enemy_vector.push_back(enemy);
			createEnemyType("Red", 0, pos, mod);
			break;
		}
		}

	}
	else if (enemyName.compare("Red") == 0) {
		sf::Color redAppearance = sf::Color::Red;
		switch (type) {
			// Case 1 causes red to ignore modifier
		case 1: {
			enemy.createInstanceEnemy(enemyName, type, mod);
			_enemy_vector.push_back(enemy);
			break;
		}
		default: {
			enemy.createInstanceEnemy(enemyName, type, mod);
			_enemy_vector.push_back(enemy);
			break;
		}
		}

	}
	else {
		enemy.createInstanceEnemy("Invalid Enemy", type, mod);
		_enemy_vector.push_back(enemy);
	}

	// Update global variables
	for (int i = 1; i < _HEALTH_ARRAY_SIZE; i++) {
		_health[i] += enemy.getHealth();
	}

	_health[0] = 0;
	_pos = pos;
	_first_loop = true;
	_dead = false;
	_instance_color = _enemy_vector[0].getColor();
	_instance_radius = _enemy_vector[0].getRadius();
}
