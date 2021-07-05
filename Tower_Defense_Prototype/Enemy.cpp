// Enemy.cpp

#include "Enemy.hpp"

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
	_shape.setRadius(_radius[0]);
	_shape.setOrigin(_radius[0], _radius[0]);
	_shape.setFillColor(_current_color);
	window.draw(_shape);
}

void Enemy::update(float damage) {

	if (!_dead) {
		if (!_invalid_enemy) {
			enforceEnemyPreConditions();
		}
		else if (_instance_health[0] > 0) {
			_instance_health[0] = 0.1;
			_instance_health[1] = 0.1;
			_instance_health[2] = 0.1;
		}

		_current_color = _appearance[0];
		if (!_initialized) {
			_instance_health[0] += _health[0];
			_initialized = !_initialized;
		}
		_instance_health[0] -= damage;
		_instance_health[1] -= damage;
		if (_instance_health[0] <= 0 && _appearance.size() > 1) {
			_appearance.erase(_appearance.begin());
			_health.erase(_health.begin());
			_radius.erase(_radius.begin());
			_enemy_name.erase(_enemy_name.begin());
			_enemy_type.erase(_enemy_type.begin());
			_initialized = !_initialized;
		}
		else if (_instance_health[0] <= 0) {
			_dead = true;
		}
	}
}

void Enemy::modifiyAllEnemyStats(Modifier mod) {
	if (!_invalid_enemy) {
		for (int i = 0; i < _health.size(); i++)
			if (mod.getEnemyScalarMode()) {
				_health[i] *= mod.getEnemyHealth();
				_instance_health[1] *= mod.getEnemyHealth();
				_radius[i] *= mod.getEnemyRadius();
			}
			else {
				_health[i] += mod.getEnemyHealth();
				_instance_health[1] += mod.getEnemyHealth();
				_radius[i] += mod.getEnemyRadius();
			}
	}
}

void Enemy::modifiyFirstEnemyStats(Modifier mod) {
	if (!_invalid_enemy) {
		if (mod.getEnemyScalarMode()) {
			_health[0] *= mod.getEnemyHealth();
			_instance_health[1] *= mod.getEnemyHealth();
			_radius[0] *= mod.getEnemyRadius();
		}
		else {
			_health[0] += mod.getEnemyHealth();
			_instance_health[1] += mod.getEnemyHealth();
			_radius[0] += mod.getEnemyRadius();
		}
	}
}

void Enemy::modifiyLastEnemyStats(Modifier mod) {
	if (_invalid_enemy) {
		if (mod.getEnemyScalarMode()) {
			_health[_health.size() - 1] *= mod.getEnemyHealth();
			_instance_health[1] *= mod.getEnemyHealth();
			_radius[_health.size() - 1] *= mod.getEnemyRadius();
		}
		else {
			_health[_health.size() - 1] += mod.getEnemyHealth();
			_instance_health[1] += mod.getEnemyHealth();
			_radius[_health.size() - 1] += mod.getEnemyRadius();
		}
	}
}

void Enemy::enforceEnemyPreConditions() {
	int sizeCondition = _health.size();
	if (_appearance.size() != sizeCondition) {
		_invalid_enemy = true;
	}
	else if (_enemy_name.size() != sizeCondition) {
		_invalid_enemy = true;
	}
	else if (_radius.size() != sizeCondition) {
		_invalid_enemy = true;
	}
	else if (_enemy_type.size() != sizeCondition) {
		_invalid_enemy = true;
	}
	if (_invalid_enemy) {
		Modifier noMod;
		createEnemyType("", -1, _pos, noMod);
	}
}

void Enemy::createEnemyType(std::string enemyName, int type, sf:: Vector2f pos, Modifier mod) {
	
	if (_first_loop) {
		clear();
		_first_loop = false;
	}

	_pos = pos;
	while (_instance_health.size() != 3) {
		_instance_health.push_back(0.0);
	}
	if (enemyName.compare("Green") == 0) {
		sf::Color greenAppearance = sf::Color::Green;
		switch (type){
			// Case 1 doesn't impliment red recursion
		case 1: {
			float greenHealth = 3;
			float greenSize = 10;
			_instance_health[1] += greenHealth;
			_appearance.push_back(greenAppearance);
			_health.push_back(greenHealth);
			_radius.push_back(greenSize);
			_dead = false;
			_first_loop = true;
			modifiyLastEnemyStats(mod);
			break;
		}
		default: {
			float greenHealth = 3;
			float greenSize = 10;
			type = 0;
			_instance_health[1] += greenHealth;
			_appearance.push_back(greenAppearance);
			_health.push_back(greenHealth);
			_radius.push_back(greenSize);
			_dead = false;
			modifiyLastEnemyStats(mod);
			createEnemyType("Red", 0, pos, mod);
			break;
		}
		}

	}
	else if (enemyName.compare("Red") == 0) {
		sf::Color redAppearance = sf::Color::Red;
		switch (type) {
			// Case 1 is currently the same as default
		case 1: {
			float redHealth = 3;
			float redSize = 10;
			_instance_health[1] += redHealth;
			_appearance.push_back(redAppearance);
			_health.push_back(redHealth);
			_radius.push_back(redSize);
			_dead = false;
			_first_loop = true;
			modifiyLastEnemyStats(mod);
			break;
		}
		default: {
			float redHealth = 3;
			float redSize = 10;
			type = 0;
			_instance_health[1] += redHealth;
			_appearance.push_back(redAppearance);
			_health.push_back(redHealth);
			_radius.push_back(redSize);
			_dead = false;
			_first_loop = true;
			modifiyLastEnemyStats(mod);
			break;
		}
		}

	}
	else {
		_invalid_enemy = true;
		float invalidArgHealth = 0.1;
		float invalidArgSize = 10;
		_instance_health[1] += invalidArgHealth;
		_appearance.push_back(sf::Color::Yellow);
		_health.push_back(invalidArgHealth);
		_radius.push_back(invalidArgSize);
		_dead = false;
		_first_loop = true;
	}

	_instance_health[2] = _instance_health[1];

	if (!_invalid_enemy) {
		_enemy_name.push_back(enemyName);
		_enemy_type.push_back(type);
	}
	else {
		_enemy_name.push_back("Invalid Enemy Name");
		_enemy_type.push_back(-1);
	}
}
