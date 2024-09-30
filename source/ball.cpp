#include "ball.h"
Ball::Ball(float radius, float x, float y)
{
    this->radius = radius;
    this->x = x;
    this->y = y;
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(float radius)
{
    this->radius = radius;
}

float Ball::getX() const
{
    return x;
}

float Ball::getY() const
{
    return y;
}

void Ball::setY(float y)
{
    this->y = y;
}
void Ball::setX(float x)
{
    this->x = x;
}

void Ball::move(float dx, float dy)
{
    setX(dx);
    setY(dy); 
}

void Ball::draw(sf::RenderWindow &window)
{
    sf::CircleShape shape(radius);
    shape.setPosition(x, y);
    window.draw(shape);
}