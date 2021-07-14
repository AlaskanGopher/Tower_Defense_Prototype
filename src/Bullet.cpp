// Bullet.cpp

#include "Bullet.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Vectors.hpp"
#include "Enemy.hpp"
#include "Collision.hpp"

Bullet::Bullet() {};

void Bullet::update() {
	_pos.x += _velocity * std::cos(DEG_TO_RAD(this->_angle));
	_pos.y += _velocity * std::sin(DEG_TO_RAD(this->_angle));
	_duration -= _velocity;
	if (_duration <= 0) {
		_dead = true;
	}
}

float Bullet::checkCollision(Enemy enemy) {	
	float damageOutput = 0;
	if (collidingWithRadius(_pos, enemy.getPosition(), _radius, enemy.getInstanceRadius())) {
		damageOutput++;
		_dead = true;
	}
	return damageOutput * _damage;
}

void Bullet::draw(sf::RenderWindow &window) {
	_shape.setPosition(_pos);
	_shape.setRadius(_radius);
	_shape.setOrigin(_radius, _radius);
	_shape.setFillColor(sf::Color::Green);
	window.draw(_shape);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = _pos;
	line[0].color = sf::Color::Yellow;
	line[1].position.x = _pos.x + _radius * 5.0 * std::cos(DEG_TO_RAD(_angle));
	line[1].position.y = _pos.y + _radius * 5.0 * std::sin(DEG_TO_RAD(_angle));
	line[1].color = sf::Color::Yellow;
	window.draw(line);
}
