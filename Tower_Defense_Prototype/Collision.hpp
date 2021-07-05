// Collision.hpp

#pragma once

#include <SFML/System.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#include "Vectors.hpp"

/** Check if the radius of two objects are colliding */
static inline bool collidingWithRadius(sf::Vector2f pos1, sf::Vector2f pos2, float radii1, float radii2) {
	sf::Vector2f vectorBetweenBulletAndEnemy(pos1.x - pos2.x, pos1.y - pos2.y);
	return (vector_magnitude(vectorBetweenBulletAndEnemy) < radii1 + radii2);
}

/** Check if an object is colliding with boundries */
/** Notation <boolean if colliding with any, boolean for top, boolean for right, boolean for bottom, boolean for left>*/
static inline std::vector<bool> collidingWithBoundries(sf::Vector2f pos, float boundryAdjustment) {
	float yTop = 0.0 + boundryAdjustment;
	float yBottom = 720.0 + boundryAdjustment;
	float xleft = 0.0 + boundryAdjustment;
	float xRight = 1280.0 + boundryAdjustment;

	std::vector<bool> collisionChecks;
	collisionChecks.push_back(false);

	if (pos.y <= yTop) {
		collisionChecks[0] = true;
		collisionChecks.push_back(true);
	}
	else { collisionChecks.push_back(false); }

	if (pos.x >= xRight) {
		collisionChecks[0] = true;
		collisionChecks.push_back(true);
	}
	else { collisionChecks.push_back(false); }

	if (pos.y >= yBottom) {
		collisionChecks[0] = true;
		collisionChecks.push_back(true);
	}
	else { collisionChecks.push_back(false); }

	if (pos.x <= xleft) {
		collisionChecks[0] = true;
		collisionChecks.push_back(true);
	}
	else { collisionChecks.push_back(false); }

	return collisionChecks;
}