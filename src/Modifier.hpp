// Modifier.hpp

#pragma once
#include <string>

class Modifier {
private:
	/*
	mod[0] = damage
	mod[1] = attack speed
	mod[2] = attack range
	mod[3] = bullet radius
	mod[4] = velocity
	mod[5] = duration
	mod[6] = radius
	*/
	static const int _TOWER_ARRAY_SIZE = 7;
	float _tower_modifier[_TOWER_ARRAY_SIZE]{ 0 };
	std::string _tower_bullet_type = "DEFAULT";

	/*
	mod[0] = health
	mod[1] = radius
	*/
	static const int _ENEMY_ARRAY_SIZE = 2;
	float _enemy_modifier[_ENEMY_ARRAY_SIZE]{ 0 };

	bool _tower_scalar_mode = false;
	bool _enemy_scalar_mode = false;
	bool _update_tower_bullet_type = false;


public:
	Modifier();

	// Set Tower Methods
	void setTowerDamage(float damage) { _tower_modifier[0] = damage; };
	void setTowerAttackSpeed(float speed) { _tower_modifier[1] = speed; };
	void setTowerAttackRange(float range) { _tower_modifier[2] = range; };
	void setTowerBulletRadius(float radius) { _tower_modifier[3] = radius; }
	void setTowerVelocity(float velocity) { _tower_modifier[4] = velocity; }
	void setTowerDuration(float duration) { _tower_modifier[5] = duration; }
	void setTowerRadius(float size) { _tower_modifier[6] = size; }
	void setTowerBulletType(std::string type) { _tower_bullet_type = type; _update_tower_bullet_type = true; }

	// Set Enemy Methods
	void setEnemyHealth(float health) { _enemy_modifier[0] = health; }
	void setEnemyRadius(float radius) { _enemy_modifier[1] = radius; }

	// Get Tower Methods
	float getTowerDamage() { return _tower_modifier[0]; };
	float getTowerAttackSpeed() { return _tower_modifier[1]; };
	float getTowerAttackRange() { return _tower_modifier[2]; };
	float getTowerBulletRadius() { return _tower_modifier[3]; }
	float getTowerVelocity() { return _tower_modifier[4]; }
	float getTowerDuration() { return _tower_modifier[5]; }
	float getTowerRadius() { return _tower_modifier[6]; }
	int getTowerArraySize() { return _TOWER_ARRAY_SIZE; }
	bool getTowerScalarMode() { return _tower_scalar_mode; }
	std::string getTowerBulletType() { return _tower_bullet_type; }

	// Get Enemy Methods
	float getEnemyHealth() { return _enemy_modifier[0]; }
	float getEnemyRadius() { return _enemy_modifier[1]; }
	int getEnemyArraySize() { return _ENEMY_ARRAY_SIZE; }
	bool getEnemyScalarMode() { return _enemy_scalar_mode; }

	bool updateTowerBulletType() { return _update_tower_bullet_type; } // Returns whether modifier modifies bullet type

	void toggleTowerScalarModeAndClear(); // Toggles scalar mode for tower modifiers and clears ({0} if additive, {1} if scalar)
	void toggleEnemyScalarModeAndClear(); // Toggles scalar mode for enemy modifiers and clears ({0} if additive, {1} if scalar)
	void towerClear(); // Clears tower modifiers ({0} if additive, {1} if scalar)
	void enemyClear(); // Clears enemy modifiers ({0} if additive, {1} if scalar)
};
