// InstanceEnemy.cpp

#include "InstanceEnemy.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Vectors.hpp"
#include "Modifier.hpp"

#define _USE_MATH_DEFINES
#include <math.h>

void InstanceEnemy::modifyStats(Modifier mod) {
	if (!_invalid_enemy) {
		if (mod.getEnemyScalarMode()) {
			_health *= mod.getEnemyHealth();
			_radius *= mod.getEnemyRadius();
		}
		else {
			_health += mod.getEnemyHealth();
			_radius += mod.getEnemyRadius();
		}
	}
}

void InstanceEnemy::createInstanceEnemy(std::string enemyName, int type, Modifier mod) {

	if (enemyName.compare("Green") == 0) {
		_appearance = sf::Color::Green;
		switch (type) {
			// Case 1 is currently the same as default
		case 1: {
			_health = 3;
			_radius = 10;
			modifyStats(mod);
			break;
		}
		default: {
			type = 0;
			_health = 3;
			_radius = 10;
			modifyStats(mod);
			break;
		}
		}

	}
	else if (enemyName.compare("Red") == 0) {
		_appearance = sf::Color::Red;
		switch (type) {
			// Case 1 is currently the same as default
		case 1: {
			_health = 3;
			_radius = 10;
			modifyStats(mod);
			break;
		}
		default: {
			type = 0;
			_health = 3;
			_radius = 10;
			modifyStats(mod);
			break;
		}
		}

	}
	else {
		_appearance = sf::Color::Yellow;
		_invalid_enemy = true;
		enemyName = "Invalid Enemy";
		type = -1;
		_health = 1;
		_radius = 10;
	}

	_enemy_name = enemyName;
	_enemy_type = type;
}