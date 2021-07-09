// Tower.cpp

#include "Tower.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Bullet.hpp"
#include "Vectors.hpp"
#include "Enemy.hpp"
#include "Modifier.hpp"

Tower::Tower() {};


void Tower::lookAt(sf::Vector2f target) {
	setAngleFacing(RAD_TO_DEG(std::atan2(target.y - _pos.y, target.x - _pos.x)));
}

void Tower::spawnBullet() {
	Bullet bullet;
	bullet.setPosition(_pos);
	bullet.setAngle(getAngleFacing());
	bullet.setVelocity(_velocity);
	bullet.setRadius(_bullet_radius);
	bullet.setDuration(_duration);
	bullet.setDead(false);
	bullet.setDamage(_damage);
	_bullets.push_back(bullet);
	
}

void Tower::update(sf::RenderWindow &window) {
	sf::Vector2f mouse_position = window.mapPixelToCoords(sf::Mouse::getPosition(window));

	float distance_to_mouse = std::sqrt(std::pow(_pos.x - mouse_position.x, 2) + std::pow(_pos.y - mouse_position.y, 2));
	if (distance_to_mouse <= _attack_range) {
		lookAt((sf::Vector2f)mouse_position);
		if (_attack_timer.getElapsedTime().asSeconds() >= (1 / _attack_speed)) {
			spawnBullet();
			_attack_timer.restart();
		}
	}

	int bulletSize = _bullets.size();
	for (int i = 0; i < bulletSize; i++) {
		_bullets[i].update();
		if (_bullets[i].getDead()) {
			_bullets.erase(_bullets.begin() + i);
			bulletSize--;
			i--;
		}
	}

}

float Tower::bulletUpdate(Enemy enemy) {

	float damageOutput = 0;

	for (int i = 0; i < _bullets.size(); i++) { 
		damageOutput += _bullets[i].checkCollision(enemy); 
	}

	return damageOutput;

}

void Tower::draw(sf::RenderWindow &window) {
	_range_shape.setPosition(_pos);
	_range_shape.setRadius(_attack_range);
	_range_shape.setOrigin(_attack_range, _attack_range);
	_range_shape.setFillColor(sf::Color(0xffffff30));
	_range_shape.setOutlineColor(sf::Color(0xffffff60));
	_range_shape.setOutlineThickness(2);
	window.draw(_range_shape);

	_shape.setPosition(_pos);
	_shape.setRadius(_tower_radius);
	_shape.setOrigin(_tower_radius, _tower_radius);
	_shape.setFillColor(_fill_color);
	window.draw(_shape);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = _pos;
	line[0].color = sf::Color::White;
	line[1].position.x = _pos.x + _attack_range * std::cos(DEG_TO_RAD(_angle_facing));
	line[1].position.y = _pos.y + _attack_range * std::sin(DEG_TO_RAD(_angle_facing));
	line[1].color = sf::Color::White;
	window.draw(line);

	for (Bullet &bullet : _bullets) {
		bullet.draw(window);
	}
}

void Tower::modifyTowerStats(Modifier mod) {
	if (mod.getTowerScalarMode()) {
		_duration *= mod.getTowerDuration();
		_attack_range *= mod.getTowerAttackRange();
		_attack_speed *= mod.getTowerAttackSpeed();
		_damage *= mod.getTowerDamage();
		_bullet_radius *= mod.getTowerBulletRadius();
		_velocity *= mod.getTowerVelocity();
		_tower_radius *= mod.getTowerRadius();
	}
	else {
		_duration += mod.getTowerDuration();
		_attack_range += mod.getTowerAttackRange();
		_attack_speed += mod.getTowerAttackSpeed();
		_damage += mod.getTowerDamage();
		_bullet_radius += mod.getTowerBulletRadius();
		_velocity += mod.getTowerVelocity();
		_tower_radius += mod.getTowerRadius();
	}

	if (mod.updateTowerBulletType()) {
		_bullet_type = mod.getTowerBulletType();
	}
}

void Tower::createTowerType(std::string name, int type, sf::Vector2f pos, Modifier mod) {
	_pos = pos;

	if (name.compare("Test") == 0) {
		switch (type) {
			// Case 1 is currently the same as default
		case 1: {
			_attack_range = 1200;
			_attack_speed = 1;
			_damage = 1;
			_bullet_radius = 5;
			_velocity = 10;
			_tower_radius = 25;
			_fill_color = sf::Color::Red;
			break;
		}
		default: {
			_attack_range = 1200;
			_attack_speed = 1;
			_damage = 1;
			_bullet_radius = 5;
			_velocity = 10;
			_tower_radius = 25;
			_fill_color = sf::Color::Red;
			type = 0;
			break;
		}
		}
	}
	else {
		_attack_range = 1200;
		_attack_speed = 1;
		_damage = 1;
		_bullet_radius = 5;
		_velocity = 10;
		_tower_radius = 25;
		_fill_color = sf::Color::Blue;
		type = 0;
		name = "Invalid";
	}

	_tower_name = name;
	_tower_type = type;

	_duration = _attack_range;

	modifyTowerStats(mod);

}
