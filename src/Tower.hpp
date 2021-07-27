// Tower.hpp

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Bullet.hpp"
#include "Enemy.hpp"
#include "Modifier.hpp"

class Tower {
private:
	// Modifable
	sf::Vector2f _pos;
	sf::Color _fill_color = sf::Color::Red; // Fill color
	float _angle_facing = 0;  // Angle that tower is looking at

	// Default values; Adjust in Tower::createTowerType to properly update
	float _damage = 1; // Damage per Projectile
	float _attack_speed = 1; // Shots per Second
	float _attack_range = 100; // Range of which the tower can shoot
	float _bullet_radius = 5; // Bullet radius
	float _velocity = 10; // Tower bullet speed
	float _duration = 200; // Distance bullet travels from tower
	float _tower_radius = 25; // Radius of tower
	int _kill_count = 0; // Internal Tower Kill Counter
	float _damage_dealt = 0.0; // Internal Damage Dealt Counter

	int _tower_type = 0;
	std::string _tower_name = "DEFAULT";
	std::string _bullet_type = "DEFAULT";

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
	void setBulletRadius(float radius) { _bullet_radius = radius; }
	void setVelocity(float velocity) { _velocity = velocity; }
	void setDuration(float duration) { _duration = duration; }
	void setTowerRadius(float size) { _tower_radius = size; }
	void setBulletType(std::string type) { _bullet_type = type;}
	void setTowerName(std::string name) { _tower_name = name; }
	void setTowerType(int type) { _tower_type = type; }
	void setKillCount(int count) { _kill_count = count; }
	void setDamageDealt(float damage) { _damage_dealt = damage; }

	// Get Commands
	sf::Vector2f getPosition() { return _pos; }
	float getAngleFacing() { return _angle_facing; }
	float getDamage() { return _damage; };
	float getAttackSpeed() { return _attack_speed; };
	float getAttackRange() { return _attack_range; };
	float getBulletRadius() { return _bullet_radius; }
	float getVelocity() { return _velocity; }
	float getDuration() { return _duration; }
	float getTowerRadius() { return _tower_radius; }
	float getDamageDealt() { return _damage_dealt; }
	int getKillCount() { return _kill_count; }
	int getTowerType() { return _tower_type; }
	std::string getTowerName() { return _tower_name; }
	std::string getBulletType() { return _bullet_type; }

	void killCountIncrement() { _kill_count++; }
	void killCountDeincrement() { _kill_count--; }
	void increaseTowerDamageDone(float damage) { _damage_dealt += damage; }
	void decreaseTowerDamageDone(float damage) { _damage_dealt -= damage; }

	void spawnBullet(); // Spawns Bullet
	void modifyTowerStats(Modifier mod); // Uses modifier to change base tower stats
	void createTowerType(std::string name, int type, sf::Vector2f pos, Modifier mod); // Creates tower at pos with pre-set name and type
	void lookAt(sf::Vector2f target);
	void update(sf::RenderWindow &window); // Updates tower variables
	float bulletUpdate(Enemy enemy); // Updates bullet variables and returns damage
	void draw(sf::RenderWindow &window); // Draws tower
};
