#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius, const sf::Vector3f& position, const sf::Vector3f& velocity,const float mass);

    void setVelocity(const sf::Vector3f& velocity);
    sf::Vector3f getVelocity() const;
    
    void move(sf::Vector3f position);
    void draw(sf::RenderWindow& window);
    bool update(float deltaTime);

    sf::Vector3f position;
    sf::Vector3f velocity  = sf::Vector3f(0.f, 0.f, 0.f);
    const sf::Vector3f GRAVITY;
private:
    sf::CircleShape shape;
    
    
};

#endif // BALL_H