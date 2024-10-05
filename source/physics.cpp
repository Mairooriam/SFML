#include "Physics.h"
#include "vectorOperators.h"
sf::Vector3f convert2fVectorTo3f(sf::Vector2f &vector)
{
    return sf::Vector3f(vector.x,vector.y, 0.0f);
}

sf::Vector3f kinematicEquation(sf::Vector3f acceleration, sf::Vector3f velocity, float deltaT, sf::Vector3f position) {
    sf::Vector3f firstpart = 0.5f * acceleration * deltaT * deltaT;
    sf::Vector3f secondpart = velocity * deltaT;
    sf::Vector3f result = firstpart + secondpart + position;
    return  result;
}
