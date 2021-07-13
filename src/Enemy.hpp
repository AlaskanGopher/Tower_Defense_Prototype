// Enemy.hpp

#pragma once

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#include "Modifier.hpp"
#include "InstanceEnemy.hpp"

class Enemy {
private:
	std::vector<InstanceEnemy> _enemy_vector; // Instance enemy vector
	static const int _HEALTH_ARRAY_SIZE = 3;
	float _health[_HEALTH_ARRAY_SIZE]{ 0 }; // Health array {Instance, Total, Max}
	float _instance_radius = 5;

	sf::Vector2f _pos; // Position of enemy

	bool _dead = true; // Boolean for if enemy is dead
	bool _initialized = false; // Checks if start up declarations for Enemy are complete
	bool _invalid_enemy = false; // Checks if enemy was properly set up
	bool _first_loop = true; // Used in creating the enemy to do specific methods prior to recursion

	sf::CircleShape _shape;
	sf::Color _instance_color = sf::Color::Blue;



public:
	Enemy();

	// Set Methods
	void setEnemyVector(std::vector<InstanceEnemy> enemyVect) { _enemy_vector = enemyVect; }
	void setPosition(sf::Vector2f pos) { _pos = pos; }
	void setDead(bool dead) { _dead = dead; }
	void setCanModify(bool tf) { _invalid_enemy = !tf; } // Purely for overwriting invalid case

	// Get Methods
	std::vector<InstanceEnemy> getEnemyVector() { return _enemy_vector; }
	sf::Vector2f getPosition() { return _pos; }
	float getInstanceRadius() { return _instance_radius; }
	bool getDead() { return _dead; }
	bool getCanModify() { return !_invalid_enemy; }


	// Class Methods
	void update(float damage); // Updates all enemy variables
	void modifiyAllEnemyStats(Modifier mod); // Modifies the stat of every sincle appearance with a modifier
	void modifiyInstanceEnemyStats(Modifier mod, int i); // Modifies the stats of the enemy at the ith position of the enemy vector
	void createEnemyType(std::string enemyName, int type, sf::Vector2f pos, Modifier mod); // Creates enemy based off of the name, position, type, and all appearences with modifier
	void draw(sf::RenderWindow &window); // Draws the enemy onto the screen
	void clear();


};
