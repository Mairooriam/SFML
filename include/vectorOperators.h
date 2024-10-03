#ifndef VECTOR_OPERATORS_H
#define VECTOR_OPERATORS_H

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
#include <iostream>

// Declarations of the operators
sf::Vector3f operator+(const sf::Vector3f& lhs, const sf::Vector3f& rhs);
sf::Vector3f operator+(const sf::Vector3f& lhs, const sf::Vector2f& rhs);
sf::Vector3f operator*(const sf::Vector3f& vector, float scalar);
sf::Vector3f operator*(float scalar, const sf::Vector3f& vector);
sf::Vector3f operator*(const sf::Vector3f& lhs, const sf::Vector3f& rhs);
std::ostream& operator<<(std::ostream& os, const sf::Vector3f& vector);

#endif // VECTOR_OPERATORS_H