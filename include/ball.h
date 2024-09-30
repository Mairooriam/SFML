#ifndef BALL_H
#define BALL_H

#include <SFML/Graphics.hpp>

class Ball {
public:
    Ball(float radius, float x, float y);

    float getRadius() const;
    void setRadius(float radius);

    float getX() const;
    void setX(float x);

    float getY() const;
    void setY(float y);

    void move(float dx, float dy);
    void draw(sf::RenderWindow& window);

private:
    float radius;
    float x;
    float y;
};

#endif // BALL_H