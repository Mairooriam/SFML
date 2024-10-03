#include "ball.h"
Ball::Ball(float radius, sf::Vector3f position, sf::Vector2f initialVelocity)
{
    this-> velocity = initialVelocity;
    this->radius = radius;
    this->position = position;
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(float radius)
{
    this->radius = radius;
}

sf::Vector3f Ball::getPosition() const
{
    return this->position;
}

void Ball::setPosition(float x, float y, float z)
{
    this->position.x = x;
    this->position.y = y;
    this->position.z = z;
}

sf::Vector2f Ball::getVelocity() const
{
    return this->velocity;
}
void Ball::setVelocity(const sf::Vector2f &velocity)
{
    this->velocity = velocity;
}



void Ball::draw(sf::RenderWindow &window)
{
    sf::CircleShape shape(radius);
    shape.setPosition(position.x, position.y);
    window.draw(shape);
}