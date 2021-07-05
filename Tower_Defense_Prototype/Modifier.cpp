// Modifier.cpp

#include "Modifier.hpp"
#include <string>

Modifier::Modifier() {}

void Modifier::toggleTowerScalarModeAndClear() {
	if (!_tower_scalar_mode) {
		_tower_scalar_mode = true;
		towerClear();
	}
	else {
		_tower_scalar_mode = false;
		towerClear();
	}
}

void Modifier::toggleEnemyScalarModeAndClear() {
	if (!_enemy_scalar_mode) {
		_enemy_scalar_mode = true;
		enemyClear();
	}
	else {
		_tower_scalar_mode = false;
		enemyClear();
	}
}

void Modifier::towerClear() {
	_update_tower_bullet_type = false;
	if (_tower_scalar_mode) {
		for (int i = 0; i < _TOWER_ARRAY_SIZE; i++) {
			_tower_modifier[i] = 1;
		}
	}
	else {
		for (int i = 0; i < _TOWER_ARRAY_SIZE; i++) {
			_tower_modifier[i] = 0;
		}
	}
}

void Modifier::enemyClear() {
	if (_enemy_scalar_mode) {
		for (int i = 0; i < _ENEMY_ARRAY_SIZE; i++) {
			_enemy_modifier[i] = 1;
		}
	}
	else {
		for (int i = 0; i < _ENEMY_ARRAY_SIZE; i++) {
			_enemy_modifier[i] = 0;
		}
	}
}