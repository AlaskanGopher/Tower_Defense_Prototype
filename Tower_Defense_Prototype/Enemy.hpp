// Enemy.hpp

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Modifier.hpp"

class Enemy {
private:
	std::vector<sf::Color> _appearance; // Appearance Vector
	std::vector<std::string> _enemy_name; // Name stored as a vector of strings
	std::vector<float> _health; // Health Vector; corresponds to the health{s} of specific appearance(s)
	std::vector<float> _instance_health; // Instance health vector stored as <Instance health, total health, max health>
	std::vector<float> _radius; // Radius Vector; corresponds to the size(s) of specific appearance(s)
	std::vector<int> _enemy_type; // Type stored as a vector of strings

	sf::Vector2f _pos; // Origin position of enemy
	sf::Color _current_color = sf::Color::Blue; // Color for a given appearance; updates from _appearance by removing the beginning value

	bool _dead = true; // Boolean for if enemy is dead
	bool _initialized = false; // Checks if start up declarations for Enemy are complete
	bool _invalid_enemy = false; // Checks if enemy was properly set up
	bool _first_loop = true; // Used in creating the enemy to do specific methods prior to recursion

	sf::CircleShape _shape;



public:
	Enemy();

	// Set Methods
	void setAppearanceVector(std::vector<sf::Color> appearance) { _appearance = appearance; }
	void setEnemyName(std::vector<std::string> name) { _enemy_name = name; }
	void setHealthVector(std::vector<float> health) { _health = health; }
	void setInstanceHealthVector(std::vector<float> health) { _instance_health = health; }
	void setRadiusVector(std::vector<float> size) { _radius = size; }
	void setEnemyTypeVector(std::vector<int> type) { _enemy_type = type; }

	void setPositionVector(sf::Vector2f pos) { _pos = pos; }
	void setCurrentColor(sf::Color color) { _current_color = color; }

	void setDead(bool dead) { _dead = dead; }
	void setCanModify(bool tf) { _invalid_enemy = !tf; } // Purely for overwriting invalid case

	void setInstanceRadius(float size, int i) { _radius[i] = size; }
	void setInstanceEnemyType(int type, int i) { _enemy_type[i] = type; }
	void setInstanceEnemyName(std::string name, int i) { _enemy_name[i] = name; }

	// Get Methods
	std::vector<sf::Color> getAppearanceVector() { return _appearance; }
	std::vector<std::string> getEnemyNameVector() { return _enemy_name; }
	std::vector<float> getHealthVector() { return _health; }
	std::vector<float> getInstanceHealthVector() { return _instance_health; }
	std::vector<float> getRadiusVector() { return _radius; }
	std::vector<int> getEnemyTypeVector() { return _enemy_type; }

	sf::Vector2f getPosition() { return _pos; }
	sf::Color getCurrentColor() { return _current_color; }

	bool getDead() { return _dead; }
	bool getCanModify() { return !_invalid_enemy; }

	float getInstanceRadius(int i) { return _radius[i]; }
	float getInstanceHealth() { return _instance_health[0]; }
	float getTotalHealth() { return _instance_health[1]; }
	float getMaxHealth() { return _instance_health[2]; }
	int getInstanceEnemyType(int i) { return _enemy_type[i]; }
	std::string getInstanceEnemyName(int i) { return _enemy_name[i]; }

	// Class Methods
	void update(float damage); // Updates all enemy variables
	void enforceEnemyPreConditions(); // Enforces vector length preconditions for variables to prevenout out of bounds errors. Creates an invalid enemy if condition is not upheld
	void modifiyAllEnemyStats(Modifier mod); // Modifies the stat of every sincle appearance with a modifier
	void modifiyFirstEnemyStats(Modifier mod); // Modifies the first enemy's stats with a modifier
	void modifiyLastEnemyStats(Modifier mod); // Modifies the last enemy's stats wiht a modifier
	void createEnemyType(std::string name, int type, sf::Vector2f pos, Modifier mod); // Creates enemy based off of the name, position, type, and all appearences with modifier
	void draw(sf::RenderWindow &window); // Draws the enemy onto the screen

	void clear() {
		// CLEARING WITHOUT RECREATING ENEMY WILL CRASH PROGRAM!!! Clears all vectors except _pos and _current color. Sets booleans to default values. 
		_appearance.clear();
		_enemy_name.clear();
		_radius.clear();
		_enemy_type.clear();
		_health.clear();
		_instance_health.clear();

		while (_instance_health.size() != 3) {
			_instance_health.push_back(0.0);
		}

		_initialized = false;
		_dead = true;
		_invalid_enemy = false;
	}

};