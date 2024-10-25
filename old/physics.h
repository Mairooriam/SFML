#ifndef PHYSICS_H
#define PHYSICS_H

#include <SFML/System/Vector3.hpp>
#include <SFML/System/Vector2.hpp>
sf::Vector3f kinematicEquation(sf::Vector3f acceleration, sf::Vector3f velocity, float deltaT, sf::Vector3f position);
sf::Vector3f convert2fVectorTo3f(sf::Vector3f& vector);
#endif  // PHYSICS_H