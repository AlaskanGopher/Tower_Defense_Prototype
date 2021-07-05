// Vectors.hpp

#pragma once

#include <SFML/System.hpp>

#define _USE_MATH_DEFINES
#include <math.h>

#define RAD_TO_DEG(rad) ((rad * 180.0f) * (1.0f / M_PI))
#define DEG_TO_RAD(deg) ((deg * M_PI) / 180.0f)

/** compute a vector from an angle (degrees) and magnitude */
static inline sf::Vector2f vector_from_angle_and_magnitude(float angle, float magnitude) {
	return sf::Vector2f(magnitude * std::cos(DEG_TO_RAD(angle)), magnitude * std::sin(DEG_TO_RAD(angle)));
}

/** compute the angle (degrees) of a vector */
static inline float vector_angle(sf::Vector2f v) {
	return RAD_TO_DEG(std::atan2(v.y, v.x));
}

/** compute the magnitude of a vector */
static inline float vector_magnitude(sf::Vector2f v) {
	return std::sqrt((v.x * v.x) + (v.y * v.y));
}

/** compute the unit vector of a vector */
static inline sf::Vector2f vector_unit(sf::Vector2f v) {
	// dividing float zero by zero returns nan
	float mag = vector_magnitude(v);
	return mag == 0.0f ? sf::Vector2f(0.0f, 0.0f) : v / mag;
}
