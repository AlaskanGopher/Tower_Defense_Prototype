#pragma once
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#define RAD_TO_DEG(rad) ((rad * 180.0f) * (1.0f / M_PI))
#define DEG_TO_RAD(deg) ((deg * M_PI) / 180.0f)

// --- CLASS BULLET ---
// Individual Bullet, calculates position via update() function

class Bullet {
public:
	Bullet(sf::Vector2f pos, int angle, int velocity) : _bullet_pos(pos), _bullet_angle(angle), _bullet_velocity(velocity) {
		_bullet_sprite.setRadius(10.f);
		_bullet_sprite.setFillColor(sf::Color::Green);
	}

	void update() {
		_bullet_pos.x += _bullet_velocity * std::cos(DEG_TO_RAD(_bullet_angle));
		_bullet_pos.y += _bullet_velocity * std::sin(DEG_TO_RAD(_bullet_angle));
		_bullet_sprite.setPosition(_bullet_pos);
	}

	// Set Functions
	void setPos(sf::Vector2f pos) { _bullet_pos = pos; }
	void setAngle(int angle) { _bullet_angle = angle; }
	void setVelocity(int velocity) { _bullet_velocity = velocity; }

	// Get Functions
	sf::CircleShape getSprite() { return _bullet_sprite; }
	sf::Vector2f getPos() { return _bullet_pos; }
	int getAngle() { return _bullet_angle; }
	int getVelocity() { return _bullet_velocity; }


private:
	sf::CircleShape _bullet_sprite;
	sf::Vector2f _bullet_pos;
	int _bullet_angle;
	int _bullet_velocity;
};

class Tower {
public:
	Tower() {
		tower_initalize();
	};
	Tower(float damage) : _damage(damage) {
		tower_initalize();
	};
	Tower(float damage, float attack_speed) : _damage(damage), _attack_speed(attack_speed) {
		tower_initalize();
	};
	Tower(float damage, float attack_speed, float attack_range) : _damage(damage), _attack_speed(attack_speed), _attack_range(attack_range) {
		tower_initalize();
	};

	void draw(sf::RenderWindow & window)
	{
		update(window);
		for(int i = 0; i < _bullets.size(); i++)
		{
			_bullets[i].update();
			window.draw(_bullets[i].getSprite());
		}
		window.draw(_tower);
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

protected:
	void update(sf::RenderWindow & window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition();
		if (_attack_range >= std::sqrt(pow(mousePosition.x - (_tower.getPosition().x + (_tower.getRadius() / 2)), 2) + pow(mousePosition.y - (_tower.getPosition().y + (_tower.getRadius() / 2)), 2))) {
			if (_attack_timer.getElapsedTime().asSeconds() >= 1)
			{
				_bullets.push_back(Bullet(_tower.getPosition(), _tower.getRotation(), 1));
				_attack_timer.restart();
			}
		}
		else
		{
			_attack_timer.restart();
		}
	}
protected:
	void tower_initalize() {
		_tower.setRadius(100);
		_tower.setPosition(100, 100);
		_tower.setFillColor(sf::Color::Red);
	}

private:
	// Modifable
	float _damage = 1; // Damage per Projectile
	float _attack_speed = 1; // Shots per Second
	float _attack_range = 100; // Range of which the tower can shoot

	// internal
	sf::CircleShape _tower;
	std::vector<Bullet> _bullets;
	sf::Clock _attack_timer;
};


