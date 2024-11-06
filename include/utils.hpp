// VectorUtils.hpp
#ifndef UTILS_HPP
#define UTILS_HPP
#include <SFML/System/Vector2.hpp>


namespace Utils {
    // Function to calculate the distance between two sf::Vector2f points
    float getDistanceVector2F(const sf::Vector2f& point1, const sf::Vector2f& point2);
}
#endif // _UTILS_HPP