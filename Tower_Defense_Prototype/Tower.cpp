// Tower.cpp

#include "Tower.hpp"

#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <vector>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Bullet.hpp"
#include "Vectors.hpp"

Tower::Tower() {};

void Tower::lookAt(sf::Vector2f target) {
	setAngleFacing(RAD_TO_DEG(std::atan2(target.y - _pos.y, target.x - _pos.x)));
}

void Tower::spawnBullet() {
	Bullet bullet;
	bullet.setPosition(_pos);
	bullet.setAngle(getAngleFacing());
	bullet.setVelocity(4);
	_bullets.push_back(bullet);
}

void Tower::update(sf::Window &window) {
	sf::Vector2i mouse_position = sf::Mouse::getPosition(window);

	float distance_to_mouse = std::sqrt(std::pow(_pos.x - mouse_position.x, 2) + std::pow(_pos.y - mouse_position.y, 2));
	if (distance_to_mouse <= _attack_range) {
		lookAt((sf::Vector2f)mouse_position);
		if (_attack_timer.getElapsedTime().asSeconds() >= (1 / _attack_speed)) {
			spawnBullet();
			_attack_timer.restart();
		}
	}

	for (Bullet &bullet : _bullets) {
		bullet.update();
	}
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
	_shape.setRadius(25);
	_shape.setOrigin(25, 25);
	_shape.setFillColor(sf::Color::Red);
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
};
