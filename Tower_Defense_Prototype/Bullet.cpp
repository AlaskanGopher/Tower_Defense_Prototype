// Bullet.cpp

#include "Bullet.hpp"

#include <SFML/Graphics.hpp>
#include <vector>

#include "Vectors.hpp"

Bullet::Bullet() {};

void Bullet::update() {
	_pos.x += _velocity * std::cos(DEG_TO_RAD(this->_angle));
	_pos.y += _velocity * std::sin(DEG_TO_RAD(this->_angle));
}

void Bullet::draw(sf::RenderWindow &window) {
	_shape.setPosition(_pos);
	_shape.setRadius(5);
	_shape.setOrigin(5, 5);
	_shape.setFillColor(sf::Color::Green);
	window.draw(_shape);

	sf::VertexArray line(sf::Lines, 2);
	line[0].position = _pos;
	line[0].color = sf::Color::Yellow;
	line[1].position.x = _pos.x + 25 * std::cos(DEG_TO_RAD(_angle));
	line[1].position.y = _pos.y + 25 * std::sin(DEG_TO_RAD(_angle));
	line[1].color = sf::Color::Yellow;
	window.draw(line);
}
