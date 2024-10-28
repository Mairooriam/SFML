#ifndef OPERATOR_UTILS_HPP
#define OPERATOR_UTILS_HPP

#include <SFML/System/Vector2.hpp>
#include <iostream>

// Overload the << operator for sf::Vector2f
inline std::ostream& operator<<(std::ostream& os, const sf::Vector2f& vec) {
    os << "(" << vec.x << ", " << vec.y << ")";
    return os;
}

// Custom hash function for sf::Vector2f
struct Vector2fHash {
    std::size_t operator()(const sf::Vector2f& vec) const {
        std::hash<float> hasher;
        return hasher(vec.x) ^ (hasher(vec.y) << 1);
    }
};

// Specialize std::hash for sf::Vector2f
namespace std {
    template <>
    struct hash<sf::Vector2f> {
        std::size_t operator()(const sf::Vector2f& vec) const {
            return Vector2fHash{}(vec);
        }
    };
}
#endif // OPERATOR_UTILS_HPP