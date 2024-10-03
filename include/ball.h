#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius, sf::Vector3f position, sf::Vector2f initialVelocity);

    float getRadius() const;
    void setRadius(float radius);

    sf::Vector3f getPosition() const;
    void setPosition(float x, float y,float z);
    sf::Vector2f getVelocity() const;
    void setVelocity(const sf::Vector2f& velocity);

    void move(float dx, float dy);
    void draw(sf::RenderWindow& window);


private:
    sf::Vector2f velocity;
    sf::Vector3f position;
    float radius;

};

#endif // BALL_H