#include "Ball.h"
#include "physics.h"
#include <iostream>
#include "vectorOperators.h"
Ball::Ball(float radius, const sf::Vector3f& position, const sf::Vector3f& velocity)
    : velocity(velocity), GRAVITY(0.f, 9.81f, 0.f), position(position){
    shape.setRadius(radius);
    shape.setPosition(position.x, position.y);
    shape.setFillColor(sf::Color::Green);
}

void Ball::setVelocity(const sf::Vector3f& velocity) {
    this->velocity = velocity;
}

sf::Vector3f Ball::getVelocity() const {
    return this->velocity;
}

void Ball::move(sf::Vector3f position) {
    shape.move(position.x, position.y);
}

void Ball::draw(sf::RenderWindow& window) {
    window.draw(shape);
}

bool Ball::update(float deltaTime) {


    position = kinematicEquation(GRAVITY, velocity, deltaTime, position);
    std::cout << "Vector " << position << std::endl;
    std::cout << "velocity" << velocity<< "\n";
    
    if(position.y > 600){
        position.y = 0;
        shape.setPosition(position.x, position.y);
        return false;
    }
    shape.setPosition(position.x, position.y);
    return true;

}

