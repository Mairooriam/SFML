// VectorUtils.cpp
#include "utils.hpp"
#include <cmath>

namespace Utils {
    // Function to calculate the distance between two sf::Vector2f points
    float getDistanceVector2F(const sf::Vector2f& a, const sf::Vector2f& b) {
        float dx = a.x - b.x;
        float dy = a.y - b.y;
        return std::sqrt(dx * dx + dy * dy);
    }
}