#include "vectorOperators.h"

// Overload for sf::Vector3f and sf::Vector3f
sf::Vector3f operator+(const sf::Vector3f& lhs, const sf::Vector3f& rhs) {
    return sf::Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z);
}

// Overload for sf::Vector3f and sf::Vector2f
sf::Vector3f operator+(const sf::Vector3f& lhs, const sf::Vector2f& rhs) {
    return sf::Vector3f(lhs.x + rhs.x, lhs.y + rhs.y, lhs.z);
}

// Overload the * operator to multiply sf::Vector3f by a scalar
sf::Vector3f operator*(const sf::Vector3f& vector, float scalar) {
    return sf::Vector3f(vector.x * scalar, vector.y * scalar, vector.z * scalar);
}

// Overload the * operator to multiply a scalar by sf::Vector3f
sf::Vector3f operator*(float scalar, const sf::Vector3f& vector) {
    return vector * scalar;
}

// Overload the * operator to multiply sf::Vector3f by sf::Vector3f (element-wise)
sf::Vector3f operator*(const sf::Vector3f& lhs, const sf::Vector3f& rhs) {
    return sf::Vector3f(lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z);
}

// Overload the << operator to print sf::Vector3f
std::ostream& operator<<(std::ostream& os, const sf::Vector3f& vector) {
    os << "(" << vector.x << ", " << vector.y << ", " << vector.z << ")";
    return os;
}